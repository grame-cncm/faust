#pragma once

#include <array>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include "HashTuple.hh"

namespace nlpl
{
/**
 * @brief Where should we declare a memory
 *
 */
enum PhaseMode : unsigned int { kFinal = 0xFFFFFFFF };

// forward declarations
class MemoryZone;
using Mem        = MemoryZone*;
using Dependency = std::pair<Mem, int>;

/**
 * @brief A MemoryZone is a place used to read and write expressions
 *
 */
class MemoryZone
{
   public:
    const std::string  fType;   // "int", "float"
    const std::string  fName;   // "myVar"
    const unsigned int fPhase;  // -1 = final
    size_t             fSize;   // 0: scalar, n: vector

   public:
    explicit MemoryZone(std::string typ, std::string name, unsigned int phase)
        : fType(std::move(typ)), fName(std::move(name)), fPhase(phase), fSize(0)
    {
    }

    void print(std::ostream& os);
    void getDependencies(std::set<Dependency>& dep);
};

/**
 * @brief A memory for a scalar of some type
 *
 * @param decl
 * @param typ the type (for example "float" or "int")
 * @param name the identifier (for example "x")
 * @param phase
 * @return Mem
 */
Mem memory(const std::string& typ, const std::string& name, unsigned int phase);

/**
 * @brief  A memory for a vector of some type and size
 *
 * @param decl
 * @param typ
 * @param name
 * @param phase
 * @param size
 * @return Mem
 */
Mem memory(const std::string& typ, const std::string& name, size_t size, unsigned int phase);

/**
 * @brief Printing operator, wrapper to the print method
 *
 * @param os
 * @param m
 * @return std::ostream&
 */
inline std::ostream& operator<<(std::ostream& os, Mem m)
{
    m->print(os);
    return os;
}

}  // namespace nlpl