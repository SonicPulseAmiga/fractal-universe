/****h* FractalUniverse/FU-Cplx.h [1.68] *
*
*  NAME
*    FU-Cplx.hc
*  COPYRIGHT
*    $VER: FU-Cplx.h 1.68 (24.10.01) © by Stefan Kost 2001-22001
*  FUNCTION
*
*  AUTHOR
*    Stefan Kost			sk		kost@imn.htwk-leipzig.de
*  CREATION DATE
*    24.Oct.2001
*  MODIFICATION HISTORY
*    24.Oct.2001	V 1.68	most recent version
*    24.Oct.2001	V 1.68	initial version
*  NOTES
*
*******
*/

#ifndef FU_CPLX_H
#define FU_CPLX_H

//-- prototypes ---------------------------------------------------------------

#ifndef FU_CPLX_C
	extern complex cplx_erg(complex p1,complex p2);
	extern complex cplx_add(complex p1,complex p2);
	extern complex cplx_sub(complex p1,complex p2);
	extern complex cplx_mul(complex p1,complex p2);
	extern complex cplx_div(complex p1,complex p2);
	extern complex cplx_abs(complex p1,complex p2);
	extern complex cplx_log(complex p1,complex p2);
	extern complex cplx_exp(complex p1,complex p2);
	extern complex cplx_pow(complex p1,complex p2);
	extern complex cplx_sin(complex p1,complex p2);
	extern complex cplx_cos(complex p1,complex p2);
	extern complex cplx_tan(complex p1,complex p2);
	extern complex cplx_sinh(complex p1,complex p2);
	extern complex cplx_cosh(complex p1,complex p2);
	extern complex cplx_tanh(complex p1,complex p2);
	extern complex cplx_real(complex p1,complex p2);
	extern complex cplx_imag(complex p1,complex p2);
	extern complex cplx_swap(complex p1,complex p2);
	extern complex cplx_inv(complex p1,complex p2);
#endif

//-- defines ------------------------------------------------------------------

//-- globals ------------------------------------------------------------------

//-- definitions --------------------------------------------------------------

#endif /* FU_CPLX_H */
//-- eof ----------------------------------------------------------------------
