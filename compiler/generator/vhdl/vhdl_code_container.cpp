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

#include "vhdl_code_container.hh"
#include "vhdl_producer.hh"
#include "binop.hh"

std::ostream& operator<<(std::ostream& out, const VhdlCodeBlock& block) {
    block._buffer.output_buffer(out);
    return out;
}

std::ostream& operator<<(std::ostream& out, const VhdlCodeContainer& container) {
    out << "-- ======= DEPENDENCIES =====" << std::endl;
    out << "library ieee;" << std::endl
        << "use ieee.std_logic_1164.all;" << std::endl
        << "use ieee.numeric_std.all;" << std::endl
        << "use ieee.std_logic_arith.all;" << std::endl
        << "use ieee.std_logic_signed.all;" << std::endl
        << "use work.fixed_float_types.all;" << std::endl;

    // Include the right package for real numbers encoding
    if (gGlobal->gVHDLFloatEncoding) {
        out << "use work.float_pkg.all;" << std::endl;
    } else {
        out << "use work.fixed_pkg.all;" << std::endl;
    }

    out << std::endl << "-- ======= ENTITIES =========" << std::endl;
    out << container._entities << std::endl;

    out << std::endl << "-- ======= FAUST IP =========" << std::endl;
    out << "entity " << container._ip_name << " is" << std::endl
        << "port (" << std::endl
        << '\t' << VhdlPort("ws", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)) << ";" << std::endl
        << '\t' << VhdlPort("ap_clk", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)) << ";" << std::endl
        << '\t' << VhdlPort("ap_rst_n", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)) << ";" << std::endl
        << '\t' << VhdlPort("ap_start", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)) << ";" << std::endl
        << '\t' << VhdlPort("bypass_dsp", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)) << ";" << std::endl
        << '\t' << VhdlPort("bypass_faust", PortMode::Input, VhdlType(VhdlInnerType::StdLogic)) << ";" << std::endl
        << '\t' << VhdlPort("ap_done", PortMode::Output, VhdlType(VhdlInnerType::StdLogic)) << ";" << std::endl;

    for (auto input = 0; input < container._num_inputs; ++input) {
        out << '\t' << VhdlPort("audio_in_" + std::to_string(input), PortMode::Input, VhdlType(VhdlInnerType::StdLogicVector, 23, 0)) << (input == container._num_inputs - 1 && container._num_outputs == 0 ? "" : ";") << std::endl;
    }
    for (auto output = 0; output < container._num_outputs; ++output) {
        out << '\t' << VhdlPort("audio_out_" + std::to_string(output), PortMode::Output, VhdlType(VhdlInnerType::StdLogicVector, 23, 0)) << ";" << std::endl;
        out << '\t' << VhdlPort("audio_out_ap_vld_" + std::to_string(output), PortMode::Output, VhdlType(VhdlInnerType::StdLogic)) << (output == container._num_outputs - 1 ? "" : ";") << std::endl;
    }

    out << ");" << std::endl << "end " << container._ip_name << ";" << std::endl;

    out << "architecture DSP of "<< container._ip_name << " is" << std::endl;
    out << "begin" << std::endl;
    out << std::endl << "-- ======= SIGNALS ==========" << std::endl;
    out << container._signals << std::endl;
    out << std::endl << "-- ======= COMPONENTS =======" << std::endl;
    out << container._components << std::endl;

    out << std::endl << "-- ======= PORT MAPPINGS ====" << std::endl;
    for (auto mapping : container._mappings) {
        // Components that do not depend on anything are constants
        if (mapping.second.empty()) {
            continue;
        }

        auto target_hash = mapping.first;
        auto target_id = container._signal_identifier.at(target_hash);
        out << target_id << " : " << /* type << */ "(" << std::endl;
        out << '\t' << "port map (" << std::endl;
        out << "\t\t" << "clock => ap_clk," << std::endl;
        out << "\t\t" << "reset => ap_rst_n," << std::endl;
        for (size_t i = 0; i < mapping.second.size(); ++i) {
            auto source_hash = mapping.second[i].first;
            auto registers_id = mapping.second[i].second;

            if (registers_id) {
                out << "\t\t" << "data_in_" << i << " => " << "registers_" << registers_id << "," << std::endl;
            } else {
                out << "\t\t" << "data_in_" << i << " => " << container._signal_identifier.at(source_hash) << "," << std::endl;
            }
        }
        out << "\t\t" << "data_out => " << target_id << std::endl;
        out << "\t" << ");" << std::endl << std::endl;
    }

    for (size_t output = 0; output < container._output_mappings.size(); ++output) {
        auto source_hash = container._output_mappings[output];
        auto source_id = container._signal_identifier.at(source_hash);

        out << "audio_out_" << output << " <= " << source_id << ";" << std::endl;
    }
    std::cout << std::endl;

    // "registers_0" is reserved for the series of registers responsible for
    // delaying the "ap_start" signal received from the I2S
    if (container._cycles_per_sample > 1) {
        out << "registers_0: RegisterSeries (" << std::endl;
        out << '\t' << "generic map (n => " << container._cycles_per_sample << ")" << std::endl;
        out << '\t' << "port map (" << std::endl;
        out << "\t\t" << "clock => ap_clk," << std::endl;
        out << "\t\t" << "reset => ap_rst_n," << std::endl;
        out << "\t\t" << "data_in => ap_start," << std::endl;
        out << "\t\t" << "data_out => registers_0" << std::endl;
        out << '\t' << ");" << std::endl << std::endl;

        out << "ap_done <= registers_0;" << std::endl;
        for (auto output = 0; output < container._num_outputs; ++output) {
            out << "audio_out_ap_vld_" << output << " <= registers_0;" << std::endl;
        }
    } else {
        out << "ap_done <= ap_start;" << std::endl;
        for (auto output = 0; output < container._num_outputs; ++output) {
            out << "audio_out_ap_vld_" << output << " <= ap_start;" << std::endl;
        }
    }

    out << std::endl << "end DSP;";

    return out;
}

