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

#include "mat3d.h"
#include "eig3.h"

const Mat3d Mat3d::Identity(1.0);
const Mat3d Mat3d::Zero(0.0);

// This routine calls a public domain routine (eigen_decomposition), which was 
// downloaded from:
// http://barnesc.blogspot.com/2007/02/eigenvectors-of-3x3-symmetric-matrix.html
// According to the header file of eig3.h, the C version in eig3.{h,cpp} 
// was obtained by copying code from the public domain Java library JAMA, 
// and declaring the resulting C code to also be public domain.
// The eig3.{h,cpp} files are included in this package, intact as they were
// downloaded from the Internet.

// This routine was written by Jernej Barbic.
void eigen_sym(Mat3d & a, Vec3d & eig_val, Vec3d eig_vec[3])
{
  double A[3][3] = { {a[0][0], a[0][1], a[0][2]},
                     {a[1][0], a[1][1], a[1][2]},
                     {a[2][0], a[2][1], a[2][2]} };
  double V[3][3];
  double d[3];
  eigen_decomposition(A, V, d);

  eig_val = Vec3d(d[2],d[1],d[0]);
  if(eig_vec)
  {
    eig_vec[0] = Vec3d(V[0][2], V[1][2], V[2][2]);
    eig_vec[1] = Vec3d(V[0][1], V[1][1], V[2][1]);
    eig_vec[2] = Vec3d(V[0][0], V[1][0], V[2][0]);
  }
}

/*
    The implementation follows section 5 of 
    G. Irving, J. Teran, and R. Fedkiw. Invertible Finite Elements for Robust Simulation of Large Deformation. 
    In Symp. on Computer Animation (SCA), pages 131–140, 2004.
    It computes a^T a, and computes its eigenvectors, a^T a = V Sigma^2 V^T . 
    Sigma is then recovered using sqrt from Sigma^2.
    To recover U, compute U = F * V * diag(Sigma^{-1}).
    Care must be taken when singular values of Sigma are small (this is 
    handled in the code).

    We have also added the ability to compute standard SVD (modifiedSVD = 0).
*/

