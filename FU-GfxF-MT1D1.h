/******************************************************************************
** FU-GFXF-MT1D1.h                                                           **
**---------------------------------------------------------------------------**
** Graphical Functions for ModeTypes=1 & Dither=1                            **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 04.02.1994                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

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
	register WORD i,j,tx1,sy2;
	register UBYTE tx2,bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
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
	register WORD i,j,tx1,tx3,sy1,sy2;
	register UBYTE tx2,bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
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
	register WORD i,j,tx1,tx3,sx1,sx2;
	register UBYTE tx2,bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(j=y1;j<=y2;j++)
		{
			sx2=j&1;
			for(i=x1;i<=x2;i++)
				WritePixel(&rrp[col[(bc+D1[rc][i&1][sx2])&GfxInfo.absmaxcol]],i,j);
		}
		tx3=ax+(ax-x1);
		tx1=tx3>>3;tx2=tx3&7;
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
	register WORD i,j,tx1,tx3,sy1,sy2,sx1,sx2;
	register UBYTE tx2,bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
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
		tx1=tx3>>3;tx2=tx3&7;
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
