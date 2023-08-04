/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#pragma once

#include "global.hh"
#include <memory>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <sstream>
#include <optional>

// General enums for VHDL constructs
enum class PortMode { Input, Output, InOut, Buffer };
std::ostream& operator<<(std::ostream& out, const PortMode& port_mode);

enum class ObjectType { Constant, Signal, Variable, File };
std::ostream& operator<<(std::ostream& out, const ObjectType& type);
std::string assignmentSymbol(ObjectType type);

enum class VhdlInnerType {
    Bit,
    BitVector,
    Boolean,
    BooleanVector,
    Integer,
    IntegerVector,
    Natural,
    Positive,
    Character,
    String,
    RealFloat,

    StdLogic, StdLogicVector,
    StdULogic, StdULogicVector,

    Unsigned, Signed,

    UFixed, SFixed,
};


struct VhdlType {
    VhdlInnerType type;
    int msb, lsb;

    VhdlType(VhdlInnerType type): type(type), msb(0), lsb(0) {}
    VhdlType(VhdlInnerType type, int msb, int lsb): type(type), msb(msb), lsb(lsb) {}
    std::string to_string() const;
};
std::ostream& operator<<(std::ostream& out, const VhdlType& type);

struct VhdlValue {
    union {
        int integer;
        double real;
        int64_t long_integer;
        bool boolean;
    } value;
    VhdlType vhdl_type;

    VhdlValue(int value): value(), vhdl_type(VhdlType(VhdlInnerType::Integer, 32, 0)) { this->value.integer = value; }
    VhdlValue(double value): value(), vhdl_type(VhdlType(VhdlInnerType::SFixed, 23, -8)) { this->value.real = value; }
    VhdlValue(int64_t value): value(), vhdl_type(VhdlType(VhdlInnerType::Integer, 64, 0)) { this->value.long_integer = value; }
    VhdlValue(VhdlType type): value(), vhdl_type(type) {
        switch (type.type) {
            case VhdlInnerType::Integer: value.integer = 0; break;

            case VhdlInnerType::RealFloat:
            case VhdlInnerType::SFixed:
            case VhdlInnerType::UFixed: value.real = 0.0; break;

            case VhdlInnerType::StdLogic:
            case VhdlInnerType::Boolean:
            case VhdlInnerType::Bit: value.boolean = false; break;
            default: {
                std::cerr << __FILE__ << ":" << __LINE__ << " ASSERT : Type does not have a default value: " << type << std::endl;
                faustassert(false);
            }
        }
    }
};
std::ostream& operator<<(std::ostream& out, const VhdlValue& value);


struct VhdlPort {
    std::string name;
    PortMode mode;
    VhdlType type;

    VhdlPort(const std::string& name, PortMode mode, VhdlType type): name(name), mode(mode), type(type) {};
};
std::ostream& operator<<(std::ostream& out, const VhdlPort& port);

/** Class allowing to store code more easily
 * Blocks are organized in a tree structure,
 */
class Vertex;

class VhdlCodeBlock : public std::ostream, public std::enable_shared_from_this<VhdlCodeBlock>
{
    class VhdlCodeBuffer: public std::stringbuf
    {
        std::stringstream _output;
        int _indent_level;

        VhdlCodeBuffer(int indent_level): _output(), _indent_level(indent_level) {}

       public:
        VhdlCodeBuffer(): _output(), _indent_level(0) {}
        ~VhdlCodeBuffer()
        {
            if (pbase() != pptr())
                indent();
        }

        virtual int sync()
        {
            indent();
            return 0;
        }
        void indent()
        {
            _output << std::string(_indent_level, '\t') << str();
            str("");
            _output.flush();
        }

        void output_buffer(std::ostream& out) const {
            out << _output.str();
        }

        void open_block() { _indent_level += 1; }
        void close_block() { _indent_level -= 1; }
    };
    VhdlCodeBuffer _buffer;

