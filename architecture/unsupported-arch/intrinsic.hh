/****************************************************/
/*                                                  */
/*  intrinsic.hh:                                   */
/*                                                  */
/*                                                  */
/*  Nicolas Scaringella                             */
/*                                                  */
/****************************************************/

// dans fichiers architectures desormais :
// inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }

#ifdef __SSE2__

/****************************************************/
/*                                                  */
/*  			   SSE2 implementation      */
/*                                                  */
/****************************************************/

#include <mmintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
//#include <sse2mmx.h>

struct vec_int 
{ 
	__m128i vec;
	
	vec_int()										{}
	vec_int(int a)									{ vec = _mm_set_epi32(a,a,a,a); }
	vec_int(int a, int b, int c, int d)				{ vec = _mm_set_epi32(d,c,b,a); }
	vec_int(__m128i m)								{ vec = m; }
	operator  __m128i() const						{ return vec; }
	const int& operator[](int i)const				{ int* ip = (int*)&vec; return *(ip+i); }
	int& operator[](int i)							{ int* ip = (int*)&vec; return *(ip+i); } 

};

struct vec_float 
{ 
	__m128 vec;
	vec_float()										{}
	vec_float(float a)								{ vec = _mm_set_ps1(a); }
	vec_float(float a, float b, float c, float d)	{ vec = _mm_set_ps(d,c,b,a); }
	vec_float(__m128 m)								{ vec = m; }
	//vec_float(vec_int vi)   						{ vec = _mm_cvtepi32_ps(vi); }
	operator  __m128() const						{ return vec; }
	const float& operator[](int i)const				{ float* fp = (float*)&vec; return *(fp+i); }
	float& operator[](int i)						{ float* fp = (float*)&vec; return *(fp+i); } 

};

// Flush to zero mode: during underflow zero result is returned when the result is true
// Not compatible with the IEEE standard 754 ( which
// deliver denormalized result in case of underflow )
#define NO_DENORMALIZE _mm_setcsr((_mm_getcsr() & ~_MM_FLUSH_ZERO_MASK) | (_MM_FLUSH_ZERO_ON))
#define DENORMALIZE    _mm_setcsr((_mm_getcsr() & ~_MM_FLUSH_ZERO_MASK) | (_MM_FLUSH_ZERO_OFF))


// constants

// 0 0 0 0
#define VEC_INT_ZERO(a)   _mm_xor_si128(a,a)

// 0xffffffff 0xffffffff 0xffffffff 0xffffffff 
#define VEC_INT_ONES(a)   _mm_cmpeq_epi32(a,a)

// Example: 2^10 - 1 = 1023 -> VEC_INT_PW2_MINUS_1(a,10)
#define VEC_INT_PW2_MINUS_1(a,pw) _mm_srli_epi32(_mm_cmpeq_epi32(a,a),32-pw)

// 1 1 1 1: particular case
#define VEC_INT_ONE(a)    _mm_srli_epi32(_mm_cmpeq_epi32(a,a),31)

// Example: 2^10 = 1024 -> VEC_INT_PW2(a,10)
#define VEC_INT_PW2(a,pw) _mm_slli_epi32(_mm_srli_epi32(_mm_cmpeq_epi32(a,a),31),pw)

// Example: -2^10 = -1024 -> VEC_INT_MINUS_PW2(a,10)
#define VEC_INT_MINUS_PW2(a,pw) _mm_slli_epi32(_mm_cmpeq_epi32(a,a),pw)

// -1 -1 -1 -1: particular case
#define VEC_INT_MINUS_ONE(a) _mm_cmpeq_epi32(a,a)

// 0.0 0.0 0.0 0.0
#define VEC_FLOAT_ZERO(a) _mm_xor_ps(a,a)

// 0xffffffff 0xffffffff 0xffffffff 0xffffffff 
#define VEC_FLOAT_ONES(a) _mm_cmpeq_ps(a,a)

// conversions entre vecteurs d'ints et de floats
inline vec_int   float2int( vec_float a)   { return _mm_cvtps_epi32(a); }
inline int       float2int( float a )      { return int(a); }

inline vec_float int2float( vec_int a)   { return _mm_cvtepi32_ps(a); } 
inline float     int2float( int a )      { return float(a); }

// arithmetic
inline vec_float add_vec( vec_float a, vec_float b)   	{ return _mm_add_ps(a,b); }
inline vec_float add_vec( vec_int a, vec_float b)   	{ return _mm_add_ps(int2float(a),b); }
inline vec_float add_vec( vec_float a, vec_int b)   	{ return _mm_add_ps(a,int2float(b)); }
inline vec_int   add_vec( vec_int a, vec_int b)       { return _mm_add_epi32(a,b); }
inline vec_float add_scal( vec_float a, vec_float b)  { return _mm_add_ss(a,b); }
inline vec_int   add_scal( vec_int a, vec_int b)      { return _mm_add_epi32(a,b); } // _mm_add_pi32 en MMX
//inline scal_int  add_scal( scal_int a, scal_int b) { return _mm_add_pi32(a,b); }

inline vec_float sub_vec( vec_float a, vec_float b)   { return _mm_sub_ps(a,b); }
inline vec_int   sub_vec( vec_int a, vec_int b)       { return _mm_sub_epi32(a,b); }
inline vec_float sub_scal( vec_float a, vec_float b)  { return _mm_sub_ss(a,b); }
inline vec_int   sub_scal( vec_int a, vec_int b)      { return _mm_sub_epi32(a,b); } // _mm_sub_pi32 en MMX
//inline scal_int  sub_scal( scal_int a, scal_int b) { return _mm_sub_pi32(a,b); }

inline vec_float mul_vec( vec_float a, vec_float b)   	{ return _mm_mul_ps(a,b); }
inline vec_float mul_vec( vec_int a, vec_float b)   	{ return _mm_mul_ps(int2float(a),b); }
inline vec_float mul_vec( vec_float a, vec_int b)   	{ return _mm_mul_ps(a,int2float(b)); }

inline vec_float mul_scal( vec_float a, vec_float b)  	{ return _mm_mul_ss(a,b); }

// INTEGER MULTIPLICATION 
// low 32 bits of a 32 * 32 bit multiplication: each double-word X and Y is broken down into two words, A & B and C & D:
// X = ( A << 16 ) + B
// Y = ( C << 16 ) + D
// then:
// X * Y = (( A << 16 ) + B ) * (( C << 16 ) + D )
// X * Y = ( A*C << 32 ) + ( A*D << 16 ) + ( B*C << 16 ) + B*D
// the partial result A*C does not appear in the low 32 bits result so does not need to be computed
// ( however, if it's different from zero, then there is an overflow )

inline vec_int mul_vec( vec_int a, vec_int b) {

  vec_int temp0 = _mm_shufflehi_epi16( _mm_shufflelo_epi16( b, 0xB1), 0xB1);
  vec_int temp1 = _mm_and_si128( b, _mm_srli_epi32( _mm_cmpeq_epi32( b,b), 16));

  vec_int temp2 = _mm_madd_epi16( a, temp0);
  vec_int temp3 = _mm_madd_epi16( a, temp1);

  vec_int temp4 = _mm_slli_epi32( temp2, 16);

  return _mm_add_epi32( temp4, temp3);
}

inline vec_int mul_scal( vec_int a, vec_int b) {

  vec_int temp0 = _mm_shufflelo_epi16( b, 0xB1);
  vec_int temp1 = _mm_and_si128( b, _mm_cvtsi32_si128(0x00ff));

  vec_int temp2 = _mm_madd_epi16( a, temp0);
  vec_int temp3 = _mm_madd_epi16( a, temp1);

  vec_int temp4 = _mm_slli_epi32( temp2, 16);

  return _mm_add_epi32( temp4, temp3);
}

inline vec_float div_vec( vec_float a, vec_float b)   { return _mm_mul_ps(a,_mm_rcp_ps(b)); /*_mm_div_ps(a,b);*/ }
inline vec_int   div_vec( vec_int a, vec_int b)       { return _mm_cvtps_epi32(_mm_mul_ps(_mm_cvtepi32_ps(a),_mm_rcp_ps(_mm_cvtepi32_ps(b)))); } // A CHANGER !!!!
inline vec_float div_scal( vec_float a, vec_float b)  { return _mm_mul_ss(a,_mm_rcp_ss(b)); /*_mm_div_ss(a,b);*/ }
inline vec_int   div_scal( vec_int a, vec_int b)      { return _mm_cvtps_epi32(_mm_mul_ss(_mm_cvtepi32_ps(a),_mm_rcp_ss(_mm_cvtepi32_ps(b)))); } // A CHANGER !!!!!
//inline scal_int  div_scal( scal_int a, scal_int b) { return _mm_cvtsi32_si64((_mm_cvtsi64_si32(a))/(_mm_cvtsi64_si32(b))); }  // A CHANGER !!!!!

