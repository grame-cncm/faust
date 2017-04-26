/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "distance field" library , Copyright (C) 2007 CMU, 2016 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Danyong Zhao, Jernej Barbic                             *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Hongyi Xu, Doug L. James                     *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Zumberge Research and Innovation Fund at USC                 *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of the BSD-style license that is            *
 * included with this library in the file LICENSE.txt                    *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file     *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

/*
  Marching cubes tables. These tables were generated programmatically,
  using our code.
*/

static char ambiguityTable[15][64] = 
{
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 1, 2, 4, 3, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 2, 3, 4, 1, 0, 3, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
  { 0, 1, 2, 7, 3, -1, 11, -1, 4, 8, -1, -1, 14, -1, -1, -1, 5, 9, 12, 42, 15, -1, 21, 34, 17, 20, -1, 32, 45, 29, 26, 40, 6, 10, 13, 19, 16, -1, 44, 33, 18, 43, -1, 31, 22, 28, 25, 39, -1, -1, -1, 30, -1, -1, 24, 38, -1, 27, -1, 37, 23, 36, 35, 41 }, 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

static int marchingCubeSymmetries[256][3] = {
  {  0,  0,  0 },   {  1,  0,  0 },   {  1,  1,  2 },   {  2,  0,  0 },   {  1,  2,  9 },   {  3,  0,  0 },   {  2,  3,  3 },   {  5,  0,  0 }, 
  {  1,  3,  1 },   {  2,  1,  6 },   {  3,  3,  3 },   {  5,  1,  6 },   {  2,  5,  1 },   {  5,  4,  9 },   {  5,  9,  3 },   {  8,  0,  0 }, 
  {  1,  4,  4 },   {  2,  2,  5 },   {  3,  4,  4 },   {  5,  2, 10 },   {  4,  2,  4 },   {  6,  2,  5 },   {  6,  9, 21 },   { 11,  0,  0 }, 
  {  3,  8,  5 },   {  5,  5,  5 },   {  7,  3,  5 },   {  9,  1,  5 },   {  6, 16,  9 },   { 14,  3,  5 },   { 12, 12,  3 },   {  5, 24, -7 }, 
  {  1,  5,  8 },   {  3,  1, 16 },   {  2,  4,  2 },   {  5,  3, 17 },   {  3,  6, 18 },   {  7,  0,  0 },   {  5, 10, 21 },   {  9,  0,  0 }, 
  {  4,  3,  1 },   {  6,  4,  6 },   {  6, 11, 17 },   { 14,  1,  6 },   {  6, 17,  1 },   { 12,  4,  9 },   { 11,  6,  3 },   {  5, 25,-14 }, 
  {  2,  8,  4 },   {  5,  7, 16 },   {  5, 12,  4 },   {  8,  1,  4 },   {  6, 18,  4 },   { 12,  5, 16 },   { 14,  7,  4 },   {  5, 28,-12 }, 
  {  6, 21,  8 },   { 11,  4,  5 },   { 12, 15,  4 },   {  5, 30,-23 },   { 10,  5,  1 },   {  6, 32, -7 },   {  6, 39,-12 },   {  2, 12, -7 }, 
  {  1,  6, 11 },   {  4,  0,  0 },   {  3,  5,  2 },   {  6,  0,  0 },   {  2,  6, 11 },   {  6,  3, 11 },   {  5, 11, 11 },   { 14,  0,  0 }, 
  {  3,  9,  1 },   {  6,  5, 20 },   {  7,  4,  1 },   { 12,  1,  6 },   {  5, 14,  1 },   { 11,  3,  1 },   {  9,  4,  1 },   {  5, 26, -8 }, 
  {  3, 10, 14 },   {  6,  6, 16 },   {  7,  5,  2 },   { 12,  2, 10 },   {  6, 19, 23 },   { 10,  1,  5 },   { 12, 13, 11 },   {  6, 24,-13 }, 
  {  7,  7, 12 },   { 12,  9,  5 },   { 13,  1,  3 },   {  7,  9, -7 },   { 12, 20,  1 },   {  6, 33, -2 },   {  7, 13, -8 },   {  3, 12, -7 }, 
  {  2, 10, 15 },   {  6,  7, 15 },   {  5, 13,  2 },   { 11,  2,  2 },   {  5, 16, 18 },   { 12,  7, 18 },   {  8,  3,  2 },   {  5, 29,-13 }, 
  {  6, 22, 18 },   { 10,  2,  6 },   { 12, 17,  2 },   {  6, 27,-14 },   { 14,  9,  1 },   {  6, 34,-19 },   {  5, 39,-19 },   {  2, 14,-14 }, 
  {  5, 20, 15 },   { 14,  5, 15 },   {  9,  5,  2 },   {  5, 32,-22 },   { 11, 10, 15 },   {  6, 35,-22 },   {  5, 41,-20 },   {  2, 16,-13 }, 
  { 12, 23, 15 },   {  6, 37, -3 },   {  7, 14, -9 },   {  3, 16,-22 },   {  6, 46,-10 },   {  4,  6, -2 },   {  3, 21,-19 },   {  1,  8, -7 }, 
  {  1,  7,  7 },   {  3,  2, 19 },   {  4,  1,  2 },   {  6,  1, 10 },   {  3,  7, 22 },   {  7,  1,  9 },   {  6, 10,  3 },   { 12,  0,  0 }, 
  {  2,  7, 13 },   {  5,  6, 20 },   {  6, 12, 22 },   { 11,  1,  6 },   {  5, 15, 22 },   {  9,  2,  9 },   { 14,  6,  3 },   {  5, 27,-15 }, 
  {  2,  9, 14 },   {  5,  8, 19 },   {  6, 13, 19 },   { 14,  2, 10 },   {  6, 20, 14 },   { 12,  6, 19 },   { 10,  3,  3 },   {  6, 25,-18 }, 
  {  5, 18, 13 },   {  8,  2,  5 },   { 12, 16, 13 },   {  5, 31,-18 },   { 11,  9, 13 },   {  5, 34, -2 },   {  6, 40,-15 },   {  2, 13,-15 }, 
  {  3, 11,  7 },   {  7,  2,  8 },   {  6, 14,  2 },   { 12,  3, 17 },   {  7,  6,  7 },   { 13,  0,  0 },   { 12, 14, 21 },   {  7,  8,-12 }, 
  {  6, 23, 13 },   { 12, 10, 20 },   { 10,  4,  2 },   {  6, 28,-23 },   { 12, 21, 22 },   {  7, 10, -2 },   {  6, 41,-16 },   {  3, 13,-14 }, 
  {  5, 21,  8 },   {  9,  3,  8 },   { 11,  8,  4 },   {  5, 33, -1 },   { 12, 22,  8 },   {  7, 11, -1 },   {  6, 42,-20 },   {  3, 14, -1 }, 
  { 14, 11,  8 },   {  5, 36,-11 },   {  6, 44,-11 },   {  2, 17,-11 },   {  6, 47,  0 },   {  3, 18, -2 },   {  4,  7,  0 },   {  1,  9,-11 }, 
  {  2, 11,  7 },   {  6,  8, 12 },   {  6, 15,  7 },   { 10,  0,  0 },   {  5, 17, 23 },   { 12,  8, 23 },   { 11,  7, 11 },   {  6, 26, -8 }, 
  {  5, 19, 12 },   { 14,  4, 12 },   { 12, 18, 12 },   {  6, 29, -4 },   {  8,  4,  1 },   {  5, 35, -4 },   {  5, 40,-16 },   {  2, 15, -4 }, 
  {  5, 22, 14 },   { 11,  5, 14 },   { 12, 19, 14 },   {  6, 30, -1 },   { 14, 10, 14 },   {  6, 36,-17 },   {  6, 43, -6 },   {  4,  4, -1 }, 
  {  9,  7, 12 },   {  5, 37,-21 },   {  7, 15,  0 },   {  3, 17,-18 },   {  5, 44,-17 },   {  2, 19, -2 },   {  3, 22,-16 },   {  1, 10, -8 }, 
  {  5, 23,  7 },   { 12, 11,  7 },   { 14,  8,  2 },   {  6, 31, -9 },   {  9,  6,  7 },   {  7, 12, -5 },   {  5, 42, -5 },   {  3, 15, -5 }, 
  { 11, 11,  7 },   {  6, 38,-21 },   {  6, 45, -5 },   {  4,  5, -4 },   {  5, 45,-10 },   {  3, 19, -4 },   {  2, 21, -5 },   {  1, 11, -4 }, 
  {  8,  5,  7 },   {  5, 38, -3 },   {  5, 43, -9 },   {  2, 18, -1 },   {  5, 46, -6 },   {  3, 20, -3 },   {  2, 22, -6 },   {  1, 12, -1 }, 
  {  5, 47,  0 },   {  2, 20, -3 },   {  3, 23,  0 },   {  1, 13, -9 },   {  2, 23,  0 },   {  1, 14, -2 },   {  1, 15,  0 },   {  0,  1,  0 }
};

static char faceTest_num[256][7] = 
{
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 5, 0, 0, 0, 0, 0 },  { 1, 1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 1, 4, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 3, 1, 5, 4, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 4, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 1, 4, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 2, 0, 0, 0, 0, 0 },  { 3, 1, 2, 5, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 1, 0, 0, 0, 0, 0 },  { 1, 5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 2, 0, 0, 0, 0, 0 },  { 2, 2, 1, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 2, 0, 0, 0, 0, 0 },  { 2, 5, 2, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 1, 4, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 4, 5, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 2, 4, 0, 0, 0, 0 },  { 1,-2, 0, 0, 0, 0, 0 },  { 1,-4, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 2, 0, 0, 0, 0, 0 },  { 1, 2, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 1, 3, 0, 0, 0, 0, 0 },  { 1, 3, 0, 0, 0, 0, 0 },  { 3, 5, 2, 3, 0, 0, 0 },  { 2, 3, 2, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 1, 6, 0, 0, 0, 0, 0 },  { 1, 6, 0, 0, 0, 0, 0 },  { 3, 1, 6, 2, 0, 0, 0 },  { 2, 2, 6, 0, 0, 0, 0 },  { 1, 6, 0, 0, 0, 0, 0 },  { 2, 5, 6, 0, 0, 0, 0 },  { 2, 6, 1, 0, 0, 0, 0 },  { 1,-6, 0, 0, 0, 0, 0 },
  { 3, 6, 4, 3, 0, 0, 0 },  { 2, 6, 3, 0, 0, 0, 0 },  { 6, 2, 3, 4, 1, 5, 6 },  { 3,-3,-2,-6, 0, 0, 0 },  { 2, 4, 6, 0, 0, 0, 0 },  { 1,-6, 0, 0, 0, 0, 0 },  { 3,-1,-4,-6, 0, 0, 0 },  { 1,-6, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 1, 5, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 1, 3, 0, 0, 0, 0, 0 },  { 2, 1, 3, 0, 0, 0, 0 },  { 2, 5, 3, 0, 0, 0, 0 },  { 1,-3, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 2, 3, 4, 0, 0, 0, 0 },  { 1,-3, 0, 0, 0, 0, 0 },  { 3,-3,-4,-5, 0, 0, 0 },  { 1,-3, 0, 0, 0, 0, 0 },  { 1,-4, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-4, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 4, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 4, 0, 0, 0, 0, 0 },  { 1, 3, 0, 0, 0, 0, 0 },  { 3, 3, 4, 5, 0, 0, 0 },  { 1, 3, 0, 0, 0, 0, 0 },  { 2, 4, 3, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 3, 0, 0, 0, 0, 0 },  { 2, 3, 5, 0, 0, 0, 0 },  { 2, 3, 1, 0, 0, 0, 0 },  { 1,-3, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 5, 1, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 1, 6, 0, 0, 0, 0, 0 },  { 3, 1, 4, 6, 0, 0, 0 },  { 1, 6, 0, 0, 0, 0, 0 },  { 2, 6, 4, 0, 0, 0, 0 },  { 3, 3, 2, 6, 0, 0, 0 },  { 6, 1, 2, 3, 4, 5, 6 },  { 2, 3, 6, 0, 0, 0, 0 },  { 3,-6,-4,-3, 0, 0, 0 },
  { 1, 6, 0, 0, 0, 0, 0 },  { 2, 1, 6, 0, 0, 0, 0 },  { 2, 6, 5, 0, 0, 0, 0 },  { 1,-6, 0, 0, 0, 0, 0 },  { 2, 6, 2, 0, 0, 0, 0 },  { 3,-1,-6,-2, 0, 0, 0 },  { 1,-6, 0, 0, 0, 0, 0 },  { 1,-6, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 2, 3, 0, 0, 0, 0 },  { 3,-5,-2,-3, 0, 0, 0 },  { 1,-3, 0, 0, 0, 0, 0 },  { 1,-3, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-2, 0, 0, 0, 0, 0 },  { 1,-2, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 1, 4, 0, 0, 0, 0, 0 },  { 1, 2, 0, 0, 0, 0, 0 },  { 2, 2, 4, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 5, 4, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-4, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 2, 5, 0, 0, 0, 0 },  { 1,-2, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 1, 2, 0, 0, 0, 0 },  { 1,-2, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-5, 0, 0, 0, 0, 0 },  { 1,-1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 3,-1,-2,-5, 0, 0, 0 },  { 1,-2, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 2, 4, 1, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-4, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 3,-1,-5,-4, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-4, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-1, 0, 0, 0, 0, 0 },  { 1,-5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-1, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 1,-5, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 },  { 0, 0, 0, 0, 0, 0, 0 }
};

static char interiorTest_num[256] = 
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static unsigned char triangleTable_1_0[5] =  { 3, 0, 8, 3, 0 };
static unsigned char * triangleTable_1[1] = { triangleTable_1_0 };

static unsigned char triangleTable_2_0[5] =  { 3, 0, 0, 1, 9 };
static unsigned char * triangleTable_2[1] = { triangleTable_2_0 };

static unsigned char triangleTable_3_0[8] =  { 6, 0, 3, 1, 8, 9, 8, 1 };
static unsigned char * triangleTable_3[1] = { triangleTable_3_0 };

static unsigned char triangleTable_4_0[5] =  { 3, 0, 10, 1, 2 };
static unsigned char * triangleTable_4[1] = { triangleTable_4_0 };

static unsigned char triangleTable_5_0[8] =  { 6, 0, 1, 2, 10, 8, 3, 0 };
static unsigned char triangleTable_5_1[14] =  { 12, 0, 8, 3, 10, 10, 1, 0, 0, 8, 10, 2, 10, 3 };
static unsigned char * triangleTable_5[2] = { triangleTable_5_0, triangleTable_5_1 };

static unsigned char triangleTable_6_0[8] =  { 6, 0, 0, 2, 9, 10, 9, 2 };
static unsigned char * triangleTable_6[1] = { triangleTable_6_0 };

static unsigned char triangleTable_7_0[11] =  { 9, 0, 8, 3, 2, 10, 8, 2, 10, 9, 8 };
static unsigned char * triangleTable_7[1] = { triangleTable_7_0 };

static unsigned char triangleTable_8_0[5] =  { 3, 0, 3, 11, 2 };
static unsigned char * triangleTable_8[1] = { triangleTable_8_0 };

static unsigned char triangleTable_9_0[8] =  { 6, 0, 2, 0, 11, 8, 11, 0 };
static unsigned char * triangleTable_9[1] = { triangleTable_9_0 };

static unsigned char triangleTable_10_0[8] =  { 6, 0, 2, 3, 11, 9, 0, 1 };
static unsigned char triangleTable_10_1[14] =  { 12, 0, 9, 0, 11, 11, 2, 1, 1, 9, 11, 3, 11, 0 };
static unsigned char * triangleTable_10[2] = { triangleTable_10_0, triangleTable_10_1 };

static unsigned char triangleTable_11_0[11] =  { 9, 0, 11, 2, 1, 9, 11, 1, 9, 8, 11 };
static unsigned char * triangleTable_11[1] = { triangleTable_11_0 };

static unsigned char triangleTable_12_0[8] =  { 6, 0, 11, 10, 3, 1, 3, 10 };
static unsigned char * triangleTable_12[1] = { triangleTable_12_0 };

static unsigned char triangleTable_13_0[11] =  { 9, 0, 10, 1, 0, 8, 10, 0, 8, 11, 10 };
static unsigned char * triangleTable_13[1] = { triangleTable_13_0 };

static unsigned char triangleTable_14_0[11] =  { 9, 0, 9, 0, 3, 11, 9, 3, 11, 10, 9 };
static unsigned char * triangleTable_14[1] = { triangleTable_14_0 };

static unsigned char triangleTable_15_0[8] =  { 6, 0, 10, 9, 8, 8, 11, 10 };
static unsigned char * triangleTable_15[1] = { triangleTable_15_0 };

static unsigned char triangleTable_16_0[5] =  { 3, 0, 7, 8, 4 };
static unsigned char * triangleTable_16[1] = { triangleTable_16_0 };

static unsigned char triangleTable_17_0[8] =  { 6, 0, 7, 3, 4, 0, 4, 3 };
static unsigned char * triangleTable_17[1] = { triangleTable_17_0 };

static unsigned char triangleTable_18_0[8] =  { 6, 0, 9, 0, 1, 7, 8, 4 };
static unsigned char triangleTable_18_1[14] =  { 12, 0, 7, 8, 1, 1, 9, 4, 4, 7, 1, 0, 1, 8 };
static unsigned char * triangleTable_18[2] = { triangleTable_18_0, triangleTable_18_1 };

static unsigned char triangleTable_19_0[11] =  { 9, 0, 1, 9, 4, 7, 1, 4, 7, 3, 1 };
static unsigned char * triangleTable_19[1] = { triangleTable_19_0 };

static unsigned char triangleTable_20_0[8] =  { 6, 0, 2, 10, 1, 8, 4, 7 };
static unsigned char triangleTable_20_1[20] =  { 18, 0, 7, 2, 10, 7, 10, 4, 2, 8, 1, 4, 10, 1, 4, 1, 8, 8, 2, 7 };
static unsigned char * triangleTable_20[2] = { triangleTable_20_0, triangleTable_20_1 };

static unsigned char triangleTable_21_0[11] =  { 9, 0, 10, 1, 2, 4, 3, 0, 4, 7, 3 };
static unsigned char triangleTable_21_1[17] =  { 15, 0, 4, 10, 1, 2, 7, 3, 4, 7, 10, 0, 4, 1, 10, 7, 2 };
static unsigned char * triangleTable_21[2] = { triangleTable_21_0, triangleTable_21_1 };

static unsigned char triangleTable_22_0[11] =  { 9, 0, 7, 8, 4, 2, 9, 0, 2, 10, 9 };
static unsigned char triangleTable_22_1[17] =  { 15, 0, 2, 7, 8, 4, 10, 9, 2, 10, 7, 0, 2, 8, 7, 10, 4 };
static unsigned char * triangleTable_22[2] = { triangleTable_22_0, triangleTable_22_1 };

static unsigned char triangleTable_23_0[14] =  { 12, 0, 4, 7, 9, 2, 10, 9, 7, 3, 2, 7, 2, 9 };
static unsigned char * triangleTable_23[1] = { triangleTable_23_0 };

static unsigned char triangleTable_24_0[8] =  { 6, 0, 3, 11, 2, 4, 7, 8 };
static unsigned char triangleTable_24_1[14] =  { 12, 0, 4, 7, 2, 2, 3, 8, 8, 4, 2, 11, 2, 7 };
static unsigned char * triangleTable_24[2] = { triangleTable_24_0, triangleTable_24_1 };

static unsigned char triangleTable_25_0[11] =  { 9, 0, 4, 7, 11, 2, 4, 11, 2, 0, 4 };
static unsigned char * triangleTable_25[1] = { triangleTable_25_0 };

