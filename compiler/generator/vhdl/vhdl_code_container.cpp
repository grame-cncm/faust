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

std::ostream& operator<<(std::ostream& out, const std::shared_ptr<VhdlCodeBlock> block) {
    block->_buffer.output_buffer(out);
    for (auto child : block->_children) {
        out << child << std::endl;
    }
    // TODO: Add closing code
    return out;
}

std::ostream& operator<<(std::ostream& out, const VhdlCodeContainer& container) {
    out << container._dependencies << std::endl;
    out << "-- ======= ENTITIES =========" << std::endl;
    out << container._entities << std::endl;
    out << "-- ======= COMPONENTS =======" << std::endl;
    out << container._components << std::endl;
    out << "-- ======= PORT MAPPINGS ====" << std::endl;
    out << container._port_mappings << std::endl;

    return out;
}

void VhdlCodeContainer::register_component(const Vertex& component)
{
    std::stringstream ss;
    ss << component.node << "_" << component.node_hash;
    std::string id = ss.str();

    _node_identifier.insert({ component.node_hash, id });

    // Generate a generic entity for this component if it
    // has not been done already

    // Declare a unique signal for each input and output of the generic component
    // TODO!
}

void VhdlCodeContainer::connect(const Vertex& source, const Vertex& target, int lag)
{
    // Find the source and target identifiers
    std::string source_id = _node_identifier.at(source.node_hash);
    std::string target_id = _node_identifier.at(target.node_hash);


}

//std::ostream& operator<<(std::ostream& out, const PortMode& port_mode) {
//    switch (port_mode) {
//        case PortMode::Input: out << "in"; break;
//        case PortMode::Output: out << "out"; break;
//        case PortMode::InOut: out << "inout"; break;
//        case PortMode::Buffer: out << "buffer"; break;
//    }
//    return out;
//}
//
//std::string assignmentSymbol(ObjectType type) {
//    switch (type) {
//        case ObjectType::Variable: return ":=";
//        case ObjectType::Signal: return "<=";
//        default:
//            faustassert(false);
//            return "";
//    }
//}
//std::ostream& operator<<(std::ostream& out, const ObjectType& type) {
//    switch (type) {
//        case ObjectType::Constant: out << "constant"; break;
//        case ObjectType::Signal: out << "signal"; break;
//        case ObjectType::Variable: out << "variable"; break;
//        default: break;
//    }
//    return out;
//}
//
//std::string VhdlValue::resetStatement() {
//    std::stringstream stream;
//    stream << name << ' ' << assignmentSymbol(object_type) << ' ' << (vhdl_type.lsb == vhdl_type.msb ? "'0'" : "(others => '0')") << ';';
//    return stream.str();
//}
//std::ostream& operator<<(std::ostream& out, const VhdlType& type) {
//    switch (type.type) {
//        case VhdlInnerType::Bit: out << "bit"; break;
//        case VhdlInnerType::BitVector: out << "bit_vector"; break;
//        case VhdlInnerType::Boolean: out << "boolean"; break;
//        case VhdlInnerType::BooleanVector: out << "boolean_vector"; break;
//        case VhdlInnerType::Integer: out << "integer"; break;
//        case VhdlInnerType::IntegerVector: out << "integer_vector"; break;
//        case VhdlInnerType::Natural: out << "natural"; break;
//        case VhdlInnerType::Positive: out << "positive"; break;
//        case VhdlInnerType::Character: out << "character"; break;
//        case VhdlInnerType::String: out << "string"; break;
//        case VhdlInnerType::RealFloat: out << "boolean_vector"; break; // TODO
//        case VhdlInnerType::RealFloatVector: out << "boolean_vector"; break; // TODO
//        case VhdlInnerType::StdLogic: out << "std_logic"; break;
//        case VhdlInnerType::StdLogicVector: out << "std_logic_vector"; break;
//        case VhdlInnerType::StdULogic: out << "std_ulogic"; break;
//        case VhdlInnerType::StdULogicVector: out << "std_ulogic_vector"; break;
//        case VhdlInnerType::Unsigned: out << "unsigned"; break;
//        case VhdlInnerType::Signed: out << "signed"; break;
//        case VhdlInnerType::UFixed: out << "ufixed"; break;
//        case VhdlInnerType::SFixed: out << "sfixed"; break;
//        case VhdlInnerType::Float: out << "float"; break;
//        default: break;
//    }
//    if (type.msb != type.lsb) {
//        out << '(' << type.msb << " downto " << type.lsb << ')';
//    }
//    return out;
//}