void VhdlCodeContainer::register_component(const Vertex& component)
{
    if (!component.is_output()) {
        _mappings.insert({ component.node_hash, {} });
    }

    Tree sig = component.signal;
    int     i;
    int64_t i64;
    double  r;
    Tree    size, gen, wi, ws, tbl, ri, c, sel, x, y, z, u, v, var, le, label, ff, largs, type, name, file, sf;

    // TODO: implement missing operators
    if (getUserData(sig)) {
        std::cout << *sig << std::endl;
        for (Tree b : sig->branches()) {
        }
    } else if (isSigInt(sig, &i)) {
        generateConstant(component.node_hash, VhdlValue(i));
    } else if (isSigInt64(sig, &i64)) {
        generateConstant(component.node_hash, VhdlValue(i64));
    } else if (isSigReal(sig, &r)) {
        generateConstant(component.node_hash, VhdlValue(r));
    } else if (isSigWaveform(sig)) {
    } else if (isSigInput(sig, &i)) {
        // For inputs, we simply need to map the hash of the vertex to the correct identifier
        _signal_identifier.insert({component.node_hash, std::string("audio_in_") + std::to_string(i)});
    } else if (isSigOutput(sig, &i, x)) {
        // Outputs do not generate anything
    } else if (isSigDelay1(sig, x)) {
        generateDelay(component.node_hash, VhdlType(VhdlInnerType::SFixed, 23, -8));
    } else if (isSigDelay(sig, x, y)) {
        generateDelay(component.node_hash, VhdlType(VhdlInnerType::SFixed, 23, -8));
    } else if (isSigPrefix(sig, x, y)) {
    } else if (isSigBinOp(sig, &i, x, y)) {
        generateBinaryOperator(component.node_hash, i, VhdlType(VhdlInnerType::SFixed, 23, -8));
    }

    // Foreign functions
    else if (isSigFFun(sig, ff, largs)) {
    } else if (isSigFConst(sig, type, name, file)) {
    } else if (isSigFVar(sig, type, name, file)) {
    }

    // Tables
    else if (isSigWRTbl(sig, size, gen, wi, ws)) {
    } else if (isSigRDTbl(sig, tbl, ri)) {
    }

    // Doc
    else if (isSigDocConstantTbl(sig, x, y)) {
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
    } else if (isSigDocAccessTbl(sig, x, y)) {
    }

    // Select2 (and Select3 expressed with Select2)
    else if (isSigSelect2(sig, sel, x, y)) {
    }

    // Table sigGen
    else if (isSigGen(sig, x)) {
    }

    // recursive signals
    else if (isProj(sig, &i, x)) {
    } else if (isRec(sig, var, le)) {
    }

    // Int, Bit and Float Cast
    else if (isSigIntCast(sig, x)) {
    } else if (isSigBitCast(sig, x)) {
    } else if (isSigFloatCast(sig, x)) {
    }

    // UI
    else if (isSigButton(sig, label)) {
    } else if (isSigCheckbox(sig, label)) {
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
    } else if (isSigVBargraph(sig, label, x, y, z)) {
    } else if (isSigHBargraph(sig, label, x, y, z)) {
    }

    // Soundfile length, rate, buffer
    else if (isSigSoundfile(sig, label)) {
    } else if (isSigSoundfileLength(sig, sf, x)) {
    } else if (isSigSoundfileRate(sig, sf, x)) {
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
    }

    // Attach, Enable, Control
    else if (isSigAttach(sig, x, y)) {
    } else if (isSigEnable(sig, x, y)) {
    } else if (isSigControl(sig, x, y)) {
    }

    else if (isNil(sig)) {
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << " ASSERT : unrecognized signal : " << *sig << std::endl;
        faustassert(false);
    }
}

