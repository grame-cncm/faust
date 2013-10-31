/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 *
 *
 *    This file is part of the Faust Tube Library
 *
 *
 * --------------------------------------------------------------------------
 */

#pragma once

#ifndef SRC_HEADERS_VALVE_H_
#define SRC_HEADERS_VALVE_H_

/****************************************************************
 * 1-dimensional function tables for linear interpolation
 *
 * table1d and table1d_imp<size> must only differ in the last
 * element, so that the typecast for tubetab below will work.
 * Can't use inheritance because then C initializers will not
 * work and initialization will be more awkward or less efficient.
 */

struct table1d { // 1-dimensional function table
    float low;
    float high;
    float istep;
    int size;
    float data[];
};

template <int tab_size>
struct table1d_imp {
    float low;
    float high;
    float istep;
    int size;
    float data[tab_size];
    operator table1d&() const { return *(table1d*)this; }
};

/*
 * data tables 
 */
#include "12ax7.cc"
#include "12AU7.cc"
#include "12AT7.cc"
#include "6V6.cc"
#include "6DJ8.cc"
#include "6C16.cc"

enum {
    TUBE_TABLE_12AX7_68k,
    TUBE_TABLE_12AX7_250k,
    TUBE_TABLE_6V6_68k,
    TUBE_TABLE_6V6_250k,
    TUBE_TABLE_12AU7_68k,
    TUBE_TABLE_12AU7_250k,
    TUBE_TABLE_6DJ8_68k,
    TUBE_TABLE_6DJ8_250k,
    TUBE_TABLE_12AT7_68k,
    TUBE_TABLE_12AT7_250k,
    TUBE_TABLE_6C16_68k,
    TUBE_TABLE_6C16_250k,
    TUBE_TABLE_SIZE
};

table1d *tubetab[TUBE_TABLE_SIZE] = {
    &static_cast<table1d&>(tubetable_12AX7[0]),
    &static_cast<table1d&>(tubetable_12AX7[1]),
    &static_cast<table1d&>(tubetable_6V6[0]),
    &static_cast<table1d&>(tubetable_6V6[1]),
    &static_cast<table1d&>(tubetable_12AU7[0]),
    &static_cast<table1d&>(tubetable_12AU7[1]),
    &static_cast<table1d&>(tubetable_6DJ8[0]),
    &static_cast<table1d&>(tubetable_6DJ8[1]),
    &static_cast<table1d&>(tubetable_12AT7[0]),
    &static_cast<table1d&>(tubetable_12AT7[1]),
    &static_cast<table1d&>(tubetable_6C16[0]),
    &static_cast<table1d&>(tubetable_6C16[1]),
};

/*
 *  definitions for ffunction(float Ftube(int,float), "valve.h", "");
 */

static inline double Ftube(int table, double Vgk) {
    const table1d& tab = *tubetab[table];
    double f = (Vgk - tab.low) * tab.istep;
    int i = static_cast<int>(f);
    if (i < 0)
        return tab.data[0];
    if (i >= tab.size-1)
        return tab.data[tab.size-1];
    f -= i;
    return tab.data[i]*(1-f) + tab.data[i+1]*f;
}

#endif  // SRC_HEADERS_VALVE_H_
