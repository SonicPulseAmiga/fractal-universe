/****h* FractalUniverse/FU-ColF.c [1.68] *
*
*  NAME
*    FU-ColF.c
*  COPYRIGHT
*    $VER: FU-ColF.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    Color Functions
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

#define FU_COLF_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void ChooseColorFunc(void);

// a is z.r, b is z.i, c is z.r², d is z.i²

UWORD GetRIOCNormal(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCStripes(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCDecomp(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCBiomorr1(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCBiomora1(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCBiomorr2(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCBiomora2(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCSumreal(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCSumimag(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCSumreim(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCRealdifn(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCImagdifn(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCReimdifn(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCRealdifp(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCImagdifp(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCReimdifp(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCContPot(double a,double b,double c,double d,UWORD n);
UWORD GetRIOCBinDecomp(double a,double b,double c,double d,UWORD n);

UWORD GetRIICNormal(double a,double b,double c,double d);
UWORD GetRIICReimmag(double a,double b,double c,double d);
UWORD GetRIICRealmag(double a,double b,double c,double d);
UWORD GetRIICImagmag(double a,double b,double c,double d);
UWORD GetRIICRealdifp(double a,double b,double c,double d);
UWORD GetRIICImagdifp(double a,double b,double c,double d);
UWORD GetRIICReimdifp(double a,double b,double c,double d);
UWORD GetRIICDecomp(double a,double b,double c,double d);
UWORD GetRIICOrbit(double a,double b,double c,double d);
UWORD GetRIICBof60(double a,double b,double c,double d);
UWORD GetRIICBof61(double a,double b,double c,double d);
UWORD GetRIICOrbitLength(double a,double b,double c,double d);
UWORD GetRIICOrbitSumReIm(double a,double b,double c,double d);

//-- definitions --------------------------------------------------------------

void ChooseColorFunc(void)
{
	if(RenderInfo.outside==ODecomp || RenderInfo.inside==IDecomp || RenderInfo.outside==OBDecomp)
	{
		RenderInfo.mirrorx=0;RenderInfo.mirrory=0;
	}
	switch((UWORD)RenderInfo.outside)
	{
		case  0: GetOutsideColor=GetRIOCBinDecomp;break;
		case  1: GetOutsideColor=GetRIOCBiomora1;break;
		case  2: GetOutsideColor=GetRIOCBiomorr1;break;
		case  3: GetOutsideColor=GetRIOCBiomora2;break;
		case  4: GetOutsideColor=GetRIOCBiomorr2;break;
		case  5: GetOutsideColor=GetRIOCContPot;break;		
		case  6: GetOutsideColor=GetRIOCDecomp;break;
		case  7: GetOutsideColor=GetRIOCImagdifn;break;
		case  8: GetOutsideColor=GetRIOCRealdifn;break;
		case  9: GetOutsideColor=GetRIOCReimdifn;break;
		case 10: GetOutsideColor=GetRIOCImagdifp;break;
		case 11: GetOutsideColor=GetRIOCRealdifp;break;
		case 12: GetOutsideColor=GetRIOCReimdifp;break;
		case 13: GetOutsideColor=GetRIOCNormal;break;
		case 14: GetOutsideColor=GetRIOCStripes;break;
		case 15: GetOutsideColor=GetRIOCSumimag;break;
		case 16: GetOutsideColor=GetRIOCSumreal;break;
		case 17: GetOutsideColor=GetRIOCSumreim;break;
	}
	switch((UWORD)RenderInfo.inside)
	{
		case  0: GetInsideColor=GetRIICBof60;break;
		case  1: GetInsideColor=GetRIICBof61;break;
		case  2: GetInsideColor=GetRIICDecomp;break;
		case  3: GetInsideColor=GetRIICImagmag;break;
		case  4: GetInsideColor=GetRIICRealmag;break;
		case  5: GetInsideColor=GetRIICReimmag;break;
		case  6: GetInsideColor=GetRIICImagdifp;break;
		case  7: GetInsideColor=GetRIICRealdifp;break;
		case  8: GetInsideColor=GetRIICReimdifp;break;
		case  9: GetInsideColor=GetRIICNormal;break;
		case 10: GetInsideColor=GetRIICOrbit;break;
		case 11: GetInsideColor=GetRIICOrbitLength;break;
		case 12: GetInsideColor=GetRIICOrbitSumReIm;break;
	}
}

//-----------------------------------------------------------------------------

UWORD GetRIOCNormal(double a,double b,double c,double d,UWORD n)
{
	return(RenderInfo.outpar1);
}

UWORD GetRIOCStripes(double a,double b,double c,double d,UWORD n)
{
	return(n);
}

UWORD GetRIOCDecomp(double a,double b,double c,double d,UWORD n)
{
	double r;

	return((UWORD)((asin(a/(r=sqrt(c+d)))+acos(b/r))*decompho));
}

UWORD GetRIOCBiomorr1(double a,double b,double c,double d,UWORD n)
{
	if(c<RenderInfo.bailout || d<RenderInfo.bailout) return((UWORD)(abs(n+RenderInfo.outpar1)));
	else return(n);
}

UWORD GetRIOCBiomora1(double a,double b,double c,double d,UWORD n)
{
	if(c<RenderInfo.bailout || d<RenderInfo.bailout) return(RenderInfo.outpar1);
	else return(n);
}

UWORD GetRIOCBiomorr2(double a,double b,double c,double d,UWORD n)
{
	if(c>RenderInfo.bailout || d>RenderInfo.bailout) return((UWORD)(abs(n+RenderInfo.outpar1)));
	else return(n);
}

UWORD GetRIOCBiomora2(double a,double b,double c,double d,UWORD n)
{
	if(c>RenderInfo.bailout || d>RenderInfo.bailout) return(RenderInfo.outpar1);
	else return(n);
}

UWORD GetRIOCSumreal(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)(n+c));
}

UWORD GetRIOCSumimag(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)(n+d));
}

UWORD GetRIOCSumreim(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)(n+c+d));
}

UWORD GetRIOCRealdifn(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)(fabs(a-x)*n));
}

UWORD GetRIOCImagdifn(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)(fabs(b-y)*n));
}

UWORD GetRIOCReimdifn(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)((fabs(a-x)+fabs(b-y))*n));
}

UWORD GetRIOCRealdifp(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)(fabs(a-x)*RenderInfo.outpar1));
}

UWORD GetRIOCImagdifp(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)(fabs(b-y)*RenderInfo.outpar1));
}

UWORD GetRIOCReimdifp(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)((fabs(a-x)+fabs(b-y))*RenderInfo.outpar1));
}

//UWORD GetRIOCContPot(double a,double b,double c,double d,UWORD n)
//{
//	return((UWORD)((0.5*(log(c+d))/(double)(1L<<n))*RenderInfo.outpar1));
//}

//UWORD GetRIOCContPot(double a,double b,double c,double d,UWORD n)
//{
//	return((UWORD)((0.5*(log(c+d))/pow((1.0+1.0/(double)RenderInfo.outpar2),(double)n))*RenderInfo.outpar1));
//}

// use bailout>>4.0 (e.g. 10000.0)
// log -> base 10
// pow -> base 2
UWORD GetRIOCContPot(double a,double b,double c,double d,UWORD n)
{
	return((UWORD)((0.5*(log(c+d))/pow(2.0,(double)n))*RenderInfo.outpar1));
//	return((UWORD)((0.5*(log(c+d))/pow(1.25,(double)n))*RenderInfo.outpar1));
}


UWORD GetRIOCBinDecomp(double a,double b,double c,double d,UWORD n)
{
	if(a>0.0)
	{
		if(b>0.0) return(0);
		else return(1);
	}
	else
	{
		if(b>0.0) return(1);
		else return(0);
	}
}

//-----------------------------------------------------------------------------

UWORD GetRIICNormal(double a,double b,double c,double d)
{
	return(RenderInfo.inpar1);
}

UWORD GetRIICReimmag(double a,double b,double c,double d)
{
	return((UWORD)((c+d)*RenderInfo.z));
}

UWORD GetRIICRealmag(double a,double b,double c,double d)
{
	return((UWORD)(c*RenderInfo.z));
}

UWORD GetRIICImagmag(double a,double b,double c,double d)
{
	return((UWORD)(d*RenderInfo.z));
}

UWORD GetRIICRealdifp(double a,double b,double c,double d)
{
	return((UWORD)(fabs(a-x)*RenderInfo.inpar1));
}

UWORD GetRIICImagdifp(double a,double b,double c,double d)
{
	return((UWORD)(fabs(b-y)*RenderInfo.inpar1));
}

UWORD GetRIICReimdifp(double a,double b,double c,double d)
{
	return((UWORD)((fabs(a-x)+fabs(b-y))*RenderInfo.inpar1));
}

UWORD GetRIICDecomp(double a,double b,double c,double d)
{
	double r;

	return((UWORD)((asin(a/(r=sqrt(c+d)))+acos(b/r))*decomphi));
}

UWORD GetRIICOrbit(double a,double b,double c,double d)
{
	return((UWORD)((fabs(ob[RenderInfo.inpar2].r)+fabs(ob[RenderInfo.inpar2].i))*RenderInfo.inpar1));
}

// abs of smallest z-value
UWORD GetRIICBof60(double a,double b,double c,double d)
{
	return((UWORD)(bofabs*RenderInfo.inpar1));
}

// index of smallest z-value
UWORD GetRIICBof61(double a,double b,double c,double d)
{
	return(bofz);
}

UWORD GetRIICOrbitLength(double a,double b,double c,double d)
{
	UWORD i;
	double s=0.0,lr,li;

	for(i=1;i<obanz;i++) {
		lr=fabs(ob[i].r-ob[i-1].r);
		li=fabs(ob[i].i-ob[i-1].i);
		s+=(lr*lr+li*li);
	}
	return((UWORD)((s*RenderInfo.inpar1)/(double)obanz));
}

UWORD GetRIICOrbitSumReIm(double a,double b,double c,double d)
{
	UWORD i;
	double s=0.0,lr,li;

	for(i=0;i<obanz;i++) {
		lr=fabs(ob[i].r-c);
		li=fabs(ob[i].i-d);
		s+=(lr*lr+li*li);
	}
	return((UWORD)((s*RenderInfo.inpar1)/(double)obanz));
}