static unsigned char triangleTable_26_0[11] =  { 9, 0, 3, 11, 2, 0, 1, 9, 4, 7, 8 };
static unsigned char triangleTable_26_1[17] =  { 15, 0, 3, 11, 2, 9, 4, 7, 1, 9, 7, 8, 1, 7, 1, 8, 0 };
static unsigned char triangleTable_26_2[17] =  { 15, 0, 8, 4, 7, 2, 1, 9, 11, 2, 9, 0, 11, 9, 11, 0, 3 };
static unsigned char triangleTable_26_3[17] =  { 15, 0, 0, 1, 9, 7, 11, 2, 4, 7, 2, 3, 4, 2, 4, 3, 8 };
static unsigned char triangleTable_26_4[29] =  { 27, 1, 12, 3, 11, 12, 0, 3, 1, 12, 2, 0, 12, 8, 12, 4, 7, 12, 1, 9, 8, 12, 7, 2, 12, 11, 9, 4, 12 };
static unsigned char triangleTable_26_5[29] =  { 27, 1, 12, 0, 1, 12, 8, 0, 4, 12, 9, 8, 12, 3, 12, 11, 2, 12, 4, 7, 3, 12, 2, 9, 12, 1, 7, 11, 12 };
static unsigned char triangleTable_26_6[29] =  { 27, 1, 12, 8, 4, 12, 3, 8, 11, 12, 7, 3, 12, 0, 12, 1, 9, 12, 11, 2, 0, 12, 9, 7, 12, 4, 2, 1, 12 };
static unsigned char triangleTable_26_7[17] =  { 15, 0, 1, 9, 4, 7, 11, 4, 0, 3, 8, 11, 1, 4, 1, 11, 2 };
static unsigned char * triangleTable_26[8] = 
{ 
  triangleTable_26_0, triangleTable_26_1, triangleTable_26_2, triangleTable_26_3, triangleTable_26_4, triangleTable_26_5, triangleTable_26_6, triangleTable_26_7
};

static unsigned char triangleTable_27_0[14] =  { 12, 0, 7, 1, 4, 7, 2, 1, 11, 2, 7, 4, 1, 9 };
static unsigned char * triangleTable_27[1] = { triangleTable_27_0 };

static unsigned char triangleTable_28_0[11] =  { 9, 0, 4, 7, 8, 10, 3, 11, 10, 1, 3 };
static unsigned char triangleTable_28_1[17] =  { 15, 0, 10, 4, 7, 8, 1, 3, 10, 1, 4, 11, 10, 7, 4, 1, 8 };
static unsigned char * triangleTable_28[2] = { triangleTable_28_0, triangleTable_28_1 };

static unsigned char triangleTable_29_0[14] =  { 12, 0, 11, 10, 7, 10, 1, 0, 10, 0, 4, 7, 10, 4 };
static unsigned char * triangleTable_29[1] = { triangleTable_29_0 };

static unsigned char triangleTable_30_0[14] =  { 12, 0, 0, 3, 11, 9, 0, 11, 7, 8, 4, 9, 11, 10 };
static unsigned char triangleTable_30_1[14] =  { 12, 0, 4, 7, 11, 9, 4, 11, 3, 8, 0, 9, 11, 10 };
static unsigned char triangleTable_30_2[26] =  { 24, 1, 12, 7, 8, 10, 12, 11, 9, 4, 12, 3, 12, 0, 0, 12, 8, 12, 10, 9, 12, 3, 11, 7, 12, 4 };
static unsigned char triangleTable_30_3[26] =  { 24, 1, 12, 3, 8, 10, 12, 11, 9, 0, 12, 7, 12, 4, 4, 12, 8, 12, 10, 9, 12, 7, 11, 3, 12, 0 };
static unsigned char * triangleTable_30[4] = { triangleTable_30_0, triangleTable_30_1, triangleTable_30_2, triangleTable_30_3 };

static unsigned char triangleTable_31_0[11] =  { 9, 0, 4, 7, 11, 4, 11, 9, 11, 10, 9 };
static unsigned char * triangleTable_31[1] = { triangleTable_31_0 };

static unsigned char triangleTable_32_0[5] =  { 3, 0, 9, 5, 4 };
static unsigned char * triangleTable_32[1] = { triangleTable_32_0 };

static unsigned char triangleTable_33_0[8] =  { 6, 0, 4, 9, 5, 3, 0, 8 };
static unsigned char triangleTable_33_1[14] =  { 12, 0, 3, 0, 5, 5, 4, 8, 8, 3, 5, 9, 5, 0 };
static unsigned char * triangleTable_33[2] = { triangleTable_33_0, triangleTable_33_1 };

static unsigned char triangleTable_34_0[8] =  { 6, 0, 1, 5, 0, 4, 0, 5 };
static unsigned char * triangleTable_34[1] = { triangleTable_34_0 };

static unsigned char triangleTable_35_0[11] =  { 9, 0, 5, 4, 8, 3, 5, 8, 3, 1, 5 };
static unsigned char * triangleTable_35[1] = { triangleTable_35_0 };

static unsigned char triangleTable_36_0[8] =  { 6, 0, 10, 1, 2, 4, 9, 5 };
static unsigned char triangleTable_36_1[14] =  { 12, 0, 4, 9, 2, 2, 10, 5, 5, 4, 2, 1, 2, 9 };
static unsigned char * triangleTable_36[2] = { triangleTable_36_0, triangleTable_36_1 };

static unsigned char triangleTable_37_0[11] =  { 9, 0, 1, 2, 10, 9, 5, 4, 8, 3, 0 };
static unsigned char triangleTable_37_1[17] =  { 15, 0, 1, 2, 10, 4, 8, 3, 5, 4, 3, 0, 5, 3, 5, 0, 9 };
static unsigned char triangleTable_37_2[17] =  { 15, 0, 0, 8, 3, 10, 5, 4, 2, 10, 4, 9, 2, 4, 2, 9, 1 };
static unsigned char triangleTable_37_3[17] =  { 15, 0, 9, 5, 4, 3, 2, 10, 8, 3, 10, 1, 8, 10, 8, 1, 0 };
static unsigned char triangleTable_37_4[29] =  { 27, 1, 12, 1, 2, 12, 9, 1, 5, 12, 10, 9, 12, 0, 12, 8, 3, 12, 5, 4, 0, 12, 3, 10, 12, 2, 4, 8, 12 };
static unsigned char triangleTable_37_5[29] =  { 27, 1, 12, 9, 5, 12, 0, 9, 8, 12, 4, 0, 12, 1, 12, 2, 10, 12, 8, 3, 1, 12, 10, 4, 12, 5, 3, 2, 12 };
static unsigned char triangleTable_37_6[29] =  { 27, 1, 12, 0, 8, 12, 1, 0, 2, 12, 3, 1, 12, 9, 12, 5, 4, 12, 2, 10, 9, 12, 4, 3, 12, 8, 10, 5, 12 };
static unsigned char triangleTable_37_7[17] =  { 15, 0, 5, 4, 8, 3, 2, 8, 9, 1, 0, 2, 5, 8, 5, 2, 10 };
static unsigned char * triangleTable_37[8] = 
{ 
  triangleTable_37_0, triangleTable_37_1, triangleTable_37_2, triangleTable_37_3, triangleTable_37_4, triangleTable_37_5, triangleTable_37_6, triangleTable_37_7
};

static unsigned char triangleTable_38_0[11] =  { 9, 0, 2, 10, 5, 4, 2, 5, 4, 0, 2 };
static unsigned char * triangleTable_38[1] = { triangleTable_38_0 };

static unsigned char triangleTable_39_0[14] =  { 12, 0, 3, 5, 8, 3, 10, 5, 2, 10, 3, 8, 5, 4 };
static unsigned char * triangleTable_39[1] = { triangleTable_39_0 };

static unsigned char triangleTable_40_0[8] =  { 6, 0, 4, 9, 5, 11, 2, 3 };
static unsigned char triangleTable_40_1[20] =  { 18, 0, 3, 4, 9, 3, 9, 2, 4, 11, 5, 2, 9, 5, 2, 5, 11, 11, 4, 3 };
static unsigned char * triangleTable_40[2] = { triangleTable_40_0, triangleTable_40_1 };

static unsigned char triangleTable_41_0[11] =  { 9, 0, 5, 4, 9, 11, 0, 8, 11, 2, 0 };
static unsigned char triangleTable_41_1[17] =  { 15, 0, 11, 5, 4, 9, 2, 0, 11, 2, 5, 8, 11, 4, 5, 2, 9 };
static unsigned char * triangleTable_41[2] = { triangleTable_41_0, triangleTable_41_1 };

static unsigned char triangleTable_42_0[11] =  { 9, 0, 11, 2, 3, 5, 0, 1, 5, 4, 0 };
static unsigned char triangleTable_42_1[17] =  { 15, 0, 5, 11, 2, 3, 4, 0, 5, 4, 11, 1, 5, 2, 11, 4, 3 };
static unsigned char * triangleTable_42[2] = { triangleTable_42_0, triangleTable_42_1 };

static unsigned char triangleTable_43_0[14] =  { 12, 0, 1, 5, 2, 5, 4, 8, 5, 8, 11, 2, 5, 11 };
static unsigned char * triangleTable_43[1] = { triangleTable_43_0 };

static unsigned char triangleTable_44_0[11] =  { 9, 0, 4, 9, 5, 3, 10, 1, 3, 11, 10 };
static unsigned char triangleTable_44_1[17] =  { 15, 0, 3, 4, 9, 5, 11, 10, 3, 11, 4, 1, 3, 9, 4, 11, 5 };
static unsigned char * triangleTable_44[2] = { triangleTable_44_0, triangleTable_44_1 };

static unsigned char triangleTable_45_0[14] =  { 12, 0, 1, 0, 8, 10, 1, 8, 4, 9, 5, 10, 8, 11 };
static unsigned char triangleTable_45_1[14] =  { 12, 0, 5, 4, 8, 10, 5, 8, 0, 9, 1, 10, 8, 11 };
static unsigned char triangleTable_45_2[26] =  { 24, 1, 12, 4, 9, 11, 12, 8, 10, 5, 12, 0, 12, 1, 1, 12, 9, 12, 11, 10, 12, 0, 8, 4, 12, 5 };
static unsigned char triangleTable_45_3[26] =  { 24, 1, 12, 0, 9, 11, 12, 8, 10, 1, 12, 4, 12, 5, 5, 12, 9, 12, 11, 10, 12, 4, 8, 0, 12, 1 };
static unsigned char * triangleTable_45[4] = { triangleTable_45_0, triangleTable_45_1, triangleTable_45_2, triangleTable_45_3 };

static unsigned char triangleTable_46_0[14] =  { 12, 0, 5, 4, 10, 3, 11, 10, 4, 0, 3, 4, 3, 10 };
static unsigned char * triangleTable_46[1] = { triangleTable_46_0 };

static unsigned char triangleTable_47_0[11] =  { 9, 0, 5, 4, 8, 5, 8, 10, 8, 11, 10 };
static unsigned char * triangleTable_47[1] = { triangleTable_47_0 };

static unsigned char triangleTable_48_0[8] =  { 6, 0, 8, 9, 7, 5, 7, 9 };
static unsigned char * triangleTable_48[1] = { triangleTable_48_0 };

static unsigned char triangleTable_49_0[11] =  { 9, 0, 3, 0, 9, 5, 3, 9, 5, 7, 3 };
static unsigned char * triangleTable_49[1] = { triangleTable_49_0 };

static unsigned char triangleTable_50_0[11] =  { 9, 0, 7, 8, 0, 1, 7, 0, 1, 5, 7 };
static unsigned char * triangleTable_50[1] = { triangleTable_50_0 };

static unsigned char triangleTable_51_0[8] =  { 6, 0, 1, 5, 7, 7, 3, 1 };
static unsigned char * triangleTable_51[1] = { triangleTable_51_0 };

static unsigned char triangleTable_52_0[11] =  { 9, 0, 2, 10, 1, 7, 9, 5, 7, 8, 9 };
static unsigned char triangleTable_52_1[17] =  { 15, 0, 7, 2, 10, 1, 8, 9, 7, 8, 2, 5, 7, 10, 2, 8, 1 };
static unsigned char * triangleTable_52[2] = { triangleTable_52_0, triangleTable_52_1 };

static unsigned char triangleTable_53_0[14] =  { 12, 0, 0, 9, 5, 3, 0, 5, 10, 1, 2, 3, 5, 7 };
static unsigned char triangleTable_53_1[14] =  { 12, 0, 2, 10, 5, 3, 2, 5, 9, 1, 0, 3, 5, 7 };
static unsigned char triangleTable_53_2[26] =  { 24, 1, 12, 10, 1, 7, 12, 5, 3, 2, 12, 9, 12, 0, 0, 12, 1, 12, 7, 3, 12, 9, 5, 10, 12, 2 };
static unsigned char triangleTable_53_3[26] =  { 24, 1, 12, 9, 1, 7, 12, 5, 3, 0, 12, 10, 12, 2, 2, 12, 1, 12, 7, 3, 12, 10, 5, 9, 12, 0 };
static unsigned char * triangleTable_53[4] = { triangleTable_53_0, triangleTable_53_1, triangleTable_53_2, triangleTable_53_3 };

static unsigned char triangleTable_54_0[14] =  { 12, 0, 0, 2, 8, 2, 10, 5, 2, 5, 7, 8, 2, 7 };
static unsigned char * triangleTable_54[1] = { triangleTable_54_0 };

static unsigned char triangleTable_55_0[11] =  { 9, 0, 2, 10, 5, 2, 5, 3, 5, 7, 3 };
static unsigned char * triangleTable_55[1] = { triangleTable_55_0 };

static unsigned char triangleTable_56_0[11] =  { 9, 0, 2, 3, 11, 9, 7, 8, 9, 5, 7 };
static unsigned char triangleTable_56_1[17] =  { 15, 0, 9, 2, 3, 11, 5, 7, 9, 5, 2, 8, 9, 3, 2, 5, 11 };
static unsigned char * triangleTable_56[2] = { triangleTable_56_0, triangleTable_56_1 };

static unsigned char triangleTable_57_0[14] =  { 12, 0, 9, 5, 0, 11, 2, 0, 5, 7, 11, 5, 11, 0 };
static unsigned char * triangleTable_57[1] = { triangleTable_57_0 };

static unsigned char triangleTable_58_0[14] =  { 12, 0, 8, 0, 1, 7, 8, 1, 2, 3, 11, 7, 1, 5 };
static unsigned char triangleTable_58_1[14] =  { 12, 0, 11, 2, 1, 7, 11, 1, 0, 3, 8, 7, 1, 5 };
static unsigned char triangleTable_58_2[26] =  { 24, 1, 12, 2, 3, 5, 12, 1, 7, 11, 12, 0, 12, 8, 8, 12, 3, 12, 5, 7, 12, 0, 1, 2, 12, 11 };
static unsigned char triangleTable_58_3[26] =  { 24, 1, 12, 0, 3, 5, 12, 1, 7, 8, 12, 2, 12, 11, 11, 12, 3, 12, 5, 7, 12, 2, 1, 0, 12, 8 };
static unsigned char * triangleTable_58[4] = { triangleTable_58_0, triangleTable_58_1, triangleTable_58_2, triangleTable_58_3 };

static unsigned char triangleTable_59_0[11] =  { 9, 0, 11, 2, 1, 11, 1, 7, 1, 5, 7 };
static unsigned char * triangleTable_59[1] = { triangleTable_59_0 };

static unsigned char triangleTable_60_0[14] =  { 12, 0, 7, 8, 5, 11, 10, 3, 10, 1, 3, 8, 9, 5 };
static unsigned char triangleTable_60_1[14] =  { 12, 0, 9, 3, 8, 11, 5, 7, 11, 10, 5, 9, 1, 3 };
static unsigned char triangleTable_60_2[26] =  { 24, 0, 7, 11, 5, 1, 8, 9, 1, 9, 5, 10, 5, 11, 8, 1, 3, 11, 8, 3, 1, 5, 10, 8, 11, 7 };
static unsigned char triangleTable_60_3[26] =  { 24, 1, 12, 11, 10, 8, 12, 7, 12, 8, 9, 12, 3, 11, 10, 5, 12, 7, 12, 5, 9, 1, 12, 12, 1, 3 };
static unsigned char triangleTable_60_4[26] =  { 24, 1, 12, 5, 7, 1, 12, 10, 12, 1, 3, 12, 9, 5, 7, 11, 12, 10, 12, 11, 3, 8, 12, 12, 8, 9 };
static unsigned char * triangleTable_60[5] = { triangleTable_60_0, triangleTable_60_1, triangleTable_60_2, triangleTable_60_3, triangleTable_60_4 };

static unsigned char triangleTable_61_0[11] =  { 9, 0, 9, 1, 0, 10, 5, 11, 5, 7, 11 };
static unsigned char triangleTable_61_1[17] =  { 15, 0, 1, 0, 11, 5, 7, 9, 0, 7, 11, 1, 11, 10, 9, 7, 0 };
static unsigned char * triangleTable_61[2] = { triangleTable_61_0, triangleTable_61_1 };

static unsigned char triangleTable_62_0[11] =  { 9, 0, 3, 8, 0, 7, 11, 5, 11, 10, 5 };
static unsigned char triangleTable_62_1[17] =  { 15, 0, 8, 0, 5, 11, 10, 3, 0, 10, 5, 8, 5, 7, 3, 10, 0 };
static unsigned char * triangleTable_62[2] = { triangleTable_62_0, triangleTable_62_1 };

static unsigned char triangleTable_63_0[8] =  { 6, 0, 11, 5, 7, 5, 11, 10 };
static unsigned char * triangleTable_63[1] = { triangleTable_63_0 };

static unsigned char triangleTable_64_0[5] =  { 3, 0, 6, 5, 10 };
static unsigned char * triangleTable_64[1] = { triangleTable_64_0 };

static unsigned char triangleTable_65_0[8] =  { 6, 0, 6, 5, 10, 3, 0, 8 };
static unsigned char triangleTable_65_1[20] =  { 18, 0, 8, 6, 5, 8, 5, 0, 6, 3, 10, 0, 5, 10, 0, 10, 3, 3, 6, 8 };
static unsigned char * triangleTable_65[2] = { triangleTable_65_0, triangleTable_65_1 };

static unsigned char triangleTable_66_0[8] =  { 6, 0, 5, 10, 6, 0, 1, 9 };
static unsigned char triangleTable_66_1[14] =  { 12, 0, 0, 1, 6, 6, 5, 9, 9, 0, 6, 10, 6, 1 };
static unsigned char * triangleTable_66[2] = { triangleTable_66_0, triangleTable_66_1 };

static unsigned char triangleTable_67_0[11] =  { 9, 0, 6, 5, 10, 8, 1, 9, 8, 3, 1 };
static unsigned char triangleTable_67_1[17] =  { 15, 0, 8, 6, 5, 10, 3, 1, 8, 3, 6, 9, 8, 5, 6, 3, 10 };
static unsigned char * triangleTable_67[2] = { triangleTable_67_0, triangleTable_67_1 };

static unsigned char triangleTable_68_0[8] =  { 6, 0, 5, 1, 6, 2, 6, 1 };
static unsigned char * triangleTable_68[1] = { triangleTable_68_0 };

static unsigned char triangleTable_69_0[11] =  { 9, 0, 8, 3, 0, 6, 1, 2, 6, 5, 1 };
static unsigned char triangleTable_69_1[17] =  { 15, 0, 6, 8, 3, 0, 5, 1, 6, 5, 8, 2, 6, 3, 8, 5, 0 };
static unsigned char * triangleTable_69[2] = { triangleTable_69_0, triangleTable_69_1 };

static unsigned char triangleTable_70_0[11] =  { 9, 0, 6, 5, 9, 0, 6, 9, 0, 2, 6 };
static unsigned char * triangleTable_70[1] = { triangleTable_70_0 };

static unsigned char triangleTable_71_0[14] =  { 12, 0, 2, 6, 3, 6, 5, 9, 6, 9, 8, 3, 6, 8 };
static unsigned char * triangleTable_71[1] = { triangleTable_71_0 };

static unsigned char triangleTable_72_0[8] =  { 6, 0, 10, 6, 5, 3, 11, 2 };
static unsigned char triangleTable_72_1[14] =  { 12, 0, 3, 11, 5, 5, 10, 2, 2, 3, 5, 6, 5, 11 };
static unsigned char * triangleTable_72[2] = { triangleTable_72_0, triangleTable_72_1 };

static unsigned char triangleTable_73_0[11] =  { 9, 0, 5, 10, 6, 0, 11, 2, 0, 8, 11 };
static unsigned char triangleTable_73_1[17] =  { 15, 0, 0, 5, 10, 6, 8, 11, 0, 8, 5, 2, 0, 10, 5, 8, 6 };
static unsigned char * triangleTable_73[2] = { triangleTable_73_0, triangleTable_73_1 };

