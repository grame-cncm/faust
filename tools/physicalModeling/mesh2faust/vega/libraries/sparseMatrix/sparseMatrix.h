/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * "sparseMatrix" library , Copyright (C) 2007 CMU, 2009 MIT, 2016 USC   *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Fun Shing Sin, Daniel Schroeder,             *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
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

#ifndef _SPARSE_MATRIX_H_
#define _SPARSE_MATRIX_H_

/*
  The "SparseMatrix" class implements double-precision sparse matrices 
  with common algebraic operations such as incremental construction, 
  addition, mtx-vec multiplication, row-column deletion. 
  The matrices can be loaded from and saved to a file.

  The matrix can be rectangular (it need not be square). 
  In memory, the matrix is stored in a row-based format. 
  For each matrix row, the class stores the integer
  indices of the columns containing non-zero entries, 
  together with the corresponding double precision values. 
  All quantities (rows, columns, etc.) in this class are 0-indexed.

  Also included is a Conjugate Gradient iterative linear system solver 
  (for positive-definite large sparse symmetric matrices).
  The solver can be used without preconditioning, or with diagonal (Jacobi) preconditoning.
  The solver either uses an explicitly provided sparse matrix, or you can only
  provide the matrix-vector multiplication routine (without explicitly giving the matrix).
  The CG Solver was implemented by following Jonathan Shewchuk's 
  "An Introduction to the Conjugate Gradient Method Without the Agonizing Pain":
  http://www.cs.cmu.edu/~jrs/jrspapers.html#cg

  The class also includes a Gauss-Seidel iterative linear system solver.

  There are two classes available to the user: SparseMatrixOutline and SparseMatrix.
  The SparseMatrixOutline class should be used to construct the non-zero 
  locations in the matrix, and (optionally) assign values to them.
  You should then transform it into a SparseMatrix class, via SparseMatrix's
  class constructor. The SparseMatrix class has all the computational routines,
  but you can only add new non-zero entries to SparseMatrixOutline, not
  to SparseMatrix.  The reason for this separation is that SparseMatrixOutline 
  does not know the number of matrix entries ahead of time, so it uses STL's 
  "map" datastructure to store the matrix data. In the SparseMatrix class, however, the number 
  of sparse entries and their locations are fixed, so all operations can use 
  known-length C arrays, which is faster.

  So: you should first create an instance of SparseMatrixOutline, then create 
  an instance of SparseMatrix by passing the SparseMatrixOutline object to 
  SparseMatrix's constructor.
  If your matrix is a text file on disk, you can load it to SparseMatrixOutline, 
  or directly load it into SparseMatrix (which will, however, internally still 
  proceed via SparseMatrixOutline).

  The text disk file format is as follows:
  <number of matrix rows>
  <number of matrix columns>
  one or more data lines, each giving one matrix entry, in the format:
  <row index> <column index> <data value> 
  (indices are 0-indexed)

  Example:
  
    [0 17 -1 0]
  A=[0  5  0 0]
    [3  8  6 0]  

  would be given as:

  3
  4
  0 1 17 
  0 2 -1
  1 1 5
  2 0 3
  2 1 8
  2 2 6
*/

#include <string.h>
#include <vector>
#include <map>

class SparseMatrix;

class SparseMatrixOutline
{
public:
  // makes an empty sparse matrix with numRows rows
  SparseMatrixOutline(int numRows);
  ~SparseMatrixOutline();

  // makes a diagonal numRows x numRows sparse matrix; with a constant diagonal
  SparseMatrixOutline(int numRows, double diagonal);
  // makes a diagonal numRows x numRows sparse matrix; diagonal is a vector of n numbers
  SparseMatrixOutline(int numRows, double * diagonal);

  // loads the sparse matrix from a text file
  // if expand is greater than 1, the routine also expands each element into a diagonal block of size expand x expand... 
  //   (expand option is useful for loading the mass matrix in structural mechanics (with expand=3 in 3D))
  SparseMatrixOutline(const char * filename, int expand=1); 

  // save matrix to a text file
  int Save(const char * filename, int oneIndexed=0) const;

  // add entry at location (i,j) in the matrix
  void AddEntry(int i, int j, double value=0.0);
  // remove entry at location (i,j)
  void RemoveEntry(int i, int j);
  // add a 3x3 matrix at location (3*i, 3*j)
  void AddBlock3x3Entry(int i, int j, const double * matrix3x3); // matrix3x3 should be given in row-major order
  void AddBlock3x3Entry(int i, int j, double value=0.0); // matrix is assigned the value at all 3x3 elements
  // add a block (sparse) matrix (optionally multiplied with "scalarFactor"), starting at row i, and column j
  void AddBlockMatrix(int i, int j, const SparseMatrix * block, double scalarFactor=1.0);
  void IncreaseNumRows(int numAddedRows); // increases the number of matrix rows (new rows are added at the bottom of the matrix, and are all empty)