inline vec_int   mod_vec( vec_int a, vec_int N) {
  
  vec_int temp = _mm_sub_epi32(a,N);
  vec_int zero = _mm_xor_si128(a,a);

  vec_int select = _mm_xor_si128( _mm_cmpgt_epi32(temp,zero), _mm_cmpeq_epi32(temp,zero)); // a - N >= 0

  return _mm_or_si128(_mm_and_si128(select,temp),_mm_andnot_si128(select,a)); // if( a - N >=0 ) return a - N; else return a;
}

inline vec_int   mod_scal( vec_int a, vec_int N) {
  
  vec_int temp = _mm_sub_epi32(a,N);
  vec_int zero = _mm_xor_si128(a,a);

  vec_int select = _mm_xor_si128( _mm_cmpgt_epi32(temp,zero), _mm_cmpeq_epi32(temp,zero)); // a - N >= 0

  return _mm_or_si128(_mm_and_si128(select,temp),_mm_andnot_si128(select,a)); // if( a - N >=0 ) return a - N; else return a;
}



// simulation of  a*b + c 
#define madd_vec(a,b,c)  add_vec(mul_vec(a,b),c)
#define madd_scal(a,b,c)  add_scal(mul_scal(a,b),c)

//inline vec_float madd_scal( vec_float a, vec_float b, vec_float c) { return _mm_add_ss(_mm_mul_ss(a,b),c); }
//inline vec_int madd_vec( vec_int a, vec_int b, vec_int c)  { return add_vec(mul_vec(a,b),c); }
//inline vec_int madd_scal( vec_int a, vec_int b, vec_int c) { return add_scal(mul_scal(a,b),c); }


// simulation of  - ( a*b - c )
//inline vec_float nmsub_vec( vec_float a, vec_float b, vec_float c) {  }

// simulation of a*(1/b) + c 
inline vec_float divadd_vec( vec_float a, vec_float b, vec_float c)  { return _mm_add_ps(_mm_mul_ps(a,_mm_rcp_ps(b)),c); }
inline vec_float divadd_scal( vec_float a, vec_float b, vec_float c) { return _mm_add_ss(_mm_mul_ss(a,_mm_rcp_ss(b)),c); }
// simulation of - ( a*(1/b) - c )
//inline vec_float divsub_vec( vec_float a, vec_float b, vec_float c) {  }

// shift ( and fill with 0's )
inline vec_int   shift_left_vec( vec_int a, vec_int num)     { return _mm_sll_epi32(a,num); }
inline vec_int   shift_left_vec( vec_int a, int num)         { return _mm_slli_epi32(a,num); }
inline vec_int   shift_left_scal( vec_int a, vec_int num)     { return _mm_sll_epi32(a,num); } // _mm_sll_pi32(a,num) en MMX
//inline scal_int shift_left_scal( scal_int a, scal_int num) { return _mm_sll_pi32(a,num); }
inline vec_int   shift_left_scal( vec_int a, int num)         { return _mm_slli_epi32(a,num); } // _mm_slli_pi32(a,num) en MMX
//inline scal_int shift_left_scal( scal_int a, int num) { return _mm_slli_pi32(a,num); }

// shift ( and fill with the sign bit )
inline vec_int   shift_right_vec( vec_int a, vec_int num)     { return _mm_sra_epi32(a,num); }
inline vec_int   shift_right_vec( vec_int a, int num)         { return _mm_srai_epi32(a,num); }
inline vec_int   shift_right_scal( vec_int a, vec_int num)     { return _mm_sra_epi32(a,num); } // _mm_sra_pi32(a,num) en MMX
//inline scal_int shift_right_scal( scal_int a, scal_int num) { return _mm_sra_pi32(a,num); }
inline vec_int   shift_right_scal( vec_int a, int num)         { return _mm_srai_epi32(a,num); } // _mm_srai_pi32(a,num) en MMX
//inline scal_int shift_right_scal( scal_int a, int num) { return _mm_srai_pi32(a,num); }

// shift ( and fill with 0's )
inline vec_int   shift_right_vec_logical( vec_int a, vec_int num)     { return _mm_srl_epi32(a,num); }
inline vec_int   shift_right_vec_logical( vec_int a, int num)         { return _mm_srli_epi32(a,num); }
inline vec_int   shift_right_scal_logical( vec_int a, vec_int num)     { return _mm_srl_epi32(a,num); } // _mm_sra_pi32(a,num) en MMX
//inline scal_int shift_right_scal_logical( scal_int a, scal_int num) { return _mm_srl_pi32(a,num); }
inline vec_int   shift_right_scal_logical( vec_int a, int num)         { return _mm_srli_epi32(a,num); } // _mm_srai_pi32(a,num) en MMX
//inline scal_int shift_right_scal_logical( scal_int a, int num) { return _mm_srli_pi32(a,num); }

// Logic
// Ajouts YO;; supprime
//inline vec_float and_vec( vec_float a, vec_int b)   { return _mm_and_ps(a,b); }
//inline vec_float and_vec( vec_int a, vec_float b)   { return _mm_and_ps(a,b); }

inline vec_float and_vec( vec_float a, vec_float b)   { return _mm_and_ps(a,b); }
inline vec_int   and_vec( vec_int a, vec_int b)       { return _mm_and_si128(a,b); }
inline vec_float and_scal( vec_float a, vec_float b)  { return _mm_and_ps(a,b); }
inline vec_int   and_scal( vec_int a, vec_int b)      { return _mm_and_si128(a,b); } // _mm_and_si64(a,b) en MMX
//inline scal_int   and_scal( scal_int a, scal_int b)      { return _mm_and_si64(a,b); }

inline vec_float or_vec( vec_float a, vec_float b)    { return _mm_or_ps(a,b); }
inline vec_int   or_vec( vec_int a, vec_int b)        { return _mm_or_si128(a,b); }
inline vec_float or_scal( vec_float a, vec_float b)   { return _mm_or_ps(a,b); }
inline vec_int   or_scal( vec_int a, vec_int b)       { return _mm_or_si128(a,b); } // _mm_or_si64(a,b) en MMX 
//inline scal_int or_scal( scal_int a, scal_int b) { return _mm_or_si64(a,b); }

inline vec_float xor_vec( vec_float a, vec_float b)   { return _mm_xor_ps(a,b); }
inline vec_int   xor_vec( vec_int a, vec_int b)       { return _mm_xor_si128(a,b); }
inline vec_float xor_scal( vec_float a, vec_float b)  { return _mm_xor_ps(a,b); }
inline vec_int   xor_scal( vec_int a, vec_int b)      { return _mm_xor_si128(a,b); } // _mm_xor_si64(a,b) en MMX
//inline scal_int xor_scal( scal_int a, scal_int b) { return _mm_xor_si64(a,b); }

//------------------------------------------------------------------------------------------------------------
// YO : remplacement de inline vec_float par inline vec_int dans les operations de comparaison entre vec_float
// pour une meilleur compatibilité avec la compilation vectorielle
//------------------------------------------------------------------------------------------------------------

// cast (without conversion)
inline vec_float cast2vec_float(vec_int x)				{ return _mm_castsi128_ps(x); }
inline vec_int cast2vec_int(vec_float x)				{ return _mm_castps_si128(x); }

// convertions 
inline vec_float conv2vec_float(vec_int x)				{ return _mm_cvtepi32_ps(x); }
inline vec_int conv2vec_int(vec_float x)				{ return _mm_cvtps_epi32(x); }

// comparaison
//inline vec_float int2float( vec_int a)   { return _mm_cvtepi32_ps(a); } 

