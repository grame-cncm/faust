// Check parseDouble: correctly rounded, independent of the locale of the host,
// and unchanged for the texts the stream refuses or does not read to the end.
#include <clocale>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "faust/gui/SimpleParser.h"

static void require(bool condition, const std::string& message)
{
    if (!condition) throw std::runtime_error(message);
}

static bool sameBits(double a, double b)
{
    return std::memcmp(&a, &b, sizeof(double)) == 0;
}

struct Case {
    const char* text;
    bool        valid;
    double      value;
    const char* rest;
};

static void checkCases()
{
    const double inf = std::numeric_limits<double>::infinity();
    const Case   cases[] = {
        {"0", true, 0.0, ""},
        {"-0", true, -0.0, ""},
        {"-0.0", true, -0.0, ""},
        {"+5", true, 5.0, ""},
        {".5", true, 0.5, ""},
        {"5.", true, 5.0, ""},
        {"-.5e3", true, -500.0, ""},
        {"1E2", true, 100.0, ""},
        {"00012", true, 12.0, ""},
        {"  1.5", true, 1.5, ""},
        {"0.1", true, 0.1, ""},
        {"1.5,2", true, 1.5, ",2"},
        {"1.5}", true, 1.5, "}"},
        {"1.2.3", true, 1.2, ".3"},
        {"0x10", true, 0.0, "x10"},
        // A number followed by blanks: the parser stands past them.
        {"1.5 ", true, 1.5, ""},
        {"1.5\n,", true, 1.5, ","},
        {"1 , 2", true, 1.0, ", 2"},
        // parseChar skips blanks, so these are one number.
        {"1 .5", true, 1.5, ""},
        {"1 e3", true, 1000.0, ""},
        {"1.5 e 2", true, 150.0, ""},
        // Refused by the stream.
        {"1e", true, 1.0, ""},
        {"1e+", true, 1.0, ""},
        {"1e-", true, 1.0, ""},
        {"1e400", true, inf, ""},
        {"-1e400", true, -inf, ""},
        {"1e-400", true, 0.0, ""},
        // Longer than any double: rounded, not accumulated.
        {"123456789012345678901234567890123456789012345678901234567890.5", true,
         std::strtod("123456789012345678901234567890123456789012345678901234567890.5", nullptr), ""},
        {"0.1234567890123456789012345678901234567890123456789012345678901234567890", true,
         std::strtod("0.1234567890123456789012345678901234567890123456789012345678901234567890",
                     nullptr),
         ""},
        // Not numbers: the position is restored.
        {"abc", false, 0.0, "abc"},
        {"-", false, 0.0, "-"},
        {"+", false, 0.0, "+"},
        {".", false, 0.0, "."},
        {"e5", false, 0.0, "e5"},
        {".e5", false, 0.0, ".e5"},
        {"- 5", false, 0.0, "- 5"},
        {"", false, 0.0, ""},
    };
    for (const Case& c : cases) {
        const char* p = c.text;
        double      x = 0.0;
        bool        valid = parseDouble(p, x);
        require(valid == c.valid, std::string("Wrong validity for '") + c.text + "'");
        require(std::strcmp(p, c.rest) == 0, std::string("Wrong position for '") + c.text + "'");
        if (c.valid) {
            require(sameBits(x, c.value), std::string("Wrong value for '") + c.text + "'");
        }
    }
    std::cout << "PASS fixed texts: " << sizeof(cases) / sizeof(cases[0]) << "\n";
}

// Every finite normal double survives printing with all its digits and reading back.
static void checkRoundTrip(int count)
{
    std::mt19937_64 random(20261031);
    int             checked = 0;
    while (checked < count) {
        uint64_t bits = random();
        double   value;
        std::memcpy(&value, &bits, sizeof(double));
        if (!std::isnormal(value)) continue;
        char text[64];
        std::snprintf(text, sizeof(text), "%.17g", value);
        const char* p = text;
        double      x = 0.0;
        require(parseDouble(p, x) && *p == 0, std::string("Refused '") + text + "'");
        require(sameBits(x, value), std::string("Round trip lost '") + text + "'");
        ++checked;
    }
    std::cout << "PASS round trips: " << checked << "\n";
}

// A subnormal may go through the sum, where the C library reports the underflow to the
// stream: its value only has to be close. The sum gives 0 below 1e-323, as it always did.
static void checkSubnormals()
{
    const char* texts[] = {"1e-320", "1e-310", "2.2250738585072009e-308"};
    for (const char* text : texts) {
        const char* p = text;
        double      x = 0.0;
        double      expected = std::strtod(text, nullptr);
        require(parseDouble(p, x) && *p == 0, std::string("Refused '") + text + "'");
        require(std::fabs(x - expected) <= 0.5 * expected, std::string("Far from '") + text + "'");
    }
    std::cout << "PASS subnormals\n";
}

// A host that writes 0,5 still reads the 0.5 of a JSON description.
static void checkLocale()
{
    const char* names[] = {"fr_FR.UTF-8", "de_DE.UTF-8", "fr_FR", "de_DE"};
    for (const char* name : names) {
        if (!std::setlocale(LC_ALL, name)) continue;
        std::string used(name);
        try {
            std::locale::global(std::locale(name));
        } catch (const std::runtime_error&) {
        }
        const char* p = "0.30000000000000004,";
        double      x = 0.0;
        bool        valid = parseDouble(p, x);
        std::locale::global(std::locale::classic());
        std::setlocale(LC_ALL, "C");
        require(valid && x == 0.30000000000000004 && std::strcmp(p, ",") == 0,
                "Wrong value under " + used);
        std::cout << "PASS locale " << used << "\n";
        return;
    }
    std::cout << "SKIP locale: no comma locale on this host\n";
}

int main()
{
    try {
        checkCases();
        checkRoundTrip(1000000);
        checkSubnormals();
        checkLocale();
    } catch (const std::exception& e) {
        std::cerr << "FAIL: " << e.what() << "\n";
        return 1;
    }
    std::cout << "PASS parse-double\n";
    return 0;
}