  void MultiplyRow(int row, double scalar); // multiplies all elements in row 'row' with scalar 'scalar'

  inline int Getn() const { return numRows; } // get number of rows
  inline int GetNumRows() const { return numRows; } // get number of rows
  int GetNumColumns() const; // get the number of columns (i.e., search for max column index)
  int GetNumEntries() const; // get total number of non-zero matrix elements
  double GetEntry(int i, int j) const; // returns the matrix entry at location (i,j) in the matrix (or zero if entry has not been assigned)
  void Print() const;

  // low-level routine which is rarely used
  inline const std::map<int,double> & GetRow(int i) const { return columnEntries[i]; }
  friend class SparseMatrix;

protected:
  int numRows;
  std::vector< std::map<int,double> > columnEntries;
  void Allocate();
};

class SparseMatrix
{
public:

  SparseMatrix(const char * filename); // load from text file (same text file format as SparseMatrixOutline)
  SparseMatrix(SparseMatrixOutline * sparseMatrixOutline); // create it from the outline
  // create it by specifying all entries: number of rows, length of each row, indices of columns of non-zero entries in each row, values of non-zero entries in each row
  // column indices in each row must be sorted (ascending)
  // if shallowCopy=1, the class will not allocate its own internal buffers, but will assume ownership of the input rowLength, columnIndices and columnEntries parameters
  SparseMatrix(int numRows, int * rowLength, int ** columnIndices, double ** columnEntries, int shallowCopy=0); 

  SparseMatrix(const SparseMatrix & source); // copy constructor
  ~SparseMatrix();

  int Save(const char * filename, int oneIndexed=0) const; // save matrix to a disk text file 

  int SaveToMatlabFormat(const char * filename) const; // save matrix to a text file that can be imported into Matlab

  // set/add value to the j-th sparse entry in the given row (NOT to matrix element at (row,j))
  inline void SetEntry(int row, int j, double value) { columnEntries[row][j] = value; }
  inline void AddEntry(int row, int j, double value) { columnEntries[row][j] += value; }
  void ResetToZero(); // reset all entries to zero
  void ResetRowToZero(int row); // reset all entries in the row to zero

  inline int Getn() const { return numRows; } // get the number of rows
  inline int GetNumRows() const { return numRows; }
  inline int GetRowLength(int row) const { return rowLength[row]; }
  int GetNumColumns() const; // get the number of columns (i.e., search for max column index)
  // returns the j-th sparse entry in row i (NOT matrix element at (row, j))
  inline double GetEntry(int row, int j) const { return columnEntries[row][j]; }
  // returns the column index of the j-th sparse entry in the given row
  inline int GetColumnIndex(int row, int j) const { return columnIndices[row][j]; } 
  inline double ** GetEntries() const { return columnEntries; }
  inline int ** GetColumnIndices() const { return columnIndices; }
  inline int * GetRowLengths() const { return rowLength; }

  // finds the compressed column index of element at location (row, jDense)
  // returns -1 if column not found
  int GetInverseIndex(int row, int jDense) const;

  int GetNumEntries() const; // returns the total number of non-zero entries
  double SumEntries() const; // returns the sum of all matrix entries
  void SumRowEntries(double * rowSums) const; // returns the sum of all entries in each row
  double GetMaxAbsEntry() const; // max abs value of a matrix entry
  double GetInfinityNorm() const; // matrix infinity norm: maximum absolute row sum of the matrix
  double GetFrobeniusNorm() const; // matrix Frobenius norm: sqrt of the sum of absolute squares of its elements
  void Print(int sparsePrint=0) const; // prints the matrix out to standard output
  double GetRowNorm2(int row) const;

  // matrix algebra (all involved matrices must have the same pattern of non-zero entries)
  SparseMatrix operator+(const SparseMatrix & mat2) const;
  SparseMatrix operator-(const SparseMatrix & mat2) const;
  friend SparseMatrix operator* (const double alpha, const SparseMatrix & mat2); // warning: this function makes a local copy; "ScalarMultiply" is more efficient
  SparseMatrix & operator=(const SparseMatrix & source); // matrices must have same size and locations of non-zero entries
  SparseMatrix & operator*=(const double alpha);
  SparseMatrix & operator+=(const SparseMatrix & mat2);
  SparseMatrix & operator-=(const SparseMatrix & mat2);
  bool operator==(const SparseMatrix & mat2) const;
  // check whether two sparse matrices share the same size and locations of non-zero entries
  bool SameStructure(const SparseMatrix & mat2) const;
  