inline vec_float gt_vec( vec_float a, vec_float b)    	{ return _mm_cmpgt_ps(a,b); }
inline vec_float gt_vec( vec_int a, vec_float b)    	{ return _mm_cmpgt_ps(_mm_cvtepi32_ps(a),b); }
inline vec_float gt_vec( vec_float a, vec_int b)    	{ return _mm_cmpgt_ps(a,_mm_cvtepi32_ps(b)); }
inline vec_int   gt_vec( vec_int a, vec_int b)      	{ return _mm_cmpgt_epi32(a,b); }

inline vec_float gt_scal( vec_float a, vec_float b)    	{ return _mm_cmpgt_ps(a,b); }
inline vec_float gt_scal( vec_int a, vec_float b)    	{ return _mm_cmpgt_ps(_mm_cvtepi32_ps(a),b); }
inline vec_float gt_scal( vec_float a, vec_int b)    	{ return _mm_cmpgt_ps(a,_mm_cvtepi32_ps(b)); }
inline vec_int   gt_scal( vec_int a, vec_int b)      	{ return _mm_cmpgt_epi32(a,b); }

// choose between two values choose(c,u,v) = c?u:v
// the type of the result depends of the types of u and v, not of the type of c

inline vec_float choose(vec_float c, vec_float u, vec_float v)	{ return _mm_or_ps(_mm_and_ps(c,u), _mm_andnot_ps(c,v)); }
inline vec_float choose(vec_float c, vec_int u, vec_float v)	{ return _mm_or_ps(_mm_and_ps(c,_mm_cvtepi32_ps(u)), _mm_andnot_ps(c,v)); }
inline vec_float choose(vec_float c, vec_float u, vec_int v)	{ return _mm_or_ps(_mm_and_ps(c,u), _mm_andnot_ps(c,_mm_cvtepi32_ps(v))); }

inline vec_float choose(vec_int c, vec_float u, vec_float v)	{ return choose(cast2vec_float(c), u, v); }	
inline vec_float choose(vec_int c, vec_int u, vec_float v)		{ return choose(cast2vec_float(c), u, v); }	
inline vec_float choose(vec_int c, vec_float u, vec_int v)		{ return choose(cast2vec_float(c), u, v); }	

inline vec_int choose(vec_int c, vec_int u, vec_int v)			{ return _mm_or_si128(_mm_and_si128(c,u), _mm_andnot_si128(c,v)); }	
inline vec_int choose(vec_float c, vec_int u, vec_int v)		{ return choose(cast2vec_int(c), u, v); }

// choose between two values choosezero(c,u) = c?u:0
inline vec_float choosezero(vec_float c, vec_float u)			{ return _mm_and_ps(c,u); }
inline vec_float choosezero(vec_int c, vec_float u)				{ return choosezero(cast2vec_float(c), u); }

inline vec_int choosezero(vec_int c, vec_int u)					{ return _mm_and_si128(c,u); }
inline vec_int choosezero(vec_float c, vec_int u)				{ return choosezero(cast2vec_int(c), u); }


//inline vec_int gt_vec( vec_float a, vec_float b)    { return _mm_srli_epi32(_mm_cmpgt_ps(a,b),31); }
//inline vec_int gt_vec( vec_float a, vec_float b)    { vec_univ v; v.f4 = _mm_cmpgt_ps(a,b); return _mm_srli_epi32(v.i4,31); }
//inline vec_int   gt_vec( vec_int a, vec_int b)        { return _mm_cmpgt_epi32(a,b); }
//inline vec_int gt_scal( vec_float a, vec_float b)   { return _mm_srli_epi32(_mm_cmpgt_ss(a,b),31); }
//inline vec_int gt_scal( vec_float a, vec_float b)   { vec_univ v; v.f4 = _mm_cmpgt_ss(a,b); return _mm_srli_epi32(v.i4,31); }
//inline vec_int gt_scal( vec_float a, vec_float b)   	{ return _mm_srli_epi32(_mm_cmpgt_ss(a,b),31); }
//inline vec_int gt_scal( vec_int a, vec_float b)   	{ return _mm_srli_epi32(_mm_cmpgt_ss(a,b),31); }
//inline vec_int   gt_scal( vec_int a, vec_int b)       { return _mm_cmpgt_epi32(a,b); } // _mm_cmpgt_pi32(a,b) en MMX

//inline scal_int gt_scal( scal_int a, scal_int b) { return (__m128i) _mm_cmpgt_pi32(a,b); }

#if 0

inline vec_int lt_vec( vec_float a, vec_float b)    { return _mm_cmplt_ps(a,b); }
inline vec_int   lt_vec( vec_int a, vec_int b)        { return _mm_cmpgt_epi32(b,a); }
inline vec_int lt_scal( vec_float a, vec_float b)   { return _mm_cmplt_ss(a,b); }
inline vec_int   lt_scal( vec_int a, vec_int b)       { return _mm_cmpgt_epi32(b,a); } // _mm_cmpgt_pi32(b,a) en MMX
//inline scal_int lt_scal( scal_int a, scal_int b) { return _mm_cmpgt_pi32(b,a); }

inline vec_int ge_vec( vec_float a, vec_float b)    { return _mm_cmpge_ps(a,b); }
inline vec_int   ge_vec( vec_int a, vec_int b)        { return _mm_xor_si128( _mm_cmpgt_epi32(a,b), _mm_cmpeq_epi32(a,b)); }
inline vec_int ge_scal( vec_float a, vec_float b)   { return _mm_cmpge_ss(a,b); }
inline vec_int   ge_scal( vec_int a, vec_int b)       { return _mm_xor_si128( _mm_cmpgt_epi32(a,b), _mm_cmpeq_epi32(a,b)); } // _mm_xor_si64,_mm_cmpgt_pi32,_mm_cmpeq_pi32 MMX 
//inline scal_int ge_scal( scal_int a, scal_int b) { return _mm_xor_si64( _mm_cmpgt_pi32(a,b),_mm_cmpeq_pi32(a,b)); }


inline vec_int le_vec( vec_float a, vec_float b)    { return _mm_cmple_ps(a,b); }
inline vec_int   le_vec( vec_int a, vec_int b)        { return _mm_xor_si128( _mm_cmpgt_epi32(b,a), _mm_cmpeq_epi32(b,a)); }
inline vec_int le_scal( vec_float a, vec_float b)   { return _mm_cmple_ss(a,b); }
inline vec_int   le_scal( vec_int a, vec_int b)       { return _mm_xor_si128( _mm_cmpgt_epi32(b,a), _mm_cmpeq_epi32(b,a)); } // _mm_xor_si64,_mm_cmpgt_pi32,_mm_cmpeq_pi32 MMX 
//inline scal_int le_scal( scal_int a, scal_int b) { return _mm_xor_si64( _mm_cmpgt_pi32(b,a),_mm_cmpeq_pi32(b,a)); }

inline vec_int eq_vec( vec_float a, vec_float b)    { return _mm_cmpeq_ps(a,b); }
inline vec_int   eq_vec( vec_int a, vec_int b)        { return _mm_cmpeq_epi32(a,b); }
inline vec_int eq_scal( vec_float a, vec_float b)   { return _mm_cmpeq_ss(a,b); }
inline vec_int   eq_scal( vec_int a, vec_int b)       { return _mm_cmpeq_epi32(a,b); } // _mm_cmpeq_pi32(a,b) en MMX
//inline scal_int eq_scal( scal_int a, scal_int b) { return _mm_cmpeq_pi32(a,b); }

inline vec_int neq_vec( vec_float a, vec_float b)   { return _mm_cmpneq_ps(a,b); }
inline vec_int   neq_vec( vec_int a, vec_int b)       { return _mm_andnot_si128(_mm_cmpeq_epi32(a,b), _mm_cmpeq_epi32(a,a)); }
inline vec_int neq_scal( vec_float a, vec_float b)  { return _mm_cmpneq_ss(a,b); }
inline vec_int   neq_scal( vec_int a, vec_int b)      { return _mm_andnot_si128(_mm_cmpeq_epi32(a,b), _mm_cmpeq_epi32(a,a)); } // _mm_andnot_si64,_mm_cmpeq_pi32 MMX
//inline scal_int neq_scal( scal_int a, scal_int b) { return _mm_andnot_si64(_mm_cmpeq_pi32(a,b),SCAL_INT_ALL_ONE); }

#endif

// memory

