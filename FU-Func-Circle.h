/******************************************************************************
** FU-FUNC-CIRCLE.h                                                          **
**---------------------------------------------------------------------------**
** Fractal Functions                                                         **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 04.02.1994                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

UWORD FuncCircle0(void)
{
	return((UWORD)((RenderInfo.bailout*(rx*rx+ry*ry))/GfxInfo.palscl));
}

UWORD FuncCircle1(void)
{
	register UWORD c1,c2;

	c1=(UWORD)(RenderInfo.bailout*(pow(rx,RenderInfo.par1.r)+pow(ry,RenderInfo.par1.i)));
	c2=(UWORD)(RenderInfo.bailout*(pow(rx-5.0,RenderInfo.par2.r)+pow(ry-5.0,RenderInfo.par2.i)));
	return((UWORD)(abs((c1+c2)>>1)/GfxInfo.palscl));
}

UWORD FuncCircle2(void)
{
	register UWORD c1,c2;

	c1=(UWORD)(RenderInfo.bailout*(pow(rx,RenderInfo.par1.r)+pow(ry,RenderInfo.par1.i)));
	c2=(UWORD)(RenderInfo.bailout*(sin(rx-5.0)*cos(ry-5.0)));
	return((UWORD)(abs((c1+c2)>>1)/GfxInfo.palscl));
}

UWORD FuncCircle3(void)
{
	register UWORD c1,c2,c3,c4;

	c1=(UWORD)(RenderInfo.bailout*(pow(rx,RenderInfo.par1.r)+pow(ry,RenderInfo.par1.i)));
	c2=(UWORD)(RenderInfo.bailout*(pow(rx-5.0,RenderInfo.par2.r)+pow(ry-5.0,RenderInfo.par2.i)));
	c3=(UWORD)(RenderInfo.bailout*(pow(rx+5.0,RenderInfo.par2.r)+pow(ry+5.0,RenderInfo.par2.i)));
	c4=(UWORD)(RenderInfo.bailout*(sin(rx)*cos(ry)));
	return((UWORD)(abs((c1+c2+c3+c4)>>2)/GfxInfo.palscl));
}

UWORD FuncCircle4(void)
{
	register UWORD c1,c2,c3,c4;

	c1=(UWORD)(RenderInfo.bailout*(pow(rx,RenderInfo.par1.r)+pow(ry,RenderInfo.par1.i)));
	c2=(UWORD)(RenderInfo.bailout*(pow(rx-5.0,RenderInfo.par2.r)+pow(ry-5.0,RenderInfo.par2.i)));
	c3=(UWORD)(RenderInfo.bailout*(pow(rx+5.0,RenderInfo.par2.r)+pow(ry+5.0,RenderInfo.par2.i)));
	c4=(UWORD)(RenderInfo.bailout*(log(rx*rx)*tan(ry*ry)));
	return((UWORD)(abs((c1+c2+c3+c4)>>2)/GfxInfo.palscl));
}

UWORD FuncCircle5(void)
{
	register UWORD c1;

	c1=(UWORD)(RenderInfo.bailout*(log(rx*rx)*tan(ry*ry)));
	return((UWORD)(abs(c1)/GfxInfo.palscl));
}

UWORD FuncCircle6(void)
{
	register UWORD c1;

	c1=(UWORD)(RenderInfo.bailout*(sin(rx)*cos(ry)));
	return((UWORD)(abs(c1)/GfxInfo.palscl));
}

UWORD FuncCircle7(void)
{
	register UWORD c1,c2;

	c1=(UWORD)(RenderInfo.bailout*(pow(rx-5.0,RenderInfo.par1.r)+pow(ry-5.0,RenderInfo.par1.i)));
	c2=(UWORD)(RenderInfo.bailout*(pow(rx+5.0,RenderInfo.par1.r)+pow(ry+5.0,RenderInfo.par1.i)));
	return((UWORD)(abs((c1+c2)>>1)/GfxInfo.palscl));
}