  void ScalarMultiply(const double alpha, SparseMatrix * dest=NULL); // dest = alpha * dest (if dest=NULL, operation is applied to this object)
  void ScalarMultiplyAdd(const double alpha, SparseMatrix * dest=NULL); // dest += alpha * dest (if dest=NULL, operation is applied to this object)
  void MultiplyRow(int row, double scalar); // multiplies all elements in row 'row' with scalar 'scalar'

  // multiplies the sparse matrix with the given vector/matrix
  void MultiplyVector(const double * vector, double * result) const; // result = A * vector
  void MultiplyVectorAdd(const double * vector, double * result) const; // result += A * vector
  void MultiplyVector(int startRow, int endRow, const double * vector, double * result) const; // result = A(startRow:endRow-1,:) * vector
  void TransposeMultiplyVector(const double * vector, int resultLength, double * result) const; // result = trans(A) * vector
  void TransposeMultiplyVectorAdd(const double * vector, double * result) const; // result += trans(A) * vector
  void MultiplyMatrix(int numDenseRows, int numDenseColumns, const double * denseMatrix, double * result) const; // result = A * denseMatrix (denseMatrix is a numDenseRows x numDenseColumns dense matrix, result is a numRows x numDenseColumns dense matrix)
  void MultiplyMatrixAdd(int numDenseRows, int numDenseColumns, const double * denseMatrix, double * result) const; // result += A * denseMatrix (denseMatrix is a numDenseRows x numDenseColumns dense matrix, result is a numDenseRows x numDenseColumns dense matrix)
  void MultiplyMatrixTranspose(int numDenseColumns, const double * denseMatrix, double * result) const; // result = A * trans(denseMatrix) (trans(denseMatrix) is a dense matrix with 'numDenseColumns' columns, result is a numRows x numDenseColumns dense matrix)

  // computes <M * vector, vector> (assumes symmetric M)
  double QuadraticForm(const double * vector) const;
  // normalizes vector in the M-norm: vector := vector / sqrt(<M * vector, vector>)  (assumes symmetric M)
  void NormalizeVector(double * vector) const;
  void ConjugateMatrix(const double * U, int r, double * MTilde) const; // computes MTilde = U^T M U (M can be a general square matrix, U need not be a square matrix; number of columns of U is r; sizes of M and U must be such that product is defined; output matrix will have size r x r, stored column-major)
  SparseMatrix ConjugateMatrix(SparseMatrix & U, int verbose=0, int numColumns=-1); // computes U^T M U (M is this matrix, and can be a general square matrix, U need not be a square matrix; sizes of M and U must be such that product is defined); numColumns is the number of columns of the result (U^T M U); this is important because there could be empty columns in U at the right border of the U matrix; if numColumns=-1, the routine will use U->GetNumColumns()

  // builds indices for subsequent faster product computation (below)
  // input: U, MTilde; MTilde must equal U^T M U, computed using the "ConjugateMatrix" routine above
  // output: precomputedIndices
  typedef int *** precomputedIndicesType;
  void BuildConjugationIndices(SparseMatrix & U, SparseMatrix & MTilde, precomputedIndicesType * precomputedIndices); // note: must be debugged
  // input: precomputedIndices, U
  // output: MTilde
  void ConjugateMatrix(precomputedIndicesType precomputedIndices, SparseMatrix & U, SparseMatrix & MTilde); // note: must be debugged

  // writes all entries into the space provided by 'data'
  // space must be pre-allocated
  // data is written row after row, and by non-zero columns within each row
  void MakeLinearDataArray(double * data) const;
  // writes row indices of non-zero entries into array "indices"
  // same order as for data
  void MakeLinearRowIndexArray(int * indices) const;
  // indices in this function version are double to ensure compatibility with Matlab
  void MakeLinearRowIndexArray(double * indices) const;
  // writes column indices
  void MakeLinearColumnIndexArray(int * indices) const;
  void MakeLinearColumnIndexArray(double * indices) const;

  // Make a dense matrix (column-major storage).
  // (this can be a huge matrix for large sparse matrices)
  // Storage in denseMatrix must be pre-allocated.
  // The size of the denseMatrix is: this->GetNumRows() x (numColumns == -1 ? this->GetNumColumns() : numColumns).
  void MakeDenseMatrix(double * denseMatrix, int numColumns=-1) const;
  // also transposes the matrix:
  void MakeDenseMatrixTranspose(int numColumns, double * denseMatrix) const;

