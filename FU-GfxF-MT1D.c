/****h* FractalUniverse/FU-GfxF-MT1D.c [1.68] *
*
*  NAME
*    FU-GfxF-MT1D.c
*  COPYRIGHT
*    $VER: FU-GfxF-MT1D.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    Graphical Functions
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

#define FU_GFXF_MT1D_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void MT1D0Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D0Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D0Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D0Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D0Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D0Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D0Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D0Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D1Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D1Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D1Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D1Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D1Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D1Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D1Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D1Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D2Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D2Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D2Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D2Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D2Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D2Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D2Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D2Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D3Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D3Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D3Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D3Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D3Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D3Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D3Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D3Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D4Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D4Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D4Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D4Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT1D4Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D4Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D4Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT1D4Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);

//-- definitions --------------------------------------------------------------

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

/******************************************************************************/

void MT1D1Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	WritePixel(&rrp[col[((h>>1)+D1[h&1][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
}

void MT1D1Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register UBYTE bc,rc;

	sy=ay+(ay-y);
	bc=h>>1;rc=h&1;
	WritePixel(&rrp[col[(bc+D1[rc][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		WritePixel(&rrp[col[(bc+D1[rc][x&1][sy&1])&GfxInfo.absmaxcol]],x,sy);
}

void MT1D1Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register UBYTE bc,rc;

	sx=ax+(ax-x);
	bc=h>>1;rc=h&1;
	WritePixel(&rrp[col[(bc+D1[rc][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
		WritePixel(&rrp[col[(bc+D1[rc][sx&1][y&1])&GfxInfo.absmaxcol]],sx,y);
}

void MT1D1Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register UBYTE bc,rc;

	sx=ax+(ax-x);sy=ay+(ay-y);
	bc=h>>1;rc=h&1;
	WritePixel(&rrp[col[(bc+D1[rc][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		WritePixel(&rrp[col[(bc+D1[rc][sx&1][y&1])&GfxInfo.absmaxcol]],sx,y);
		WritePixel(&rrp[col[(bc+D1[rc][x&1][sy&1])&GfxInfo.absmaxcol]],x,sy);
		WritePixel(&rrp[col[(bc+D1[rc][sx&1][sy&1])&GfxInfo.absmaxcol]],sx,sy);
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
			WritePixel(&rrp[col[(bc+D1[rc][sx&1][y&1])&GfxInfo.absmaxcol]],sx,y);
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
			WritePixel(&rrp[col[(bc+D1[rc][x&1][sy&1])&GfxInfo.absmaxcol]],x,sy);
	}
}

void MT1D1Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,sy2;
	register UBYTE bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sy2=j&1;
			for(i=x1;i<=x2;i++)
			{
				WritePixel(&rrp[col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,j);
			}
		}
	}
	else RectFill(&rrp[col[bc&GfxInfo.absmaxcol]],x1,y1,x2,y2);
}

void MT1D1Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx3,sy1,sy2;
	register UBYTE bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sy2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ay+(ay-y1);
		sy1=tx3;
		for(j=y1;j<=y2;j++,sy1--)
			if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
			{
				sy2=sy1&1;
				for(i=x1;i<=x2;i++)
					WritePixel(&rrp[col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,sy1);
			}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ay+(ay-y1);j=ay+(ay-y2);
		if(i<j) { sy1=i;sy2=j; }
		else { sy1=j;sy2=i; }
		if(sy2>RenderInfo.yb2) sy2=RenderInfo.yb2;
		if(sy1<RenderInfo.yb1) sy1=RenderInfo.yb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sy2>=sy1)	RectFill(&rrp[h],x1,sy1,x2,sy2);
	}
}

void MT1D1Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx3,sx1,sx2;
	register UBYTE bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sx2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D1[rc][i&1][sx2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ax+(ax-x1);
		for(j=y1;j<=y2;j++)
		{
			sx1=tx3;
			sx2=j&1;
			for(i=x1;i<=x2;i++,sx1--)
				if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
					WritePixel(&rrp[col[(bc+D1[rc][i&1][sx2])&GfxInfo.absmaxcol]],sx1,j);
			}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ax+(ax-x1);j=ax+(ax-x2);
		if(i<j) { sx1=i;sx2=j; }
		else { sx1=j;sx2=i; }
		if(sx2>RenderInfo.xb2) sx2=RenderInfo.xb2;
		if(sx1<RenderInfo.xb1) sx1=RenderInfo.xb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sx2>=sx1)	RectFill(&rrp[h],sx1,y1,sx2,y2);
	}
}

void MT1D1Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx3,sy1,sy2,sx1,sx2;
	register UBYTE bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sy2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ay+(ay-y1);
		sy1=tx3;
		for(j=y1;j<=y2;j++,sy1--)
			if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
			{
				sy2=sy1&1;
				for(i=x1;i<=x2;i++)
					WritePixel(&rrp[col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,sy1);
			}
		tx3=ax+(ax-x1);
		for(j=y1;j<=y2;j++)
		{
			sx1=tx3;sx2=j&1;
			for(i=x1;i<=x2;i++,sx1--)
				if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
					WritePixel(&rrp[col[(bc+D1[rc][i&1][sx2])&GfxInfo.absmaxcol]],sx1,j);
		}
		sy1=ay+(ay-y1);
		for(j=y1;j<=y2;j++,sy1--)
		{
			if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
			{
				sx1=tx3;sx2=sy1&1;
				for(i=x1;i<=x2;i++,sx1--)
					if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
						WritePixel(&rrp[col[(bc+D1[rc][i&1][sx2])&GfxInfo.absmaxcol]],sx1,sy1);
			}
		}
	}
	else
	{
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
}

/******************************************************************************/

void MT1D2Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	WritePixel(&rrp[col[((h>>2)+D2[h&3][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
}

void MT1D2Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register UBYTE bc,rc;

	sy=ay+(ay-y);
	bc=h>>2;rc=h&3;
	WritePixel(&rrp[col[(bc+D2[rc][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		WritePixel(&rrp[col[(bc+D2[rc][x&1][sy&1])&GfxInfo.absmaxcol]],x,sy);
}

void MT1D2Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register UBYTE bc,rc;

	sx=ax+(ax-x);
	bc=h>>2;rc=h&3;
	WritePixel(&rrp[col[(bc+D2[rc][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
		WritePixel(&rrp[col[(bc+D2[rc][sx&1][y&1])&GfxInfo.absmaxcol]],sx,y);
}

void MT1D2Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register UBYTE bc,rc;

	sx=ax+(ax-x);sy=ay+(ay-y);
	bc=h>>2;rc=h&3;
	WritePixel(&rrp[col[(bc+D2[rc][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		WritePixel(&rrp[col[(bc+D2[rc][sx&1][y&1])&GfxInfo.absmaxcol]],sx,y);
		WritePixel(&rrp[col[(bc+D2[rc][x&1][sy&1])&GfxInfo.absmaxcol]],x,sy);
		WritePixel(&rrp[col[(bc+D2[rc][sx&1][sy&1])&GfxInfo.absmaxcol]],sx,sy);
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
			WritePixel(&rrp[col[(bc+D2[rc][sx&1][y&1])&GfxInfo.absmaxcol]],sx,y);
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
			WritePixel(&rrp[col[(bc+D2[rc][x&1][sy&1])&GfxInfo.absmaxcol]],x,sy);
	}
}

void MT1D2Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,sy2;
	register UBYTE bc,rc;

	bc=h>>2;rc=h&3;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sy2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,j);
		}
	}
	else RectFill(&rrp[col[bc&GfxInfo.absmaxcol]],x1,y1,x2,y2);
}

void MT1D2Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx3,sy1,sy2;
	register UBYTE bc,rc;

	bc=h>>2;rc=h&3;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sy2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ay+(ay-y1);
		sy1=tx3;
		for(j=y1;j<=y2;j++,sy1--)
			if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
			{
				sy2=sy1&1;
				for(i=x1;i<=x2;i++)
					WritePixel(&rrp[col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,sy1);
			}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ay+(ay-y1);j=ay+(ay-y2);
		if(i<j) { sy1=i;sy2=j; }
		else { sy1=j;sy2=i; }
		if(sy2>RenderInfo.yb2) sy2=RenderInfo.yb2;
		if(sy1<RenderInfo.yb1) sy1=RenderInfo.yb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sy2>=sy1) RectFill(&rrp[h],x1,sy1,x2,sy2);
	}
}

void MT1D2Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx3,sx1,sx2;
	register UBYTE bc,rc;

	bc=h>>2;rc=h&3;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sx2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D2[rc][i&1][sx2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ax+(ax-x1);
		for(j=y1;j<=y2;j++)
		{
			sx1=tx3;
			sx2=j&1;
			for(i=x1;i<=x2;i++,sx1--)
				if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
					WritePixel(&rrp[col[(bc+D2[rc][i&1][sx2])&GfxInfo.absmaxcol]],sx1,j);
			}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ax+(ax-x1);j=ax+(ax-x2);
		if(i<j) { sx1=i;sx2=j; }
		else { sx1=j;sx2=i; }
		if(sx2>RenderInfo.xb2) sx2=RenderInfo.xb2;
		if(sx1<RenderInfo.xb1) sx1=RenderInfo.xb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sx2>=sx1) RectFill(&rrp[h],sx1,y1,sx2,y2);
	}
}

void MT1D2Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx3,sy1,sy2,sx1,sx2;
	register UBYTE bc,rc;

	bc=h>>2;rc=h&3;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sy2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ay+(ay-y1);
		sy1=tx3;
		for(j=y1;j<=y2;j++,sy1--)
			if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
			{
				sy2=sy1&1;
				for(i=x1;i<=x2;i++)
					WritePixel(&rrp[col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,sy1);
			}
		tx3=ax+(ax-x1);
		for(j=y1;j<=y2;j++)
		{
			sx1=tx3;sx2=j&1;
			for(i=x1;i<=x2;i++,sx1--)
				if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
					WritePixel(&rrp[col[(bc+D2[rc][i&1][sx2])&GfxInfo.absmaxcol]],sx1,j);
		}
		sy1=ay+(ay-y1);
		for(j=y1;j<=y2;j++,sy1--)
		{
			if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
			{
				sx1=tx3;sx2=sy1&1;
				for(i=x1;i<=x2;i++,sx1--)
					if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
						WritePixel(&rrp[col[(bc+D2[rc][i&1][sx2])&GfxInfo.absmaxcol]],sx1,sy1);
			}
		}
	}
	else
	{
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
}

/******************************************************************************/

void MT1D3Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	WritePixel(&rrp[col[((h>>4)+D3[h&15][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
}

void MT1D3Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register UBYTE bc,rc;

	sy=ay+(ay-y);
	bc=h>>4;rc=h&15;
	WritePixel(&rrp[col[(bc+D3[rc][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		WritePixel(&rrp[col[(bc+D3[rc][x&1][sy&1])&GfxInfo.absmaxcol]],x,sy);
}

void MT1D3Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register UBYTE bc,rc;

	sx=ax+(ax-x);
	bc=h>>4;rc=h&15;
	WritePixel(&rrp[col[(bc+D3[rc][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
		WritePixel(&rrp[col[(bc+D3[rc][sx&1][y&1])&GfxInfo.absmaxcol]],sx,y);
}

void MT1D3Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register UBYTE bc,rc;

	sx=ax+(ax-x);sy=ay+(ay-y);
	bc=h>>4;rc=h&15;
	WritePixel(&rrp[col[(bc+D3[rc][x&1][y&1])&GfxInfo.absmaxcol]],x,y);
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		WritePixel(&rrp[col[(bc+D3[rc][sx&1][y&1])&GfxInfo.absmaxcol]],sx,y);
		WritePixel(&rrp[col[(bc+D3[rc][x&1][sy&1])&GfxInfo.absmaxcol]],x,sy);
		WritePixel(&rrp[col[(bc+D3[rc][sx&1][sy&1])&GfxInfo.absmaxcol]],sx,sy);
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
			WritePixel(&rrp[col[(bc+D3[rc][sx&1][y&1])&GfxInfo.absmaxcol]],sx,y);
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
			WritePixel(&rrp[col[(bc+D3[rc][x&1][sy&1])&GfxInfo.absmaxcol]],x,sy);
	}
}

void MT1D3Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,sy2;
	register UBYTE bc,rc;

	bc=h>>4;rc=h&15;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sy2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D3[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,j);
		}
	}
	else RectFill(&rrp[col[bc&GfxInfo.absmaxcol]],x1,y1,x2,y2);
}

void MT1D3Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx3,sy1,sy2;
	register UBYTE bc,rc;

	bc=h>>4;rc=h&15;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sy2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D3[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ay+(ay-y1);
		sy1=tx3;
		for(j=y1;j<=y2;j++,sy1--)
			if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
			{
				sy2=sy1&1;
				for(i=x1;i<=x2;i++)
					WritePixel(&rrp[col[(bc+D3[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,sy1);
			}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ay+(ay-y1);j=ay+(ay-y2);
		if(i<j) { sy1=i;sy2=j; }
		else { sy1=j;sy2=i; }
		if(sy2>RenderInfo.yb2) sy2=RenderInfo.yb2;
		if(sy1<RenderInfo.yb1) sy1=RenderInfo.yb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sy2>=sy1) RectFill(&rrp[h],x1,sy1,x2,sy2);
	}
}

void MT1D3Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx3,sx1,sx2;
	register UBYTE bc,rc;

	bc=h>>4;rc=h&15;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sx2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D3[rc][i&1][sx2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ax+(ax-x1);
		for(j=y1;j<=y2;j++)
		{
			sx1=tx3;
			sx2=j&1;
			for(i=x1;i<=x2;i++,sx1--)
				if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
					WritePixel(&rrp[col[(bc+D3[rc][i&1][sx2])&GfxInfo.absmaxcol]],sx1,j);
			}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ax+(ax-x1);j=ax+(ax-x2);
		if(i<j) { sx1=i;sx2=j; }
		else { sx1=j;sx2=i; }
		if(sx2>RenderInfo.xb2) sx2=RenderInfo.xb2;
		if(sx1<RenderInfo.xb1) sx1=RenderInfo.xb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sx2>=sx1) RectFill(&rrp[h],sx1,y1,sx2,y2);
	}
}

void MT1D3Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,tx3,sy1,sy2,sx1,sx2;
	register UBYTE bc,rc;

	bc=h>>4;rc=h&15;
	if(rc)
	{
		for(j=y1;j<=y2;j++)
		{
			sy2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D3[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ay+(ay-y1);
		sy1=tx3;
		for(j=y1;j<=y2;j++,sy1--)
			if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
			{
				sy2=sy1&1;
				for(i=x1;i<=x2;i++)
					WritePixel(&rrp[col[(bc+D3[rc][i&1][sy2])&GfxInfo.absmaxcol]],i,sy1);
			}
		tx3=ax+(ax-x1);
		for(j=y1;j<=y2;j++)
		{
			sx1=tx3;sx2=j&1;
			for(i=x1;i<=x2;i++,sx1--)
				if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
					WritePixel(&rrp[col[(bc+D3[rc][i&1][sx2])&GfxInfo.absmaxcol]],sx1,j);
		}
		sy1=ay+(ay-y1);
		for(j=y1;j<=y2;j++,sy1--)
		{
			if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
			{
				sx1=tx3;sx2=sy1&1;
				for(i=x1;i<=x2;i++,sx1--)
					if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
						WritePixel(&rrp[col[(bc+D3[rc][i&1][sx2])&GfxInfo.absmaxcol]],sx1,sy1);
			}
		}
	}
	else
	{
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
}

/******************************************************************************/

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
	register WORD i,j;
	register UBYTE c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
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
	register WORD i,j,sy;
	register UBYTE c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
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
	register WORD i,j,tx3,sx;
	register UBYTE c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
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
	register WORD i,j,tx3,sy,sx;
	register UBYTE c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
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