#if 0
inline vec_float set_vec( double a)       	{ float val = float(a); vec_float temp = _mm_load_ss(&val); return _mm_shuffle_ps(temp,temp,0x00); }
inline vec_float set_vec( float a)         	{ float val = a; vec_float temp = _mm_load_ss(&val); return _mm_shuffle_ps(temp,temp,0x00); }
inline vec_int   set_vec( long int a)    	{ vec_int temp = _mm_cvtsi32_si128(int(a)); temp = _mm_unpacklo_epi32(temp,temp); return _mm_unpacklo_epi32(temp,temp); }
inline vec_int   set_vec( int a)          	{ vec_int temp = _mm_cvtsi32_si128(a); temp = _mm_unpacklo_epi32(temp,temp); return _mm_unpacklo_epi32(temp,temp);}
inline vec_int   set_vec( short a)      	{ vec_int temp = _mm_cvtsi32_si128(int(a)); temp = _mm_unpacklo_epi32(temp,temp); return _mm_unpacklo_epi32(temp,temp); }
//inline scal_int  set_vec( long int a) { _mm_cvtsi32_si64(int(a)); }
//inline scal_int  set_vec( int a) { _mm_cvtsi32_si64(a); }
//inline scal_int  set_vec( short a) { _mm_cvtsi32_si64(int(a)); }
#endif

#if 0

inline vec_float set_vec( double a, double b, double c, double d)         { __vec_float temp; temp.s[0]=float(a); temp.s[1]=float(b); temp.s[2]=float(c); temp.s[3]=float(d); return temp.v; }
inline vec_float set_vec( float a, float b, float c, float d)             { __vec_float temp; temp.s[0]=a; temp.s[1]=b; temp.s[2]=c; temp.s[3]=d; return temp.v; }
inline vec_int   set_vec( int a, int b, int c, int d)                     { __vec_int temp; temp.s[0]=a; temp.s[1]=b; temp.s[2]=c; temp.s[3]=d; return temp.v; }
inline vec_int   set_vec( long int a, long int b, long int c, long int d) { __vec_int temp; temp.s[0]=int(a); temp.s[1]=int(b); temp.s[2]=int(c); temp.s[3]=int(d); return temp.v; } 
inline vec_int   set_vec( short a, short b, short c, short d)             { __vec_int temp; temp.s[0]=short(a); temp.s[1]=short(b); temp.s[2]=short(c); temp.s[3]=short(d); return temp.v; }

#endif

inline vec_float set_vec( float a, float b, float c, float d)         	{ return vec_float(a,b,c,d); } 
inline vec_int   set_vec( int a, int b, int c, int d)             		{ return vec_int(a,b,c,d); } 

inline vec_float set_vec( float a)                                		{ return vec_float(a); }
inline vec_int   set_vec( int a)                                  		{ return vec_int(a); }    

inline vec_float load_a_vec( float* a)                                { return _mm_load_ps(a); }
inline vec_int   load_a_vec( int* a)                                  { return _mm_load_si128((__m128i*)a); }    
                 
inline vec_float load_u_vec( float* a)                                { return _mm_loadu_ps(a); }
inline vec_int   load_u_vec( int* a)                                  { return _mm_loadu_si128((__m128i*)a); }  
   
// nouvelles fonctions d'écriture sans polluer le cache                                   
inline void store_stream( float* a, vec_float b)                       { return _mm_stream_ps(a,b); }
inline void store_stream( int* a, vec_int b)                           { return _mm_stream_si128((__m128i*)a,b); }
                                     
inline void store_a_vec( float* a, vec_float b)                       { return _mm_store_ps(a,b); }
inline void store_a_vec( int* a, vec_int b)                           { return _mm_store_si128((__m128i*)a,b); }

inline void store_u_vec( float* a, vec_float b)                       { return _mm_storeu_ps(a,b); }
inline void store_u_vec( int* a, vec_int b)                           { return _mm_storeu_si128((__m128i*)a,b); }
      
                                                             
inline vec_float load_scal(float* a) { return _mm_load_ss(a); }
inline vec_int   load_scal(int* a) { return _mm_cvtsi32_si128(*a); }
//inline scal_int  load_scal(int* a) { return _mm_cvtsi32_si64(*a); }

inline void store_scal(float* a, vec_float content) { return _mm_store_ss(a,content); }
inline void store_scal(int* a, vec_int content)     { *a = _mm_cvtsi128_si32(content); return; }
//inline void store_scal(int* a, scal_int content) { *a = _mm_cvtsi64_si32(content); return; }

inline vec_float REC0(vec_float a) { return _mm_unpacklo_ps(a,a); }
inline vec_float REC1(vec_float a) { return _mm_unpacklo_ps(a,a); }
inline vec_float REC2(vec_float a) { return _mm_shuffle_ps(a,a,0x90); }
inline vec_float REC3(vec_float a) { return _mm_shuffle_ps(a,a,0x1B); }

inline vec_int REC0(vec_int a) { return _mm_unpacklo_epi32(a,a); }
inline vec_int REC1(vec_int a) { return _mm_unpacklo_epi32(a,a); }
inline vec_int REC2(vec_int a) { return _mm_shuffle_epi32(a,0x90); }
inline vec_int REC3(vec_int a) { return _mm_shuffle_epi32(a,0x1B); }

// scalar to vector: takes 4 vector which lower elements stands for a scalar value and rebuild a vector from these 4 scalar
//inline vec_float SCAL2VEC(vec_float a0,vec_float a1,vec_float a2,vec_float a3) { return _mm_shuffle_ps(_mm_shuffle_ps(a0,a1,0x00),_mm_shuffle_ps(a2,a3,0x00),0x88); }
inline vec_float SCAL2VEC(vec_float a0,vec_float a1,vec_float a2,vec_float a3) { return _mm_unpacklo_ps(_mm_unpacklo_ps(a0,a2),_mm_unpacklo_ps(a1,a3)); }
inline vec_int   SCAL2VEC(vec_int a0,vec_int a1,vec_int a2,vec_int a3) { return _mm_unpacklo_epi32(_mm_unpacklo_epi32(a0,a2),_mm_unpacklo_epi32(a1,a3)); }
//inline vec_int   SCAL2VEC(scal_int a0,scal_int a1,scal_int a2,scal_int a3) { return _mm_unpacklo_epi32( _mm_movpi64_epi64(_mm_unpacklo_pi32(a0,a2)), _mm_movpi64_epi64(_mm_unpacklo_pi32(a1,a3)) ); } // ou _mm_set_epi64( _mm_unpacklo_pi32(a0,a1), _mm_unpacklo_pi32(a2,a3))

inline vec_float SCAL2VEC(double a0, double a1, double a2, double a3) { return _mm_set_ps(float(a3),float(a2),float(a1),float(a0)); }
inline vec_float SCAL2VEC(float a0, float a1, float a2, float a3) { return _mm_set_ps(a3,a2,a1,a0); }
inline vec_int   SCAL2VEC(long a0, long a1, long a2, long a3) { return _mm_set_epi32(int(a3),int(a2),int(a1),int(a0)); }
inline vec_int   SCAL2VEC(int a0, int a1, int a2, int a3) { return _mm_set_epi32(a3,a2,a1,a0); }
inline vec_int   SCAL2VEC(short a0, short a1, short a2, short a3) { return _mm_set_epi32(int(a3),int(a2),int(a1),int(a0)); }


// vector to scalar: build a scalar vector from one element of the initial vector
inline vec_float VEC2SCALVEC0(vec_float a) { return a; } // return x,x,x,a0   // _mm_shuffle_ps(a,a,Ox00) would return a0,a0,a0,a0
inline vec_float VEC2SCALVEC1(vec_float a) { return _mm_shuffle_ps(a,a,0x55); } // return a1,a1,a1,a1
inline vec_float VEC2SCALVEC2(vec_float a) { return _mm_shuffle_ps(a,a,0xAA); } // return a2,a2,a2,a2
inline vec_float VEC2SCALVEC3(vec_float a) { return _mm_shuffle_ps(a,a,0xFF); } // return a3,a3,a3,a3

inline vec_int VEC2SCALVEC0(vec_int a) { return a; } // return x,x,x,a0   // _mm_shuffle_epi32(a,Ox00) would return a0,a0,a0,a0
inline vec_int VEC2SCALVEC1(vec_int a) { return _mm_shuffle_epi32(a,0x55); } // return a1,a1,a1,a1
inline vec_int VEC2SCALVEC2(vec_int a) { return _mm_shuffle_epi32(a,0xAA); } // return a2,a2,a2,a2
inline vec_int VEC2SCALVEC3(vec_int a) { return _mm_shuffle_epi32(a,0xFF); } // return a3,a3,a3,a3