static unsigned char triangleTable_74_0[11] =  { 9, 0, 10, 6, 5, 1, 9, 0, 3, 11, 2 };
static unsigned char triangleTable_74_1[17] =  { 15, 0, 10, 6, 5, 0, 3, 11, 9, 0, 11, 2, 9, 11, 9, 2, 1 };
static unsigned char triangleTable_74_2[17] =  { 15, 0, 2, 3, 11, 5, 9, 0, 6, 5, 0, 1, 6, 0, 6, 1, 10 };
static unsigned char triangleTable_74_3[17] =  { 15, 0, 1, 9, 0, 11, 6, 5, 3, 11, 5, 10, 3, 5, 3, 10, 2 };
static unsigned char triangleTable_74_4[29] =  { 27, 1, 12, 10, 6, 12, 1, 10, 9, 12, 5, 1, 12, 2, 12, 3, 11, 12, 9, 0, 2, 12, 11, 5, 12, 6, 0, 3, 12 };
static unsigned char triangleTable_74_5[29] =  { 27, 1, 12, 1, 9, 12, 2, 1, 3, 12, 0, 2, 12, 10, 12, 6, 5, 12, 3, 11, 10, 12, 5, 0, 12, 9, 11, 6, 12 };
static unsigned char triangleTable_74_6[29] =  { 27, 1, 12, 2, 3, 12, 10, 2, 6, 12, 11, 10, 12, 1, 12, 9, 0, 12, 6, 5, 1, 12, 0, 11, 12, 3, 5, 9, 12 };
static unsigned char triangleTable_74_7[17] =  { 15, 0, 9, 0, 3, 11, 6, 3, 1, 10, 2, 6, 9, 3, 9, 6, 5 };
static unsigned char * triangleTable_74[8] = 
{ 
  triangleTable_74_0, triangleTable_74_1, triangleTable_74_2, triangleTable_74_3, triangleTable_74_4, triangleTable_74_5, triangleTable_74_6, triangleTable_74_7
};

static unsigned char triangleTable_75_0[14] =  { 12, 0, 2, 1, 9, 11, 2, 9, 5, 10, 6, 11, 9, 8 };
static unsigned char triangleTable_75_1[14] =  { 12, 0, 6, 5, 9, 11, 6, 9, 1, 10, 2, 11, 9, 8 };
static unsigned char triangleTable_75_2[26] =  { 24, 1, 12, 5, 10, 8, 12, 9, 11, 6, 12, 1, 12, 2, 2, 12, 10, 12, 8, 11, 12, 1, 9, 5, 12, 6 };
static unsigned char triangleTable_75_3[26] =  { 24, 1, 12, 1, 10, 8, 12, 9, 11, 2, 12, 5, 12, 6, 6, 12, 10, 12, 8, 11, 12, 5, 9, 1, 12, 2 };
static unsigned char * triangleTable_75[4] = { triangleTable_75_0, triangleTable_75_1, triangleTable_75_2, triangleTable_75_3 };

static unsigned char triangleTable_76_0[11] =  { 9, 0, 3, 11, 6, 5, 3, 6, 5, 1, 3 };
static unsigned char * triangleTable_76[1] = { triangleTable_76_0 };

static unsigned char triangleTable_77_0[14] =  { 12, 0, 0, 8, 1, 6, 5, 1, 8, 11, 6, 8, 6, 1 };
static unsigned char * triangleTable_77[1] = { triangleTable_77_0 };

static unsigned char triangleTable_78_0[14] =  { 12, 0, 11, 9, 3, 11, 5, 9, 6, 5, 11, 3, 9, 0 };
static unsigned char * triangleTable_78[1] = { triangleTable_78_0 };

static unsigned char triangleTable_79_0[11] =  { 9, 0, 6, 5, 9, 6, 9, 11, 9, 8, 11 };
static unsigned char * triangleTable_79[1] = { triangleTable_79_0 };

static unsigned char triangleTable_80_0[8] =  { 6, 0, 6, 5, 10, 8, 4, 7 };
static unsigned char triangleTable_80_1[14] =  { 12, 0, 8, 4, 10, 10, 6, 7, 7, 8, 10, 5, 10, 4 };
static unsigned char * triangleTable_80[2] = { triangleTable_80_0, triangleTable_80_1 };

static unsigned char triangleTable_81_0[11] =  { 9, 0, 10, 6, 5, 3, 4, 7, 3, 0, 4 };
static unsigned char triangleTable_81_1[17] =  { 15, 0, 3, 10, 6, 5, 0, 4, 3, 0, 10, 7, 3, 6, 10, 0, 5 };
static unsigned char * triangleTable_81[2] = { triangleTable_81_0, triangleTable_81_1 };

static unsigned char triangleTable_82_0[11] =  { 9, 0, 5, 10, 6, 4, 7, 8, 0, 1, 9 };
static unsigned char triangleTable_82_1[17] =  { 15, 0, 5, 10, 6, 8, 0, 1, 7, 8, 1, 9, 7, 1, 7, 9, 4 };
static unsigned char triangleTable_82_2[17] =  { 15, 0, 9, 0, 1, 6, 7, 8, 10, 6, 8, 4, 10, 8, 10, 4, 5 };
static unsigned char triangleTable_82_3[17] =  { 15, 0, 4, 7, 8, 1, 10, 6, 0, 1, 6, 5, 0, 6, 0, 5, 9 };
static unsigned char triangleTable_82_4[29] =  { 27, 1, 12, 5, 10, 12, 4, 5, 7, 12, 6, 4, 12, 9, 12, 0, 1, 12, 7, 8, 9, 12, 1, 6, 12, 10, 8, 0, 12 };
static unsigned char triangleTable_82_5[29] =  { 27, 1, 12, 4, 7, 12, 9, 4, 0, 12, 8, 9, 12, 5, 12, 10, 6, 12, 0, 1, 5, 12, 6, 8, 12, 7, 1, 10, 12 };
static unsigned char triangleTable_82_6[29] =  { 27, 1, 12, 9, 0, 12, 5, 9, 10, 12, 1, 5, 12, 4, 12, 7, 8, 12, 10, 6, 4, 12, 8, 1, 12, 0, 6, 7, 12 };
static unsigned char triangleTable_82_7[17] =  { 15, 0, 7, 8, 0, 1, 10, 0, 4, 5, 9, 10, 7, 0, 7, 10, 6 };
static unsigned char * triangleTable_82[8] = 
{ 
  triangleTable_82_0, triangleTable_82_1, triangleTable_82_2, triangleTable_82_3, triangleTable_82_4, triangleTable_82_5, triangleTable_82_6, triangleTable_82_7
};

static unsigned char triangleTable_83_0[14] =  { 12, 0, 9, 4, 7, 1, 9, 7, 6, 5, 10, 1, 7, 3 };
static unsigned char triangleTable_83_1[14] =  { 12, 0, 10, 6, 7, 1, 10, 7, 4, 5, 9, 1, 7, 3 };
static unsigned char triangleTable_83_2[26] =  { 24, 1, 12, 6, 5, 3, 12, 7, 1, 10, 12, 4, 12, 9, 9, 12, 5, 12, 3, 1, 12, 4, 7, 6, 12, 10 };
static unsigned char triangleTable_83_3[26] =  { 24, 1, 12, 4, 5, 3, 12, 7, 1, 9, 12, 6, 12, 10, 10, 12, 5, 12, 3, 1, 12, 6, 7, 4, 12, 9 };
static unsigned char * triangleTable_83[4] = { triangleTable_83_0, triangleTable_83_1, triangleTable_83_2, triangleTable_83_3 };

static unsigned char triangleTable_84_0[11] =  { 9, 0, 8, 4, 7, 1, 6, 5, 1, 2, 6 };
static unsigned char triangleTable_84_1[17] =  { 15, 0, 1, 8, 4, 7, 2, 6, 1, 2, 8, 5, 1, 4, 8, 2, 7 };
static unsigned char * triangleTable_84[2] = { triangleTable_84_0, triangleTable_84_1 };

static unsigned char triangleTable_85_0[14] =  { 12, 0, 6, 5, 2, 7, 3, 4, 3, 0, 4, 5, 1, 2 };
static unsigned char triangleTable_85_1[14] =  { 12, 0, 1, 4, 5, 7, 2, 6, 7, 3, 2, 1, 0, 4 };
static unsigned char triangleTable_85_2[26] =  { 24, 0, 6, 7, 2, 0, 5, 1, 0, 1, 2, 3, 2, 7, 5, 0, 4, 7, 5, 4, 0, 2, 3, 5, 7, 6 };
static unsigned char triangleTable_85_3[26] =  { 24, 1, 12, 7, 3, 5, 12, 6, 12, 5, 1, 12, 4, 7, 3, 2, 12, 6, 12, 2, 1, 0, 12, 12, 0, 4 };
static unsigned char triangleTable_85_4[26] =  { 24, 1, 12, 2, 6, 0, 12, 3, 12, 0, 4, 12, 1, 2, 6, 7, 12, 3, 12, 7, 4, 5, 12, 12, 5, 1 };
static unsigned char * triangleTable_85[5] = { triangleTable_85_0, triangleTable_85_1, triangleTable_85_2, triangleTable_85_3, triangleTable_85_4 };

static unsigned char triangleTable_86_0[14] =  { 12, 0, 5, 9, 0, 6, 5, 0, 8, 4, 7, 6, 0, 2 };
static unsigned char triangleTable_86_1[14] =  { 12, 0, 7, 8, 0, 6, 7, 0, 9, 4, 5, 6, 0, 2 };
static unsigned char triangleTable_86_2[26] =  { 24, 1, 12, 8, 4, 2, 12, 0, 6, 7, 12, 9, 12, 5, 5, 12, 4, 12, 2, 6, 12, 9, 0, 8, 12, 7 };
static unsigned char triangleTable_86_3[26] =  { 24, 1, 12, 9, 4, 2, 12, 0, 6, 5, 12, 8, 12, 7, 7, 12, 4, 12, 2, 6, 12, 8, 0, 9, 12, 5 };
static unsigned char * triangleTable_86[4] = { triangleTable_86_0, triangleTable_86_1, triangleTable_86_2, triangleTable_86_3 };

static unsigned char triangleTable_87_0[11] =  { 9, 0, 4, 5, 9, 6, 7, 2, 7, 3, 2 };
static unsigned char triangleTable_87_1[17] =  { 15, 0, 5, 9, 2, 7, 3, 4, 9, 3, 2, 5, 2, 6, 4, 3, 9 };
static unsigned char * triangleTable_87[2] = { triangleTable_87_0, triangleTable_87_1 };

static unsigned char triangleTable_88_0[11] =  { 9, 0, 11, 2, 3, 7, 8, 4, 5, 10, 6 };
static unsigned char triangleTable_88_1[17] =  { 15, 0, 11, 2, 3, 4, 5, 10, 8, 4, 10, 6, 8, 10, 8, 6, 7 };
static unsigned char triangleTable_88_2[17] =  { 15, 0, 6, 5, 10, 3, 8, 4, 2, 3, 4, 7, 2, 4, 2, 7, 11 };
static unsigned char triangleTable_88_3[17] =  { 15, 0, 7, 8, 4, 10, 2, 3, 5, 10, 3, 11, 5, 3, 5, 11, 6 };
static unsigned char triangleTable_88_4[29] =  { 27, 1, 12, 11, 2, 12, 7, 11, 8, 12, 3, 7, 12, 6, 12, 5, 10, 12, 8, 4, 6, 12, 10, 3, 12, 2, 4, 5, 12 };
static unsigned char triangleTable_88_5[29] =  { 27, 1, 12, 7, 8, 12, 6, 7, 5, 12, 4, 6, 12, 11, 12, 2, 3, 12, 5, 10, 11, 12, 3, 4, 12, 8, 10, 2, 12 };
static unsigned char triangleTable_88_6[29] =  { 27, 1, 12, 6, 5, 12, 11, 6, 2, 12, 10, 11, 12, 7, 12, 8, 4, 12, 2, 3, 7, 12, 4, 10, 12, 5, 3, 8, 12 };
static unsigned char triangleTable_88_7[17] =  { 15, 0, 8, 4, 5, 10, 2, 5, 7, 11, 6, 2, 8, 5, 8, 2, 3 };
static unsigned char * triangleTable_88[8] = 
{ 
  triangleTable_88_0, triangleTable_88_1, triangleTable_88_2, triangleTable_88_3, triangleTable_88_4, triangleTable_88_5, triangleTable_88_6, triangleTable_88_7
};

static unsigned char triangleTable_89_0[14] =  { 12, 0, 7, 11, 2, 4, 7, 2, 10, 6, 5, 4, 2, 0 };
static unsigned char triangleTable_89_1[14] =  { 12, 0, 5, 10, 2, 4, 5, 2, 11, 6, 7, 4, 2, 0 };
static unsigned char triangleTable_89_2[26] =  { 24, 1, 12, 10, 6, 0, 12, 2, 4, 5, 12, 11, 12, 7, 7, 12, 6, 12, 0, 4, 12, 11, 2, 10, 12, 5 };
static unsigned char triangleTable_89_3[26] =  { 24, 1, 12, 11, 6, 0, 12, 2, 4, 7, 12, 10, 12, 5, 5, 12, 6, 12, 0, 4, 12, 10, 2, 11, 12, 7 };
static unsigned char * triangleTable_89[4] = { triangleTable_89_0, triangleTable_89_1, triangleTable_89_2, triangleTable_89_3 };