  // removes row(s) and column(s) from the matrix
  void RemoveRowColumn(int rowColumn); // 0-indexed
  void RemoveRowsColumns(int numRemovedRowColumns, const int * removedRowColumns, int oneIndexed=0); // the rowColumns must be sorted (ascending)
  void RemoveRowsColumnsSlow(int numRemovedRowColumns, const int * removedRowColumns, int oneIndexed=0); // the rowColumns need not be sorted

  // removes row(s) from the matrix
  void RemoveRow(int row); // 0-indexed
  void RemoveRows(int numRemovedRows, const int * removedRows, int oneIndexed=0); // rows must be sorted (ascending)
  void RemoveRowsSlow(int numRemovedRows, const int * removedRows, int oneIndexed=0); // the rows need not be sorted

  // removes column(s) from the matrix
  void RemoveColumn(int column); // 0-indexed
  void RemoveColumns(int numRemovedColumns, const int * removedColumns, int oneIndexed=0); // columns must be sorted (ascending)
  void RemoveColumnsSlow(int numRemovedColumns, const int * removedColumns, int oneIndexed=0); // columns need not be sorted 

  void IncreaseNumRows(int numAddedRows); // increases the number of matrix rows (new rows are added at the bottom of the matrix, and are all empty)
  void SetRows(const SparseMatrix * source, int startRow, int startColumn=0); // starting with startRow, overwrites the rows with those of matrix "source"; data is written into columns starting at startColumn
  void AppendRowsColumns(const SparseMatrix * source); // appends the matrix "source" at the bottom of matrix, and trans(source) to the right of the matrix

  // transposition (note: the matrix need not be symmetric)
  void BuildTranspositionIndices();
  void FreeTranspositionIndices();
  // returns the list position of the transposed element (row, list position j)
  // must first call BuildTranspositionIndices()
  inline int TransposedIndex(int row, int j) const { return transposedIndices[row][j]; }

  // returns the transposed matrix
  // numColumns is the number of columns in the original matrix;
  // this is important in case there are zero columns at the end of the matrix
  // if numColumns=-1 (default), GetNumColumns() will be called; however, this will lead to a transposed matrix with a fewer number of rows in case of empty columns at the end of the original matrix
  SparseMatrix * Transpose(int numColumns=-1);
  // assign a transposed matrix AT to this matrix; topology of AT must be transpose of topology of this matrix
  // note: this function calls BuildTranspositionIndices internally, so you don't need to call BuildTranspositionIndices first
  void AssignTransposedMatrix(SparseMatrix & AT);

  // checks if the matrix is skew-symmetric
  // the non-zero entry locations must form a symmetric pattern
  // returns max ( abs ( A^T + A ) ) = || A^T + A ||_{\infty}
  // note: this function calls BuildTranspositionIndices internally, so you don't need to call BuildTranspositionIndices first
  double SkewSymmetricCheck(); 
  // makes matrix symmetric by copying upper triangle + diagonal into the lower triangle
  // the non-zero entry locations must form a symmetric pattern
  // note: this function calls BuildTranspositionIndices internally, so you don't need to call BuildTranspositionIndices first
  void SymmetrizeMatrix();

  // pre-computes the sparse columns of diagonal matrix entries
  // this routine will accelerate subsequent GetDiagonal or AddDiagonalMatrix calls, but is not necessary for GetDiagonal or AddDiagonalMatrix
  void BuildDiagonalIndices();
  void FreeDiagonalIndices();
  void GetDiagonal(double * diagonal) const;
  void AddDiagonalMatrix(double * diagonalMatrix);
  void AddDiagonalMatrix(double constDiagonalElement);

  // Build submatrix indices is used for pair of matrices where the sparsity of one matrix is a subset of another matrix (for example, mass matrix and stiffness matrix). 
  // It allows you to assign/add a submatrix to the current matrix.
  // The submatrix begins at row "startRow" and column "startColumn" of this matrix.
  // submatrixID allows you to keep several submatrices at once
  // Call this once to establish the correspondence:
  void BuildSubMatrixIndices(const SparseMatrix & submatrix, int subMatrixID=0, int startRow=0, int startColumn=0);
  void FreeSubMatrixIndices(int subMatrixID=0);
  // assign a submatrix to the current matrix, whose elements are a subset of the elements of the current matrix
  // note: the other entries of the current matrix are unmodified
  void AssignSubMatrix(const SparseMatrix & submatrix, int subMatrixID=0);
  // assign the current matrix to a submatrix
  void AssignToSubMatrix(SparseMatrix & submatrix, int subMatrixID=0) const;
  // add a matrix to the current matrix, whose elements are a subset of the elements of the current matrix
  // += factor * mat2
  // returns *this
  SparseMatrix & AddSubMatrix(double factor, SparseMatrix & submatrix, int subMatrixID=0);

