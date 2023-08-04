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

// Forward declaration of Vertex from vhdl_producer
class Vertex;

/**
 * GENERAL ENUMS FOR VHDL CONSTRUCTS
 */
enum class PortMode { Input, Output, InOut, Buffer };
std::ostream& operator<<(std::ostream& out, const PortMode& port_mode);

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

    Any,
};

struct VhdlType {
    VhdlInnerType type;
    int msb, lsb;

    VhdlType(): type(VhdlInnerType::Any), msb(0), lsb(0) {}
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

    /** Creates a "default value" for a given VHDL type */
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

/** Handles indentation automatically, to avoid repeating '\t' everywhere which is error prone */
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

    /** Opens a new block, incrementing the indentation level */
    void open_block() {
        _buffer.open_block();
    }

    /** Closes a block, decrementing the indentation level */
    void close_block() {
        _buffer.close_block();
    }

    friend std::ostream& operator<<(std::ostream& out, const VhdlCodeBlock& block);
};

/**
 * Holds information about series of registers.
 * Note that 'source' is optional, in the absence of a value it is assumed that the register series
 * carries the 'ap_start' signal.
 */
struct RegisterSeriesInfo {
    std::string name;
    std::optional<size_t> source;
    int registers_count;
};

/**
 * Generates actual VHDL source code from the intermediate representations used in VhdlProducer.
 */
class VhdlCodeContainer
{
    // General information about the IP
    std::string _ip_name;
    size_t _num_inputs;
    size_t _num_outputs;
    size_t _cycles_per_sample;

    // Core blocks that are always accessible
    VhdlCodeBlock _entities;
    VhdlCodeBlock _signals;
    VhdlCodeBlock _components;

    // Keeps track of which entities are already declared, to avoid generating the same
    // code twice
    std::map<std::string, size_t> _declared_entities;

    // Associates vertices of the graph to their VHDL signal identifier
    std::map<size_t, std::string> _signal_identifier;
    // Maps a source node's hash to a pair of target node hash and register count along the connection
    std::map<size_t, std::vector<std::pair<size_t, size_t>>> _mappings;
    // Information about initialized register series
    std::vector<RegisterSeriesInfo> _register_series;

    // Mappings specific to outputs and/or recursive storage
    std::vector<size_t> _output_mappings;
    std::map<size_t, size_t> _one_sample_delay_mappings;

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
        // If the implementation takes more than one clock cycle to produce an output, we create a series of
        // registers to sync the 'ap_done' and validation signals.
        if (cycles_per_sample) {
            generateRegisterSeries(cycles_per_sample, VhdlType(VhdlInnerType::StdLogic));
        }
    }

    // Registers a new unique component, declaring its related signals and generic
    // component if necessary
    void register_component(const Vertex& component, std::optional<int> cycles_from_input = std::nullopt);

    // Connects two nodes with the given amount of lag i.e registers in between source and target
    void connect(const Vertex& source, const Vertex& target, int lag);

    std::string entityName(const std::string& name, VhdlType type) const;

    /**
     * COMPONENT GENERATORS
     */
    size_t generateRegisterSeries(int n, VhdlType type);
    void generateDelay(size_t hash, VhdlType type);
    void generateConstant(size_t hash, VhdlValue value);
    void generateOneSampleDelay(size_t hash, VhdlType type, int cycles_from_input);
    void generateBinaryOperator(size_t hash, int kind, VhdlType type);

    friend std::ostream& operator<<(std::ostream& out, const VhdlCodeContainer& container);
};
