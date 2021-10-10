/****h* FractalUniverse/FU-Cplx.c [1.68] *
*
*  NAME
*    FU-Cplx.c
*  COPYRIGHT
*    $VER: FU-Cplx.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    The Complex Math Functions
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

//-- includes -----------------------------------------------------------------

#define FU_CPLX_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

complex cplx_erg(complex p1,complex p2);
complex cplx_add(complex p1,complex p2);
complex cplx_sub(complex p1,complex p2);
complex cplx_mul(complex p1,complex p2);
complex cplx_div(complex p1,complex p2);
complex cplx_abs(complex p1,complex p2);
complex cplx_log(complex p1,complex p2);
complex cplx_exp(complex p1,complex p2);
complex cplx_pow(complex p1,complex p2);
complex cplx_sin(complex p1,complex p2);
complex cplx_cos(complex p1,complex p2);
complex cplx_tan(complex p1,complex p2);
complex cplx_sinh(complex p1,complex p2);
complex cplx_cosh(complex p1,complex p2);
complex cplx_tanh(complex p1,complex p2);
complex cplx_real(complex p1,complex p2);
complex cplx_imag(complex p1,complex p2);
complex cplx_swap(complex p1,complex p2);
complex cplx_inv(complex p1,complex p2);

//-- definitions --------------------------------------------------------------

complex cplx_erg(complex p1,complex p2)
{
	return(p1);
}

complex cplx_add(complex p1,complex p2)
{
	static complex e;

	e.r=p1.r+p2.r;
	e.i=p1.i+p2.i;
	return(e);
}

complex cplx_sub(complex p1,complex p2)
{
	static complex e;

	e.r=p1.r-p2.r;
	e.i=p1.i-p2.i;
	return(e);
}

complex cplx_mul(complex p1,complex p2)
{
	static complex e;

	e.r=p1.r*p2.r-p1.i*p2.i;
	e.i=p1.r*p2.i+p1.i*p2.r;
	return(e);
}

complex cplx_div(complex p1,complex p2)
{
	static complex e;
	double t;

	e.r=(p1.r*p2.r+p1.i*p2.i)/(t=p2.r*p2.r+p2.i*p2.i);
	e.i=(p1.i*p2.r-p2.i*p1.r)/t;
	return(e);
}

complex cplx_abs(complex p1,complex p2)
{
	static complex e;

	e.r=sqrt(p1.r*p1.r+p1.i*p1.i);
	e.i=0;
	return(e);
}

complex cplx_log(complex p1,complex p2)
{
	static complex e;

	e.r=log(p1.r*p1.r+p1.i*p1.i)/2.0;
	e.i=atan2(p1.i,p1.r);			/* atan(p1.i/p1.r); */
	return(e);
}

complex cplx_exp(complex p1,complex p2)
{
	static complex e;

	e.r=exp(p1.r)*cos(p1.i);
	e.i=exp(p1.r)*sin(p1.i);
	return(e);
}

complex cplx_pow(complex p1,complex p2)
{
	static complex h1;
	complex h2;

	h1.r=log(p1.r*p1.r+p1.i*p1.i)/2.0;
	h1.i=atan2(p1.i,p1.r);									/* h1=cplx_log(p1,p2); */

	h2.r=p2.r*h1.r-p2.i*h1.i;
	h2.i=p2.r*h1.i+p2.i*h1.r;

	h1.r=exp(h2.r)*cos(h2.i);
	h1.i=exp(h2.r)*sin(h2.i);								/* h1=cplx_exp(h2,p2) */

	return(h1);
}

complex cplx_sin(complex p1,complex p2)
{
	static complex e;

	e.r=sin(p1.r)*cosh(p1.i);
	e.i=cos(p1.r)*sinh(p1.i);
	return(e);
}

complex cplx_cos(complex p1,complex p2)
{
	static complex e;

	e.r=cos(p1.r)*cosh(p1.i);
	e.i=-1*sin(p1.r)*sinh(p1.i);
	return(e);
}

complex cplx_tan(complex p1,complex p2)
{
	static complex e;

	e.r=sin(p1.r+p1.r)/(cos(p1.r+p1.r)+cosh(p1.i+p1.i));
	e.i=sinh(p1.i+p1.i)/(cos(p1.r+p1.r)+cosh(p1.i+p1.i));
	return(e);
}

complex cplx_sinh(complex p1,complex p2)
{
	static complex e;

	e.r=sinh(p1.r)*cos(p1.i);
	e.i=cosh(p1.r)*sin(p1.i);
	return(e);
}

complex cplx_cosh(complex p1,complex p2)
{
	static complex e;

	e.r=cosh(p1.r)*cos(p1.i);
	e.i=sinh(p1.r)*sin(p1.i);
	return(e);
}

complex cplx_tanh(complex p1,complex p2)
{
	static complex e;

	e.r=sinh(p1.r+p1.r)/(cosh(p1.r+p1.r)+cos(p1.i+p1.i));
	e.i=sin(p1.i+p1.i)/(cosh(p1.r+p1.r)+cos(p1.i+p1.i));
	return(e);
}

complex cplx_real(complex p1,complex p2)
{
	static complex e;

	e.r=p1.r;
	e.i=0.0;
	return(e);
}

complex cplx_imag(complex p1,complex p2)
{
	static complex e;

	e.r=0.0;
	e.i=p1.i;
	return(e);
}

complex cplx_swap(complex p1,complex p2)
{
	static complex e;

	e.r=p1.i;
	e.i=p1.r;
	return(e);
}

complex cplx_inv(complex p1,complex p2)
{
	static complex e;
	double t;

	e.r=p1.r/(t=p1.r*p1.r+p1.i*p1.i);
	e.i=-p1.i/t;
	return(e);
}