//inline scal_int VEC2SCALVEC0(vec_int a) { return _mm_movepi64_pi64(a); }  // ATTENTION !!!! :
//inline scal_int VEC2SCALVEC1(vec_int a) { __m64 temp = _mm_movepi64_pi64(a); return _mm_unpackhi_pi32(temp,temp); } // VEC2SCALVEC0 et 1 peuvent être réunis en une instruction plus efficace
//inline scal_int VEC2SCALVEC2(vec_int a) { return _mm_movepi64_pi64(_mm_shuffle_epi32(a,0xAA)); }
//inline scal_int VEC2SCALVEC3(vec_int a) { return _mm_movepi64_pi64(_mm_shuffle_epi32(a,0xFF)); }

// vector to scalar: build a single scalar from a vector
inline float VEC2SCAL0(vec_float a) { float temp; _mm_store_ss(&temp,a); return temp; }
inline float VEC2SCAL1(vec_float a) { float temp; _mm_store_ss(&temp,_mm_shuffle_ps(a,a,0x55)); return temp; }
inline float VEC2SCAL2(vec_float a) { float temp; _mm_store_ss(&temp,_mm_shuffle_ps(a,a,0xAA)); return temp; }
inline float VEC2SCAL3(vec_float a) { float temp; _mm_store_ss(&temp,_mm_shuffle_ps(a,a,0xFF)); return temp; }

inline int VEC2SCAL0(vec_int a) { return _mm_cvtsi128_si32(a); } 
inline int VEC2SCAL1(vec_int a) { return _mm_cvtsi128_si32(_mm_shuffle_epi32(a,0x55)); }
inline int VEC2SCAL2(vec_int a) { return _mm_cvtsi128_si32(_mm_shuffle_epi32(a,0xAA)); }
inline int VEC2SCAL3(vec_int a) { return _mm_cvtsi128_si32(_mm_shuffle_epi32(a,0xFF)); }
//inline int VEC2SCAL0(scal_int a) { return _mm_cvtsi64_si32(a); }

// select: if( select == 0 ) then a ; else b ;
inline vec_float select_vec( vec_float select, vec_float a, vec_float b) { return _mm_or_ps( _mm_andnot_ps(select,a), _mm_and_ps(select,b));}
inline vec_float select_scal( vec_float select, vec_float a, vec_float b){ return _mm_or_ps( _mm_andnot_ps(select,a), _mm_and_ps(select,b));}
inline vec_float select_vec( vec_int select, vec_float a, vec_float b) { __m128 temp = _mm_cvtepi32_ps(select); return _mm_or_ps( _mm_andnot_ps(temp,a), _mm_and_ps(temp,b));}
inline vec_float select_scal( vec_int select, vec_float a, vec_float b){ __m128 temp = _mm_cvtepi32_ps(select); return _mm_or_ps( _mm_andnot_ps(temp,a), _mm_and_ps(temp,b));}
inline vec_int select_vec( vec_int select, vec_int a, vec_int b)  { return _mm_or_si128( _mm_andnot_si128(select,a), _mm_and_si128(select,b)); }
inline vec_int select_scal( vec_int select, vec_int a, vec_int b) { return _mm_or_si128( _mm_andnot_si128(select,a), _mm_and_si128(select,b)); } // ou MMX

// vectorial version of the "mem" Faust key-word
// return a[2] a[1] a[0] b[3]
inline vec_float mem1_vec( vec_float a, vec_float b)       { return _mm_shuffle_ps(_mm_shuffle_ps(b,a,0x4E),a,0x99); } 
inline vec_int   mem1_vec( vec_int a, vec_int b)           { 
  return _mm_unpacklo_epi32( _mm_shuffle_epi32( _mm_unpacklo_epi32( _mm_shuffle_epi32( b, 0xFF), a), 0xEE), _mm_shuffle_epi32( a, 0x88) );
}

// return a[1] a[0] b[3] b[2]
inline vec_float mem2_vec( vec_float a, vec_float b)       { return _mm_shuffle_ps(b,a,0x4E); } 
inline vec_int   mem2_vec( vec_int a, vec_int b)           { return _mm_shuffle_epi32( _mm_unpackhi_epi32( b, _mm_shuffle_epi32( a, 0x44)), 0xD8 );
  
}

// return a[0] b[3] b[2] b[1]
inline vec_float mem3_vec( vec_float a, vec_float b)       { return _mm_shuffle_ps(b,_mm_shuffle_ps(b,a,0x4E),0x99);  } 
inline vec_int   mem3_vec( vec_int a, vec_int b)           {  
  return _mm_unpacklo_epi32( _mm_shuffle_epi32( b, 0x99), _mm_shuffle_epi32( _mm_unpackhi_epi32( b, _mm_shuffle_epi32( a, 0x00)), 0xEE) );
}

// conversion
inline vec_float bool2float( vec_float a )  { return _mm_and_ps(a,set_vec(1.0f)); }
inline vec_float bool2float( vec_int a )    { return _mm_cvtepi32_ps(_mm_and_si128(a,_mm_sub_epi32(_mm_xor_si128(a,a),_mm_cmpeq_epi32(a,a)))); }

inline vec_int   bool2int( vec_int   a)     { return _mm_and_si128(a,_mm_sub_epi32(_mm_xor_si128(a,a),_mm_cmpeq_epi32(a,a))); }
inline vec_int   bool2int( vec_float a )    { return _mm_cvtps_epi32(_mm_and_ps(a,set_vec(1.0f))); }

inline vec_int   boolfloat2boolint( vec_float a ) { vec_int   temp; asm volatile("" : "=xmm" (temp) : "0" (a)); return temp; }
inline vec_float boolint2boolfloat( vec_int   a ) { vec_float temp; asm volatile("" : "=xmm" (temp) : "0" (a)); return temp; }

#elif  defined(__ALTIVEC__)

/****************************************************/
/*                                                  */
/*  			  ALTIVEC implementation    */
/*                                                  */
/****************************************************/

//#define vec_float vector float
//#define vec_int vector signed int
//#define vec_bool vector bool int

struct vec_int 
{ 
	vector signed int vec;
	vec_int()								{}
	vec_int(vector signed int m)			{ vec = m; }
//	operator  __m128i() const				{ return vec; }		

};

struct vec_float 
{ 
//	union { __m128 vec; __m128i i4; };
	vector float vec;
	vec_float()							{}
	vec_float(vector float m)			{ vec = m; }
	//vec_float(vec_int a)   		{ vec = _mm_cvtepi32_ps(a); } 
	
	//operator  __m128() const	{ return vec; }		
};

typedef union{
  float s[4];
  vec_float v;
} __vec_float;


typedef union{ 
  int s[4];
  vec_int v;
} __vec_int;

// Non-Java mode: during underflow zero result is returned
// Not compatible with the Java-IEEE-C9X standard ( which
// deliver denormalized result in case of underflow )
#define NO_DENORMALIZE vec_mtvscr(vec_or(vec_mfvscr(),(vector unsigned short)(0x8000)))
#define DENORMALIZE    vec_mtvscr(vec_or(vec_mfvscr(),(vector unsigned short)(0x0000)))

// constants

// 0 0 0 0
#define VEC_INT_ZERO(a)   vec_xor(a,a)

// 0xffffffff 0xffffffff 0xffffffff 0xffffffff 
#define VEC_INT_ONES(a)   (vector signed int)vec_cmpeq(a,a)

// 1 1 1 1
#define VEC_INT_ONE(a) vec_splat_s32(1)

// -1 -1 -1 -1
#define VEC_INT_MINUS_ONE(a) vec_splat_s32(-1)

// a must belong to [-16,15]
// no efficient equivalent with SSE2
#define VEC_INT_MINUS_16_TO_15(a) vec_splat_s32(a)

// This not exactly equivalent to the SSE2 version
// the power must belong to [17,31]
// ( that is 2^17 - 1 = 32767 is the minimum 
//   and  2^31 - 1 = 2147483647 is the maximum;
// if you need 2^32 - 1, use VEC_INT_ONES )
// Example: 2^19 - 1 = 524287 -> VEC_INT_PW2_MINUS_1(a,19)
#define VEC_INT_PW2_MINUS_1(a,pw) vec_sr((vector signed int)vec_cmpeq(a,a), vec_splat_u32(32-pw))