void VhdlCodeContainer::connect(const Vertex& source, const Vertex& target, int lag)
{
    // Find the source and target identifiers
    size_t source_hash = source.node_hash;
    size_t target_hash = target.node_hash;

    // Finally, add the connection in the correct mappings table
    if (target.is_output()) {
        _output_mappings.push_back(source_hash);
    } else {
        // Create the lag component if necessary, returning the resulting id or 0
        size_t registers_id = lag ? generateRegisterSeries(lag, VhdlType(VhdlInnerType::SFixed, 23, -8)) : 0;

        _mappings.find(target_hash)->second.push_back({ source_hash, registers_id });
    }
}

std::string VhdlCodeContainer::entityName(const std::string& name, VhdlType type) const
{
    std::stringstream ss;
    ss << name << type.to_string();
    return ss.str();
}

size_t VhdlCodeContainer::generateRegisterSeries(int n, VhdlType type)
{
    std::string entity_name = entityName("RegisterSeries", type);

    int instance_identifier;
    auto entry = _declared_entities.find(entity_name);
    // If the generic entity is already declared, we do not redeclare it
    if (entry == _declared_entities.end())
    {
        _declared_entities.insert({entity_name, 0});
        _entities << "entity " << entity_name << " is" << std::endl;
        _entities.open_block();
        _entities << "generic (" << std::endl;
        _entities.open_block();
        _entities << "n: natural := " << n << std::endl;
        _entities.close_block();
        _entities << ");" << std::endl;
        _entities << "port (" << std::endl;
        _entities.open_block();
        _entities << "clock: in std_logic;" << std::endl;
        _entities << "reset: in std_logic;" << std::endl;
        _entities << "data_in: in " << type << ";" << std::endl;
        _entities << "data_out: out " << type << std::endl;
        _entities.close_block();
        _entities << ");" << std::endl;
        _entities.close_block();
        _entities << "end entity " << entity_name << ";" << std::endl;

        _entities << "architecture Behavioral of " << entity_name << " is" << std::endl;
        _entities.open_block();
        _entities << "type register_array is array(0 to n - 1) of " << type << ";" << std::endl;
        _entities << "signal registers: register_array := (others => (others => '0'));" << std::endl;
        _entities.close_block();
        _entities << "begin" << std::endl;
        _entities.open_block();
        _entities << "process (clock, reset)" << std::endl;
        _entities << "begin" << std::endl;
        _entities.open_block();
        _entities << "if reset = '1' then" << std::endl;
        _entities.open_block();
        _entities << "registers <= (others => (others => '0'));" << std::endl;
        _entities.close_block();
        _entities << "elsif rising_edge(clock) then" << std::endl;
        _entities.open_block();
        _entities << "for i in n - 1 downto 1 loop" << std::endl;
        _entities.open_block();
        _entities << "registers(i) <= registers(i - 1);" << std::endl;
        _entities.close_block();
        _entities << "end loop;" << std::endl;
        _entities << "registers(0) <= data_in;" << std::endl;
        _entities.close_block();
        _entities << "end if;" << std::endl;
        _entities.close_block();
        _entities << "end process;" << std::endl;
        _entities << "data_out <= registers(n - 1);" << std::endl;
        _entities.close_block();
        _entities << "end architecture Behavioral;" << std::endl << std::endl;

        _components << "component " << entity_name << " is" << std::endl;
        _components.open_block();
        _components << "generic (" << std::endl;
        _components.open_block();
        _components << "n: natural := " << n << std::endl;
        _components.close_block();
        _components << ");" << std::endl;
        _components << "port (" << std::endl;
        _components.open_block();
        _components << "clock: in std_logic;" << std::endl;
        _components << "reset: in std_logic;" << std::endl;
        _components << "data_in: in " << type << ";" << std::endl;
        _components << "data_out: out " << type << std::endl;
        _components.close_block();
        _components << ");" << std::endl;
        _components.close_block();
        _components << "end component " << entity_name << ";" << std::endl << std::endl;

        instance_identifier = 0;
    } else {
        entry->second += 1;
        instance_identifier = entry->second;
    }

    // Anyhow, we still instantiate a new signal
    _signals << "signal " << entity_name << "_" << instance_identifier << " : " << type << " := " << VhdlValue(type) <<  ";" << std::endl;

    return instance_identifier;
}