  // Build supermatrix indices is used for pair of matrices with rows/columns removed.
  // It allows you to assign a super matrix to the current matrix.
  // oneIndexed: tells whether the fixed rows and columns are specified 1-indexed or 0-indexed
  // First, call BuildSuperMatrixIndices once to inialize (all fixed rows and columns are indexed with respect the superMatrix):
  void BuildSuperMatrixIndices(int numFixedRowColumns, int * fixedRowColumns, const SparseMatrix * superMatrix, int oneIndexed=0); // use this version if the indices of removed rows and columns are the same
  void BuildSuperMatrixIndices(int numFixedRows, int * fixedRows, int numFixedColumns, int * fixedColumns, const SparseMatrix * superMatrix, int oneIndexed=0); // allows arbitrary row and column indices
  // Then, call this (potentially many times) to quickly assign the values at the appropriate places in the submatrix.
  // For example, you can use this to copy data from a matrix into a submatrix obtained by a previous call to RemoveRowColumns.
  void AssignSuperMatrix(const SparseMatrix & superMatrix);

  // returns the total number of non-zero entries in the lower triangle (including diagonal)
  int GetNumLowerTriangleEntries() const;
  int GetNumUpperTriangleEntries() const;
  // exports the matrix to format for NAG library
  int GenerateNAGFormat(double * a,int * irow,int * icol, int * istr) const;

  void GenerateCompressedRowMajorFormat(double * a, int * ia, int * ja, int upperTriangleOnly=0, int oneIndexed=0) const; 
  void GenerateCompressedRowMajorFormat_four_array(double * values, int * columns, int * pointerB, int * pointerE, int upperTriangleOnly=0, int oneIndexed=0) const; 

  // diagonal solve M * x = b
  // ASSUMES the sparse matrix is diagonal !
  // result is overwritten into rhs
  // (to solve non-diagonal linear systems, you need to use an external library; or you can use the CGSolver class, or you can use the Gauss-Seidel iteration below)
  void DiagonalSolve(double * rhs) const;

  // performs one Gauss-Seidel iteration of solving the system A * x = b
  // updates vector x in place, b is not modified
  // (A can be a general matrix)
  // assumes that diagonal entries of the matrix are set and are non-zero
  void DoOneGaussSeidelIteration(double * x, const double * b) const;
  void ComputeResidual(const double * x, const double * b, double * residual) const;
  // checks if A * x - b is close to zero and prints out the findings
  // returns ||A * x - b|| / ||b|| (all norms are infinity)
  // passing a buffer (length of n) will avoid a malloc/free pair to generate scratch space for the residual
  double CheckLinearSystemSolution(const double * x, const double * b, int verbose=1, double * buffer=NULL) const;

  // below are low-level routines which are rarely used
  inline double ** GetDataHandle() const { return columnEntries; }
  inline double * GetRowHandle(int row) const { return columnEntries[row]; }

  // create a nxn identity matrix
  static SparseMatrix * CreateIdentityMatrix(int n);

protected:

  // compressed row storage
  int numRows; // number of rows
  int * rowLength; // length of each row
  int ** columnIndices; // indices of columns of non-zero entries in each row
  double ** columnEntries; // values of non-zero entries in each row

  int * diagonalIndices;
  int ** transposedIndices;

  /*
    numSubMatrixIDs specifies how many sub-matrix relationships we have
    length(subMatrixIndices) == length(subMatrixIndexLengths) == length(subMatrixStartRow) == (numSubMatrixIDs + 1)
    length(subMatrixIndexLengths[subMatrixID]) == length(subMatrixIndices[subMatrixID]) == number of rows = numRows
    length(subMatrixIndices[subMatrixID][rowIndex]) == subMatrixIndexLengths[subMatrixID][rowIndex]
  */
  int numSubMatrixIDs;
  int *** subMatrixIndices;
  int ** subMatrixIndexLengths;
  int * subMatrixStartRow;
  int * subMatrixNumRows;

  int ** superMatrixIndices;
  int * superRows;

  void InitFromOutline(SparseMatrixOutline * sparseMatrixOutline);
  void Allocate();
  void BuildRenumberingVector(int nConstrained, int nSuper, int numFixedDOFs, int * fixedDOFs, int ** superDOFs, int oneIndexed=0);
};

#endif