// This not exactly equivalent to the SSE2 version
// the power must belong to [4,18]
// ( that is 2^18 = 262144 is the maximum 
//   and  2^4 = 16 is the minimum;
// if you need 2^0 = 1, use VEC_INT_ONE,
// if you need 2^1 = 2, use VEC_INT_MINUS_16_TO_15(2)
// if you need 2^2 = 4, use VEC_INT_MINUS_16_TO_15(4)
// if you need 2^3 = 8, use VEC_INT_MINUS_16_TO_15(8) )
// Example: 2^10 = 1024 -> VEC_INT_PW2(a,10)
#define VEC_INT_PW2(a,pw) vec_sl(vec_splat_s32(8), vec_splat_u32(pw-3))


//vec_sr(a,(vector unsigned int)num);

// 0.0 0.0 0.0 0.0
#define VEC_FLOAT_ZERO(a) vec_xor(a,a)

// 0xffffffff 0xffffffff 0xffffffff 0xffffffff 
#define VEC_FLOAT_ONES(a) (vector float)vec_cmpeq(a,a)

// arithmetic
inline vec_float add_vec( vec_float a, vec_float b)   { return vec_add(a,b); }
inline vec_float add_scal(vec_float a, vec_float b)   { return vec_add(a,b); }
inline vec_int   add_vec( vec_int a, vec_int b)       { return vec_add(a,b); }
inline vec_int   add_scal(vec_int a, vec_int b)       { return vec_add(a,b); }

inline vec_float sub_vec( vec_float a, vec_float b)   { return vec_sub(a,b); }
inline vec_float sub_scal( vec_float a, vec_float b)  { return vec_sub(a,b); }
inline vec_int   sub_vec( vec_int a, vec_int b)       { return vec_sub(a,b); }
inline vec_int   sub_scal( vec_int a, vec_int b)      { return vec_sub(a,b); }

inline vec_float mul_vec( vec_float a, vec_float b)   { return vec_madd(a,b,(vec_float)(vec_splat_s32(int(0x00000000)))); }
inline vec_float mul_scal( vec_float a, vec_float b)  { return vec_madd(a,b,(vec_float)(vec_splat_s32(int(0x00000000)))); }

// low 32 bits of a 32 * 32 bit multiplication: each double-word X and Y is broken down into two words, A & B and C & D:
// X = ( A << 16 ) + B
// Y = ( C << 16 ) + D
// then:
// X * Y = (( A << 16 ) + B ) * (( C << 16 ) + D )
// X * Y = ( A*C << 32 ) + ( A*D << 16 ) + ( B*C << 16 ) + B*D
// the partial result A*C does not appear in the low 32 bits result so does not need to be computed ( however, if it's different
// from zero, then there is an overflow )
// In this implementation A*D + B*C is computed in a single "vec_msum"

inline vec_int mul_vec( vec_int a, vec_int b)   {
  const vector unsigned int VEC_SIXTEEN_UINT32 = vec_splat_u32(-16);
  return (vector signed int)vec_add( vec_sl( vec_msum( (vector unsigned short)a, (vector unsigned short)(vec_rl( b, VEC_SIXTEEN_UINT32 ) ), vec_splat_u32(0)  ), VEC_SIXTEEN_UINT32 ),   vec_mulo( (vector unsigned short)a, (vector unsigned short)b ) );
                                                }
inline vec_int mul_scal( vec_int a, vec_int b)   {
  const vector unsigned int VEC_SIXTEEN_UINT32 = vec_splat_u32(-16);
  return (vector signed int)vec_add( vec_sl( vec_msum( (vector unsigned short)a, (vector unsigned short)(vec_rl( b, VEC_SIXTEEN_UINT32 ) ), vec_splat_u32(0)  ), VEC_SIXTEEN_UINT32 ),   vec_mulo( (vector unsigned short)a, (vector unsigned short)b ) );
                                                }
//inline vec_int mul_vec( vec_int a, vec_int b)   { return (vec_int)vec_round(vec_madd((vec_float)(a),(vec_float)(b),(vec_float)(vec_splat_s32(int(0x00000000))))); }
//inline vec_int mul_scal( vec_int a, vec_int b)  { return (vec_int)vec_round(vec_madd((vec_float)(a),(vec_float)(b),(vec_float)(vec_splat_s32(int(0x00000000))))); }

inline vec_float div_vec( vec_float a, vec_float b)   { return vec_madd(a,vec_re(b),(vec_float)(vec_splat_s32(int(0x00000000)))); }
inline vec_float div_scal( vec_float a, vec_float b)  { return vec_madd(a,vec_re(b),(vec_float)(vec_splat_s32(int(0x00000000)))); }
inline vec_int div_vec( vec_int a, vec_int b)         { return (vec_int)vec_round(vec_madd((vec_float)(a),vec_re((vec_float)(b)),(vec_float)(vec_splat_s32(int(0x00000000))))); }
inline vec_int div_scal( vec_int a, vec_int b)        { return (vec_int)vec_round(vec_madd((vec_float)(a),vec_re((vec_float)(b)),(vec_float)(vec_splat_s32(int(0x00000000))))); }

inline vec_int   mod_vec( vec_int a, vec_int N) {

  vec_int temp = vec_sub(a,N);
  vec_int zero = vec_splat_s32(int(0x00000000));
  vector bool int select = (vector bool int )(vec_xor(vec_cmpgt(temp,zero),vec_cmpeq(temp,zero))); // a - N >= 0
  return vec_sel(a,temp,select); // if( a - N >=0 ) return a - N; else return a;
}

inline vec_int   mod_scal( vec_int a, vec_int N) {
  
  vec_int temp = vec_sub(a,N);
  vec_int zero = vec_splat_s32(int(0x00000000));
  vector bool int select = (vector bool int )(vec_xor(vec_cmpgt(temp,zero),vec_cmpeq(temp,zero))); // a - N >= 0
  return vec_sel(a,temp,select); // if( a - N >=0 ) return a - N; else return a;
}

// return a*b + c 
inline vec_float madd_vec( vec_float a, vec_float b, vec_float c)  { return vec_madd(a,b,c); }
inline vec_float madd_scal( vec_float a, vec_float b, vec_float c) { return vec_madd(a,b,c); }

// return  - ( a*b - c )
inline vec_float nmsub_vec( vec_float a, vec_float b, vec_float c)  { return vec_nmsub(a,b,c); }
inline vec_float nmsub_scal( vec_float a, vec_float b, vec_float c) { return vec_nmsub(a,b,c); }

// return a*(1/b) + c 
inline vec_float divadd_vec( vec_float a, vec_float b, vec_float c)  { return vec_madd(a,vec_re(b),c); }
inline vec_float divadd_scal( vec_float a, vec_float b, vec_float c) { return vec_madd(a,vec_re(b),c); }

// return - ( a*(1/b) - c )
inline vec_float divsub_vec( vec_float a, vec_float b, vec_float c)  { return vec_nmsub(a,vec_re(b),c); }
inline vec_float divsub_scal( vec_float a, vec_float b, vec_float c) { return vec_nmsub(a,vec_re(b),c); }

// logic
inline vec_float and_vec( vec_float a, vec_float b)   { return vec_and(a,b); }
inline vec_float and_scal( vec_float a, vec_float b)  { return vec_and(a,b); }
inline vec_int   and_vec( vec_int a, vec_int b)       { return vec_and(a,b); }
inline vec_int   and_scal( vec_int a, vec_int b)      { return vec_and(a,b); }

inline vec_float or_vec( vec_float a, vec_float b)    { return vec_or(a,b); }
inline vec_float or_scal( vec_float a, vec_float b)   { return vec_or(a,b); }
inline vec_int   or_vec( vec_int a, vec_int b)        { return vec_or(a,b); }
inline vec_int   or_scal( vec_int a, vec_int b)       { return vec_or(a,b); }

inline vec_float xor_vec( vec_float a, vec_float b)   { return vec_xor(a,b); }
inline vec_float xor_scal( vec_float a, vec_float b)  { return vec_xor(a,b); }
inline vec_int   xor_vec( vec_int a, vec_int b)       { return vec_xor(a,b); }
inline vec_int   xor_scal( vec_int a, vec_int b)      { return vec_xor(a,b); }

