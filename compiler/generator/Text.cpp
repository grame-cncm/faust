/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Text.hh"
#include "compatibility.hh"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "floats.hh"

extern bool gInternDoubleSwitch;

static string substitution(const string &model, const vector<string> &args);

/**
 * Text substitution. Creates a string by replacing all the $n
 * occurences in the model string, with the corresponding arguments.
 * Example :
 * 		subst("float $0 = $1;", "var", T(10.2))
 */
string subst(const string &model, const vector<string> &args)
{
    return substitution(model, args);
}

string subst(const string &model, const string &a0)
{
    vector<string> args(10);
    args[0] = a0;
    return substitution(model, args);
}

string subst(const string &model, const string &a0, const string &a1)
{
    vector<string> args(10);
    args[0] = a0;
    args[1] = a1;

    return substitution(model, args);
}

string subst(const string &model, const string &a0, const string &a1, const string &a2)
{
    vector<string> args(10);

    args[0] = a0;
    args[1] = a1;
    args[2] = a2;

    return substitution(model, args);
}

string subst(const string &model, const string &a0, const string &a1, const string &a2, const string &a3)
{
    vector<string> args(10);

    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;

    return substitution(model, args);
}

string subst(const string &model, const string &a0, const string &a1, const string &a2, const string &a3, const string &a4)
{
    vector<string> args(10);

    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;

    return substitution(model, args);
}

string subst(const string &model, const string &a0, const string &a1, const string &a2, const string &a3, const string &a4, const string &a5)
{
    vector<string> args(10);

    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    args[5] = a5;

    return substitution(model, args);
}

string subst(const string &model, const string &a0, const string &a1, const string &a2, const string &a3, const string &a4, const string &a5, const string &a6)
{
    vector<string> args(10);

    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    args[5] = a5;
    args[6] = a6;

    return substitution(model, args);
}

static string substitution(const string &model, const vector<string> &args)
{
    char c;
    int i = 0, ilast = (int)model.length() - 1;
    string result;

    while (i < ilast)
    {
        c = model[i++];
        if (c != '$')
        {
            result += c;
        }
        else
        {
            c = model[i++];
            if (c >= '0' && c <= '9')
            {
                result += args[c - '0'];
            }
            else
            {
                result += c;
            }
        }
    }
    if (i == ilast)
        result += model[i];
    return result;
}

string T(char *c) { return string(c); }
string T(int n)
{
    char c[64];
    snprintf(c, 63, "%d", n);
    return string(c);
}
string T(long n)
{
    char c[64];
    snprintf(c, 63, "%ld", n);
    return string(c);
}

/**
 * If needed add a trailing '.0' to the
 * the textual representation of a floating point number
 * to avoid confusions with an int.
 */
static void ensureFloat(char *c)
{
    bool isInt = true;
    while (*c != 0)
    {
        if ((*c == '.') | (*c == 'e'))
            isInt = false;
        c++;
    }

    if (isInt)
    {
        *c++ = '.';
        *c++ = '0';
        *c = 0;
    }
}

/**
 * Convert a double-precision float into a string.
 * Adjusts the precision p to the needs. Add a trailing
 * f if single-precision is required.
 */
string T(double n)
{
    char c[64];
    int p = 1;
    if (isfinite(n))
    {
        do
        {
            snprintf(c, 32, "%.*g", p++, n);
        } while (atof(c) != n);
        ensureFloat(c);
        return string(c) + inumix();
    }
    else
    {
        snprintf(c, 32, "%g", n);
        return string(c);
    }
}

/**
 * remove quotes from a string
 */
string unquote(const string &s)
{
    assert(s.size() >= 2);
    assert(s[0] == '"');
    assert(s[s.size() - 1] == '"');
    return s.substr(1, s.size() - 2);
}

/**
 * add quotes to a string
 */
string quote(const string &s)
{
    return "\"" + s + "\"";
}

string rmWhiteSpaces(const string &s)
{
    size_t i = s.find_first_not_of(" \t");
    size_t j = s.find_last_not_of(" \t");

    if ((i != string::npos) & (j != string::npos))
    {
        return s.substr(i, 1 + j - i);
    }
    else
    {
        return "";
    }
}

//---------------------------------------------------
// Analyse a string and return true x cond x body if
// str == if (cond) { body }
// false otherwise
//
bool isIfExpression(const string &expr, string &cond, string &body)
{
    string cpart, bpart;
    int state = 0;
    int depth = 0;

    for (char c : expr)
    {
        switch (state)
        {
        case 0:
            if (c == 'i')
            {
                state = 1;
                break;
            }
        case 1:
            if (c == 'f')
            {
                state = 2;
            }
            else
            {
                state = 0;
            }
            break;

        case 2:
            if (c == '(')
            {
                state = 3;
                depth = 1;
            }
            break;
        case 3:
            if (c == '(')
            {
                depth++;
            }
            else if (c == ')')
            {
                depth--;
            }
            if (depth > 0)
            {
                // we are inside the condition part
                cpart += c;
            }
            else
            {
                state = 4;
            }
            break;
        case 4:
            if (c == '{')
            {
                depth = 1;
                state = 5;
            }
            break;
        case 5:
            if (c == '{')
            {
                depth++;
            }
            else if (c == '}')
            {
                depth--;
            }
            if (depth > 0)
            {
                // we are inside the body part
                bpart += c;
            }
            else
            {
                state = 6;
            }
            break;
        default:
            break;
        }
    }
    if (state == 6)
    {
        // cerr << "it is a if statement with condition : " << cpart
        //     << " and with body: " << bpart << endl;
        cond = cpart;
        body = bpart;
        return true;
    }
    else
    {
        return false;
    }
}