   public:
    VhdlCodeBlock(): std::ostream(&_buffer), _buffer() {}

    // Returns a pointer to the currently opened block, defaulting to self if no block
    // is currently opened
    // This is a recursive function, it follows blocks until it finds one with no opened child
    void open_block() {
        _buffer.open_block();
    }

    void close_block() {
        _buffer.close_block();
    }

    friend std::ostream& operator<<(std::ostream& out, const VhdlCodeBlock& block);
};

/**
 * The VhdlCodeContainer avoids common pitfalls like dealing with
 * indentation manually or generating redundant code
 * The three core methods that should be used let the user access blocks of code as C++ streams
 */
class VhdlCodeContainer
{
    std::string _ip_name;
    int _num_inputs;
    int _num_outputs;
    int _cycles_per_sample;

    // Core blocks that are always accessible
    VhdlCodeBlock _entities;
    VhdlCodeBlock _signals;
    VhdlCodeBlock _components;

    // Keeps track of which entities are already declared, to avoid generating the same
    // code twice
    std::map<std::string, int> _declared_entities;

    // Associates vertices of the graph to their VHDL signal identifier
    std::map<size_t, std::string> _signal_identifier;
    std::map<size_t, std::vector<std::pair<size_t, size_t>>> _mappings;
    std::vector<size_t> _output_mappings;

    // Stores code for custom operators
    std::map<size_t, std::string> _custom_operators;

   public:
    VhdlCodeContainer(const std::string& ip_name, int num_inputs, int num_outputs, int cycles_per_sample, std::map<size_t, std::string> custom_operators):
          _ip_name(ip_name),
          _num_inputs(num_inputs),
          _num_outputs(num_outputs),
          _cycles_per_sample(cycles_per_sample),
          _custom_operators(custom_operators)
    {
        if (cycles_per_sample) {
            generateRegisterSeries(cycles_per_sample, VhdlType(VhdlInnerType::StdLogic));
        }


    }

    // Registers a new unique component, declaring its related signals and generic
    // component if necessary
    void register_component(const Vertex& component);

    // Connects two nodes with the given amount of lag i.e registers in between source and target
    void connect(const Vertex& source, const Vertex& target, int lag);

    std::string entityName(const std::string& name, VhdlType type) const;

    /**
     * COMPONENT GENERATORS
     */
    size_t generateRegisterSeries(int n, VhdlType type);
    void generateDelay(size_t hash, VhdlType type);
    void generateConstant(size_t hash, VhdlValue value);
    void generateOneSampleStorage(VhdlType type);
    void generateBinaryOperator(size_t hash, int kind, VhdlType type);

    friend std::ostream& operator<<(std::ostream& out, const VhdlCodeContainer& container);
};

//-------------------------Signal2VHDLVisitor---------------------------
// A signal visitor used to compile signals to VHDL code
//----------------------------------------------------------------------