void VhdlCodeContainer::generateDelay(size_t hash, VhdlType type)
{
    std::string entity_name = entityName("Delay", type);

    int instance_identifier;

    auto entry = _declared_entities.find(entity_name);
    // If the generic entity is already declared, we do not redeclare it
    if (entry == _declared_entities.end()) {
        // TODO: right now, this is just a bypass entity made for basic programs to compile
        _declared_entities.insert({entity_name, 0});

        _entities << "entity " << entity_name << " is" << std::endl;
        _entities.open_block();
        _entities << "port (" << std::endl;
        _entities.open_block();
        _entities << "clock: in std_logic;" << std::endl;
        _entities << "reset: in std_logic;" << std::endl;
        _entities << "data_in_0: in " << type << ";" << std::endl;
        _entities << "data_in_1: in " << type << ";" << std::endl;
        _entities << "data_out: out " << type << std::endl;
        _entities.close_block();
        _entities << ");" << std::endl;
        _entities.close_block();
        _entities << "end entity " << entity_name << ";" << std::endl;

        _entities << "architecture Behavioral of " << entity_name << " is" << std::endl;
        _entities << "begin" << std::endl;
        _entities.open_block();
        _entities << "data_out <= data_in_0;" << std::endl;
        _entities.close_block();
        _entities << "end architecture Behavioral;" << std::endl << std::endl;

        _components << "component " << entity_name << " is" << std::endl;
        _components.open_block();
        _components << "port (" << std::endl;
        _components.open_block();
        _components << "clock: in std_logic;" << std::endl;
        _components << "reset: in std_logic;" << std::endl;
        _components << "data_in_0: in " << type << ";" << std::endl;
        _components << "data_in_1: in " << type << ";" << std::endl;
        _components << "data_out: out " << type << std::endl;
        _components.close_block();
        _components << ");" << std::endl;
        _components.close_block();
        _components << "end component " << entity_name << ";" << std::endl << std::endl;

        instance_identifier = 0;
    } else {
        entry->second += 1;
        instance_identifier = entry->second;
    }

    std::string signal_identifier = entity_name + "_" + std::to_string(instance_identifier);
    _signals << "signal " << signal_identifier << " : " << type << " := " << VhdlValue(type) << ";" << std::endl;
    _signal_identifier.insert({hash, signal_identifier});
}

void VhdlCodeContainer::generateConstant(size_t hash, VhdlValue value)
{
    int instance_identifier;
    auto entry = _declared_entities.find("Constant");
    if (entry == _declared_entities.end())
    {
        _declared_entities.insert({"Constant", 0});
        instance_identifier = 0;
    } else {
        entry->second += 1;
        instance_identifier = entry->second;
    }
    std::string signal_identifier = std::string("constant_") + std::to_string(instance_identifier);
    _signals << "signal " << signal_identifier << " : " << value.vhdl_type << " := " << value << ";" << std::endl;
    _signal_identifier.insert({hash, signal_identifier});
}

