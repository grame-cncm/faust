#pragma once

#include <array>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include "HashTuple.hh"

namespace nlpl {
/**
 * @brief Where should we declare a memory
 *
 */
enum DeclareMode : int { kPermanent, kBlock, kSample };
enum PhaseMode : unsigned int { kFinal = 0xffffffff };

// forward declarations
class MemoryZone;
using Memory     = MemoryZone*;
using Dependency = std::pair<Memory, int>;

/**
 * @brief A MemoryZone is a place used to read and write expressions
 *
 */
class MemoryZone {
   public:
    virtual std::string  name()                                     = 0;
    virtual void         print(std::ostream& os)                    = 0;
    virtual DeclareMode  declarationMode()                          = 0;
    virtual unsigned int phase()                                    = 0;
    virtual void         getDependencies(std::set<Dependency>& dep) = 0;
};

/**
 * @brief A memory for a scalar of some type
 *
 * @param typ the type (for example "float" or "int")
 * @param name the identifier (for example "x")
 * @return Memory
 */
Memory Scalar(DeclareMode decl, const std::string& typ, const std::string& name, unsigned int phase);

/**
 * @brief  A memory for a vector of some type and size
 *
 * @param typ
 * @param name
 * @param size
 * @return Memory
 */
Memory Vector(DeclareMode decl, const std::string& typ, const std::string& name, size_t size, unsigned int phase);

/**
 * @brief Printing operator, wrapper to the print method
 *
 * @param os
 * @param m
 * @return std::ostream&
 */
inline std::ostream& operator<<(std::ostream& os, Memory m)
{
    m->print(os);
    return os;
}

//==================================
// simplified API
//==================================

inline Memory sFloat(const std::string& name)
{
    return Scalar(kSample, "float", name, kFinal);
}

inline Memory sInt(const std::string& name)
{
    return Scalar(kSample, "int", name, kFinal);
}

inline Memory vFloat(const std::string& name, size_t size)
{
    return Vector(kSample, "float", name, size, kFinal);
}

inline Memory vInt(const std::string& name, size_t size)
{
    return Vector(kSample, "int", name, size, kFinal);
}

}  // namespace nlpl