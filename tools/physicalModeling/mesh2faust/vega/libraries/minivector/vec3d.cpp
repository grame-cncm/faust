/*
* Copyright (c) 2008, Carnegie Mellon University
* All rights reserved.
*
* Code author: Jernej Barbic
* Research: Jernej Barbic, Doug L. James
* Funding: NSF, Link Foundation
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of Carnegie Mellon University, nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "vec3d.h"

/*
  Given an input vector v, find a unit vector that is orthogonal to it 
*/
Vec3d Vec3d::findOrthonormalVector() const
{
  // find smallest abs component of v
  int smallestIndex = 0;
  for(int dim=1; dim<3; dim++)
    if (fabs(elt[dim]) < fabs(elt[smallestIndex]))
      smallestIndex = dim;

  Vec3d axis(0.0, 0.0, 0.0);
  axis[smallestIndex] = 1.0;

  // this cross-product will be non-zero (as long as v is not zero)
  Vec3d result = norm(cross(elt, axis));
  return result;
}