// shift left
inline vec_int   shift_left_vec( vec_int a, vec_int num)     { return vec_sl(a,(vector unsigned int)num); }
inline vec_int   shift_left_scal( vec_int a, vec_int num)    { return vec_sl(a,(vector unsigned int)num); }

// shift ( and fill with the sign bit )
inline vec_int   shift_right_vec( vec_int a, vec_int num)     { return vec_sra(a,(vector unsigned int)num); }
inline vec_int   shift_right_scal( vec_int a, vec_int num)    { return vec_sra(a,(vector unsigned int)num); }

// shift ( and fill with 0's )
//inline vec_int   shift_right_vec_logical( vec_int a, int num)         { return vec_sr(a, set_vec(num) ); }
//inline vec_int   shift_right_scal_logical( vec_int a, int num)        { return vec_sr(a, set_vec(num) ); ); }
inline vec_int   shift_right_vec_logical( vec_int a, vec_int num)     { return vec_sr(a,(vector unsigned int)num); }
inline vec_int   shift_right_scal_logical( vec_int a, vec_int num)    { return vec_sr(a,(vector unsigned int)num); }

// comparaison
inline vec_float gt_vec( vec_float a, vec_float b)    { return (vector float)vec_cmpgt(a,b); }
inline vec_float gt_scal( vec_float a, vec_float b)   { return (vector float)vec_cmpgt(a,b); }
inline vec_int gt_vec( vec_int a, vec_int b)        { return (vector signed int)vec_cmpgt(a,b); }
inline vec_int gt_scal( vec_int a, vec_int b)       { return (vector signed int)vec_cmpgt(a,b); }

inline vec_float lt_vec( vec_float a, vec_float b)    { return (vector float)vec_cmplt(a,b); }
inline vec_float lt_scal( vec_float a, vec_float b)   { return (vector float)vec_cmplt(a,b); }
inline vec_int lt_vec( vec_int a, vec_int b)        { return (vector signed int)vec_cmplt(a,b); }
inline vec_int lt_scal( vec_int a, vec_int b)       { return (vector signed int)vec_cmplt(a,b); }

inline vec_float ge_vec( vec_float a, vec_float b)    { return (vector float)vec_cmpge(a,b); }
inline vec_float ge_scal( vec_float a, vec_float b)   { return (vector float)vec_cmpge(a,b); }
inline vec_int ge_vec( vec_int a, vec_int b)        { return (vector signed int)vec_xor(vec_cmpgt(a,b),vec_cmpeq(a,b)); }
inline vec_int ge_scal( vec_int a, vec_int b)       { return (vector signed int)vec_xor(vec_cmpgt(a,b),vec_cmpeq(a,b)); }

inline vec_float le_vec( vec_float a, vec_float b)    { return (vector float)vec_cmple(a,b); }
inline vec_float le_scal( vec_float a, vec_float b)   { return (vector float)vec_cmple(a,b); }
inline vec_int le_vec( vec_int a, vec_int b)        { return (vector signed int)vec_xor(vec_cmplt(a,b),vec_cmpeq(a,b)); }
inline vec_int le_scal( vec_int a, vec_int b)       { return (vector signed int)vec_xor(vec_cmplt(a,b),vec_cmpeq(a,b)); }


inline vec_float eq_vec( vec_float a, vec_float b)    { return (vector float)vec_cmpeq(a,b); }
inline vec_float eq_scal( vec_float a, vec_float b)   { return (vector float)vec_cmpeq(a,b); }
inline vec_int eq_vec( vec_int a, vec_int b)        { return (vector signed int)vec_cmpeq(a,b); }
inline vec_int eq_scal( vec_int a, vec_int b)       { return (vector signed int)vec_cmpeq(a,b); }


inline vec_float neq_vec( vec_float a, vec_float b)    { return (vector float)vec_xor(vec_cmpeq(a,b),vec_cmpeq(a,a)); }
inline vec_float neq_scal( vec_float a, vec_float b)   { return (vector float)vec_xor(vec_cmpeq(a,b),vec_cmpeq(a,a)); }
inline vec_int neq_vec( vec_int a, vec_int b)        { return (vector signed int)vec_xor(vec_cmpeq(a,b),vec_cmpeq(a,a)); }
inline vec_int neq_scal( vec_int a, vec_int b)       { return (vector signed int)vec_xor(vec_cmpeq(a,b),vec_cmpeq(a,a)); }

// memory
inline vec_float set_vec( vec_float a)                { return a; }
inline vec_float set_vec( __vec_float a)              { return a.v; }
inline vec_int   set_vec( vec_int a)                  { return a; }
inline vec_int   set_vec( __vec_int a)                { return a.v; }

inline vec_float set_vec( double a)                   {
	float af;
	af = (float)a;
	vector float temp; temp = vec_lde(0,&af);
	temp = vec_perm(temp,temp,vec_lvsl(0,&af));
	return vec_splat(temp,0);
	//__vec_float temp; float af = float(a); temp.s[0]=af; temp.s[1]=af; temp.s[2]=af; temp.s[3]=af; return temp.v;
}
inline vec_float set_vec( float a)                    {
	float af;
	af = a;
	vector float temp; temp = vec_lde(0,&af);
	temp = vec_perm(temp,temp,vec_lvsl(0,&af));
	return vec_splat(temp,0);
	//__vec_float temp; temp.s[0]=a; temp.s[1]=a; temp.s[2]=a; temp.s[3]=a; return temp.v;
}
inline vec_int   set_vec( long int a)                 {
	int ai;
	ai = (int)a;
	vector signed int temp; temp = vec_lde(0,&ai);
	temp = vec_perm(temp,temp,vec_lvsl(0,&ai));
	return vec_splat(temp,0);
	//__vec_int temp; int al = int(a); temp.s[0]=al; temp.s[1]=al; temp.s[2]=al; temp.s[3]=al; return temp.v;
}
inline vec_int   set_vec( int a)                      {
	int ai;
	ai = a;
	vector signed int temp; temp = vec_lde(0,&ai);
	temp = vec_perm(temp,temp,vec_lvsl(0,&ai));
	return vec_splat(temp,0);
	//__vec_int temp; temp.s[0]=a; temp.s[1]=a; temp.s[2]=a; temp.s[3]=a; return temp.v;
}
inline vec_int   set_vec( short a)                    {
	int ai;
	ai = (int)a;
	vector signed int temp; temp = vec_lde(0,&ai);
	temp = vec_perm(temp,temp,vec_lvsl(0,&ai));
	return vec_splat(temp,0);
	//__vec_int temp; int as = int(a); temp.s[0]=as; temp.s[1]=as; temp.s[2]=as; temp.s[3]=as; return temp.v;
}

inline vec_float set_vec( double a, double b, double c, double d)         { __vec_float temp; temp.s[0]=float(a); temp.s[1]=float(b); temp.s[2]=float(c); temp.s[3]=float(d); return temp.v; }
inline vec_float set_vec( float a, float b, float c, float d)             { __vec_float temp; temp.s[0]=a; temp.s[1]=b; temp.s[2]=c; temp.s[3]=d; return temp.v; }
inline vec_int   set_vec( int a, int b, int c, int d)                     { __vec_int temp; temp.s[0]=a; temp.s[1]=b; temp.s[2]=c; temp.s[3]=d; return temp.v; }
inline vec_int   set_vec( long int a, long int b, long int c, long int d) { __vec_int temp; temp.s[0]=int(a); temp.s[1]=int(b); temp.s[2]=int(c); temp.s[3]=int(d); return temp.v; } 
inline vec_int   set_vec( short a, short b, short c, short d)             { __vec_int temp; temp.s[0]=short(a); temp.s[1]=short(b); temp.s[2]=short(c); temp.s[3]=short(d); return temp.v; }

inline vec_float load_a_vec( float* a)                                { return vec_ld(0,a); }
//inline vec_float load_u_vec( float* a)                                {  }
inline vec_int   load_a_vec( int* a)                                  { return vec_ld(0,a); }                     
//inline vec_int   load_u_vec( int* a)                                  {  }  
                                     
inline void store_a_vec( float* a, vec_float b)                       { return vec_st(b,0,a); }
//inline void store_u_vec( float* a, vec_float b)                       {  }
inline void store_a_vec( int* a, vec_int b)                           { return vec_st(b,0,a); }
//inline void store_u_vec( int* a, vec_int b)                           {  }
    

