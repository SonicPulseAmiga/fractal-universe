/******************************************************************************
** FU-GFXF-MT1D4.h                                                           **
**---------------------------------------------------------------------------**
** Graphical Functions for ModeTypes=0 & Dither=4                            **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 04.02.1994                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

void MT1D4Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register UBYTE c;
	register double in;

	in=(double)h/GfxInfo.ordscl+derr;
	c=(int)in;derr=in-c;
	WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],x,y);
}

void MT1D4Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register UBYTE c;
	register double in;

	sy=ay+(ay-y);
	in=(double)h/GfxInfo.ordscl+derr;
	c=(int)in;derr=in-(double)c;
	WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],x,y);
	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],x,sy);
}

void MT1D4Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register UBYTE c;
	register double in;

	sx=ax+(ax-x);
	in=(double)h/GfxInfo.ordscl+derr;
	c=(int)in;derr=in-(double)c;
	WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
		WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],sx,y);
}

void MT1D4Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register UBYTE c;
	register double in;

	sx=ax+(ax-x);sy=ay+(ay-y);
	in=(double)h/GfxInfo.ordscl+derr;
	c=(int)in;derr=in-(double)c;
	WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],sx,y);
		WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],x,sy);
		WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],sx,sy);
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
			WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],sx,y);
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
			WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],x,sy);
	}
}

void MT1D4Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx1;
	register UBYTE tx2,c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
	tx1=x1>>3;tx2=x1&7;
	for(j=y1;j<=y2;j++)
	{
		for(i=x1;i<=x2;i++)
		{
			in=hs+derr;
			c=(int)in;derr=in-c;
			WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],i,j);
		}
	}
}

void MT1D4Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx1,sy;
	register UBYTE tx2,c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
	tx1=x1>>3;tx2=x1&7;
	for(j=y1;j<=y2;j++)
	{
		for(i=x1;i<=x2;i++)
		{
			in=hs+derr;
			c=(int)in;derr=in-c;
			WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],i,j);
		}
	}
	sy=ay+(ay-y1);
	for(j=y1;j<=y2;j++,sy--)
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			for(i=x1;i<=x2;i++)
			{
				in=hs+derr;
				c=(int)in;derr=in-c;
				WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],i,sy);
			}
		}
	
}

void MT1D4Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx1,tx3,sx;
	register UBYTE tx2,c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
	tx1=x1>>3;tx2=x1&7;
	for(j=y1;j<=y2;j++)
	{
		for(i=x1;i<=x2;i++)
		{
			in=hs+derr;
			c=(int)in;derr=in-c;
			WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],i,j);
		}
	}
	tx3=ax+(ax-x1);
	tx1=tx3>>3;tx2=tx3&7;
	for(j=y1;j<=y2;j++)
	{
		sx=tx3;
		for(i=x1;i<=x2;i++,sx--)
			if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
			{
				in=hs+derr;
				c=(int)in;derr=in-c;
				WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],sx,j);
			}
		
	}
}

void MT1D4Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx1,tx3,sy,sx;
	register UBYTE tx2,c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
	tx1=x1>>3;tx2=x1&7;
	for(j=y1;j<=y2;j++)
	{
		for(i=x1;i<=x2;i++)
		{
			in=hs+derr;
			c=(int)in;derr=in-c;
			WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],i,j);
		}
	}
	sy=ay+(ay-y1);
	for(j=y1;j<=y2;j++,sy--)
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			for(i=x1;i<=x2;i++)
			{
				in=hs+derr;
				c=(int)in;derr=in-c;
				WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],i,sy);
			}
		}
	tx3=ax+(ax-x1);
	tx1=tx3>>3;tx2=tx3&7;
	for(j=y1;j<=y2;j++)
	{
		sx=tx3;
		for(i=x1;i<=x2;i++,sx--)
			if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
			{
				in=hs+derr;
				c=(int)in;derr=in-c;
				WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],sx,j);
			}
	}
	sy=ay+(ay-y1);
	for(j=y1;j<=y2;j++,sy--)
	{
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			sx=tx3;
			for(i=x1;i<=x2;i++,sx--)
				if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
				{
					in=hs+derr;
					c=(int)in;derr=in-c;
					WritePixel(&rrp[col[c&GfxInfo.absmaxcol]],sx,sy);
				}
		}
	}
}