void VhdlCodeContainer::generateOneSampleStorage(VhdlType type)
{

}

void VhdlCodeContainer::generateBinaryOperator(size_t hash, int kind, VhdlType type)
{
    std::string operator_name;
    switch (kind) {
        case SOperator::kAdd: { operator_name = "Add"; break; }
        case SOperator::kSub: { operator_name = "Sub"; break; }
        case SOperator::kMul: { operator_name = "Mul"; break; }
        case SOperator::kDiv: { operator_name = "Div"; break; }
        case SOperator::kRem: { operator_name = "Rem"; break; }
        default:
            std::cerr << __FILE__ << ":" << __LINE__ << " ASSERT : Unimplemented operator : " << kind << std::endl;
            faustassert(false);
    };

    std::string entity_name = entityName(operator_name, type);

    int instance_identifier;
    auto entry = _declared_entities.find(entity_name);
    // If the generic entity is already declared, we do not redeclare it
    if (entry == _declared_entities.end())
    {
        _declared_entities.insert({entity_name, 0});
        _entities << "entity " << entity_name << " is" << std::endl;
        _entities.open_block();
        _entities << "port (" << std::endl;
        _entities.open_block();
        _entities << "clock: in std_logic;" << std::endl;
        _entities << "reset: in std_logic;" << std::endl;
        _entities << "data_in_0: in " << type << ";" << std::endl;
        _entities << "data_in_1: in " << type << ";" << std::endl;
        _entities << "data_out: out " << type << std::endl;
        _entities.close_block();
        _entities << ");" << std::endl;
        _entities.close_block();
        _entities << "end entity " << entity_name << ";" << std::endl;

        _entities << "architecture Behavioral of " << entity_name << " is" << std::endl;
        _entities << "begin" << std::endl;
        _entities.open_block();
        _entities << "data_out <= data_in_0 " << gBinOpTable[kind]->fName << " data_in_1;" << std::endl;
        _entities.close_block();
        _entities << "end architecture Behavioral;" << std::endl << std::endl;

        _components << "component " << entity_name << " is" << std::endl;
        _components.open_block();
        _components << "port (" << std::endl;
        _components.open_block();
        _components << "clock: in std_logic;" << std::endl;
        _components << "reset: in std_logic;" << std::endl;
        _components << "data_in_0: in " << type << ";" << std::endl;
        _components << "data_in_1: in " << type << ";" << std::endl;
        _components << "data_out: out " << type << std::endl;
        _components.close_block();
        _components << ");" << std::endl;
        _components.close_block();
        _components << "end component " << entity_name << ";" << std::endl << std::endl;

        instance_identifier = 0;
    } else {
        entry->second += 1;
        instance_identifier = entry->second;
    }

    std::string signal_identifier = entity_name + "_" + std::to_string(instance_identifier);
    _signals << "signal " << signal_identifier << " : " << type << " := " << VhdlValue(type) << ";" << std::endl;
    _signal_identifier.insert({hash, signal_identifier});
}

std::ostream& operator<<(std::ostream& out, const PortMode& port_mode) {
    switch (port_mode) {
        case PortMode::Input: out << "in"; break;
        case PortMode::Output: out << "out"; break;
        case PortMode::InOut: out << "inout"; break;
        case PortMode::Buffer: out << "buffer"; break;
    }
    return out;
}

std::string assignmentSymbol(ObjectType type) {
    switch (type) {
        case ObjectType::Variable: return ":=";
        case ObjectType::Signal: return "<=";
        default:
            faustassert(false);
            return "";
    }
}
std::ostream& operator<<(std::ostream& out, const ObjectType& type) {
    switch (type) {
        case ObjectType::Constant: out << "constant"; break;
        case ObjectType::Signal: out << "signal"; break;
        case ObjectType::Variable: out << "variable"; break;
        default: break;
    }
    return out;
}