inline vec_float load_scal(float* a) { vector float temp; temp = vec_lde(0,a); return vec_perm(temp,temp,vec_lvsl(0,a)); }
inline vec_int   load_scal(int* a)   { vector signed int temp; temp = vec_lde(0,a); return vec_perm(temp,temp,vec_lvsl(0,a)); } 
inline void store_scal(float* a, vec_float content) { vec_float temp = vec_splat(content,0); return vec_ste(temp,0,a); }
inline void store_scal(int* a, vec_int content)     { vec_int temp = vec_splat(content,0); return vec_ste(temp,0,a); }

inline vec_float REC0(vec_float a) { return vec_mergeh(a,a); }
inline vec_float REC1(vec_float a) { return vec_mergeh(a,a); }
inline vec_float REC2(vec_float a) { return vec_sld(vec_splat(a,0),a,12); }
inline vec_float REC3(vec_float a) {
  vector float temp1 = vec_mergel(a,a);
  vector float temp2 = vec_mergeh(a,a);
  return vec_mergel(vec_mergel(temp1,temp2),vec_mergeh(temp1,temp2));
}

inline vec_int REC0(vec_int a) { return vec_mergeh(a,a); }
inline vec_int REC1(vec_int a) { return vec_mergeh(a,a); }
inline vec_int REC2(vec_int a) { return vec_sld(vec_splat(a,0),a,12); }
inline vec_int REC3(vec_int a) {
  vector signed int temp1 = vec_mergel(a,a);
  vector signed int temp2 = vec_mergeh(a,a);
  return vec_mergel(vec_mergel(temp1,temp2),vec_mergeh(temp1,temp2));
}

// scalar to vector: takes 4 vector which lower elements stands for a scalar value and rebuild a vector from these 4 scalar
inline vec_float SCAL2VEC(vec_float a0,vec_float a1,vec_float a2,vec_float a3) {
	return vec_perm(vec_mergeh(a0,a1),vec_mergeh(a2,a3),vec_lvsl(8,(float*)(0)));
	//return vec_perm(vec_perm(a0,a1,VEC_PERM0),vec_perm(a2,a3,VEC_PERM0),VEC_PERM1);
}
inline vec_int   SCAL2VEC(vec_int a0,vec_int a1,vec_int a2,vec_int a3) {
	return vec_perm(vec_mergeh(a0,a1),vec_mergeh(a2,a3),vec_lvsl(8,(int*)(0)));
	//return vec_perm(vec_perm(a0,a1,VEC_PERM0),vec_perm(a2,a3,VEC_PERM0),VEC_PERM1);
}

inline vec_float SCAL2VEC(float a0, float a1, float a2, float a3) { __vec_float temp; temp.s[0]=a0; temp.s[1]=a1; temp.s[2]=a2; temp.s[3]=a3; return temp.v; }
inline vec_int   SCAL2VEC(int a0, int a1, int a2, int a3) { __vec_int temp; temp.s[0]=a0; temp.s[1]=a1; temp.s[2]=a2; temp.s[3]=a3; return temp.v; }

// vector to scalar: build a scalar vector from one element of the initial vector
inline vec_float VEC2SCALVEC0(vec_float a) { return a; } // return x,x,x,a0   // vec_splat(a,0) would return a0,a0,a0,a0
inline vec_float VEC2SCALVEC1(vec_float a) { return vec_splat(a,1); } // return a1,a1,a1,a1
inline vec_float VEC2SCALVEC2(vec_float a) { return vec_splat(a,2); } // return a2,a2,a2,a2
inline vec_float VEC2SCALVEC3(vec_float a) { return vec_splat(a,3); } // return a3,a3,a3,a3

inline vec_int VEC2SCALVEC0(vec_int a) { return a; } // return x,x,x,a0   // vec_splat(a,0) would return a0,a0,a0,a0
inline vec_int VEC2SCALVEC1(vec_int a) { return vec_splat(a,1); } // return a1,a1,a1,a1
inline vec_int VEC2SCALVEC2(vec_int a) { return vec_splat(a,2); } // return a2,a2,a2,a2
inline vec_int VEC2SCALVEC3(vec_int a) { return vec_splat(a,3); } // return a3,a3,a3,a3

// vector to scalar: build a single scalar from a vector
inline float VEC2SCAL0(vec_float a) { float temp __attribute__ ((aligned(16))); vec_ste(vec_splat(a,0),0,&temp); return temp; }
inline float VEC2SCAL1(vec_float a) { float temp __attribute__ ((aligned(16))); vec_ste(vec_splat(a,1),0,&temp); return temp; }
inline float VEC2SCAL2(vec_float a) { float temp __attribute__ ((aligned(16))); vec_ste(vec_splat(a,2),0,&temp); return temp; }
inline float VEC2SCAL3(vec_float a) { float temp __attribute__ ((aligned(16))); vec_ste(vec_splat(a,3),0,&temp); return temp; }

inline int VEC2SCAL0(vec_int a) { int temp __attribute__ ((aligned(16))); vec_ste(vec_splat(a,0),0,&temp); return temp; } 
inline int VEC2SCAL1(vec_int a) { int temp __attribute__ ((aligned(16))); vec_ste(vec_splat(a,1),0,&temp); return temp; }
inline int VEC2SCAL2(vec_int a) { int temp __attribute__ ((aligned(16))); vec_ste(vec_splat(a,2),0,&temp); return temp; }
inline int VEC2SCAL3(vec_int a) { int temp __attribute__ ((aligned(16))); vec_ste(vec_splat(a,3),0,&temp); return temp; }

// select: if( select == 0 ) then a ; else b ;
inline vec_float select_vec( vec_float select, vec_float a, vec_float b)  { return vec_sel(a,b,(vector bool int)select ); }
inline vec_float select_scal( vec_float select, vec_float a, vec_float b) {return vec_sel(a,b,(vector bool int)select );  }
inline vec_float select_vec( vec_int select, vec_float a, vec_float b)  { return vec_sel(a,b,(vector bool int)select ); }
inline vec_float select_scal( vec_int select, vec_float a, vec_float b) {return vec_sel(a,b,(vector bool int)select );  }
inline vec_int select_vec( vec_int select, vec_int a, vec_int b)  { return vec_sel(a,b,(vector bool int)select ); }
inline vec_int select_scal( vec_int select, vec_int a, vec_int b) { return vec_sel(a,b,(vector bool int)select ); }

// vectorial version of the "mem" Faust key-word
// result = { a[2] a[1] a[0] b[3] }
inline vec_float mem1_vec( vec_float a, vec_float b)       { return vec_sld(b,a,12); }
inline vec_int   mem1_vec( vec_int a, vec_int b)           { return vec_sld(b,a,12); }

// result = { a[1] a[0] b[3] b[2] }
inline vec_float mem2_vec( vec_float a, vec_float b)       { return vec_sld(b,a,8); }
inline vec_int   mem2_vec( vec_int a, vec_int b)           { return vec_sld(b,a,8); }

// result = { a[0] b[3] b[2] b[1] }
inline vec_float mem3_vec( vec_float a, vec_float b)       { return vec_sld(b,a,4); }
inline vec_int   mem3_vec( vec_int a, vec_int b)           { return vec_sld(b,a,4); }

// conversion
inline vec_float bool2float( vec_float a )  { return vec_and(a,(vec_float)(vec_splat_s32(int(0x00000001)))); }
inline vec_float bool2float( vec_int a )    { return (vec_float)(vec_and(a,vec_splat_s32(int(0x00000001)))); }

inline vec_int   bool2int( vec_int   a)     { return (vec_int)vec_and(a,vec_splat_s32(int(0x00000001))); }
inline vec_int   bool2int( vec_float a )    { return (vec_int)vec_round(vec_and(a,(vec_float)(vec_splat_s32(int(0x00000001))))); }

inline vec_int   boolfloat2boolint( vec_float a ) { return (vector signed int)a; }
inline vec_float boolint2boolfloat( vec_int   a ) { return (vector float)a; }

inline vec_int   float2int( vec_float a)   { return (vec_int)vec_round(a); }
inline int       float2int( float a )      { return int(a); }

inline vec_float int2float( vec_int a)   { return vec_ctf(a,0); } 
inline float     int2float( int a )      { return float(a); }

#endif
