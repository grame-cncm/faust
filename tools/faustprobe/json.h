/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// A JSON document: built by the modes, printed once. Keys print sorted, so
// that a document does not depend on the order it was filled in.

#ifndef __faustprobe_json__
#define __faustprobe_json__

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "text.h"

class Json {
   public:
    Json();                         // null
    Json(bool value);
    Json(int value);
    Json(size_t value);
    Json(double value);             // a non-finite value is null, which never hides a run
    Json(const char* value);
    Json(const std::string& value);

    template <typename T>
    Json(const Optional<T>& value) : Json()
    {
        if (value.has) {
            *this = Json(value.value);
        }
    }

    static Json object();
    static Json array();
    static Json strings(const std::vector<std::string>& values);
    static Json numbers(const std::vector<double>& values);
    static Json sizes(const std::vector<size_t>& values);

    Json& set(const std::string& key, const Json& value);  // of an object
    Json& push(const Json& value);                         // of an array
    bool  empty() const;
    std::string pretty() const;

   private:
    enum class Kind { Null, Bool, Integer, Number, String, Array, Object };
    Kind                        fKind;
    bool                        fBool    = false;
    size_t                      fInteger = 0;
    bool                        fNegative = false;
    double                      fNumber  = 0.0;
    std::string                 fString;
    std::vector<Json>           fArray;
    std::map<std::string, Json> fObject;

    void write(std::string& out, int indent) const;
};

#endif