std::string VhdlType::to_string() const
{
    std::stringstream s;
    switch (type) {
        case VhdlInnerType::Bit: s << "Bit"; break;
        case VhdlInnerType::BitVector: s << "BitVector"; break;
        case VhdlInnerType::Boolean: s << "Boolean"; break;
        case VhdlInnerType::BooleanVector: s << "BooleanVector"; break;
        case VhdlInnerType::Integer: s << "Integer"; break;
        case VhdlInnerType::IntegerVector: s << "IntegerVector"; break;
        case VhdlInnerType::Natural: s << "Natural"; break;
        case VhdlInnerType::Positive: s << "Positive"; break;
        case VhdlInnerType::Character: s << "Character"; break;
        case VhdlInnerType::String: s << "String"; break;
        case VhdlInnerType::RealFloat: s << "Real"; break;
        case VhdlInnerType::StdLogic: s << "Logic"; break;
        case VhdlInnerType::StdLogicVector: s << "LogicVector"; break;
        case VhdlInnerType::StdULogic: s << "ULogic"; break;
        case VhdlInnerType::StdULogicVector: s << "ULogicVector"; break;
        case VhdlInnerType::Unsigned: s << "Unsigned"; break;
        case VhdlInnerType::Signed: s << "Signed"; break;
        case VhdlInnerType::UFixed: s << "UFixed"; break;
        case VhdlInnerType::SFixed: s << "SFixed"; break;
        default: break;
    }
    if (msb != lsb) {
        s << (msb < 0 ? "m" : "") << (msb < 0 ? -msb : msb) << "_" << (lsb < 0 ? "m" : "") << (lsb < 0 ? -lsb : lsb);
    }
    return s.str();
}
std::ostream& operator<<(std::ostream& out, const VhdlType& type) {
    switch (type.type) {
        case VhdlInnerType::Bit: out << "bit"; break;
        case VhdlInnerType::BitVector: out << "bit_vector"; break;
        case VhdlInnerType::Boolean: out << "boolean"; break;
        case VhdlInnerType::BooleanVector: out << "boolean_vector"; break;
        case VhdlInnerType::Integer: out << "integer"; break;
        case VhdlInnerType::IntegerVector: out << "integer_vector"; break;
        case VhdlInnerType::Natural: out << "natural"; break;
        case VhdlInnerType::Positive: out << "positive"; break;
        case VhdlInnerType::Character: out << "character"; break;
        case VhdlInnerType::String: out << "string"; break;
        case VhdlInnerType::RealFloat: out << "real"; break;
        case VhdlInnerType::StdLogic: out << "std_logic"; break;
        case VhdlInnerType::StdLogicVector: out << "std_logic_vector"; break;
        case VhdlInnerType::StdULogic: out << "std_ulogic"; break;
        case VhdlInnerType::StdULogicVector: out << "std_ulogic_vector"; break;
        case VhdlInnerType::Unsigned: out << "unsigned"; break;
        case VhdlInnerType::Signed: out << "signed"; break;
        case VhdlInnerType::UFixed: out << "ufixed"; break;
        case VhdlInnerType::SFixed: out << "sfixed"; break;
        default: break;
    }
    if (type.msb != type.lsb) {
        out << '(' << type.msb << " downto " << type.lsb << ')';
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const VhdlPort& port)
{
   out << port.name << " : " << port.mode << " " << port.type;
   return out;
}

std::ostream& operator<<(std::ostream& out, const VhdlValue& value) {
   switch (value.vhdl_type.type) {
       case VhdlInnerType::Integer:
       case VhdlInnerType::Natural:
       case VhdlInnerType::Positive:
       case VhdlInnerType::Signed:
       case VhdlInnerType::Unsigned: out << value.value.integer; break;

       case VhdlInnerType::RealFloat: out << value.value.real; break;

       case VhdlInnerType::UFixed: out << "to_ufixed(" << value.value.real << ", " << value.vhdl_type.msb << ", " << value.vhdl_type.lsb << ")"; break;
       case VhdlInnerType::SFixed: out << "to_sfixed(" << value.value.real << ", " << value.vhdl_type.msb << ", " << value.vhdl_type.lsb << ")"; break;

       case VhdlInnerType::StdLogic: out << (value.value.boolean ? "'1'" : "'0'"); break;
       default: {
            std::cerr << __FILE__ << ":" << __LINE__ << " ASSERT : Values of type " << value.vhdl_type << " are not yet implemented" << std::endl;
            faustassert(false);
       }
   }

   return out;
}