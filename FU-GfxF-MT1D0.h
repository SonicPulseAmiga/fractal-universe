/******************************************************************************
** FU-GFXF-MT1D0.h                                                           **
**---------------------------------------------------------------------------**
** Graphical Functions for ModeTypes=1 & Dither=0                            **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 04.02.1994                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

void MT1D0Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	WritePixel(&rrp[col[h&GfxInfo.absmaxcol]],x,y);
}

void MT1D0Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register UBYTE c;

	sy=ay+(ay-y);
	c=col[h&GfxInfo.absmaxcol];
	WritePixel(&rrp[c],x,y);
	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2) WritePixel(&rrp[c],x,sy);
}

void MT1D0Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register UBYTE c;

	sx=ax+(ax-x);
	c=col[h&GfxInfo.absmaxcol];
	WritePixel(&rrp[c],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2) WritePixel(&rrp[c],sx,y);
}

void MT1D0Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register UBYTE c;

	sx=ax+(ax-x);sy=ay+(ay-y);
	c=col[h&GfxInfo.absmaxcol];
	WritePixel(&rrp[c],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		WritePixel(&rrp[c],sx,y);
		WritePixel(&rrp[c],x,sy);
		WritePixel(&rrp[c],sx,sy);
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2) WritePixel(&rrp[c],sx,y);
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2) WritePixel(&rrp[c],x,sy);
	}
}

void MT1D0Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	RectFill(&rrp[col[h&GfxInfo.absmaxcol]],x1,y1,x2,y2);
}

void MT1D0Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,sy1,sy2;

	h=col[h&GfxInfo.absmaxcol];
	i=ay+(ay-y1);j=ay+(ay-y2);
	if(i<j) { sy1=i;sy2=j; }
	else { sy1=j;sy2=i; }
	if(sy2>RenderInfo.yb2) sy2=RenderInfo.yb2;
	if(sy1<RenderInfo.yb1) sy1=RenderInfo.yb1;
	RectFill(&rrp[h],x1,y1,x2,y2);
	if(sy2>=sy1) RectFill(&rrp[h],x1,sy1,x2,sy2);
}

void MT1D0Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,sx1,sx2;

	h=col[h&GfxInfo.absmaxcol];
	i=ax+(ax-x1);j=ax+(ax-x2);
	if(i<j) { sx1=i;sx2=j; }
	else { sx1=j;sx2=i; }
	if(sx2>RenderInfo.xb2) sx2=RenderInfo.xb2;
	if(sx1<RenderInfo.xb1) sx1=RenderInfo.xb1;
	RectFill(&rrp[h],x1,y1,x2,y2);
	if(sx2>=sx1) RectFill(&rrp[h],sx1,y1,sx2,y2);
}

void MT1D0Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,sy1,sy2,sx1,sx2;

	h=col[h&GfxInfo.absmaxcol];
	i=ax+(ax-x1);j=ax+(ax-x2);
	if(i<j) { sx1=i;sx2=j; }
	else { sx1=j;sx2=i; }
	if(sx2>RenderInfo.xb2) sx2=RenderInfo.xb2;
	if(sx1<RenderInfo.xb1) sx1=RenderInfo.xb1;
	i=ay+(ay-y1);j=ay+(ay-y2);
	if(i<j) { sy1=i;sy2=j; }
	else { sy1=j;sy2=i; }
	if(sy2>RenderInfo.yb2) sy2=RenderInfo.yb2;
	if(sy1<RenderInfo.yb1) sy1=RenderInfo.yb1;
	RectFill(&rrp[h],x1,y1,x2,y2);
	if(sx2>=sx1) RectFill(&rrp[h],sx1,y1,sx2,y2);
	if(sy2>=sy1) RectFill(&rrp[h],x1,sy1,x2,sy2);
	if(sx2>=sx1 && sy2>=sy1) RectFill(&rrp[h],sx1,sy1,sx2,sy2);
}