//
//class Signal2VhdlVisitor : public SignalVisitor {
//   private:
//    int fSignalsCount = 0;
//    int fAssignedOutputs = 0;
//    std::vector<VhdlValue> fInputs;
//    std::vector<VhdlValue> fOutputs;
//    VhdlCodeContainer fOutput;
//
//    void startBlock() {
//        fOutput.startBlock();
//    }
//    void endBlock() {
//        fOutput.endBlock();
//    }
//
//
//    /** Generates code to declare a real value depending on whether float encoding is used */
//    std::string genReal(float value) const {
//        std::string as_str = std::to_string(value);
//        if (usingFloatEncoding()) {
//            return "float(" + as_str + ")";
//        } else {
//            return "sfixed(" + as_str + ")";
//        }
//    }
//
//    // Signal assignment
//    void assignSignal(const std::string& signal_name, const std::string& port_name) {
//        // fPortSignalAssignments[port_name] = signal_name;
//    }
//
//    /**
//     * Dependencies declaration
//     */
//    void genDependencies()
//    {
//        fOutput
//            << "library ieee;" << std::endl
//            << "use ieee.std_logic_1164.all;" << std::endl
//            << "use ieee.numeric_std.all;" << std::endl
//            << "use ieee.std_logic_arith.all;" << std::endl
//            << "use ieee.std_logic_signed.all;" << std::endl
//            << "use work.fixed_float_types.all;" << std::endl;
//
//        // Include the right package for real numbers encoding
//        if (usingFloatEncoding()) {
//            fOutput << "use work.float_pkg.all;" << std::endl;
//        } else {
//            fOutput << "use work.fixed_pkg.all;" << std::endl;
//        }
//    }
//
//    /**
//     * Blocks declaration
//     * TODO: The best would be to use CodeContainer, but it seems too tied with FIR
//     * TODO: A variant of said container might need to be created, allows more control over code generation
//     */
//    // Entities
//    void startEntity(const std::string& name)
//    {
//        fOutput << "entity " << name << " is" << std::endl;
//        startBlock();
//    }
//    void endEntity(const std::string& name)
//    {
//        endBlock();
//        fOutput << "end " << name << ";" << std::endl;
//    }
//
//    // Architecture
//    void startArchitecture(const std::string& name, const std::string& target) {
//        fOutput << "architecture " << name << " of " << target << " is" << std::endl;
//        startBlock();
//    }
//    void endArchitecture(const std::string& name) {
//        endBlock();
//        fOutput << "end architecture " << name << ";" << std::endl;
//    }
//
//    // Processes
//    // TODO: Add support for variables and constant declarations
//    void startProcess(std::initializer_list<std::string> args) {
//        fOutput << "begin process(";
//        for (auto arg_name = args.begin(); arg_name != args.end() - 1; ++arg_name) {
//            fOutput << *arg_name << ", ";
//        }
//        fOutput << *(args.end() - 1) << ")" << std::endl << "begin" << std::endl;
//        startBlock();
//    }
//    void endProcess() {
//        endBlock();
//        fOutput << "end process;" << std::endl;
//    }
//    void genFaustProcess(Tree signal) {
//        // First part is the reset input
//        fOutput << "if (ap_rst_n = '0') then" << std::endl;
//        startBlock();
//        for (auto output_port : fOutputs) {
//            fOutput << output_port.resetStatement() << std::endl;
//        }
//        endBlock();
//
//        // Main faust process
//        fOutput << "elsif (ap_clk'event and ap_clk = '1') then" << std::endl;
//        startBlock();
//        fOutput << "if (ap_start = '1') then" << std::endl;
//        startBlock();
//        visitRoot(signal);
//        fOutput << "out_left_V_ap_vld <= '1';" << std::endl;
//        fOutput << "out_right_V_ap_vld <= '1';" << std::endl;
//        fOutput << "ap_done <= '1';" << std::endl;
//        endBlock();
//        fOutput << "else" << std::endl;
//        startBlock();
//        fOutput << "out_left_V_ap_vld <= '0';" << std::endl;
//        fOutput << "out_right_V_ap_vld <= '0';" << std::endl;
//        fOutput << "ap_done <= '0';" << std::endl;
//        endBlock();
//        fOutput << "end if;" << std::endl;
//        endBlock();
//        fOutput << "end if;" << std::endl;
//    }
//
//    // Ports
//    void genPortsBlock(std::initializer_list<VhdlPort> ports)
//    {
//        fOutput << "port (" << std::endl;
//        startBlock();
//        for (auto port = ports.begin(); port != ports.end() - 1; ++port) {
//            registerPort(port);
//            fOutput << port->name << ": " << port->mode << ' ' << port->type << ';' << std::endl;
//        }
//        auto final_port = ports.end() - 1;
//        registerPort(final_port);
//        fOutput << final_port->name << ": " << final_port->mode << ' ' << final_port->type << std::endl;
//        endBlock();
//        fOutput << ");" << std::endl;
//    }
//    void registerPort(const VhdlPort* port)
//    {
//        // TODO: Deal with other port types
//        auto vhdl_object = VhdlValue(ObjectType::Signal, port->name, port->type);
//        switch (port->mode) {
//            case PortMode::Input: fInputs.push_back(vhdl_object); break;
//            case PortMode::Output: fOutputs.push_back(vhdl_object); break;
//            default: break;
//        }
//    }
//    std::string nextUnassignedOutput() {
//        return fOutputs[fAssignedOutputs++].name;
//    }
//
//    // Generics
//    void startGenericsBlock()
//    {
//
//    }
//    void endGenericsBlock()
//    {
//
//    }
//    void genGeneric(const std::string& name, VhdlType type, int value)
//    {
//
//    }
//
//    /**
//     * VHDL Objects
//     */
//    void genSignal(VhdlType type) {
//        genSignal("sig" + std::to_string(fSignalsCount++), type);
//    }
//    void genSignal(const std::string& name, VhdlType type) {
//        fOutput << "signal " << name << ": " << type << ";" << std::endl;
//    }
//    void genSignal(const std::string& name, VhdlType type, int default_value) {
//        fOutput << "signal " << name << ": " << type << " := " << default_value << ";" << std::endl;
//    }
//
//    void genConstant(const std::string& name, VhdlType type, int value) {
//        fOutput << "constant " << name << ": " << type << " := " << value << ';' << std::endl;
//    }
//
//    void genVariable() {} // TODO: Very similar to signal in declaration
//
//    /**
//     * General helper functions for code generation
//     */
//     /*
//     void genRange(int sig_nature) {
//         fOutput << "(" << getTypeMSB(sig_nature) << " downto " << getTypeLSB(sig_nature) << ")";
//     }
//     void genTypeSuffix(int sig_nature) {
//         fOutput << '_';
//         if (sig_nature == kReal && usingFloatEncoding()) {
//             fOutput << "float";
//         } else if (sig_nature == kReal) {
//             fOutput << "sfixed";
//         } else {
//             fOutput << "int";
//         }
//     }
//      */
//
//   protected:
//    void visit(Tree signal) override {
//        // TODO: Debug printing
//        std::cout << "compiling: " << *signal << std::endl;
//
//        // TODO: Feels a bit hacky to work with... This alone could justify an IR
//        int integer_value, op_kind;
//        int64_t long_value;
//        double real_value;
//        Tree    size, gen, wi, ws, tbl, ri, c, sel, x, y, z, u, v, var, le, label, ff, largs, type, name, file, sf;
//
//        // Primitive types
//        // TODO: Those are terminal. Use `genSignal` to declare those
//        if (isSigInt(signal, &integer_value)) {
//            fOutput << integer_value;
//        } else if (isSigReal(signal, &real_value)) {
//            fOutput << genReal(real_value);
//        } else if (isSigInt64(signal, &long_value)) {
//            fOutput << long_value;
//        } else if (isSigWaveform(signal)) {
//            // TODO: Create a completely separated component whose job is to return waveform values
//        }
//
//        // User data
//        else if (getUserData(signal)) {
//
//        }
//
//        // Input/Output
//        // TODO: Affect signal to the given input/output
//        else if (isSigInput(signal, &integer_value)) {
//            fOutput << nextUnassignedOutput() << " <= " << fInputs[integer_value].name << ";" << std::endl;
//        } else if (isSigOutput(signal, &integer_value, x)) {
//            // NOTE: Previous implementer says this is never reached
//            // TODO: Check with Stéphane whether or not this is true
//        }
//
//        // Delays
//        else if (isSigDelay(signal, x, y)) {
//            self(x);
//            self(y);
//        } else if (isSigDelay1(signal, x)) {
//            self(x);
//        } else if (isSigPrefix(signal, x, y)) {
//            self(x);
//            self(y);
//        }
//
//        // Operators
//        else if (isSigBinOp(signal, &op_kind, x, y)) {
//            const std::string BINARY_OPERATORS_TABLE[] = {"+", "-",  "*",  "/", "MOD", "SLL", "SRA", "SRL", ">",
//                                                     "<", ">=", "<=", "=", "/=",  "AND", "OR",  "XOR"};
//            self(x);
//            fOutput << " " << BINARY_OPERATORS_TABLE[op_kind] << " ";
//            self(y);
//            fOutput << ";" << std::endl;
//        }
//
//        // Foreign functions
//        else if (isSigFFun(signal, ff, largs)) {
//
//        } else if (isSigFConst(signal, type, name, file)) {
//
//        } else if (isSigFVar(signal, type, name, file)) {
//
//        }
//
//        // Tables
//        else if (isSigWRTbl(signal, size, gen, wi, ws)) {
//
//        } else if (isSigRDTbl(signal, tbl, ri)) {
//
//        } else if (isSigGen(signal, x)) {
//
//        }
//
//        // Recursion
//        else if (isProj(signal, &integer_value, x)) {
//            self(x);
//        } else if (isRec(signal, var, le)) {
//
//        }
//
//        // Casts
//        else if (isSigIntCast(signal, x)) {
//
//        } else if (isSigBitCast(signal, x)) {
//
//        } else if (isSigFloatCast(signal, x)) {
//
//        }
//
//        // TODO: UI, controls, soundfiles, selects, doc...
//        // All of those fall under AXI and are not necessary to compile a working example
//
//        else if (isNil(signal)) {
//            // NOTE: This can apparently just happen in tables, and is not an error
//            std::cerr << "Found NIL signal" << std::endl;
//        } else {
//            std::cerr << __FILE__ << ":" << __LINE__ << " ASSERT: unrecognized signal : " << *signal << std::endl;
//            faustassert(false);
//        }
//    };
//
//   public:
//    Signal2VhdlVisitor(Tree signal, const std::string& name, int numInputs, int numOutputs, std::ostream& out)
//    : SignalVisitor(), fOutput(out)
//    {
//         // We first generate the header containing required dependencies
//         // TODO: Some of those may not always be needed, maybe include them only if necessary
//         genDependencies();
//
//         // Generate the main entity and its architecture
//         startEntity(name);
//         genPortsBlock({
//             VhdlPort("in_left_V", PortMode::Input, VhdlType(VhdlInnerType::StdLogicVector, 23, 0)),
//             VhdlPort("in_right_V", PortMode::Input, VhdlType(VhdlInnerType::StdLogicVector, 23, 0)),
//             VhdlPort("ws", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)),
//             VhdlPort("ap_rst_n", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)),
//             VhdlPort("ap_clk", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)),
//             VhdlPort("ap_start", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)),
//             VhdlPort("bypass_dsp", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)),
//             VhdlPort("bypass_faust", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)),
//
//             VhdlPort("out_left_V", PortMode::Output, VhdlType(VhdlInnerType::StdLogicVector, 23, 0)),
//             VhdlPort("out_right_V", PortMode::Output, VhdlType(VhdlInnerType::StdLogicVector, 23, 0)),
//             VhdlPort("ap_done", PortMode::Output, VhdlType(VhdlInnerType::StdLogic)),
//             VhdlPort("out_left_V_ap_vld", PortMode::Output, VhdlType(VhdlInnerType::StdLogic)),
//             VhdlPort("out_right_V_ap_vld", PortMode::Output, VhdlType(VhdlInnerType::StdLogic)),
//         });
//         endEntity(name);
//
//         startArchitecture("logic", name);
//
//         // Process part of the application
//         startProcess({ "ap_clk", "ap_rst_n", "ap_start" });
//         genFaustProcess(signal);
//         endProcess();
//
//         // TODO: Setup inputs and port mapping
//         endArchitecture("logic");
//    }
//};