int SVD(Mat3d & F, Mat3d & U, Vec3d & Sigma, Mat3d & V, double singularValue_eps, int modifiedSVD)
{
  // The code handles the following special situations:

  //---------------------------------------------------------
  // 1. det(V) == -1
  //    - multiply the first column of V by -1
  //---------------------------------------------------------
  // 2. An entry of Sigma is near zero
  //---------------------------------------------------------
  // (if modifiedSVD == 1) :
  // 3. negative determinant (Tet is inverted in solid mechanics).
  //    - check if det(U) == -1
  //    - If yes, then negate the minimal element of Sigma
  //      and the corresponding column of U
  //---------------------------------------------------------

  // form F^T F and do eigendecomposition
  Mat3d normalEq = trans(F) * F;
  Vec3d eigenValues;
  Vec3d eigenVectors[3];

  eigen_sym(normalEq, eigenValues, eigenVectors);

  V.set(eigenVectors[0][0], eigenVectors[1][0], eigenVectors[2][0],
    eigenVectors[0][1], eigenVectors[1][1], eigenVectors[2][1],
    eigenVectors[0][2], eigenVectors[1][2], eigenVectors[2][2]);
  /*
    printf("--- original V ---\n");
    V.print();
    printf("--- eigenValues ---\n");
    printf("%G %G %G\n", eigenValues[0], eigenValues[1], eigenValues[2]);
  */

  // Handle situation:
  // 1. det(V) == -1
  //    - multiply the first column of V by -1
  if (det(V) < 0.0)
  {
    // convert V into a rotation (multiply column 1 by -1)
    V[0][0] *= -1.0;
    V[1][0] *= -1.0;
    V[2][0] *= -1.0;
  }

  Sigma[0] = (eigenValues[0] > 0.0) ? sqrt(eigenValues[0]) : 0.0;
  Sigma[1] = (eigenValues[1] > 0.0) ? sqrt(eigenValues[1]) : 0.0;
  Sigma[2] = (eigenValues[2] > 0.0) ? sqrt(eigenValues[2]) : 0.0;

  //printf("--- Sigma ---\n");
  //printf("%G %G %G\n", Sigma[0][0], Sigma[1][1], Sigma[2][2]);

  // compute inverse of singular values
  // also check if singular values are close to zero
  Vec3d SigmaInverse;
  SigmaInverse[0] = (Sigma[0] > singularValue_eps) ? (1.0 / Sigma[0]) : 0.0;
  SigmaInverse[1] = (Sigma[1] > singularValue_eps) ? (1.0 / Sigma[1]) : 0.0;
  SigmaInverse[2] = (Sigma[2] > singularValue_eps) ? (1.0 / Sigma[2]) : 0.0;
  
  // compute U using the formula:
  // U = F * V * diag(SigmaInverse)
  U = F * V;
  U.multiplyDiagRight(SigmaInverse);

  // In theory, U is now orthonormal, U^T U = U U^T = I .. it may be a rotation or a reflection, depending on F.
  // But in practice, if singular values are small or zero, it may not be orthonormal, so we need to fix it.
  // Handle situation:
  // 2. An entry of Sigma is near zero
  // ---------------------------------------------------------

  /*
    printf("--- SigmaInverse ---\n");
    SigmaInverse.print();
    printf(" --- U ---\n");
    U.print();
  */
  
  if ((Sigma[0] < singularValue_eps) && (Sigma[1] < singularValue_eps) && (Sigma[2] < singularValue_eps))
  {
    // extreme case, all singular values are small, material has collapsed almost to a point
    // see [Irving 04], p. 4
    U.set(1.0, 0.0, 0.0,
          0.0, 1.0, 0.0,
          0.0, 0.0, 1.0);
  }
  else 
  {
    // handle the case where two singular values are small, but the third one is not
    // handle it by computing two (arbitrary) vectors orthogonal to the eigenvector for the large singular value
    int done = 0;
    for(int dim=0; dim<3; dim++)
    {
      int dimA = dim;
      int dimB = (dim + 1) % 3;
      int dimC = (dim + 2) % 3;
      if ((Sigma[dimB] < singularValue_eps) && (Sigma[dimC] < singularValue_eps))
      {
        // only the column dimA can be trusted, columns dimB and dimC correspond to tiny singular values
        Vec3d tmpVec1(U[0][dimA], U[1][dimA], U[2][dimA]); // column dimA
        Vec3d tmpVec2;
        tmpVec2 = tmpVec1.findOrthonormalVector();
        Vec3d tmpVec3 = norm(cross(tmpVec1, tmpVec2));
        U[0][dimB] = tmpVec2[0];
        U[1][dimB] = tmpVec2[1];
        U[2][dimB] = tmpVec2[2];
        U[0][dimC] = tmpVec3[0];
        U[1][dimC] = tmpVec3[1];
        U[2][dimC] = tmpVec3[2];
        if (det(U) < 0.0)
        {
          U[0][dimB] *= -1.0;
          U[1][dimB] *= -1.0;
          U[2][dimB] *= -1.0;
        }
        done = 1;
        break; // out of for
      }
    }

    // handle the case where one singular value is small, but the other two are not
    // handle it by computing the cross product of the two eigenvectors for the two large singular values
    if (!done) 
    {
      for(int dim=0; dim<3; dim++)
      {
        int dimA = dim;
        int dimB = (dim + 1) % 3;
        int dimC = (dim + 2) % 3;

        if (Sigma[dimA] < singularValue_eps)
        {
          // columns dimB and dimC are both good, but column dimA corresponds to a tiny singular value
          Vec3d tmpVec1(U[0][dimB], U[1][dimB], U[2][dimB]); // column dimB
          Vec3d tmpVec2(U[0][dimC], U[1][dimC], U[2][dimC]); // column dimC
          Vec3d tmpVec3 = norm(cross(tmpVec1, tmpVec2));
          U[0][dimA] = tmpVec3[0];
          U[1][dimA] = tmpVec3[1];
          U[2][dimA] = tmpVec3[2];
          if (det(U) < 0.0)
          {
            U[0][dimA] *= -1.0;
            U[1][dimA] *= -1.0;
            U[2][dimA] *= -1.0;
          }
          done = 1;
          break; // out of for
        }
      }
    }

    if ((!done) && (modifiedSVD == 1))
    {
      // Handle situation:
      // 3. negative determinant (Tet is inverted in solid mechanics)
      //    - check if det(U) == -1
      //    - If yes, then negate the minimal element of Sigma
      //      and the corresponding column of U

      double detU = det(U);
      if (detU < 0.0)
      {
        // negative determinant
        // find the smallest singular value (they are all non-negative)
        int smallestSingularValueIndex = 0;
        for(int dim=1; dim<3; dim++)
          if (Sigma[dim] < Sigma[smallestSingularValueIndex])
            smallestSingularValueIndex = dim;

        // negate the smallest singular value
        Sigma[smallestSingularValueIndex] *= -1.0;
        U[0][smallestSingularValueIndex] *= -1.0;
        U[1][smallestSingularValueIndex] *= -1.0;
        U[2][smallestSingularValueIndex] *= -1.0;
      }
    }
  }

  /*
    printf("U = \n");
    U.print();
    printf("Sigma = \n");
    Sigma.print();
    printf("V = \n");
    V.print();
  */

  return 0;
}

  // NOTE: This particular routine is not publicly released, as its implementation
  // was taken from Numerical Recipes, which is not free software.
  // (you can use the eigen_sym routine above which is public domain)
bool eigen_sym_NR(Mat3d & M, Vec3d & eig_val, Vec3d eig_vec[3], int maxIterations, double epsilon)
{
  return false;
}