static unsigned char triangleTable_90_0[14] =  { 12, 0, 11, 2, 3, 4, 7, 8, 1, 9, 0, 6, 5, 10 };
static unsigned char triangleTable_90_1[20] =  { 18, 0, 2, 3, 11, 8, 4, 7, 6, 5, 0, 1, 10, 6, 5, 9, 0, 6, 0, 1 };
static unsigned char triangleTable_90_2[20] =  { 18, 0, 7, 8, 4, 0, 1, 9, 5, 10, 3, 11, 6, 5, 10, 2, 3, 5, 3, 11 };
static unsigned char triangleTable_90_3[20] =  { 18, 0, 0, 1, 9, 10, 6, 5, 4, 7, 2, 3, 8, 4, 7, 11, 2, 4, 2, 3 };
static unsigned char triangleTable_90_4[20] =  { 18, 0, 5, 10, 6, 2, 3, 11, 7, 8, 1, 9, 4, 7, 8, 0, 1, 7, 1, 9 };
static unsigned char triangleTable_90_5[20] =  { 18, 0, 8, 4, 7, 5, 10, 6, 11, 2, 9, 0, 3, 11, 2, 1, 9, 11, 9, 0 };
static unsigned char triangleTable_90_6[20] =  { 18, 0, 9, 0, 1, 3, 11, 2, 10, 6, 8, 4, 5, 10, 6, 7, 8, 10, 8, 4 };
static unsigned char triangleTable_90_7[32] =  { 30, 1, 5, 12, 6, 12, 3, 11, 2, 12, 10, 12, 2, 3, 12, 9, 0, 6, 12, 11, 10, 12, 1, 7, 8, 4, 0, 1, 12, 9, 12, 5 };
static unsigned char triangleTable_90_8[32] =  { 30, 1, 1, 12, 0, 12, 7, 8, 4, 12, 9, 12, 4, 7, 12, 10, 6, 0, 12, 8, 9, 12, 5, 3, 11, 2, 6, 5, 12, 10, 12, 1 };
static unsigned char triangleTable_90_9[32] =  { 30, 1, 0, 12, 9, 3, 11, 12, 1, 12, 2, 11, 2, 12, 6, 5, 12, 3, 12, 0, 10, 12, 1, 4, 7, 8, 12, 10, 6, 9, 12, 5 };
static unsigned char triangleTable_90_10[32] =  { 30, 1, 6, 12, 10, 7, 8, 12, 5, 12, 4, 8, 4, 12, 0, 1, 12, 7, 12, 6, 9, 12, 5, 2, 3, 11, 12, 9, 0, 10, 12, 1 };
static unsigned char triangleTable_90_11[32] =  { 30, 1, 3, 12, 2, 8, 4, 12, 11, 12, 7, 4, 7, 12, 5, 10, 12, 8, 12, 3, 6, 12, 11, 1, 9, 0, 12, 6, 5, 2, 12, 10 };
static unsigned char triangleTable_90_12[32] =  { 30, 1, 11, 12, 3, 12, 9, 0, 1, 12, 2, 12, 1, 9, 12, 6, 5, 3, 12, 0, 2, 12, 10, 8, 4, 7, 5, 10, 12, 6, 12, 11 };
static unsigned char triangleTable_90_13[32] =  { 30, 1, 10, 12, 5, 2, 3, 12, 6, 12, 11, 3, 11, 12, 8, 4, 12, 2, 12, 10, 7, 12, 6, 9, 0, 1, 12, 7, 8, 5, 12, 4 };
static unsigned char triangleTable_90_14[32] =  { 30, 1, 7, 12, 4, 12, 1, 9, 0, 12, 8, 12, 0, 1, 12, 11, 2, 4, 12, 9, 8, 12, 3, 5, 10, 6, 2, 3, 12, 11, 12, 7 };
static unsigned char triangleTable_90_15[32] =  { 30, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
static unsigned char triangleTable_90_16[32] =  { 30, 1, 4, 12, 8, 12, 2, 3, 11, 12, 7, 12, 11, 2, 12, 5, 10, 8, 12, 3, 7, 12, 6, 0, 1, 9, 10, 6, 12, 5, 12, 4 };
static unsigned char triangleTable_90_17[32] =  { 30, 1, 9, 12, 1, 4, 7, 12, 0, 12, 8, 7, 8, 12, 11, 2, 12, 4, 12, 9, 3, 12, 0, 10, 6, 5, 12, 3, 11, 1, 12, 2 };
static unsigned char triangleTable_90_18[32] =  { 30, 1, 8, 12, 7, 12, 10, 6, 5, 12, 4, 12, 5, 10, 12, 0, 1, 7, 12, 6, 4, 12, 9, 11, 2, 3, 1, 9, 12, 0, 12, 8 };
static unsigned char triangleTable_90_19[38] =  { 36, 1, 12, 5, 9, 11, 6, 12, 1, 12, 0, 5, 12, 4, 3, 12, 2, 12, 1, 10, 2, 12, 10, 12, 8, 4, 9, 0, 12, 7, 12, 6, 3, 11, 12, 7, 8, 12 };
static unsigned char triangleTable_90_20[38] =  { 36, 1, 12, 1, 10, 8, 0, 12, 5, 12, 6, 1, 12, 2, 7, 12, 4, 12, 5, 9, 4, 12, 9, 12, 11, 2, 10, 6, 12, 3, 12, 0, 7, 8, 12, 3, 11, 12 };
static unsigned char triangleTable_90_21[38] =  { 36, 1, 12, 11, 6, 0, 3, 12, 10, 12, 5, 11, 12, 7, 9, 12, 1, 12, 10, 2, 1, 12, 2, 12, 4, 7, 6, 5, 12, 8, 12, 3, 9, 0, 12, 8, 4, 12 };
static unsigned char triangleTable_90_22[38] =  { 36, 1, 12, 7, 11, 9, 4, 12, 3, 12, 2, 7, 12, 6, 1, 12, 0, 12, 3, 8, 0, 12, 8, 12, 10, 6, 11, 2, 12, 5, 12, 4, 1, 9, 12, 5, 10, 12 };
static unsigned char triangleTable_90_23[32] =  { 30, 1, 1, 12, 2, 12, 7, 11, 6, 12, 10, 12, 6, 7, 12, 9, 4, 2, 12, 11, 10, 12, 5, 3, 8, 0, 4, 5, 12, 9, 12, 1 };
static unsigned char triangleTable_90_24[32] =  { 30, 1, 5, 12, 4, 12, 3, 8, 0, 12, 9, 12, 0, 3, 12, 10, 2, 4, 12, 8, 9, 12, 1, 7, 11, 6, 2, 1, 12, 10, 12, 5 };
static unsigned char triangleTable_90_25[32] =  { 30, 1, 2, 12, 10, 3, 8, 12, 1, 12, 0, 8, 0, 12, 4, 5, 12, 3, 12, 2, 9, 12, 1, 6, 7, 11, 12, 9, 4, 10, 12, 5 };
static unsigned char triangleTable_90_26[32] =  { 30, 1, 4, 12, 9, 7, 11, 12, 5, 12, 6, 11, 6, 12, 2, 1, 12, 7, 12, 4, 10, 12, 5, 0, 3, 8, 12, 10, 2, 9, 12, 1 };
static unsigned char triangleTable_90_27[32] =  { 30, 1, 7, 12, 6, 8, 0, 12, 11, 12, 3, 0, 3, 12, 1, 10, 12, 8, 12, 7, 2, 12, 11, 5, 9, 4, 12, 2, 1, 6, 12, 10 };
static unsigned char triangleTable_90_28[32] =  { 30, 1, 10, 12, 1, 12, 8, 0, 3, 12, 2, 12, 3, 8, 12, 6, 7, 1, 12, 0, 2, 12, 11, 9, 4, 5, 7, 11, 12, 6, 12, 10 };
static unsigned char triangleTable_90_29[32] =  { 30, 1, 11, 12, 7, 2, 1, 12, 6, 12, 10, 1, 10, 12, 9, 4, 12, 2, 12, 11, 5, 12, 6, 8, 0, 3, 12, 5, 9, 7, 12, 4 };
static unsigned char triangleTable_90_30[32] =  { 30, 1, 3, 12, 0, 12, 5, 9, 4, 12, 8, 12, 4, 5, 12, 11, 6, 0, 12, 9, 8, 12, 7, 1, 10, 2, 6, 7, 12, 11, 12, 3 };
static unsigned char triangleTable_90_31[32] =  { 30, 1, 2, 12, 11, 1, 9, 12, 3, 12, 0, 9, 0, 12, 4, 7, 12, 1, 12, 2, 8, 12, 3, 6, 5, 10, 12, 8, 4, 11, 12, 7 };
static unsigned char triangleTable_90_32[32] =  { 30, 1, 6, 12, 11, 12, 0, 3, 8, 12, 7, 12, 8, 0, 12, 5, 9, 11, 12, 3, 7, 12, 4, 2, 1, 10, 9, 4, 12, 5, 12, 6 };
static unsigned char triangleTable_90_33[32] =  { 30, 1, 8, 12, 3, 4, 5, 12, 0, 12, 9, 5, 9, 12, 10, 2, 12, 4, 12, 8, 1, 12, 0, 11, 6, 7, 12, 1, 10, 3, 12, 2 };
static unsigned char triangleTable_90_34[32] =  { 30, 1, 9, 12, 5, 12, 11, 6, 7, 12, 4, 12, 7, 11, 12, 0, 3, 5, 12, 6, 4, 12, 8, 10, 2, 1, 3, 8, 12, 0, 12, 9 };
static unsigned char triangleTable_90_35[20] =  { 18, 0, 7, 11, 6, 8, 0, 3, 2, 9, 4, 4, 5, 10, 2, 1, 9, 10, 2, 4 };
static unsigned char triangleTable_90_36[20] =  { 18, 0, 9, 4, 5, 0, 3, 8, 7, 2, 1, 1, 10, 6, 7, 11, 2, 6, 7, 1 };
static unsigned char triangleTable_90_37[20] =  { 18, 0, 5, 9, 4, 10, 2, 1, 0, 11, 6, 6, 7, 8, 0, 3, 11, 8, 0, 6 };
static unsigned char triangleTable_90_38[20] =  { 18, 0, 11, 6, 7, 2, 1, 10, 5, 0, 3, 3, 8, 4, 5, 9, 0, 4, 5, 3 };
static unsigned char triangleTable_90_39[20] =  { 18, 0, 6, 7, 11, 5, 9, 4, 8, 1, 10, 10, 2, 3, 8, 0, 1, 3, 8, 10 };
static unsigned char triangleTable_90_40[20] =  { 18, 0, 2, 1, 10, 3, 8, 0, 9, 7, 11, 11, 6, 5, 9, 4, 7, 5, 9, 11 };
static unsigned char triangleTable_90_41[14] =  { 12, 0, 0, 3, 8, 9, 4, 5, 1, 10, 2, 11, 6, 7 };
static unsigned char triangleTable_90_42[20] =  { 18, 0, 3, 11, 5, 5, 9, 3, 2, 1, 10, 3, 9, 0, 7, 8, 4, 5, 11, 6 };
static unsigned char triangleTable_90_43[20] =  { 18, 0, 7, 8, 1, 1, 10, 7, 4, 5, 9, 7, 10, 6, 3, 11, 2, 1, 8, 0 };
static unsigned char triangleTable_90_44[20] =  { 18, 0, 5, 10, 3, 3, 8, 5, 6, 7, 11, 5, 8, 4, 1, 9, 0, 3, 10, 2 };
static unsigned char triangleTable_90_45[20] =  { 18, 0, 1, 9, 7, 7, 11, 1, 0, 3, 8, 1, 11, 2, 5, 10, 6, 7, 9, 4 };
static unsigned char * triangleTable_90[46] = 
{ 
  triangleTable_90_0, triangleTable_90_1, triangleTable_90_2, triangleTable_90_3, triangleTable_90_4, triangleTable_90_5, triangleTable_90_6, triangleTable_90_7, 
  triangleTable_90_8, triangleTable_90_9, triangleTable_90_10, triangleTable_90_11, triangleTable_90_12, triangleTable_90_13, triangleTable_90_14, triangleTable_90_15, 
  triangleTable_90_16, triangleTable_90_17, triangleTable_90_18, triangleTable_90_19, triangleTable_90_20, triangleTable_90_21, triangleTable_90_22, triangleTable_90_23, 
  triangleTable_90_24, triangleTable_90_25, triangleTable_90_26, triangleTable_90_27, triangleTable_90_28, triangleTable_90_29, triangleTable_90_30, triangleTable_90_31, 
  triangleTable_90_32, triangleTable_90_33, triangleTable_90_34, triangleTable_90_35, triangleTable_90_36, triangleTable_90_37, triangleTable_90_38, triangleTable_90_39, 
  triangleTable_90_40, triangleTable_90_41, triangleTable_90_42, triangleTable_90_43, triangleTable_90_44, triangleTable_90_45
};

static unsigned char triangleTable_91_0[11] =  { 9, 0, 9, 4, 5, 2, 1, 10, 6, 7, 11 };
static unsigned char triangleTable_91_1[17] =  { 15, 0, 9, 4, 5, 7, 11, 2, 7, 2, 1, 7, 1, 6, 10, 6, 1 };
static unsigned char triangleTable_91_2[17] =  { 15, 0, 7, 11, 6, 2, 1, 9, 2, 9, 4, 2, 4, 10, 5, 10, 4 };
static unsigned char triangleTable_91_3[17] =  { 15, 0, 2, 1, 10, 9, 4, 7, 9, 7, 11, 9, 11, 5, 6, 5, 11 };
static unsigned char triangleTable_91_4[29] =  { 27, 1, 4, 5, 12, 5, 10, 12, 9, 12, 1, 6, 12, 10, 7, 11, 12, 2, 1, 12, 7, 12, 6, 4, 12, 9, 12, 11, 2 };
static unsigned char triangleTable_91_5[29] =  { 27, 1, 1, 10, 12, 10, 6, 12, 2, 12, 11, 5, 12, 6, 9, 4, 12, 7, 11, 12, 9, 12, 5, 1, 12, 2, 12, 4, 7 };
static unsigned char triangleTable_91_6[29] =  { 27, 1, 11, 6, 12, 6, 5, 12, 7, 12, 4, 10, 12, 5, 2, 1, 12, 9, 4, 12, 2, 12, 10, 11, 12, 7, 12, 1, 9 };
static unsigned char triangleTable_91_7[17] =  { 15, 0, 11, 2, 1, 11, 4, 7, 6, 5, 10, 11, 1, 4, 9, 4, 1 };
static unsigned char * triangleTable_91[8] = 
{ 
  triangleTable_91_0, triangleTable_91_1, triangleTable_91_2, triangleTable_91_3, triangleTable_91_4, triangleTable_91_5, triangleTable_91_6, triangleTable_91_7
};

static unsigned char triangleTable_92_0[14] =  { 12, 0, 11, 6, 5, 3, 11, 5, 4, 7, 8, 3, 5, 1 };
static unsigned char triangleTable_92_1[14] =  { 12, 0, 8, 4, 5, 3, 8, 5, 6, 7, 11, 3, 5, 1 };
static unsigned char triangleTable_92_2[26] =  { 24, 1, 12, 4, 7, 1, 12, 5, 3, 8, 12, 6, 12, 11, 11, 12, 7, 12, 1, 3, 12, 6, 5, 4, 12, 8 };
static unsigned char triangleTable_92_3[26] =  { 24, 1, 12, 6, 7, 1, 12, 5, 3, 11, 12, 4, 12, 8, 8, 12, 7, 12, 1, 3, 12, 4, 5, 6, 12, 11 };
static unsigned char * triangleTable_92[4] = { triangleTable_92_0, triangleTable_92_1, triangleTable_92_2, triangleTable_92_3 };

static unsigned char triangleTable_93_0[11] =  { 9, 0, 6, 7, 11, 4, 5, 0, 5, 1, 0 };
static unsigned char triangleTable_93_1[17] =  { 15, 0, 7, 11, 0, 5, 1, 6, 11, 1, 0, 7, 0, 4, 6, 1, 11 };
static unsigned char * triangleTable_93[2] = { triangleTable_93_0, triangleTable_93_1 };

static unsigned char triangleTable_94_0[11] =  { 9, 0, 11, 6, 7, 0, 3, 8, 4, 5, 9 };
static unsigned char triangleTable_94_1[17] =  { 15, 0, 11, 6, 7, 5, 9, 0, 5, 0, 3, 5, 3, 4, 8, 4, 3 };
static unsigned char triangleTable_94_2[17] =  { 15, 0, 5, 9, 4, 0, 3, 11, 0, 11, 6, 0, 6, 8, 7, 8, 6 };
static unsigned char triangleTable_94_3[17] =  { 15, 0, 0, 3, 8, 11, 6, 5, 11, 5, 9, 11, 9, 7, 4, 7, 9 };
static unsigned char triangleTable_94_4[29] =  { 27, 1, 6, 7, 12, 7, 8, 12, 11, 12, 3, 4, 12, 8, 5, 9, 12, 0, 3, 12, 5, 12, 4, 6, 12, 11, 12, 9, 0 };
static unsigned char triangleTable_94_5[29] =  { 27, 1, 3, 8, 12, 8, 4, 12, 0, 12, 9, 7, 12, 4, 11, 6, 12, 5, 9, 12, 11, 12, 7, 3, 12, 0, 12, 6, 5 };
static unsigned char triangleTable_94_6[29] =  { 27, 1, 9, 4, 12, 4, 7, 12, 5, 12, 6, 8, 12, 7, 0, 3, 12, 11, 6, 12, 0, 12, 8, 9, 12, 5, 12, 3, 11 };
static unsigned char triangleTable_94_7[17] =  { 15, 0, 9, 0, 3, 9, 6, 5, 4, 7, 8, 9, 3, 6, 11, 6, 3 };
static unsigned char * triangleTable_94[8] = 
{ 
  triangleTable_94_0, triangleTable_94_1, triangleTable_94_2, triangleTable_94_3, triangleTable_94_4, triangleTable_94_5, triangleTable_94_6, triangleTable_94_7
};

static unsigned char triangleTable_95_0[8] =  { 6, 0, 9, 4, 5, 6, 7, 11 };
static unsigned char triangleTable_95_1[14] =  { 12, 0, 9, 7, 11, 6, 5, 9, 9, 11, 6, 7, 9, 4 };
static unsigned char * triangleTable_95[2] = { triangleTable_95_0, triangleTable_95_1 };

static unsigned char triangleTable_96_0[8] =  { 6, 0, 6, 4, 10, 9, 10, 4 };
static unsigned char * triangleTable_96[1] = { triangleTable_96_0 };

static unsigned char triangleTable_97_0[11] =  { 9, 0, 3, 0, 8, 10, 4, 9, 10, 6, 4 };
static unsigned char triangleTable_97_1[17] =  { 15, 0, 10, 3, 0, 8, 6, 4, 10, 6, 3, 9, 10, 0, 3, 6, 8 };
static unsigned char * triangleTable_97[2] = { triangleTable_97_0, triangleTable_97_1 };

static unsigned char triangleTable_98_0[11] =  { 9, 0, 0, 1, 10, 6, 0, 10, 6, 4, 0 };
static unsigned char * triangleTable_98[1] = { triangleTable_98_0 };

static unsigned char triangleTable_99_0[14] =  { 12, 0, 8, 3, 4, 10, 6, 4, 3, 1, 10, 3, 10, 4 };
static unsigned char * triangleTable_99[1] = { triangleTable_99_0 };

static unsigned char triangleTable_100_0[11] =  { 9, 0, 4, 9, 1, 2, 4, 1, 2, 6, 4 };
static unsigned char * triangleTable_100[1] = { triangleTable_100_0 };

static unsigned char triangleTable_101_0[14] =  { 12, 0, 9, 1, 2, 4, 9, 2, 3, 0, 8, 4, 2, 6 };
static unsigned char triangleTable_101_1[14] =  { 12, 0, 8, 3, 2, 4, 8, 2, 1, 0, 9, 4, 2, 6 };
static unsigned char triangleTable_101_2[26] =  { 24, 1, 12, 3, 0, 6, 12, 2, 4, 8, 12, 1, 12, 9, 9, 12, 0, 12, 6, 4, 12, 1, 2, 3, 12, 8 };
static unsigned char triangleTable_101_3[26] =  { 24, 1, 12, 1, 0, 6, 12, 2, 4, 9, 12, 3, 12, 8, 8, 12, 0, 12, 6, 4, 12, 3, 2, 1, 12, 9 };
static unsigned char * triangleTable_101[4] = { triangleTable_101_0, triangleTable_101_1, triangleTable_101_2, triangleTable_101_3 };

static unsigned char triangleTable_102_0[8] =  { 6, 0, 6, 4, 0, 0, 2, 6 };
static unsigned char * triangleTable_102[1] = { triangleTable_102_0 };

static unsigned char triangleTable_103_0[11] =  { 9, 0, 8, 3, 2, 8, 2, 4, 2, 6, 4 };
static unsigned char * triangleTable_103[1] = { triangleTable_103_0 };

static unsigned char triangleTable_104_0[11] =  { 9, 0, 3, 11, 2, 4, 10, 6, 4, 9, 10 };
static unsigned char triangleTable_104_1[17] =  { 15, 0, 4, 3, 11, 2, 9, 10, 4, 9, 3, 6, 4, 11, 3, 9, 2 };
static unsigned char * triangleTable_104[2] = { triangleTable_104_0, triangleTable_104_1 };

static unsigned char triangleTable_105_0[14] =  { 12, 0, 10, 6, 9, 2, 0, 11, 0, 8, 11, 6, 4, 9 };
static unsigned char triangleTable_105_1[14] =  { 12, 0, 4, 11, 6, 2, 9, 10, 2, 0, 9, 4, 8, 11 };
static unsigned char triangleTable_105_2[26] =  { 24, 0, 10, 2, 9, 8, 6, 4, 8, 4, 9, 0, 9, 2, 6, 8, 11, 2, 6, 11, 8, 9, 0, 6, 2, 10 };
static unsigned char triangleTable_105_3[26] =  { 24, 1, 12, 2, 0, 6, 12, 10, 12, 6, 4, 12, 11, 2, 0, 9, 12, 10, 12, 9, 4, 8, 12, 12, 8, 11 };
static unsigned char triangleTable_105_4[26] =  { 24, 1, 12, 9, 10, 8, 12, 0, 12, 8, 11, 12, 4, 9, 10, 2, 12, 0, 12, 2, 11, 6, 12, 12, 6, 4 };
static unsigned char * triangleTable_105[5] = { triangleTable_105_0, triangleTable_105_1, triangleTable_105_2, triangleTable_105_3, triangleTable_105_4 };

static unsigned char triangleTable_106_0[14] =  { 12, 0, 1, 10, 6, 0, 1, 6, 11, 2, 3, 0, 6, 4 };
static unsigned char triangleTable_106_1[14] =  { 12, 0, 3, 11, 6, 0, 3, 6, 10, 2, 1, 0, 6, 4 };
static unsigned char triangleTable_106_2[26] =  { 24, 1, 12, 11, 2, 4, 12, 6, 0, 3, 12, 10, 12, 1, 1, 12, 2, 12, 4, 0, 12, 10, 6, 11, 12, 3 };
static unsigned char triangleTable_106_3[26] =  { 24, 1, 12, 10, 2, 4, 12, 6, 0, 1, 12, 11, 12, 3, 3, 12, 2, 12, 4, 0, 12, 11, 6, 10, 12, 1 };
static unsigned char * triangleTable_106[4] = { triangleTable_106_0, triangleTable_106_1, triangleTable_106_2, triangleTable_106_3 };

static unsigned char triangleTable_107_0[11] =  { 9, 0, 10, 2, 1, 11, 6, 8, 6, 4, 8 };
static unsigned char triangleTable_107_1[17] =  { 15, 0, 2, 1, 8, 6, 4, 10, 1, 4, 8, 2, 8, 11, 10, 4, 1 };
static unsigned char * triangleTable_107[2] = { triangleTable_107_0, triangleTable_107_1 };

static unsigned char triangleTable_108_0[14] =  { 12, 0, 6, 4, 11, 4, 9, 1, 4, 1, 3, 11, 4, 3 };
static unsigned char * triangleTable_108[1] = { triangleTable_108_0 };

static unsigned char triangleTable_109_0[11] =  { 9, 0, 0, 9, 1, 4, 8, 6, 8, 11, 6 };
static unsigned char triangleTable_109_1[17] =  { 15, 0, 9, 1, 6, 8, 11, 0, 1, 11, 6, 9, 6, 4, 0, 11, 1 };
static unsigned char * triangleTable_109[2] = { triangleTable_109_0, triangleTable_109_1 };

static unsigned char triangleTable_110_0[11] =  { 9, 0, 3, 11, 6, 3, 6, 0, 6, 4, 0 };
static unsigned char * triangleTable_110[1] = { triangleTable_110_0 };

static unsigned char triangleTable_111_0[8] =  { 6, 0, 8, 6, 4, 6, 8, 11 };
static unsigned char * triangleTable_111[1] = { triangleTable_111_0 };

static unsigned char triangleTable_112_0[11] =  { 9, 0, 10, 6, 7, 8, 10, 7, 8, 9, 10 };
static unsigned char * triangleTable_112[1] = { triangleTable_112_0 };

static unsigned char triangleTable_113_0[14] =  { 12, 0, 7, 3, 6, 3, 0, 9, 3, 9, 10, 6, 3, 10 };
static unsigned char * triangleTable_113[1] = { triangleTable_113_0 };

static unsigned char triangleTable_114_0[14] =  { 12, 0, 1, 7, 0, 1, 6, 7, 10, 6, 1, 0, 7, 8 };
static unsigned char * triangleTable_114[1] = { triangleTable_114_0 };

static unsigned char triangleTable_115_0[11] =  { 9, 0, 10, 6, 7, 10, 7, 1, 7, 3, 1 };
static unsigned char * triangleTable_115[1] = { triangleTable_115_0 };

static unsigned char triangleTable_116_0[14] =  { 12, 0, 1, 2, 9, 7, 8, 9, 2, 6, 7, 2, 7, 9 };
static unsigned char * triangleTable_116[1] = { triangleTable_116_0 };

static unsigned char triangleTable_117_0[11] =  { 9, 0, 1, 0, 9, 3, 2, 7, 2, 6, 7 };
static unsigned char triangleTable_117_1[17] =  { 15, 0, 0, 9, 7, 2, 6, 1, 9, 6, 7, 0, 7, 3, 1, 6, 9 };
static unsigned char * triangleTable_117[2] = { triangleTable_117_0, triangleTable_117_1 };

static unsigned char triangleTable_118_0[11] =  { 9, 0, 7, 8, 0, 7, 0, 6, 0, 2, 6 };
static unsigned char * triangleTable_118[1] = { triangleTable_118_0 };

static unsigned char triangleTable_119_0[8] =  { 6, 0, 2, 7, 3, 7, 2, 6 };
static unsigned char * triangleTable_119[1] = { triangleTable_119_0 };

static unsigned char triangleTable_120_0[14] =  { 12, 0, 6, 7, 8, 10, 6, 8, 3, 11, 2, 10, 8, 9 };
static unsigned char triangleTable_120_1[14] =  { 12, 0, 2, 3, 8, 10, 2, 8, 7, 11, 6, 10, 8, 9 };
static unsigned char triangleTable_120_2[26] =  { 24, 1, 12, 3, 11, 9, 12, 8, 10, 2, 12, 7, 12, 6, 6, 12, 11, 12, 9, 10, 12, 7, 8, 3, 12, 2 };
static unsigned char triangleTable_120_3[26] =  { 24, 1, 12, 7, 11, 9, 12, 8, 10, 6, 12, 3, 12, 2, 2, 12, 11, 12, 9, 10, 12, 3, 8, 7, 12, 6 };
static unsigned char * triangleTable_120[4] = { triangleTable_120_0, triangleTable_120_1, triangleTable_120_2, triangleTable_120_3 };

static unsigned char triangleTable_121_0[11] =  { 9, 0, 11, 6, 7, 10, 2, 9, 2, 0, 9 };
static unsigned char triangleTable_121_1[17] =  { 15, 0, 6, 7, 9, 2, 0, 11, 7, 0, 9, 6, 9, 10, 11, 0, 7 };
static unsigned char * triangleTable_121[2] = { triangleTable_121_0, triangleTable_121_1 };

static unsigned char triangleTable_122_0[11] =  { 9, 0, 8, 0, 3, 6, 7, 11, 2, 1, 10 };
static unsigned char triangleTable_122_1[17] =  { 15, 0, 8, 0, 3, 1, 10, 6, 1, 6, 7, 1, 7, 2, 11, 2, 7 };
static unsigned char triangleTable_122_2[17] =  { 15, 0, 1, 10, 2, 6, 7, 8, 6, 8, 0, 6, 0, 11, 3, 11, 0 };
static unsigned char triangleTable_122_3[17] =  { 15, 0, 6, 7, 11, 8, 0, 1, 8, 1, 10, 8, 10, 3, 2, 3, 10 };
static unsigned char triangleTable_122_4[29] =  { 27, 1, 0, 3, 12, 3, 11, 12, 8, 12, 7, 2, 12, 11, 1, 10, 12, 6, 7, 12, 1, 12, 2, 0, 12, 8, 12, 10, 6 };
static unsigned char triangleTable_122_5[29] =  { 27, 1, 7, 11, 12, 11, 2, 12, 6, 12, 10, 3, 12, 2, 8, 0, 12, 1, 10, 12, 8, 12, 3, 7, 12, 6, 12, 0, 1 };
static unsigned char triangleTable_122_6[29] =  { 27, 1, 10, 2, 12, 2, 3, 12, 1, 12, 0, 11, 12, 3, 6, 7, 12, 8, 0, 12, 6, 12, 11, 10, 12, 1, 12, 7, 8 };
static unsigned char triangleTable_122_7[17] =  { 15, 0, 10, 6, 7, 10, 0, 1, 2, 3, 11, 10, 7, 0, 8, 0, 7 };
static unsigned char * triangleTable_122[8] = 
{ 
  triangleTable_122_0, triangleTable_122_1, triangleTable_122_2, triangleTable_122_3, triangleTable_122_4, triangleTable_122_5, triangleTable_122_6, triangleTable_122_7
};

static unsigned char triangleTable_123_0[8] =  { 6, 0, 1, 10, 2, 11, 6, 7 };
static unsigned char triangleTable_123_1[14] =  { 12, 0, 1, 6, 7, 11, 2, 1, 1, 7, 11, 6, 1, 10 };
static unsigned char * triangleTable_123[2] = { triangleTable_123_0, triangleTable_123_1 };

static unsigned char triangleTable_124_0[11] =  { 9, 0, 7, 11, 6, 3, 8, 1, 8, 9, 1 };
static unsigned char triangleTable_124_1[17] =  { 15, 0, 11, 6, 1, 8, 9, 7, 6, 9, 1, 11, 1, 3, 7, 9, 6 };
static unsigned char * triangleTable_124[2] = { triangleTable_124_0, triangleTable_124_1 };

static unsigned char triangleTable_125_0[8] =  { 6, 0, 6, 7, 11, 0, 9, 1 };
static unsigned char triangleTable_125_1[20] =  { 18, 0, 7, 11, 0, 9, 7, 0, 6, 1, 11, 6, 7, 9, 1, 6, 9, 0, 11, 1 };
static unsigned char * triangleTable_125[2] = { triangleTable_125_0, triangleTable_125_1 };

static unsigned char triangleTable_126_0[8] =  { 6, 0, 0, 3, 8, 7, 11, 6 };
static unsigned char triangleTable_126_1[14] =  { 12, 0, 0, 11, 6, 7, 8, 0, 0, 6, 7, 11, 0, 3 };
static unsigned char * triangleTable_126[2] = { triangleTable_126_0, triangleTable_126_1 };

static unsigned char triangleTable_127_0[5] =  { 3, 0, 6, 7, 11 };
static unsigned char * triangleTable_127[1] = { triangleTable_127_0 };

static unsigned char triangleTable_128_0[5] =  { 3, 0, 11, 7, 6 };
static unsigned char * triangleTable_128[1] = { triangleTable_128_0 };

static unsigned char triangleTable_129_0[8] =  { 6, 0, 8, 3, 0, 6, 11, 7 };
static unsigned char triangleTable_129_1[14] =  { 12, 0, 6, 11, 0, 0, 8, 7, 7, 6, 0, 3, 0, 11 };
static unsigned char * triangleTable_129[2] = { triangleTable_129_0, triangleTable_129_1 };

static unsigned char triangleTable_130_0[8] =  { 6, 0, 11, 7, 6, 1, 9, 0 };
static unsigned char triangleTable_130_1[20] =  { 18, 0, 0, 11, 7, 0, 7, 9, 11, 1, 6, 9, 7, 6, 9, 6, 1, 1, 11, 0 };
static unsigned char * triangleTable_130[2] = { triangleTable_130_0, triangleTable_130_1 };

static unsigned char triangleTable_131_0[11] =  { 9, 0, 6, 11, 7, 1, 8, 3, 1, 9, 8 };
static unsigned char triangleTable_131_1[17] =  { 15, 0, 1, 6, 11, 7, 9, 8, 1, 9, 6, 3, 1, 11, 6, 9, 7 };
static unsigned char * triangleTable_131[2] = { triangleTable_131_0, triangleTable_131_1 };

static unsigned char triangleTable_132_0[8] =  { 6, 0, 2, 10, 1, 7, 6, 11 };
static unsigned char triangleTable_132_1[14] =  { 12, 0, 7, 6, 1, 1, 2, 11, 11, 7, 1, 10, 1, 6 };
static unsigned char * triangleTable_132[2] = { triangleTable_132_0, triangleTable_132_1 };

static unsigned char triangleTable_133_0[11] =  { 9, 0, 3, 0, 8, 11, 7, 6, 10, 1, 2 };
static unsigned char triangleTable_133_1[17] =  { 15, 0, 3, 0, 8, 6, 10, 1, 7, 6, 1, 2, 7, 1, 7, 2, 11 };
static unsigned char triangleTable_133_2[17] =  { 15, 0, 2, 10, 1, 8, 7, 6, 0, 8, 6, 11, 0, 6, 0, 11, 3 };
static unsigned char triangleTable_133_3[17] =  { 15, 0, 11, 7, 6, 1, 0, 8, 10, 1, 8, 3, 10, 8, 10, 3, 2 };
static unsigned char triangleTable_133_4[29] =  { 27, 1, 12, 3, 0, 12, 11, 3, 7, 12, 8, 11, 12, 2, 12, 10, 1, 12, 7, 6, 2, 12, 1, 8, 12, 0, 6, 10, 12 };
static unsigned char triangleTable_133_5[29] =  { 27, 1, 12, 11, 7, 12, 2, 11, 10, 12, 6, 2, 12, 3, 12, 0, 8, 12, 10, 1, 3, 12, 8, 6, 12, 7, 1, 0, 12 };
static unsigned char triangleTable_133_6[29] =  { 27, 1, 12, 2, 10, 12, 3, 2, 0, 12, 1, 3, 12, 11, 12, 7, 6, 12, 0, 8, 11, 12, 6, 1, 12, 10, 8, 7, 12 };
static unsigned char triangleTable_133_7[17] =  { 15, 0, 7, 6, 10, 1, 0, 10, 11, 3, 2, 0, 7, 10, 7, 0, 8 };
static unsigned char * triangleTable_133[8] = 
{ 
  triangleTable_133_0, triangleTable_133_1, triangleTable_133_2, triangleTable_133_3, triangleTable_133_4, triangleTable_133_5, triangleTable_133_6, triangleTable_133_7
};

static unsigned char triangleTable_134_0[11] =  { 9, 0, 7, 6, 11, 9, 2, 10, 9, 0, 2 };
static unsigned char triangleTable_134_1[17] =  { 15, 0, 9, 7, 6, 11, 0, 2, 9, 0, 7, 10, 9, 6, 7, 0, 11 };
static unsigned char * triangleTable_134[2] = { triangleTable_134_0, triangleTable_134_1 };

static unsigned char triangleTable_135_0[14] =  { 12, 0, 3, 2, 10, 8, 3, 10, 6, 11, 7, 8, 10, 9 };
static unsigned char triangleTable_135_1[14] =  { 12, 0, 7, 6, 10, 8, 7, 10, 2, 11, 3, 8, 10, 9 };
static unsigned char triangleTable_135_2[26] =  { 24, 1, 12, 6, 11, 9, 12, 10, 8, 7, 12, 2, 12, 3, 3, 12, 11, 12, 9, 8, 12, 2, 10, 6, 12, 7 };
static unsigned char triangleTable_135_3[26] =  { 24, 1, 12, 2, 11, 9, 12, 10, 8, 3, 12, 6, 12, 7, 7, 12, 11, 12, 9, 8, 12, 6, 10, 2, 12, 3 };
static unsigned char * triangleTable_135[4] = { triangleTable_135_0, triangleTable_135_1, triangleTable_135_2, triangleTable_135_3 };

static unsigned char triangleTable_136_0[8] =  { 6, 0, 3, 7, 2, 6, 2, 7 };
static unsigned char * triangleTable_136[1] = { triangleTable_136_0 };

static unsigned char triangleTable_137_0[11] =  { 9, 0, 0, 8, 7, 6, 0, 7, 6, 2, 0 };
static unsigned char * triangleTable_137[1] = { triangleTable_137_0 };

static unsigned char triangleTable_138_0[11] =  { 9, 0, 9, 0, 1, 7, 2, 3, 7, 6, 2 };
static unsigned char triangleTable_138_1[17] =  { 15, 0, 7, 9, 0, 1, 6, 2, 7, 6, 9, 3, 7, 0, 9, 6, 1 };
static unsigned char * triangleTable_138[2] = { triangleTable_138_0, triangleTable_138_1 };

static unsigned char triangleTable_139_0[14] =  { 12, 0, 7, 6, 8, 1, 9, 8, 6, 2, 1, 6, 1, 8 };
static unsigned char * triangleTable_139[1] = { triangleTable_139_0 };

static unsigned char triangleTable_140_0[11] =  { 9, 0, 7, 6, 10, 1, 7, 10, 1, 3, 7 };
static unsigned char * triangleTable_140[1] = { triangleTable_140_0 };

static unsigned char triangleTable_141_0[14] =  { 12, 0, 1, 7, 10, 1, 8, 7, 0, 8, 1, 10, 7, 6 };
static unsigned char * triangleTable_141[1] = { triangleTable_141_0 };

static unsigned char triangleTable_142_0[14] =  { 12, 0, 3, 7, 0, 7, 6, 10, 7, 10, 9, 0, 7, 9 };
static unsigned char * triangleTable_142[1] = { triangleTable_142_0 };

static unsigned char triangleTable_143_0[11] =  { 9, 0, 7, 6, 10, 7, 10, 8, 10, 9, 8 };
static unsigned char * triangleTable_143[1] = { triangleTable_143_0 };

static unsigned char triangleTable_144_0[8] =  { 6, 0, 4, 6, 8, 11, 8, 6 };
static unsigned char * triangleTable_144[1] = { triangleTable_144_0 };

static unsigned char triangleTable_145_0[11] =  { 9, 0, 6, 11, 3, 0, 6, 3, 0, 4, 6 };
static unsigned char * triangleTable_145[1] = { triangleTable_145_0 };

static unsigned char triangleTable_146_0[11] =  { 9, 0, 1, 9, 0, 6, 8, 4, 6, 11, 8 };
static unsigned char triangleTable_146_1[17] =  { 15, 0, 6, 1, 9, 0, 11, 8, 6, 11, 1, 4, 6, 9, 1, 11, 0 };
static unsigned char * triangleTable_146[2] = { triangleTable_146_0, triangleTable_146_1 };

static unsigned char triangleTable_147_0[14] =  { 12, 0, 4, 6, 9, 6, 11, 3, 6, 3, 1, 9, 6, 1 };
static unsigned char * triangleTable_147[1] = { triangleTable_147_0 };

static unsigned char triangleTable_148_0[11] =  { 9, 0, 1, 2, 10, 8, 6, 11, 8, 4, 6 };
static unsigned char triangleTable_148_1[17] =  { 15, 0, 8, 1, 2, 10, 4, 6, 8, 4, 1, 11, 8, 2, 1, 4, 10 };
static unsigned char * triangleTable_148[2] = { triangleTable_148_0, triangleTable_148_1 };

static unsigned char triangleTable_149_0[14] =  { 12, 0, 11, 3, 0, 6, 11, 0, 1, 2, 10, 6, 0, 4 };
static unsigned char triangleTable_149_1[14] =  { 12, 0, 10, 1, 0, 6, 10, 0, 3, 2, 11, 6, 0, 4 };
static unsigned char triangleTable_149_2[26] =  { 24, 1, 12, 1, 2, 4, 12, 0, 6, 10, 12, 3, 12, 11, 11, 12, 2, 12, 4, 6, 12, 3, 0, 1, 12, 10 };
static unsigned char triangleTable_149_3[26] =  { 24, 1, 12, 3, 2, 4, 12, 0, 6, 11, 12, 1, 12, 10, 10, 12, 2, 12, 4, 6, 12, 1, 0, 3, 12, 11 };
static unsigned char * triangleTable_149[4] = { triangleTable_149_0, triangleTable_149_1, triangleTable_149_2, triangleTable_149_3 };

static unsigned char triangleTable_150_0[14] =  { 12, 0, 8, 4, 11, 0, 2, 9, 2, 10, 9, 4, 6, 11 };
static unsigned char triangleTable_150_1[14] =  { 12, 0, 6, 9, 4, 0, 11, 8, 0, 2, 11, 6, 10, 9 };
static unsigned char triangleTable_150_2[26] =  { 24, 0, 8, 0, 11, 10, 4, 6, 10, 6, 11, 2, 11, 0, 4, 10, 9, 0, 4, 9, 10, 11, 2, 4, 0, 8 };
static unsigned char triangleTable_150_3[26] =  { 24, 1, 12, 0, 2, 4, 12, 8, 12, 4, 6, 12, 9, 0, 2, 11, 12, 8, 12, 11, 6, 10, 12, 12, 10, 9 };
static unsigned char triangleTable_150_4[26] =  { 24, 1, 12, 11, 8, 10, 12, 2, 12, 10, 9, 12, 6, 11, 8, 0, 12, 2, 12, 0, 9, 4, 12, 12, 4, 6 };
static unsigned char * triangleTable_150[5] = { triangleTable_150_0, triangleTable_150_1, triangleTable_150_2, triangleTable_150_3, triangleTable_150_4 };

static unsigned char triangleTable_151_0[11] =  { 9, 0, 2, 11, 3, 6, 10, 4, 10, 9, 4 };
static unsigned char triangleTable_151_1[17] =  { 15, 0, 11, 3, 4, 10, 9, 2, 3, 9, 4, 11, 4, 6, 2, 9, 3 };
static unsigned char * triangleTable_151[2] = { triangleTable_151_0, triangleTable_151_1 };

static unsigned char triangleTable_152_0[11] =  { 9, 0, 2, 3, 8, 4, 2, 8, 4, 6, 2 };
static unsigned char * triangleTable_152[1] = { triangleTable_152_0 };

static unsigned char triangleTable_153_0[8] =  { 6, 0, 2, 0, 4, 4, 6, 2 };
static unsigned char * triangleTable_153[1] = { triangleTable_153_0 };

static unsigned char triangleTable_154_0[14] =  { 12, 0, 3, 8, 4, 2, 3, 4, 9, 0, 1, 2, 4, 6 };
static unsigned char triangleTable_154_1[14] =  { 12, 0, 1, 9, 4, 2, 1, 4, 8, 0, 3, 2, 4, 6 };
static unsigned char triangleTable_154_2[26] =  { 24, 1, 12, 9, 0, 6, 12, 4, 2, 1, 12, 8, 12, 3, 3, 12, 0, 12, 6, 2, 12, 8, 4, 9, 12, 1 };
static unsigned char triangleTable_154_3[26] =  { 24, 1, 12, 8, 0, 6, 12, 4, 2, 3, 12, 9, 12, 1, 1, 12, 0, 12, 6, 2, 12, 9, 4, 8, 12, 3 };
static unsigned char * triangleTable_154[4] = { triangleTable_154_0, triangleTable_154_1, triangleTable_154_2, triangleTable_154_3 };

static unsigned char triangleTable_155_0[11] =  { 9, 0, 1, 9, 4, 1, 4, 2, 4, 6, 2 };
static unsigned char * triangleTable_155[1] = { triangleTable_155_0 };

static unsigned char triangleTable_156_0[14] =  { 12, 0, 10, 1, 6, 8, 4, 6, 1, 3, 8, 1, 8, 6 };
static unsigned char * triangleTable_156[1] = { triangleTable_156_0 };

static unsigned char triangleTable_157_0[11] =  { 9, 0, 10, 1, 0, 10, 0, 6, 0, 4, 6 };
static unsigned char * triangleTable_157[1] = { triangleTable_157_0 };

static unsigned char triangleTable_158_0[11] =  { 9, 0, 8, 0, 3, 9, 4, 10, 4, 6, 10 };
static unsigned char triangleTable_158_1[17] =  { 15, 0, 0, 3, 10, 4, 6, 8, 3, 6, 10, 0, 10, 9, 8, 6, 3 };
static unsigned char * triangleTable_158[2] = { triangleTable_158_0, triangleTable_158_1 };

static unsigned char triangleTable_159_0[8] =  { 6, 0, 10, 4, 6, 4, 10, 9 };
static unsigned char * triangleTable_159[1] = { triangleTable_159_0 };

static unsigned char triangleTable_160_0[8] =  { 6, 0, 5, 4, 9, 11, 7, 6 };
static unsigned char triangleTable_160_1[14] =  { 12, 0, 11, 7, 9, 9, 5, 6, 6, 11, 9, 4, 9, 7 };
static unsigned char * triangleTable_160[2] = { triangleTable_160_0, triangleTable_160_1 };

static unsigned char triangleTable_161_0[11] =  { 9, 0, 7, 6, 11, 8, 3, 0, 9, 5, 4 };
static unsigned char triangleTable_161_1[17] =  { 15, 0, 7, 6, 11, 0, 9, 5, 3, 0, 5, 4, 3, 5, 3, 4, 8 };
static unsigned char triangleTable_161_2[17] =  { 15, 0, 4, 9, 5, 11, 3, 0, 6, 11, 0, 8, 6, 0, 6, 8, 7 };
static unsigned char triangleTable_161_3[17] =  { 15, 0, 8, 3, 0, 5, 6, 11, 9, 5, 11, 7, 9, 11, 9, 7, 4 };
static unsigned char triangleTable_161_4[29] =  { 27, 1, 12, 7, 6, 12, 8, 7, 3, 12, 11, 8, 12, 4, 12, 9, 5, 12, 3, 0, 4, 12, 5, 11, 12, 6, 0, 9, 12 };
static unsigned char triangleTable_161_5[29] =  { 27, 1, 12, 8, 3, 12, 4, 8, 9, 12, 0, 4, 12, 7, 12, 6, 11, 12, 9, 5, 7, 12, 11, 0, 12, 3, 5, 6, 12 };
static unsigned char triangleTable_161_6[29] =  { 27, 1, 12, 4, 9, 12, 7, 4, 6, 12, 5, 7, 12, 8, 12, 3, 0, 12, 6, 11, 8, 12, 0, 5, 12, 9, 11, 3, 12 };
static unsigned char triangleTable_161_7[17] =  { 15, 0, 3, 0, 9, 5, 6, 9, 8, 7, 4, 6, 3, 9, 3, 6, 11 };
static unsigned char * triangleTable_161[8] = 
{ 
  triangleTable_161_0, triangleTable_161_1, triangleTable_161_2, triangleTable_161_3, triangleTable_161_4, triangleTable_161_5, triangleTable_161_6, triangleTable_161_7
};

static unsigned char triangleTable_162_0[11] =  { 9, 0, 11, 7, 6, 0, 5, 4, 0, 1, 5 };
static unsigned char triangleTable_162_1[17] =  { 15, 0, 0, 11, 7, 6, 1, 5, 0, 1, 11, 4, 0, 7, 11, 1, 6 };
static unsigned char * triangleTable_162[2] = { triangleTable_162_0, triangleTable_162_1 };

static unsigned char triangleTable_163_0[14] =  { 12, 0, 4, 8, 3, 5, 4, 3, 11, 7, 6, 5, 3, 1 };
static unsigned char triangleTable_163_1[14] =  { 12, 0, 6, 11, 3, 5, 6, 3, 8, 7, 4, 5, 3, 1 };
static unsigned char triangleTable_163_2[26] =  { 24, 1, 12, 11, 7, 1, 12, 3, 5, 6, 12, 8, 12, 4, 4, 12, 7, 12, 1, 5, 12, 8, 3, 11, 12, 6 };
static unsigned char triangleTable_163_3[26] =  { 24, 1, 12, 8, 7, 1, 12, 3, 5, 4, 12, 11, 12, 6, 6, 12, 7, 12, 1, 5, 12, 11, 3, 8, 12, 4 };
static unsigned char * triangleTable_163[4] = { triangleTable_163_0, triangleTable_163_1, triangleTable_163_2, triangleTable_163_3 };

static unsigned char triangleTable_164_0[11] =  { 9, 0, 5, 4, 9, 10, 1, 2, 11, 7, 6 };
static unsigned char triangleTable_164_1[17] =  { 15, 0, 5, 4, 9, 2, 11, 7, 1, 2, 7, 6, 1, 7, 1, 6, 10 };
static unsigned char triangleTable_164_2[17] =  { 15, 0, 6, 11, 7, 9, 1, 2, 4, 9, 2, 10, 4, 2, 4, 10, 5 };
static unsigned char triangleTable_164_3[17] =  { 15, 0, 10, 1, 2, 7, 4, 9, 11, 7, 9, 5, 11, 9, 11, 5, 6 };
static unsigned char triangleTable_164_4[29] =  { 27, 1, 12, 5, 4, 12, 10, 5, 1, 12, 9, 10, 12, 6, 12, 11, 7, 12, 1, 2, 6, 12, 7, 9, 12, 4, 2, 11, 12 };
static unsigned char triangleTable_164_5[29] =  { 27, 1, 12, 10, 1, 12, 6, 10, 11, 12, 2, 6, 12, 5, 12, 4, 9, 12, 11, 7, 5, 12, 9, 2, 12, 1, 7, 4, 12 };
static unsigned char triangleTable_164_6[29] =  { 27, 1, 12, 6, 11, 12, 5, 6, 4, 12, 7, 5, 12, 10, 12, 1, 2, 12, 4, 9, 10, 12, 2, 7, 12, 11, 9, 1, 12 };
static unsigned char triangleTable_164_7[17] =  { 15, 0, 1, 2, 11, 7, 4, 11, 10, 5, 6, 4, 1, 11, 1, 4, 9 };
static unsigned char * triangleTable_164[8] = 
{ 
  triangleTable_164_0, triangleTable_164_1, triangleTable_164_2, triangleTable_164_3, triangleTable_164_4, triangleTable_164_5, triangleTable_164_6, triangleTable_164_7
};

static unsigned char triangleTable_165_0[14] =  { 12, 0, 10, 1, 2, 7, 6, 11, 0, 8, 3, 5, 4, 9 };
static unsigned char triangleTable_165_1[20] =  { 18, 0, 1, 2, 10, 11, 7, 6, 5, 4, 3, 0, 9, 5, 4, 8, 3, 5, 3, 0 };
static unsigned char triangleTable_165_2[20] =  { 18, 0, 6, 11, 7, 3, 0, 8, 4, 9, 2, 10, 5, 4, 9, 1, 2, 4, 2, 10 };
static unsigned char triangleTable_165_3[20] =  { 18, 0, 3, 0, 8, 9, 5, 4, 7, 6, 1, 2, 11, 7, 6, 10, 1, 7, 1, 2 };
static unsigned char triangleTable_165_4[20] =  { 18, 0, 4, 9, 5, 1, 2, 10, 6, 11, 0, 8, 7, 6, 11, 3, 0, 6, 0, 8 };
static unsigned char triangleTable_165_5[20] =  { 18, 0, 11, 7, 6, 4, 9, 5, 10, 1, 8, 3, 2, 10, 1, 0, 8, 10, 8, 3 };
static unsigned char triangleTable_165_6[20] =  { 18, 0, 8, 3, 0, 2, 10, 1, 9, 5, 11, 7, 4, 9, 5, 6, 11, 9, 11, 7 };
static unsigned char triangleTable_165_7[32] =  { 30, 1, 4, 12, 5, 12, 2, 10, 1, 12, 9, 12, 1, 2, 12, 8, 3, 5, 12, 10, 9, 12, 0, 6, 11, 7, 3, 0, 12, 8, 12, 4 };
static unsigned char triangleTable_165_8[32] =  { 30, 1, 0, 12, 3, 12, 6, 11, 7, 12, 8, 12, 7, 6, 12, 9, 5, 3, 12, 11, 8, 12, 4, 2, 10, 1, 5, 4, 12, 9, 12, 0 };
static unsigned char triangleTable_165_9[32] =  { 30, 1, 3, 12, 8, 2, 10, 12, 0, 12, 1, 10, 1, 12, 5, 4, 12, 2, 12, 3, 9, 12, 0, 7, 6, 11, 12, 9, 5, 8, 12, 4 };
static unsigned char triangleTable_165_10[32] =  { 30, 1, 5, 12, 9, 6, 11, 12, 4, 12, 7, 11, 7, 12, 3, 0, 12, 6, 12, 5, 8, 12, 4, 1, 2, 10, 12, 8, 3, 9, 12, 0 };
static unsigned char triangleTable_165_11[32] =  { 30, 1, 2, 12, 1, 11, 7, 12, 10, 12, 6, 7, 6, 12, 4, 9, 12, 11, 12, 2, 5, 12, 10, 0, 8, 3, 12, 5, 4, 1, 12, 9 };
static unsigned char triangleTable_165_12[32] =  { 30, 1, 10, 12, 2, 12, 8, 3, 0, 12, 1, 12, 0, 8, 12, 5, 4, 2, 12, 3, 1, 12, 9, 11, 7, 6, 4, 9, 12, 5, 12, 10 };
static unsigned char triangleTable_165_13[32] =  { 30, 1, 9, 12, 4, 1, 2, 12, 5, 12, 10, 2, 10, 12, 11, 7, 12, 1, 12, 9, 6, 12, 5, 8, 3, 0, 12, 6, 11, 4, 12, 7 };
static unsigned char triangleTable_165_14[32] =  { 30, 1, 6, 12, 7, 12, 0, 8, 3, 12, 11, 12, 3, 0, 12, 10, 1, 7, 12, 8, 11, 12, 2, 4, 9, 5, 1, 2, 12, 10, 12, 6 };
static unsigned char triangleTable_165_15[32] =  { 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char triangleTable_165_16[32] =  { 30, 1, 7, 12, 11, 12, 1, 2, 10, 12, 6, 12, 10, 1, 12, 4, 9, 11, 12, 2, 6, 12, 5, 3, 0, 8, 9, 5, 12, 4, 12, 7 };
static unsigned char triangleTable_165_17[32] =  { 30, 1, 8, 12, 0, 7, 6, 12, 3, 12, 11, 6, 11, 12, 10, 1, 12, 7, 12, 8, 2, 12, 3, 9, 5, 4, 12, 2, 10, 0, 12, 1 };
static unsigned char triangleTable_165_18[32] =  { 30, 1, 11, 12, 6, 12, 9, 5, 4, 12, 7, 12, 4, 9, 12, 3, 0, 6, 12, 5, 7, 12, 8, 10, 1, 2, 0, 8, 12, 3, 12, 11 };
static unsigned char triangleTable_165_19[38] =  { 36, 1, 12, 4, 8, 10, 5, 12, 0, 12, 3, 4, 12, 7, 2, 12, 1, 12, 0, 9, 1, 12, 9, 12, 11, 7, 8, 3, 12, 6, 12, 5, 2, 10, 12, 6, 11, 12 };
static unsigned char triangleTable_165_20[38] =  { 36, 1, 12, 0, 9, 11, 3, 12, 4, 12, 5, 0, 12, 1, 6, 12, 7, 12, 4, 8, 7, 12, 8, 12, 10, 1, 9, 5, 12, 2, 12, 3, 6, 11, 12, 2, 10, 12 };
static unsigned char triangleTable_165_21[38] =  { 36, 1, 12, 10, 5, 3, 2, 12, 9, 12, 4, 10, 12, 6, 8, 12, 0, 12, 9, 1, 0, 12, 1, 12, 7, 6, 5, 4, 12, 11, 12, 2, 8, 3, 12, 11, 7, 12 };
static unsigned char triangleTable_165_22[38] =  { 36, 1, 12, 6, 10, 8, 7, 12, 2, 12, 1, 6, 12, 5, 0, 12, 3, 12, 2, 11, 3, 12, 11, 12, 9, 5, 10, 1, 12, 4, 12, 7, 0, 8, 12, 4, 9, 12 };
static unsigned char triangleTable_165_23[32] =  { 30, 1, 0, 12, 1, 12, 6, 10, 5, 12, 9, 12, 5, 6, 12, 8, 7, 1, 12, 10, 9, 12, 4, 2, 11, 3, 7, 4, 12, 8, 12, 0 };
static unsigned char triangleTable_165_24[32] =  { 30, 1, 4, 12, 7, 12, 2, 11, 3, 12, 8, 12, 3, 2, 12, 9, 1, 7, 12, 11, 8, 12, 0, 6, 10, 5, 1, 0, 12, 9, 12, 4 };
static unsigned char triangleTable_165_25[32] =  { 30, 1, 1, 12, 9, 2, 11, 12, 0, 12, 3, 11, 3, 12, 7, 4, 12, 2, 12, 1, 8, 12, 0, 5, 6, 10, 12, 8, 7, 9, 12, 4 };
static unsigned char triangleTable_165_26[32] =  { 30, 1, 7, 12, 8, 6, 10, 12, 4, 12, 5, 10, 5, 12, 1, 0, 12, 6, 12, 7, 9, 12, 4, 3, 2, 11, 12, 9, 1, 8, 12, 0 };
static unsigned char triangleTable_165_27[32] =  { 30, 1, 6, 12, 5, 11, 3, 12, 10, 12, 2, 3, 2, 12, 0, 9, 12, 11, 12, 6, 1, 12, 10, 4, 8, 7, 12, 1, 0, 5, 12, 9 };
static unsigned char triangleTable_165_28[32] =  { 30, 1, 9, 12, 0, 12, 11, 3, 2, 12, 1, 12, 2, 11, 12, 5, 6, 0, 12, 3, 1, 12, 10, 8, 7, 4, 6, 10, 12, 5, 12, 9 };
static unsigned char triangleTable_165_29[32] =  { 30, 1, 10, 12, 6, 1, 0, 12, 5, 12, 9, 0, 9, 12, 8, 7, 12, 1, 12, 10, 4, 12, 5, 11, 3, 2, 12, 4, 8, 6, 12, 7 };
static unsigned char triangleTable_165_30[32] =  { 30, 1, 2, 12, 3, 12, 4, 8, 7, 12, 11, 12, 7, 4, 12, 10, 5, 3, 12, 8, 11, 12, 6, 0, 9, 1, 5, 6, 12, 10, 12, 2 };
static unsigned char triangleTable_165_31[32] =  { 30, 1, 1, 12, 10, 0, 8, 12, 2, 12, 3, 8, 3, 12, 7, 6, 12, 0, 12, 1, 11, 12, 2, 5, 4, 9, 12, 11, 7, 10, 12, 6 };
static unsigned char triangleTable_165_32[32] =  { 30, 1, 5, 12, 10, 12, 3, 2, 11, 12, 6, 12, 11, 3, 12, 4, 8, 10, 12, 2, 6, 12, 7, 1, 0, 9, 8, 7, 12, 4, 12, 5 };
static unsigned char triangleTable_165_33[32] =  { 30, 1, 11, 12, 2, 7, 4, 12, 3, 12, 8, 4, 8, 12, 9, 1, 12, 7, 12, 11, 0, 12, 3, 10, 5, 6, 12, 0, 9, 2, 12, 1 };
static unsigned char triangleTable_165_34[32] =  { 30, 1, 8, 12, 4, 12, 10, 5, 6, 12, 7, 12, 6, 10, 12, 3, 2, 4, 12, 5, 7, 12, 11, 9, 1, 0, 2, 11, 12, 3, 12, 8 };
static unsigned char triangleTable_165_35[20] =  { 18, 0, 6, 10, 5, 11, 3, 2, 1, 8, 7, 7, 4, 9, 1, 0, 8, 9, 1, 7 };
static unsigned char triangleTable_165_36[20] =  { 18, 0, 8, 7, 4, 3, 2, 11, 6, 1, 0, 0, 9, 5, 6, 10, 1, 5, 6, 0 };
static unsigned char triangleTable_165_37[20] =  { 18, 0, 4, 8, 7, 9, 1, 0, 3, 10, 5, 5, 6, 11, 3, 2, 10, 11, 3, 5 };
static unsigned char triangleTable_165_38[20] =  { 18, 0, 10, 5, 6, 1, 0, 9, 4, 3, 2, 2, 11, 7, 4, 8, 3, 7, 4, 2 };
static unsigned char triangleTable_165_39[20] =  { 18, 0, 5, 6, 10, 4, 8, 7, 11, 0, 9, 9, 1, 2, 11, 3, 0, 2, 11, 9 };
static unsigned char triangleTable_165_40[20] =  { 18, 0, 1, 0, 9, 2, 11, 3, 8, 6, 10, 10, 5, 4, 8, 7, 6, 4, 8, 10 };
static unsigned char triangleTable_165_41[14] =  { 12, 0, 3, 2, 11, 8, 7, 4, 0, 9, 1, 10, 5, 6 };
static unsigned char triangleTable_165_42[20] =  { 18, 0, 2, 10, 4, 4, 8, 2, 1, 0, 9, 2, 8, 3, 6, 11, 7, 4, 10, 5 };
static unsigned char triangleTable_165_43[20] =  { 18, 0, 6, 11, 0, 0, 9, 6, 7, 4, 8, 6, 9, 5, 2, 10, 1, 0, 11, 3 };
static unsigned char triangleTable_165_44[20] =  { 18, 0, 4, 9, 2, 2, 11, 4, 5, 6, 10, 4, 11, 7, 0, 8, 3, 2, 9, 1 };
static unsigned char triangleTable_165_45[20] =  { 18, 0, 0, 8, 6, 6, 10, 0, 3, 2, 11, 0, 10, 1, 4, 9, 5, 6, 8, 7 };
static unsigned char * triangleTable_165[46] = 
{ 
  triangleTable_165_0, triangleTable_165_1, triangleTable_165_2, triangleTable_165_3, triangleTable_165_4, triangleTable_165_5, triangleTable_165_6, triangleTable_165_7, 
  triangleTable_165_8, triangleTable_165_9, triangleTable_165_10, triangleTable_165_11, triangleTable_165_12, triangleTable_165_13, triangleTable_165_14, triangleTable_165_15, 
  triangleTable_165_16, triangleTable_165_17, triangleTable_165_18, triangleTable_165_19, triangleTable_165_20, triangleTable_165_21, triangleTable_165_22, triangleTable_165_23, 
  triangleTable_165_24, triangleTable_165_25, triangleTable_165_26, triangleTable_165_27, triangleTable_165_28, triangleTable_165_29, triangleTable_165_30, triangleTable_165_31, 
  triangleTable_165_32, triangleTable_165_33, triangleTable_165_34, triangleTable_165_35, triangleTable_165_36, triangleTable_165_37, triangleTable_165_38, triangleTable_165_39, 
  triangleTable_165_40, triangleTable_165_41, triangleTable_165_42, triangleTable_165_43, triangleTable_165_44, triangleTable_165_45
};

static unsigned char triangleTable_166_0[14] =  { 12, 0, 10, 5, 4, 2, 10, 4, 7, 6, 11, 2, 4, 0 };
static unsigned char triangleTable_166_1[14] =  { 12, 0, 11, 7, 4, 2, 11, 4, 5, 6, 10, 2, 4, 0 };
static unsigned char triangleTable_166_2[26] =  { 24, 1, 12, 7, 6, 0, 12, 4, 2, 11, 12, 5, 12, 10, 10, 12, 6, 12, 0, 2, 12, 5, 4, 7, 12, 11 };
static unsigned char triangleTable_166_3[26] =  { 24, 1, 12, 5, 6, 0, 12, 4, 2, 10, 12, 7, 12, 11, 11, 12, 6, 12, 0, 2, 12, 7, 4, 5, 12, 10 };
static unsigned char * triangleTable_166[4] = { triangleTable_166_0, triangleTable_166_1, triangleTable_166_2, triangleTable_166_3 };

static unsigned char triangleTable_167_0[11] =  { 9, 0, 3, 2, 11, 4, 8, 7, 6, 10, 5 };
static unsigned char triangleTable_167_1[17] =  { 15, 0, 3, 2, 11, 10, 5, 4, 10, 4, 8, 10, 8, 6, 7, 6, 8 };
static unsigned char triangleTable_167_2[17] =  { 15, 0, 10, 5, 6, 4, 8, 3, 4, 3, 2, 4, 2, 7, 11, 7, 2 };
static unsigned char triangleTable_167_3[17] =  { 15, 0, 4, 8, 7, 3, 2, 10, 3, 10, 5, 3, 5, 11, 6, 11, 5 };
static unsigned char triangleTable_167_4[29] =  { 27, 1, 2, 11, 12, 11, 7, 12, 3, 12, 8, 6, 12, 7, 10, 5, 12, 4, 8, 12, 10, 12, 6, 2, 12, 3, 12, 5, 4 };
static unsigned char triangleTable_167_5[29] =  { 27, 1, 8, 7, 12, 7, 6, 12, 4, 12, 5, 11, 12, 6, 3, 2, 12, 10, 5, 12, 3, 12, 11, 8, 12, 4, 12, 2, 10 };
static unsigned char triangleTable_167_6[29] =  { 27, 1, 5, 6, 12, 6, 11, 12, 10, 12, 2, 7, 12, 11, 4, 8, 12, 3, 2, 12, 4, 12, 7, 5, 12, 10, 12, 8, 3 };
static unsigned char triangleTable_167_7[17] =  { 15, 0, 5, 4, 8, 5, 2, 10, 6, 11, 7, 5, 8, 2, 3, 2, 8 };
static unsigned char * triangleTable_167[8] = 
{ 
  triangleTable_167_0, triangleTable_167_1, triangleTable_167_2, triangleTable_167_3, triangleTable_167_4, triangleTable_167_5, triangleTable_167_6, triangleTable_167_7
};

static unsigned char triangleTable_168_0[11] =  { 9, 0, 9, 5, 4, 2, 7, 6, 2, 3, 7 };
static unsigned char triangleTable_168_1[17] =  { 15, 0, 2, 9, 5, 4, 3, 7, 2, 3, 9, 6, 2, 5, 9, 3, 4 };
static unsigned char * triangleTable_168[2] = { triangleTable_168_0, triangleTable_168_1 };

static unsigned char triangleTable_169_0[14] =  { 12, 0, 8, 7, 6, 0, 8, 6, 5, 4, 9, 0, 6, 2 };
static unsigned char triangleTable_169_1[14] =  { 12, 0, 9, 5, 6, 0, 9, 6, 7, 4, 8, 0, 6, 2 };
static unsigned char triangleTable_169_2[26] =  { 24, 1, 12, 5, 4, 2, 12, 6, 0, 9, 12, 7, 12, 8, 8, 12, 4, 12, 2, 0, 12, 7, 6, 5, 12, 9 };
static unsigned char triangleTable_169_3[26] =  { 24, 1, 12, 7, 4, 2, 12, 6, 0, 8, 12, 5, 12, 9, 9, 12, 4, 12, 2, 0, 12, 5, 6, 7, 12, 8 };
static unsigned char * triangleTable_169[4] = { triangleTable_169_0, triangleTable_169_1, triangleTable_169_2, triangleTable_169_3 };

static unsigned char triangleTable_170_0[14] =  { 12, 0, 2, 3, 6, 1, 5, 0, 5, 4, 0, 3, 7, 6 };
static unsigned char triangleTable_170_1[14] =  { 12, 0, 7, 0, 3, 1, 6, 2, 1, 5, 6, 7, 4, 0 };
static unsigned char triangleTable_170_2[26] =  { 24, 0, 2, 1, 6, 4, 3, 7, 4, 7, 6, 5, 6, 1, 3, 4, 0, 1, 3, 0, 4, 6, 5, 3, 1, 2 };
static unsigned char triangleTable_170_3[26] =  { 24, 1, 12, 1, 5, 3, 12, 2, 12, 3, 7, 12, 0, 1, 5, 6, 12, 2, 12, 6, 7, 4, 12, 12, 4, 0 };
static unsigned char triangleTable_170_4[26] =  { 24, 1, 12, 6, 2, 4, 12, 5, 12, 4, 0, 12, 7, 6, 2, 1, 12, 5, 12, 1, 0, 3, 12, 12, 3, 7 };
static unsigned char * triangleTable_170[5] = { triangleTable_170_0, triangleTable_170_1, triangleTable_170_2, triangleTable_170_3, triangleTable_170_4 };

static unsigned char triangleTable_171_0[11] =  { 9, 0, 7, 4, 8, 5, 6, 1, 6, 2, 1 };
static unsigned char triangleTable_171_1[17] =  { 15, 0, 4, 8, 1, 6, 2, 7, 8, 2, 1, 4, 1, 5, 7, 2, 8 };
static unsigned char * triangleTable_171[2] = { triangleTable_171_0, triangleTable_171_1 };

static unsigned char triangleTable_172_0[14] =  { 12, 0, 6, 10, 1, 7, 6, 1, 9, 5, 4, 7, 1, 3 };
static unsigned char triangleTable_172_1[14] =  { 12, 0, 4, 9, 1, 7, 4, 1, 10, 5, 6, 7, 1, 3 };
static unsigned char triangleTable_172_2[26] =  { 24, 1, 12, 9, 5, 3, 12, 1, 7, 4, 12, 10, 12, 6, 6, 12, 5, 12, 3, 7, 12, 10, 1, 9, 12, 4 };
static unsigned char triangleTable_172_3[26] =  { 24, 1, 12, 10, 5, 3, 12, 1, 7, 6, 12, 9, 12, 4, 4, 12, 5, 12, 3, 7, 12, 9, 1, 10, 12, 6 };
static unsigned char * triangleTable_172[4] = { triangleTable_172_0, triangleTable_172_1, triangleTable_172_2, triangleTable_172_3 };

static unsigned char triangleTable_173_0[11] =  { 9, 0, 6, 10, 5, 8, 7, 4, 9, 1, 0 };
static unsigned char triangleTable_173_1[17] =  { 15, 0, 6, 10, 5, 1, 0, 8, 1, 8, 7, 1, 7, 9, 4, 9, 7 };
static unsigned char triangleTable_173_2[17] =  { 15, 0, 1, 0, 9, 8, 7, 6, 8, 6, 10, 8, 10, 4, 5, 4, 10 };
static unsigned char triangleTable_173_3[17] =  { 15, 0, 8, 7, 4, 6, 10, 1, 6, 1, 0, 6, 0, 5, 9, 5, 0 };
static unsigned char triangleTable_173_4[29] =  { 27, 1, 10, 5, 12, 5, 4, 12, 6, 12, 7, 9, 12, 4, 1, 0, 12, 8, 7, 12, 1, 12, 9, 10, 12, 6, 12, 0, 8 };
static unsigned char triangleTable_173_5[29] =  { 27, 1, 7, 4, 12, 4, 9, 12, 8, 12, 0, 5, 12, 9, 6, 10, 12, 1, 0, 12, 6, 12, 5, 7, 12, 8, 12, 10, 1 };
static unsigned char triangleTable_173_6[29] =  { 27, 1, 0, 9, 12, 9, 5, 12, 1, 12, 10, 4, 12, 5, 8, 7, 12, 6, 10, 12, 8, 12, 4, 0, 12, 1, 12, 7, 6 };
static unsigned char triangleTable_173_7[17] =  { 15, 0, 0, 8, 7, 0, 10, 1, 9, 5, 4, 0, 7, 10, 6, 10, 7 };
static unsigned char * triangleTable_173[8] = 
{ 
  triangleTable_173_0, triangleTable_173_1, triangleTable_173_2, triangleTable_173_3, triangleTable_173_4, triangleTable_173_5, triangleTable_173_6, triangleTable_173_7
};

static unsigned char triangleTable_174_0[11] =  { 9, 0, 5, 6, 10, 7, 4, 3, 4, 0, 3 };
static unsigned char triangleTable_174_1[17] =  { 15, 0, 6, 10, 3, 4, 0, 5, 10, 0, 3, 6, 3, 7, 5, 0, 10 };
static unsigned char * triangleTable_174[2] = { triangleTable_174_0, triangleTable_174_1 };

static unsigned char triangleTable_175_0[8] =  { 6, 0, 10, 5, 6, 7, 4, 8 };
static unsigned char triangleTable_175_1[14] =  { 12, 0, 10, 4, 8, 7, 6, 10, 10, 8, 7, 4, 10, 5 };
static unsigned char * triangleTable_175[2] = { triangleTable_175_0, triangleTable_175_1 };

static unsigned char triangleTable_176_0[11] =  { 9, 0, 9, 5, 6, 11, 9, 6, 11, 8, 9 };
static unsigned char * triangleTable_176[1] = { triangleTable_176_0 };

static unsigned char triangleTable_177_0[14] =  { 12, 0, 5, 3, 9, 5, 11, 3, 6, 11, 5, 9, 3, 0 };
static unsigned char * triangleTable_177[1] = { triangleTable_177_0 };

static unsigned char triangleTable_178_0[14] =  { 12, 0, 6, 11, 5, 0, 1, 5, 11, 8, 0, 11, 0, 5 };
static unsigned char * triangleTable_178[1] = { triangleTable_178_0 };

static unsigned char triangleTable_179_0[11] =  { 9, 0, 6, 11, 3, 6, 3, 5, 3, 1, 5 };
static unsigned char * triangleTable_179[1] = { triangleTable_179_0 };

static unsigned char triangleTable_180_0[14] =  { 12, 0, 5, 6, 11, 9, 5, 11, 2, 10, 1, 9, 11, 8 };
static unsigned char triangleTable_180_1[14] =  { 12, 0, 1, 2, 11, 9, 1, 11, 6, 10, 5, 9, 11, 8 };
static unsigned char triangleTable_180_2[26] =  { 24, 1, 12, 2, 10, 8, 12, 11, 9, 1, 12, 6, 12, 5, 5, 12, 10, 12, 8, 9, 12, 6, 11, 2, 12, 1 };
static unsigned char triangleTable_180_3[26] =  { 24, 1, 12, 6, 10, 8, 12, 11, 9, 5, 12, 2, 12, 1, 1, 12, 10, 12, 8, 9, 12, 2, 11, 6, 12, 5 };
static unsigned char * triangleTable_180[4] = { triangleTable_180_0, triangleTable_180_1, triangleTable_180_2, triangleTable_180_3 };

static unsigned char triangleTable_181_0[11] =  { 9, 0, 5, 6, 10, 0, 9, 1, 2, 11, 3 };
static unsigned char triangleTable_181_1[17] =  { 15, 0, 5, 6, 10, 11, 3, 0, 11, 0, 9, 11, 9, 2, 1, 2, 9 };
static unsigned char triangleTable_181_2[17] =  { 15, 0, 11, 3, 2, 0, 9, 5, 0, 5, 6, 0, 6, 1, 10, 1, 6 };
static unsigned char triangleTable_181_3[17] =  { 15, 0, 0, 9, 1, 5, 6, 11, 5, 11, 3, 5, 3, 10, 2, 10, 3 };
static unsigned char triangleTable_181_4[29] =  { 27, 1, 6, 10, 12, 10, 1, 12, 5, 12, 9, 2, 12, 1, 11, 3, 12, 0, 9, 12, 11, 12, 2, 6, 12, 5, 12, 3, 0 };
static unsigned char triangleTable_181_5[29] =  { 27, 1, 9, 1, 12, 1, 2, 12, 0, 12, 3, 10, 12, 2, 5, 6, 12, 11, 3, 12, 5, 12, 10, 9, 12, 0, 12, 6, 11 };
static unsigned char triangleTable_181_6[29] =  { 27, 1, 3, 2, 12, 2, 10, 12, 11, 12, 6, 1, 12, 10, 0, 9, 12, 5, 6, 12, 0, 12, 1, 3, 12, 11, 12, 9, 5 };
static unsigned char triangleTable_181_7[17] =  { 15, 0, 3, 0, 9, 3, 6, 11, 2, 10, 1, 3, 9, 6, 5, 6, 9 };
static unsigned char * triangleTable_181[8] = 
{ 
  triangleTable_181_0, triangleTable_181_1, triangleTable_181_2, triangleTable_181_3, triangleTable_181_4, triangleTable_181_5, triangleTable_181_6, triangleTable_181_7
};

static unsigned char triangleTable_182_0[11] =  { 9, 0, 6, 10, 5, 2, 11, 0, 11, 8, 0 };
static unsigned char triangleTable_182_1[17] =  { 15, 0, 10, 5, 0, 11, 8, 6, 5, 8, 0, 10, 0, 2, 6, 8, 5 };
static unsigned char * triangleTable_182[2] = { triangleTable_182_0, triangleTable_182_1 };

static unsigned char triangleTable_183_0[8] =  { 6, 0, 5, 6, 10, 2, 11, 3 };
static unsigned char triangleTable_183_1[14] =  { 12, 0, 5, 11, 3, 2, 10, 5, 5, 3, 2, 11, 5, 6 };
static unsigned char * triangleTable_183[2] = { triangleTable_183_0, triangleTable_183_1 };

static unsigned char triangleTable_184_0[14] =  { 12, 0, 6, 2, 5, 2, 3, 8, 2, 8, 9, 5, 2, 9 };
static unsigned char * triangleTable_184[1] = { triangleTable_184_0 };

static unsigned char triangleTable_185_0[11] =  { 9, 0, 9, 5, 6, 9, 6, 0, 6, 2, 0 };
static unsigned char * triangleTable_185[1] = { triangleTable_185_0 };

static unsigned char triangleTable_186_0[11] =  { 9, 0, 0, 3, 8, 2, 1, 6, 1, 5, 6 };
static unsigned char triangleTable_186_1[17] =  { 15, 0, 3, 8, 6, 1, 5, 0, 8, 5, 6, 3, 6, 2, 0, 5, 8 };
static unsigned char * triangleTable_186[2] = { triangleTable_186_0, triangleTable_186_1 };

static unsigned char triangleTable_187_0[8] =  { 6, 0, 6, 1, 5, 1, 6, 2 };
static unsigned char * triangleTable_187[1] = { triangleTable_187_0 };

static unsigned char triangleTable_188_0[11] =  { 9, 0, 10, 5, 6, 9, 1, 8, 1, 3, 8 };
static unsigned char triangleTable_188_1[17] =  { 15, 0, 5, 6, 8, 1, 3, 10, 6, 3, 8, 5, 8, 9, 10, 3, 6 };
static unsigned char * triangleTable_188[2] = { triangleTable_188_0, triangleTable_188_1 };

static unsigned char triangleTable_189_0[8] =  { 6, 0, 6, 10, 5, 9, 1, 0 };
static unsigned char triangleTable_189_1[14] =  { 12, 0, 6, 1, 0, 9, 5, 6, 6, 0, 9, 1, 6, 10 };
static unsigned char * triangleTable_189[2] = { triangleTable_189_0, triangleTable_189_1 };

static unsigned char triangleTable_190_0[8] =  { 6, 0, 10, 5, 6, 8, 0, 3 };
static unsigned char triangleTable_190_1[20] =  { 18, 0, 5, 6, 8, 0, 5, 8, 10, 3, 6, 10, 5, 0, 3, 10, 0, 8, 6, 3 };
static unsigned char * triangleTable_190[2] = { triangleTable_190_0, triangleTable_190_1 };

static unsigned char triangleTable_191_0[5] =  { 3, 0, 10, 5, 6 };
static unsigned char * triangleTable_191[1] = { triangleTable_191_0 };

static unsigned char triangleTable_192_0[8] =  { 6, 0, 7, 5, 11, 10, 11, 5 };
static unsigned char * triangleTable_192[1] = { triangleTable_192_0 };

static unsigned char triangleTable_193_0[11] =  { 9, 0, 0, 8, 3, 5, 11, 7, 5, 10, 11 };
static unsigned char triangleTable_193_1[17] =  { 15, 0, 5, 0, 8, 3, 10, 11, 5, 10, 0, 7, 5, 8, 0, 10, 3 };
static unsigned char * triangleTable_193[2] = { triangleTable_193_0, triangleTable_193_1 };

static unsigned char triangleTable_194_0[11] =  { 9, 0, 0, 1, 9, 11, 5, 10, 11, 7, 5 };
static unsigned char triangleTable_194_1[17] =  { 15, 0, 11, 0, 1, 9, 7, 5, 11, 7, 0, 10, 11, 1, 0, 7, 9 };
static unsigned char * triangleTable_194[2] = { triangleTable_194_0, triangleTable_194_1 };

static unsigned char triangleTable_195_0[14] =  { 12, 0, 11, 7, 10, 3, 1, 8, 1, 9, 8, 7, 5, 10 };
static unsigned char triangleTable_195_1[14] =  { 12, 0, 5, 8, 7, 3, 10, 11, 3, 1, 10, 5, 9, 8 };
static unsigned char triangleTable_195_2[26] =  { 24, 0, 11, 3, 10, 9, 7, 5, 9, 5, 10, 1, 10, 3, 7, 9, 8, 3, 7, 8, 9, 10, 1, 7, 3, 11 };
static unsigned char triangleTable_195_3[26] =  { 24, 1, 12, 3, 1, 7, 12, 11, 12, 7, 5, 12, 8, 3, 1, 10, 12, 11, 12, 10, 5, 9, 12, 12, 9, 8 };
static unsigned char triangleTable_195_4[26] =  { 24, 1, 12, 10, 11, 9, 12, 1, 12, 9, 8, 12, 5, 10, 11, 3, 12, 1, 12, 3, 8, 7, 12, 12, 7, 5 };
static unsigned char * triangleTable_195[5] = { triangleTable_195_0, triangleTable_195_1, triangleTable_195_2, triangleTable_195_3, triangleTable_195_4 };

static unsigned char triangleTable_196_0[11] =  { 9, 0, 1, 2, 11, 7, 1, 11, 7, 5, 1 };
static unsigned char * triangleTable_196[1] = { triangleTable_196_0 };

static unsigned char triangleTable_197_0[14] =  { 12, 0, 2, 11, 7, 1, 2, 7, 8, 3, 0, 1, 7, 5 };
static unsigned char triangleTable_197_1[14] =  { 12, 0, 0, 8, 7, 1, 0, 7, 11, 3, 2, 1, 7, 5 };
static unsigned char triangleTable_197_2[26] =  { 24, 1, 12, 8, 3, 5, 12, 7, 1, 0, 12, 11, 12, 2, 2, 12, 3, 12, 5, 1, 12, 11, 7, 8, 12, 0 };
static unsigned char triangleTable_197_3[26] =  { 24, 1, 12, 11, 3, 5, 12, 7, 1, 2, 12, 8, 12, 0, 0, 12, 3, 12, 5, 1, 12, 8, 7, 11, 12, 2 };
static unsigned char * triangleTable_197[4] = { triangleTable_197_0, triangleTable_197_1, triangleTable_197_2, triangleTable_197_3 };

static unsigned char triangleTable_198_0[14] =  { 12, 0, 11, 7, 2, 9, 0, 2, 7, 5, 9, 7, 9, 2 };
static unsigned char * triangleTable_198[1] = { triangleTable_198_0 };

static unsigned char triangleTable_199_0[11] =  { 9, 0, 11, 3, 2, 8, 7, 9, 7, 5, 9 };
static unsigned char triangleTable_199_1[17] =  { 15, 0, 3, 2, 9, 7, 5, 11, 2, 5, 9, 3, 9, 8, 11, 5, 2 };
static unsigned char * triangleTable_199[2] = { triangleTable_199_0, triangleTable_199_1 };

static unsigned char triangleTable_200_0[11] =  { 9, 0, 5, 10, 2, 3, 5, 2, 3, 7, 5 };
static unsigned char * triangleTable_200[1] = { triangleTable_200_0 };

static unsigned char triangleTable_201_0[14] =  { 12, 0, 2, 0, 10, 0, 8, 7, 0, 7, 5, 10, 0, 5 };
static unsigned char * triangleTable_201[1] = { triangleTable_201_0 };

static unsigned char triangleTable_202_0[14] =  { 12, 0, 10, 2, 3, 5, 10, 3, 0, 1, 9, 5, 3, 7 };
static unsigned char triangleTable_202_1[14] =  { 12, 0, 9, 0, 3, 5, 9, 3, 2, 1, 10, 5, 3, 7 };
static unsigned char triangleTable_202_2[26] =  { 24, 1, 12, 0, 1, 7, 12, 3, 5, 9, 12, 2, 12, 10, 10, 12, 1, 12, 7, 5, 12, 2, 3, 0, 12, 9 };
static unsigned char triangleTable_202_3[26] =  { 24, 1, 12, 2, 1, 7, 12, 3, 5, 10, 12, 0, 12, 9, 9, 12, 1, 12, 7, 5, 12, 0, 3, 2, 12, 10 };
static unsigned char * triangleTable_202[4] = { triangleTable_202_0, triangleTable_202_1, triangleTable_202_2, triangleTable_202_3 };

static unsigned char triangleTable_203_0[11] =  { 9, 0, 1, 10, 2, 5, 9, 7, 9, 8, 7 };
static unsigned char triangleTable_203_1[17] =  { 15, 0, 10, 2, 7, 9, 8, 1, 2, 8, 7, 10, 7, 5, 1, 8, 2 };
static unsigned char * triangleTable_203[2] = { triangleTable_203_0, triangleTable_203_1 };

static unsigned char triangleTable_204_0[8] =  { 6, 0, 5, 1, 3, 3, 7, 5 };
static unsigned char * triangleTable_204[1] = { triangleTable_204_0 };

static unsigned char triangleTable_205_0[11] =  { 9, 0, 0, 8, 7, 0, 7, 1, 7, 5, 1 };
static unsigned char * triangleTable_205[1] = { triangleTable_205_0 };

static unsigned char triangleTable_206_0[11] =  { 9, 0, 9, 0, 3, 9, 3, 5, 3, 7, 5 };
static unsigned char * triangleTable_206[1] = { triangleTable_206_0 };

static unsigned char triangleTable_207_0[8] =  { 6, 0, 7, 9, 8, 9, 7, 5 };
static unsigned char * triangleTable_207[1] = { triangleTable_207_0 };

static unsigned char triangleTable_208_0[11] =  { 9, 0, 8, 4, 5, 10, 8, 5, 10, 11, 8 };
static unsigned char * triangleTable_208[1] = { triangleTable_208_0 };

static unsigned char triangleTable_209_0[14] =  { 12, 0, 3, 0, 11, 5, 10, 11, 0, 4, 5, 0, 5, 11 };
static unsigned char * triangleTable_209[1] = { triangleTable_209_0 };

static unsigned char triangleTable_210_0[14] =  { 12, 0, 4, 5, 10, 8, 4, 10, 1, 9, 0, 8, 10, 11 };
static unsigned char triangleTable_210_1[14] =  { 12, 0, 0, 1, 10, 8, 0, 10, 5, 9, 4, 8, 10, 11 };
static unsigned char triangleTable_210_2[26] =  { 24, 1, 12, 1, 9, 11, 12, 10, 8, 0, 12, 5, 12, 4, 4, 12, 9, 12, 11, 8, 12, 5, 10, 1, 12, 0 };
static unsigned char triangleTable_210_3[26] =  { 24, 1, 12, 5, 9, 11, 12, 10, 8, 4, 12, 1, 12, 0, 0, 12, 9, 12, 11, 8, 12, 1, 10, 5, 12, 4 };
static unsigned char * triangleTable_210[4] = { triangleTable_210_0, triangleTable_210_1, triangleTable_210_2, triangleTable_210_3 };

static unsigned char triangleTable_211_0[11] =  { 9, 0, 5, 9, 4, 1, 10, 3, 10, 11, 3 };
static unsigned char triangleTable_211_1[17] =  { 15, 0, 9, 4, 3, 10, 11, 5, 4, 11, 3, 9, 3, 1, 5, 11, 4 };
static unsigned char * triangleTable_211[2] = { triangleTable_211_0, triangleTable_211_1 };

static unsigned char triangleTable_212_0[14] =  { 12, 0, 5, 1, 4, 1, 2, 11, 1, 11, 8, 4, 1, 8 };
static unsigned char * triangleTable_212[1] = { triangleTable_212_0 };

static unsigned char triangleTable_213_0[11] =  { 9, 0, 3, 2, 11, 1, 0, 5, 0, 4, 5 };
static unsigned char triangleTable_213_1[17] =  { 15, 0, 2, 11, 5, 0, 4, 3, 11, 4, 5, 2, 5, 1, 3, 4, 11 };
static unsigned char * triangleTable_213[2] = { triangleTable_213_0, triangleTable_213_1 };

static unsigned char triangleTable_214_0[11] =  { 9, 0, 9, 4, 5, 8, 0, 11, 0, 2, 11 };
static unsigned char triangleTable_214_1[17] =  { 15, 0, 4, 5, 11, 0, 2, 9, 5, 2, 11, 4, 11, 8, 9, 2, 5 };
static unsigned char * triangleTable_214[2] = { triangleTable_214_0, triangleTable_214_1 };

static unsigned char triangleTable_215_0[8] =  { 6, 0, 5, 9, 4, 3, 2, 11 };
static unsigned char triangleTable_215_1[20] =  { 18, 0, 9, 4, 3, 2, 9, 3, 5, 11, 4, 5, 9, 2, 11, 5, 2, 3, 4, 11 };
static unsigned char * triangleTable_215[2] = { triangleTable_215_0, triangleTable_215_1 };

static unsigned char triangleTable_216_0[14] =  { 12, 0, 10, 8, 5, 10, 3, 8, 2, 3, 10, 5, 8, 4 };
static unsigned char * triangleTable_216[1] = { triangleTable_216_0 };

static unsigned char triangleTable_217_0[11] =  { 9, 0, 5, 10, 2, 5, 2, 4, 2, 0, 4 };
static unsigned char * triangleTable_217[1] = { triangleTable_217_0 };

static unsigned char triangleTable_218_0[11] =  { 9, 0, 10, 2, 1, 4, 5, 9, 0, 3, 8 };
static unsigned char triangleTable_218_1[17] =  { 15, 0, 10, 2, 1, 3, 8, 4, 3, 4, 5, 3, 5, 0, 9, 0, 5 };
static unsigned char triangleTable_218_2[17] =  { 15, 0, 3, 8, 0, 4, 5, 10, 4, 10, 2, 4, 2, 9, 1, 9, 2 };
static unsigned char triangleTable_218_3[17] =  { 15, 0, 4, 5, 9, 10, 2, 3, 10, 3, 8, 10, 8, 1, 0, 1, 8 };
static unsigned char triangleTable_218_4[29] =  { 27, 1, 2, 1, 12, 1, 9, 12, 10, 12, 5, 0, 12, 9, 3, 8, 12, 4, 5, 12, 3, 12, 0, 2, 12, 10, 12, 8, 4 };
static unsigned char triangleTable_218_5[29] =  { 27, 1, 5, 9, 12, 9, 0, 12, 4, 12, 8, 1, 12, 0, 10, 2, 12, 3, 8, 12, 10, 12, 1, 5, 12, 4, 12, 2, 3 };
static unsigned char triangleTable_218_6[29] =  { 27, 1, 8, 0, 12, 0, 1, 12, 3, 12, 2, 9, 12, 1, 4, 5, 12, 10, 2, 12, 4, 12, 9, 8, 12, 3, 12, 5, 10 };
static unsigned char triangleTable_218_7[17] =  { 15, 0, 8, 4, 5, 8, 2, 3, 0, 1, 9, 8, 5, 2, 10, 2, 5 };
static unsigned char * triangleTable_218[8] = 
{ 
  triangleTable_218_0, triangleTable_218_1, triangleTable_218_2, triangleTable_218_3, triangleTable_218_4, triangleTable_218_5, triangleTable_218_6, triangleTable_218_7
};

static unsigned char triangleTable_219_0[8] =  { 6, 0, 2, 1, 10, 5, 9, 4 };
static unsigned char triangleTable_219_1[14] =  { 12, 0, 2, 9, 4, 5, 10, 2, 2, 4, 5, 9, 2, 1 };
static unsigned char * triangleTable_219[2] = { triangleTable_219_0, triangleTable_219_1 };

static unsigned char triangleTable_220_0[11] =  { 9, 0, 8, 4, 5, 8, 5, 3, 5, 1, 3 };
static unsigned char * triangleTable_220[1] = { triangleTable_220_0 };

static unsigned char triangleTable_221_0[8] =  { 6, 0, 0, 5, 1, 5, 0, 4 };
static unsigned char * triangleTable_221[1] = { triangleTable_221_0 };

static unsigned char triangleTable_222_0[8] =  { 6, 0, 5, 9, 4, 8, 0, 3 };
static unsigned char triangleTable_222_1[14] =  { 12, 0, 5, 0, 3, 8, 4, 5, 5, 3, 8, 0, 5, 9 };
static unsigned char * triangleTable_222[2] = { triangleTable_222_0, triangleTable_222_1 };

static unsigned char triangleTable_223_0[5] =  { 3, 0, 4, 5, 9 };
static unsigned char * triangleTable_223[1] = { triangleTable_223_0 };

static unsigned char triangleTable_224_0[11] =  { 9, 0, 11, 7, 4, 9, 11, 4, 9, 10, 11 };
static unsigned char * triangleTable_224[1] = { triangleTable_224_0 };

static unsigned char triangleTable_225_0[14] =  { 12, 0, 7, 4, 9, 11, 7, 9, 0, 8, 3, 11, 9, 10 };
static unsigned char triangleTable_225_1[14] =  { 12, 0, 3, 0, 9, 11, 3, 9, 4, 8, 7, 11, 9, 10 };
static unsigned char triangleTable_225_2[26] =  { 24, 1, 12, 0, 8, 10, 12, 9, 11, 3, 12, 4, 12, 7, 7, 12, 8, 12, 10, 11, 12, 4, 9, 0, 12, 3 };
static unsigned char triangleTable_225_3[26] =  { 24, 1, 12, 4, 8, 10, 12, 9, 11, 7, 12, 0, 12, 3, 3, 12, 8, 12, 10, 11, 12, 0, 9, 4, 12, 7 };
static unsigned char * triangleTable_225[4] = { triangleTable_225_0, triangleTable_225_1, triangleTable_225_2, triangleTable_225_3 };

static unsigned char triangleTable_226_0[14] =  { 12, 0, 10, 11, 1, 11, 7, 4, 11, 4, 0, 1, 11, 0 };
static unsigned char * triangleTable_226[1] = { triangleTable_226_0 };

static unsigned char triangleTable_227_0[11] =  { 9, 0, 8, 7, 4, 11, 3, 10, 3, 1, 10 };
static unsigned char triangleTable_227_1[17] =  { 15, 0, 7, 4, 10, 3, 1, 8, 4, 1, 10, 7, 10, 11, 8, 1, 4 };
static unsigned char * triangleTable_227[2] = { triangleTable_227_0, triangleTable_227_1 };

static unsigned char triangleTable_228_0[14] =  { 12, 0, 7, 1, 11, 7, 9, 1, 4, 9, 7, 11, 1, 2 };
static unsigned char * triangleTable_228[1] = { triangleTable_228_0 };

static unsigned char triangleTable_229_0[11] =  { 9, 0, 2, 11, 3, 9, 1, 0, 8, 7, 4 };
static unsigned char triangleTable_229_1[17] =  { 15, 0, 2, 11, 3, 7, 4, 9, 7, 9, 1, 7, 1, 8, 0, 8, 1 };
static unsigned char triangleTable_229_2[17] =  { 15, 0, 7, 4, 8, 9, 1, 2, 9, 2, 11, 9, 11, 0, 3, 0, 11 };
static unsigned char triangleTable_229_3[17] =  { 15, 0, 9, 1, 0, 2, 11, 7, 2, 7, 4, 2, 4, 3, 8, 3, 4 };
static unsigned char triangleTable_229_4[29] =  { 27, 1, 11, 3, 12, 3, 0, 12, 2, 12, 1, 8, 12, 0, 7, 4, 12, 9, 1, 12, 7, 12, 8, 11, 12, 2, 12, 4, 9 };
static unsigned char triangleTable_229_5[29] =  { 27, 1, 1, 0, 12, 0, 8, 12, 9, 12, 4, 3, 12, 8, 2, 11, 12, 7, 4, 12, 2, 12, 3, 1, 12, 9, 12, 11, 7 };
static unsigned char triangleTable_229_6[29] =  { 27, 1, 4, 8, 12, 8, 3, 12, 7, 12, 11, 0, 12, 3, 9, 1, 12, 2, 11, 12, 9, 12, 0, 4, 12, 7, 12, 1, 2 };
static unsigned char triangleTable_229_7[17] =  { 15, 0, 4, 9, 1, 4, 11, 7, 8, 3, 0, 4, 1, 11, 2, 11, 1 };
static unsigned char * triangleTable_229[8] = 
{ 
  triangleTable_229_0, triangleTable_229_1, triangleTable_229_2, triangleTable_229_3, triangleTable_229_4, triangleTable_229_5, triangleTable_229_6, triangleTable_229_7
};

static unsigned char triangleTable_230_0[11] =  { 9, 0, 11, 7, 4, 11, 4, 2, 4, 0, 2 };
static unsigned char * triangleTable_230[1] = { triangleTable_230_0 };

static unsigned char triangleTable_231_0[8] =  { 6, 0, 2, 11, 3, 8, 7, 4 };
static unsigned char triangleTable_231_1[14] =  { 12, 0, 2, 7, 4, 8, 3, 2, 2, 4, 8, 7, 2, 11 };
static unsigned char * triangleTable_231[2] = { triangleTable_231_0, triangleTable_231_1 };

static unsigned char triangleTable_232_0[14] =  { 12, 0, 2, 3, 10, 4, 9, 10, 3, 7, 4, 3, 4, 10 };
static unsigned char * triangleTable_232[1] = { triangleTable_232_0 };

static unsigned char triangleTable_233_0[11] =  { 9, 0, 4, 8, 7, 0, 9, 2, 9, 10, 2 };
static unsigned char triangleTable_233_1[17] =  { 15, 0, 8, 7, 2, 9, 10, 4, 7, 10, 2, 8, 2, 0, 4, 10, 7 };
static unsigned char * triangleTable_233[2] = { triangleTable_233_0, triangleTable_233_1 };

static unsigned char triangleTable_234_0[11] =  { 9, 0, 2, 1, 10, 0, 3, 4, 3, 7, 4 };
static unsigned char triangleTable_234_1[17] =  { 15, 0, 1, 10, 4, 3, 7, 2, 10, 7, 4, 1, 4, 0, 2, 7, 10 };
static unsigned char * triangleTable_234[2] = { triangleTable_234_0, triangleTable_234_1 };

static unsigned char triangleTable_235_0[8] =  { 6, 0, 1, 10, 2, 7, 4, 8 };
static unsigned char triangleTable_235_1[20] =  { 18, 0, 10, 2, 7, 4, 10, 7, 1, 8, 2, 1, 10, 4, 8, 1, 4, 7, 2, 8 };
static unsigned char * triangleTable_235[2] = { triangleTable_235_0, triangleTable_235_1 };

static unsigned char triangleTable_236_0[11] =  { 9, 0, 4, 9, 1, 4, 1, 7, 1, 3, 7 };
static unsigned char * triangleTable_236[1] = { triangleTable_236_0 };

static unsigned char triangleTable_237_0[8] =  { 6, 0, 1, 0, 9, 4, 8, 7 };
static unsigned char triangleTable_237_1[14] =  { 12, 0, 1, 8, 7, 4, 9, 1, 1, 7, 4, 8, 1, 0 };
static unsigned char * triangleTable_237[2] = { triangleTable_237_0, triangleTable_237_1 };

static unsigned char triangleTable_238_0[8] =  { 6, 0, 4, 3, 7, 3, 4, 0 };
static unsigned char * triangleTable_238[1] = { triangleTable_238_0 };

static unsigned char triangleTable_239_0[5] =  { 3, 0, 4, 8, 7 };
static unsigned char * triangleTable_239[1] = { triangleTable_239_0 };

static unsigned char triangleTable_240_0[8] =  { 6, 0, 9, 10, 11, 11, 8, 9 };
static unsigned char * triangleTable_240[1] = { triangleTable_240_0 };

static unsigned char triangleTable_241_0[11] =  { 9, 0, 3, 0, 9, 3, 9, 11, 9, 10, 11 };
static unsigned char * triangleTable_241[1] = { triangleTable_241_0 };

static unsigned char triangleTable_242_0[11] =  { 9, 0, 0, 1, 10, 0, 10, 8, 10, 11, 8 };
static unsigned char * triangleTable_242[1] = { triangleTable_242_0 };

static unsigned char triangleTable_243_0[8] =  { 6, 0, 3, 10, 11, 10, 3, 1 };
static unsigned char * triangleTable_243[1] = { triangleTable_243_0 };

static unsigned char triangleTable_244_0[11] =  { 9, 0, 1, 2, 11, 1, 11, 9, 11, 8, 9 };
static unsigned char * triangleTable_244[1] = { triangleTable_244_0 };

static unsigned char triangleTable_245_0[8] =  { 6, 0, 11, 3, 2, 1, 0, 9 };
static unsigned char triangleTable_245_1[14] =  { 12, 0, 11, 0, 9, 1, 2, 11, 11, 9, 1, 0, 11, 3 };
static unsigned char * triangleTable_245[2] = { triangleTable_245_0, triangleTable_245_1 };

static unsigned char triangleTable_246_0[8] =  { 6, 0, 11, 0, 2, 0, 11, 8 };
static unsigned char * triangleTable_246[1] = { triangleTable_246_0 };

static unsigned char triangleTable_247_0[5] =  { 3, 0, 2, 11, 3 };
static unsigned char * triangleTable_247[1] = { triangleTable_247_0 };

static unsigned char triangleTable_248_0[11] =  { 9, 0, 2, 3, 8, 2, 8, 10, 8, 9, 10 };
static unsigned char * triangleTable_248[1] = { triangleTable_248_0 };

static unsigned char triangleTable_249_0[8] =  { 6, 0, 9, 2, 0, 2, 9, 10 };
static unsigned char * triangleTable_249[1] = { triangleTable_249_0 };

static unsigned char triangleTable_250_0[8] =  { 6, 0, 10, 2, 1, 0, 3, 8 };
static unsigned char triangleTable_250_1[14] =  { 12, 0, 10, 3, 8, 0, 1, 10, 10, 8, 0, 3, 10, 2 };
static unsigned char * triangleTable_250[2] = { triangleTable_250_0, triangleTable_250_1 };

static unsigned char triangleTable_251_0[5] =  { 3, 0, 2, 1, 10 };
static unsigned char * triangleTable_251[1] = { triangleTable_251_0 };

static unsigned char triangleTable_252_0[8] =  { 6, 0, 8, 1, 3, 1, 8, 9 };
static unsigned char * triangleTable_252[1] = { triangleTable_252_0 };

static unsigned char triangleTable_253_0[5] =  { 3, 0, 9, 1, 0 };
static unsigned char * triangleTable_253[1] = { triangleTable_253_0 };

static unsigned char triangleTable_254_0[5] =  { 3, 0, 0, 3, 8 };
static unsigned char * triangleTable_254[1] = { triangleTable_254_0 };

static unsigned char ** triangleTable[256] = 
{ 
  NULL, triangleTable_1, triangleTable_2, triangleTable_3, triangleTable_4, triangleTable_5, triangleTable_6, triangleTable_7, 
  triangleTable_8, triangleTable_9, triangleTable_10, triangleTable_11, triangleTable_12, triangleTable_13, triangleTable_14, triangleTable_15, 
  triangleTable_16, triangleTable_17, triangleTable_18, triangleTable_19, triangleTable_20, triangleTable_21, triangleTable_22, triangleTable_23, 
  triangleTable_24, triangleTable_25, triangleTable_26, triangleTable_27, triangleTable_28, triangleTable_29, triangleTable_30, triangleTable_31, 
  triangleTable_32, triangleTable_33, triangleTable_34, triangleTable_35, triangleTable_36, triangleTable_37, triangleTable_38, triangleTable_39, 
  triangleTable_40, triangleTable_41, triangleTable_42, triangleTable_43, triangleTable_44, triangleTable_45, triangleTable_46, triangleTable_47, 
  triangleTable_48, triangleTable_49, triangleTable_50, triangleTable_51, triangleTable_52, triangleTable_53, triangleTable_54, triangleTable_55, 
  triangleTable_56, triangleTable_57, triangleTable_58, triangleTable_59, triangleTable_60, triangleTable_61, triangleTable_62, triangleTable_63, 
  triangleTable_64, triangleTable_65, triangleTable_66, triangleTable_67, triangleTable_68, triangleTable_69, triangleTable_70, triangleTable_71, 
  triangleTable_72, triangleTable_73, triangleTable_74, triangleTable_75, triangleTable_76, triangleTable_77, triangleTable_78, triangleTable_79, 
  triangleTable_80, triangleTable_81, triangleTable_82, triangleTable_83, triangleTable_84, triangleTable_85, triangleTable_86, triangleTable_87, 
  triangleTable_88, triangleTable_89, triangleTable_90, triangleTable_91, triangleTable_92, triangleTable_93, triangleTable_94, triangleTable_95, 
  triangleTable_96, triangleTable_97, triangleTable_98, triangleTable_99, triangleTable_100, triangleTable_101, triangleTable_102, triangleTable_103, 
  triangleTable_104, triangleTable_105, triangleTable_106, triangleTable_107, triangleTable_108, triangleTable_109, triangleTable_110, triangleTable_111, 
  triangleTable_112, triangleTable_113, triangleTable_114, triangleTable_115, triangleTable_116, triangleTable_117, triangleTable_118, triangleTable_119, 
  triangleTable_120, triangleTable_121, triangleTable_122, triangleTable_123, triangleTable_124, triangleTable_125, triangleTable_126, triangleTable_127, 
  triangleTable_128, triangleTable_129, triangleTable_130, triangleTable_131, triangleTable_132, triangleTable_133, triangleTable_134, triangleTable_135, 
  triangleTable_136, triangleTable_137, triangleTable_138, triangleTable_139, triangleTable_140, triangleTable_141, triangleTable_142, triangleTable_143, 
  triangleTable_144, triangleTable_145, triangleTable_146, triangleTable_147, triangleTable_148, triangleTable_149, triangleTable_150, triangleTable_151, 
  triangleTable_152, triangleTable_153, triangleTable_154, triangleTable_155, triangleTable_156, triangleTable_157, triangleTable_158, triangleTable_159, 
  triangleTable_160, triangleTable_161, triangleTable_162, triangleTable_163, triangleTable_164, triangleTable_165, triangleTable_166, triangleTable_167, 
  triangleTable_168, triangleTable_169, triangleTable_170, triangleTable_171, triangleTable_172, triangleTable_173, triangleTable_174, triangleTable_175, 
  triangleTable_176, triangleTable_177, triangleTable_178, triangleTable_179, triangleTable_180, triangleTable_181, triangleTable_182, triangleTable_183, 
  triangleTable_184, triangleTable_185, triangleTable_186, triangleTable_187, triangleTable_188, triangleTable_189, triangleTable_190, triangleTable_191, 
  triangleTable_192, triangleTable_193, triangleTable_194, triangleTable_195, triangleTable_196, triangleTable_197, triangleTable_198, triangleTable_199, 
  triangleTable_200, triangleTable_201, triangleTable_202, triangleTable_203, triangleTable_204, triangleTable_205, triangleTable_206, triangleTable_207, 
  triangleTable_208, triangleTable_209, triangleTable_210, triangleTable_211, triangleTable_212, triangleTable_213, triangleTable_214, triangleTable_215, 
  triangleTable_216, triangleTable_217, triangleTable_218, triangleTable_219, triangleTable_220, triangleTable_221, triangleTable_222, triangleTable_223, 
  triangleTable_224, triangleTable_225, triangleTable_226, triangleTable_227, triangleTable_228, triangleTable_229, triangleTable_230, triangleTable_231, 
  triangleTable_232, triangleTable_233, triangleTable_234, triangleTable_235, triangleTable_236, triangleTable_237, triangleTable_238, triangleTable_239, 
  triangleTable_240, triangleTable_241, triangleTable_242, triangleTable_243, triangleTable_244, triangleTable_245, triangleTable_246, triangleTable_247, 
  triangleTable_248, triangleTable_249, triangleTable_250, triangleTable_251, triangleTable_252, triangleTable_253, triangleTable_254, NULL
};

