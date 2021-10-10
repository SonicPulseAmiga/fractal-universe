/****h* FractalUniverse/FU-GfxF-MT0D.c [1.68] *
*
*  NAME
*    FU-GfxF-MT0D.c
*  COPYRIGHT
*    $VER: FU-GfxF-MT0D.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
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

#define FU_GFXF_MT0D_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void MT0D0Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D0Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D0Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D0Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D0Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D0Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D0Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D0Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D1Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D1Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D1Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D1Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D1Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D1Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D1Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D1Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D2Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D2Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D2Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D2Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D2Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D2Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D2Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D2Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D3Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D3Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D3Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D3Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D3Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D3Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D3Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D3Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D4Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D4Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D4Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D4Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay);
void MT0D4Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D4Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D4Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);
void MT0D4Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay);

//-- definitions --------------------------------------------------------------

void MT0D0Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register ULONG addr;
	register UBYTE i,c,p;

	c=col[h&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
}

void MT0D0Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register ULONG addr;
	register UBYTE i,rest,c,p;

	sy=ay+(ay-y);
	c=col[h&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		addr=BPR*sy+(x>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D0Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register ULONG addr;
	register UBYTE i,rest,c,p;

	sx=ax+(ax-x);
	c=col[h&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
	{
		addr=BPR*y+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D0Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register ULONG addr;
	register UBYTE i,rest,c,p;

	sx=ax+(ax-x);sy=ay+(ay-y);
	c=col[h&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		addr=BPR*sy+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		addr=BPR*y+(sx>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		addr=BPR*sy+(x>>3);
		p=128>>(rest=x&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
		{
			addr=BPR*y+(sx>>3);
			p=128>>(rest=sx&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			addr=BPR*sy+(x>>3);
			p=128>>(rest=x&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
	}
}

void MT0D0Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	RectFill(&rrp[col[h&GfxInfo.absmaxcol]],x1,y1,x2,y2);
}

void MT0D0Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
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

void MT0D0Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
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

void MT0D0Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
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
	if(sx2>=sx1)	RectFill(&rrp[h],sx1,y1,sx2,y2);
	if(sy2>=sy1)	RectFill(&rrp[h],x1,sy1,x2,sy2);
	if(sx2>=sx1 && sy2>=sy1) RectFill(&rrp[h],sx1,sy1,sx2,sy2);
}

/******************************************************************************/

void MT0D1Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	bc=h>>1;rc=h&1;
	c=col[(bc+D1[rc][x&1][y&1])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
}

void MT0D1Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	sy=ay+(ay-y);
	bc=h>>1;rc=h&1;
	c=col[(bc+D1[rc][x&1][y&1])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		c=col[(bc+D1[rc][x&1][sy&1])&GfxInfo.absmaxcol];
		addr=BPR*sy+(x>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D1Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	sx=ax+(ax-x);
	bc=h>>1;rc=h&1;
	c=col[(bc+D1[rc][x&1][y&1])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
	{
		c=col[(bc+D1[rc][sx&1][y&1])&GfxInfo.absmaxcol];
		addr=BPR*y+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D1Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	sx=ax+(ax-x);sy=ay+(ay-y);
	bc=h>>1;rc=h&1;
	c=col[(bc+D1[rc][x&1][y&1])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		c=col[(bc+D1[rc][sx&1][sy&1])&GfxInfo.absmaxcol];
		addr=BPR*sy+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		c=col[(bc+D1[rc][sx&1][y&1])&GfxInfo.absmaxcol];
		addr=BPR*y+(sx>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		c=col[(bc+D1[rc][x&1][sy&1])&GfxInfo.absmaxcol];
		addr=BPR*sy+(x>>3);
		p=128>>(rest=x&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
		{
			c=col[(bc+D1[rc][sx&1][y&1])&GfxInfo.absmaxcol];
			addr=BPR*y+(sx>>3);
			p=128>>(rest=sx&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			c=col[(bc+D1[rc][x&1][sy&1])&GfxInfo.absmaxcol];
			addr=BPR*sy+(x>>3);
			p=128>>(rest=x&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
	}
}

void MT0D1Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,sy2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sy2=j&1;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
	}
	else RectFill(&rrp[col[bc&GfxInfo.absmaxcol]],x1,y1,x2,y2);
}

void MT0D1Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,tx3,sy,sy2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sy2=j&1;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
		tx3=ay+(ay-y1);
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;sy=tx3;
			for(j=y1;j<=y2;j++,sy--)
				if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
				{
					addr=planes[k]+BPR*sy+tx1;rest=tx2;
					sy2=sy&1;
					for(i=x1;i<=x2;i++)
					{
						if(col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
						rest++;if(rest==8){rest=0;addr++;}
					}
				}
		}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ay+(ay-y1);j=ay+(ay-y2);
		sy=min(i,j);sy2=max(i,j);
		if(sy2>RenderInfo.yb2) sy2=RenderInfo.yb2;
		if(sy<RenderInfo.yb1) sy=RenderInfo.yb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sy2>=sy)	RectFill(&rrp[h],x1,sy,x2,sy2);
	}
}

void MT0D1Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,tx3,sx,sx2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sx2=j&1;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D1[rc][i&1][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
		tx3=ax+(ax-x1);
		tx1=tx3>>3;tx2=tx3&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				sx=tx3;
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sx2=j&1;
				for(i=x1;i<=x2;i++,sx--)
				{
					if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
						if(col[(bc+D1[rc][i&1][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest--;if(rest==-1){rest=7;addr--;}
				}
			}
		}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ax+(ax-x1);j=ax+(ax-x2);
		sx=min(i,j);sx2=max(i,j);
		if(sx2>RenderInfo.xb2) sx2=RenderInfo.xb2;
		if(sx<RenderInfo.xb1) sx=RenderInfo.xb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sx2>=sx)	RectFill(&rrp[h],sx,y1,sx2,y2);
	}
}

void MT0D1Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,tx3,tx4,sy1,sy2,sx1,sx2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>1;rc=h&1;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sy2=j&1;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
		tx3=ay+(ay-y1);
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;sy1=tx3;
			for(j=y1;j<=y2;j++,sy1--)
				if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
				{
					addr=planes[k]+BPR*sy1+tx1;rest=tx2;
					sy2=sy1&1;
					for(i=x1;i<=x2;i++)
					{
						if(col[(bc+D1[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
						rest++;if(rest==8){rest=0;addr++;}
					}
				}
		}
		tx3=ax+(ax-x1);
		tx1=tx3>>3;tx2=tx3&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				sx1=tx3;
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sx2=j&1;
				for(i=x1;i<=x2;i++,sx1--)
				{
					if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
						if(col[(bc+D1[rc][i&1][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest--;if(rest==-1){rest=7;addr--;}
				}
			}
		}
		tx4=ay+(ay-y1);
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;sy1=tx4;
			for(j=y1;j<=y2;j++,sy1--)
			{
				if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
				{
					sx1=tx3;
					addr=planes[k]+BPR*sy1+tx1;rest=tx2;
					sx2=sy1&1;
					for(i=x1;i<=x2;i++,sx1--)
					{
						if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
							if(col[(bc+D1[rc][i&1][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
						rest--;if(rest==-1){rest=7;addr--;}
					}
				}
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

void MT0D2Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	bc=h>>2;rc=h&3;
	c=col[(bc+D2[rc][x&1][y&1])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
}

void MT0D2Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	sy=ay+(ay-y);
	bc=h>>2;rc=h&3;
	c=col[(bc+D2[rc][x&1][y&1])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		c=col[(bc+D2[rc][x&1][sy&1])&GfxInfo.absmaxcol];
		addr=BPR*sy+(x>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D2Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	sx=ax+(ax-x);
	bc=h>>2;rc=h&3;
	c=col[(bc+D2[rc][x&1][y&1])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
	{
		c=col[(bc+D2[rc][sx&1][y&1])&GfxInfo.absmaxcol];
		addr=BPR*y+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D2Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	sx=ax+(ax-x);sy=ay+(ay-y);
	bc=h>>2;rc=h&3;
	c=col[(bc+D2[rc][x&1][y&1])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		c=col[(bc+D2[rc][sx&1][sy&1])&GfxInfo.absmaxcol];
		addr=BPR*sy+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		c=col[(bc+D2[rc][sx&1][y&1])&GfxInfo.absmaxcol];
		addr=BPR*y+(sx>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		c=col[(bc+D2[rc][x&1][sy&1])&GfxInfo.absmaxcol];
		addr=BPR*sy+(x>>3);
		p=128>>(rest=x&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
		{
			c=col[(bc+D2[rc][sx&1][y&1])&GfxInfo.absmaxcol];
			addr=BPR*y+(sx>>3);
			p=128>>(rest=sx&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			c=col[(bc+D2[rc][x&1][sy&1])&GfxInfo.absmaxcol];
			addr=BPR*sy+(x>>3);
			p=128>>(rest=x&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
	}
}

void MT0D2Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,sy2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>2;rc=h&3;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sy2=j&1;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
	}
	else RectFill(&rrp[col[bc&GfxInfo.absmaxcol]],x1,y1,x2,y2);
}

void MT0D2Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,tx3,sy,sy2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>2;rc=h&3;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sy2=j&1;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
		tx3=ay+(ay-y1);
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;sy=tx3;
			for(j=y1;j<=y2;j++,sy--)
				if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
				{
					addr=planes[k]+BPR*sy+tx1;rest=tx2;
					sy2=sy&1;
					for(i=x1;i<=x2;i++)
					{
						if(col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
						rest++;if(rest==8){rest=0;addr++;}
					}
				}
		}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ay+(ay-y1);j=ay+(ay-y2);
		sy=min(i,j);sy2=max(i,j);
		if(sy2>RenderInfo.yb2) sy2=RenderInfo.yb2;
		if(sy<RenderInfo.yb1) sy=RenderInfo.yb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sy2>=sy)	RectFill(&rrp[h],x1,sy,x2,sy2);
	}
}

void MT0D2Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,tx3,sx,sx2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>2;rc=h&3;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sx2=j&1;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D2[rc][i&1][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
		tx3=ax+(ax-x1);
		tx1=tx3>>3;tx2=tx3&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				sx=tx3;
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sx2=j&1;
				for(i=x1;i<=x2;i++,sx--)
				{
					if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
						if(col[(bc+D2[rc][i&1][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest--;if(rest==-1){rest=7;addr--;}
				}
			}
		}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ax+(ax-x1);j=ax+(ax-x2);
		sx=min(i,j);sx2=max(i,j);
		if(sx2>RenderInfo.xb2) sx2=RenderInfo.xb2;
		if(sx<RenderInfo.xb1) sx=RenderInfo.xb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sx2>=sx)	RectFill(&rrp[h],sx,y1,sx2,y2);
	}
}

void MT0D2Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,tx3,tx4,sy1,sy2,sx1,sx2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>2;rc=h&3;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sy2=j&1;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
		tx3=ay+(ay-y1);
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;sy1=tx3;
			for(j=y1;j<=y2;j++,sy1--)
				if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
				{
					addr=planes[k]+BPR*sy1+tx1;rest=tx2;
					sy2=sy1&1;
					for(i=x1;i<=x2;i++)
					{
						if(col[(bc+D2[rc][i&1][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
						rest++;if(rest==8){rest=0;addr++;}
					}
				}
		}
		tx3=ax+(ax-x1);
		tx1=tx3>>3;tx2=tx3&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				sx1=tx3;
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sx2=j&1;
				for(i=x1;i<=x2;i++,sx1--)
				{
					if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
						if(col[(bc+D2[rc][i&1][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest--;if(rest==-1){rest=7;addr--;}
				}
			}
		}
		tx4=ay+(ay-y1);
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;sy1=tx4;
			for(j=y1;j<=y2;j++,sy1--)
			{
				if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
				{
					sx1=tx3;
					addr=planes[k]+BPR*sy1+tx1;rest=tx2;
					sx2=sy1&1;
					for(i=x1;i<=x2;i++,sx1--)
					{
						if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
							if(col[(bc+D2[rc][i&1][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
						rest--;if(rest==-1){rest=7;addr--;}
					}
				}
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

void MT0D3Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	bc=h>>4;rc=h&15;
	c=col[(bc+D3[rc][x&3][y&3])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
}

void MT0D3Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	sy=ay+(ay-y);
	bc=h>>4;rc=h&15;
	c=col[(bc+D3[rc][x&3][y&3])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		c=col[(bc+D3[rc][x&3][sy&3])&GfxInfo.absmaxcol];
		addr=BPR*sy+(x>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D3Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	sx=ax+(ax-x);
	bc=h>>4;rc=h&15;
	c=col[(bc+D3[rc][x&3][y&3])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
	{
		c=col[(bc+D3[rc][sx&3][y&3])&GfxInfo.absmaxcol];
		addr=BPR*y+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D3Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register ULONG addr;
	register UBYTE i,rest,c,bc,rc,p;

	sx=ax+(ax-x);sy=ay+(ay-y);
	bc=h>>4;rc=h&15;
	c=col[(bc+D3[rc][x&3][y&3])&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		c=col[(bc+D3[rc][sx&3][sy&3])&GfxInfo.absmaxcol];
		addr=BPR*sy+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		c=col[(bc+D3[rc][sx&3][y&3])&GfxInfo.absmaxcol];
		addr=BPR*y+(sx>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		c=col[(bc+D3[rc][x&3][sy&3])&GfxInfo.absmaxcol];
		addr=BPR*sy+(x>>3);
		p=128>>(rest=x&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
		{
			c=col[(bc+D3[rc][sx&3][y&3])&GfxInfo.absmaxcol];
			addr=BPR*y+(sx>>3);
			p=128>>(rest=sx&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			c=col[(bc+D3[rc][x&3][sy&3])&GfxInfo.absmaxcol];
			addr=BPR*sy+(x>>3);
			p=128>>(rest=x&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
	}
}

void MT0D3Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,sy2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>4;rc=h&15;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sy2=j&3;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D3[rc][i&3][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
	}
	else RectFill(&rrp[col[bc&GfxInfo.absmaxcol]],x1,y1,x2,y2);
}

void MT0D3Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,tx3,sy,sy2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>4;rc=h&15;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sy2=j&3;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D3[rc][i&3][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
		tx3=ay+(ay-y1);
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;sy=tx3;
			for(j=y1;j<=y2;j++,sy--)
				if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
				{
					addr=planes[k]+BPR*sy+tx1;rest=tx2;
					sy2=sy&3;
					for(i=x1;i<=x2;i++)
					{
						if(col[(bc+D3[rc][i&3][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
						rest++;if(rest==8){rest=0;addr++;}
					}
				}
		}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ay+(ay-y1);j=ay+(ay-y2);
		sy=min(i,j);sy2=max(i,j);
		if(sy2>RenderInfo.yb2) sy2=RenderInfo.yb2;
		if(sy<RenderInfo.yb1) sy=RenderInfo.yb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sy2>=sy)	RectFill(&rrp[h],x1,sy,x2,sy2);
	}
}

void MT0D3Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,tx3,sx,sx2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>4;rc=h&15;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sx2=j&3;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D3[rc][i&3][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
		tx3=ax+(ax-x1);
		tx1=tx3>>3;tx2=tx3&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				sx=tx3;
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sx2=j&3;
				for(i=x1;i<=x2;i++,sx--)
				{
					if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
						if(col[(bc+D3[rc][i&3][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest--;if(rest==-1){rest=7;addr--;}
				}
			}
		}
	}
	else
	{
		h=col[bc&GfxInfo.absmaxcol];
		i=ax+(ax-x1);j=ax+(ax-x2);
		sx=min(i,j);sx2=max(i,j);
		if(sx2>RenderInfo.xb2) sx2=RenderInfo.xb2;
		if(sx<RenderInfo.xb1) sx=RenderInfo.xb1;
		RectFill(&rrp[h],x1,y1,x2,y2);
		if(sx2>=sx)	RectFill(&rrp[h],sx,y1,sx2,y2);
	}
}

void MT0D3Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,l,tx1,tx3,tx4,sy1,sy2,sx1,sx2;
	register PLANEPTR addr;
	register UBYTE rest,tx2,bc,rc;

	bc=h>>4;rc=h&15;
	if(rc)
	{
		tx1=x1>>3;tx2=x1&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sy2=j&3;
				for(i=x1;i<=x2;i++)
				{
					if(col[(bc+D3[rc][i&3][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest++;if(rest==8){rest=0;addr++;}
				}
			}
		}
		tx3=ay+(ay-y1);
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;sy1=tx3;
			for(j=y1;j<=y2;j++,sy1--)
				if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
				{
					addr=planes[k]+BPR*sy1+tx1;rest=tx2;
					sy2=sy1&3;
					for(i=x1;i<=x2;i++)
					{
						if(col[(bc+D3[rc][i&3][sy2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
						rest++;if(rest==8){rest=0;addr++;}
					}
				}
		}
		tx3=ax+(ax-x1);
		tx1=tx3>>3;tx2=tx3&7;
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;
			for(j=y1;j<=y2;j++)
			{
				sx1=tx3;
				addr=planes[k]+BPR*j+tx1;rest=tx2;
				sx2=j&3;
				for(i=x1;i<=x2;i++,sx1--)
				{
					if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
						if(col[(bc+D3[rc][i&3][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
					rest--;if(rest==-1){rest=7;addr--;}
				}
			}
		}
		tx4=ay+(ay-y1);
		for(k=0;k<GfxInfo.depth;k++)
		{
			l=1<<k;sy1=tx4;
			for(j=y1;j<=y2;j++,sy1--)
			{
				if(sy1>=RenderInfo.yb1 && sy1<=RenderInfo.yb2)
				{
					sx1=tx3;
					addr=planes[k]+BPR*sy1+tx1;rest=tx2;
					sx2=sy1&3;
					for(i=x1;i<=x2;i++,sx1--)
					{
						if(sx1>=RenderInfo.xb1 && sx1<=RenderInfo.xb2)
							if(col[(bc+D3[rc][i&3][sx2])&GfxInfo.absmaxcol]&l) *addr|=(128>>rest);
						rest--;if(rest==-1){rest=7;addr--;}
					}
				}
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

void MT0D4Point(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register ULONG addr;
	register UBYTE i,rest,c,p;
	register double in;

	in=(double)h/GfxInfo.ordscl+derr;
	c=(int)in;derr=in-c;
	c=col[c&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;
}

void MT0D4Pointx(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sy;
	register ULONG addr;
	register UBYTE i,rest,c,p;
	register double in;

	sy=ay+(ay-y);
	in=(double)h/GfxInfo.ordscl+derr;
	c=(int)in;derr=in-(double)c;
	c=col[c&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;

	if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		c=col[c&GfxInfo.absmaxcol];
		addr=BPR*sy+(x>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D4Pointy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx;
	register ULONG addr;
	register UBYTE i,rest,c,p;
	register double in;

	sx=ax+(ax-x);
	in=(double)h/GfxInfo.ordscl+derr;
	c=(int)in;derr=in-(double)c;
	c=col[c&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;

	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
	{
		addr=BPR*y+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
}

void MT0D4Pointxy(UWORD x,UWORD y,UWORD h,UWORD ax,UWORD ay)
{
	register WORD sx,sy;
	register ULONG addr;
	register UBYTE i,rest,c,p;
	register double in;

	sx=ax+(ax-x);sy=ay+(ay-y);
	in=(double)h/GfxInfo.ordscl+derr;
	c=(int)in;derr=in-(double)c;
	c=col[c&GfxInfo.absmaxcol];
	addr=BPR*y+(x>>3);
	p=128>>(rest=x&7);
	for(i=0;i<GfxInfo.depth;i++)
		if(c&(1<<i)) *(planes[i]+addr)|=p;

	if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2 && sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
	{
		addr=BPR*sy+(sx>>3);
		p=128>>(rest=sx&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		addr=BPR*y+(sx>>3);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;

		addr=BPR*sy+(x>>3);
		p=128>>(rest=x&7);
		for(i=0;i<GfxInfo.depth;i++)
			if(c&(1<<i)) *(planes[i]+addr)|=p;
	}
	else
	{
		if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
		{
			addr=BPR*y+(sx>>3);
			p=128>>(rest=sx&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			addr=BPR*sy+(x>>3);
			p=128>>(rest=x&7);
			for(i=0;i<GfxInfo.depth;i++)
				if(c&(1<<i)) *(planes[i]+addr)|=p;
		}
	}
}

void MT0D4Recta(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,tx1;
	register ULONG addr;
	register UBYTE rest,tx2,c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
	tx1=x1>>3;tx2=x1&7;
	for(j=y1;j<=y2;j++)
	{
		addr=BPR*j+tx1;rest=tx2;
		for(i=x1;i<=x2;i++)
		{
			in=hs+derr;
			c=(int)in;derr=in-c;
			c=col[c&GfxInfo.absmaxcol];
			for(k=0;k<GfxInfo.depth;k++)
				if(c&(1<<k)) *(planes[k]+addr)|=(128>>rest);
			rest++;if(rest==8){rest=0;addr++;}
		}
	}
}

void MT0D4Rectax(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,tx1,sy;
	register ULONG addr;
	register UBYTE rest,tx2,c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
	tx1=x1>>3;tx2=x1&7;
	for(j=y1;j<=y2;j++)
	{
		addr=BPR*j+tx1;rest=tx2;
		for(i=x1;i<=x2;i++)
		{
			in=hs+derr;
			c=(int)in;derr=in-c;
			c=col[c&GfxInfo.absmaxcol];
			for(k=0;k<GfxInfo.depth;k++)
				if(c&(1<<k)) *(planes[k]+addr)|=(128>>rest);
			rest++;if(rest==8){rest=0;addr++;}
		}
	}
	sy=ay+(ay-y1);
	for(j=y1;j<=y2;j++,sy--)
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			addr=BPR*sy+tx1;rest=tx2;
			for(i=x1;i<=x2;i++)
			{
				in=hs+derr;
				c=(int)in;derr=in-c;
				c=col[c&GfxInfo.absmaxcol];
				for(k=0;k<GfxInfo.depth;k++)
					if(c&(1<<k)) *(planes[k]+addr)|=(128>>rest);
				rest++;if(rest==8){rest=0;addr++;}
			}
		}
}

void MT0D4Rectay(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,tx1,tx3,sx;
	register ULONG addr;
	register UBYTE rest,tx2,c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
	tx1=x1>>3;tx2=x1&7;
	for(j=y1;j<=y2;j++)
	{
		addr=BPR*j+tx1;rest=tx2;
		for(i=x1;i<=x2;i++)
		{
			in=hs+derr;
			c=(int)in;derr=in-c;
			c=col[c&GfxInfo.absmaxcol];
			for(k=0;k<GfxInfo.depth;k++)
				if(c&(1<<k)) *(planes[k]+addr)|=(128>>rest);
			rest++;if(rest==8){rest=0;addr++;}
		}
	}
	tx3=ax+(ax-x1);
	tx1=tx3>>3;tx2=tx3&7;
	for(j=y1;j<=y2;j++)
	{
		sx=tx3;
		addr=BPR*j+tx1;rest=tx2;
		for(i=x1;i<=x2;i++,sx--)
		{
			if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
			{
				in=hs+derr;
				c=(int)in;derr=in-c;
				c=col[c&GfxInfo.absmaxcol];
				for(k=0;k<GfxInfo.depth;k++)
					if(c&(1<<k)) *(planes[k]+addr)|=(128>>rest);
			}
			rest--;if(rest==-1){rest=7;addr--;}
		}
	}
}

void MT0D4Rectaxy(UWORD x1,UWORD y1,UWORD x2,UWORD y2,UWORD h,UWORD ax,UWORD ay)
{
	register WORD i,j,k,tx1,tx3,sy,sx;
	register ULONG addr;
	register UBYTE rest,tx2,c;
	register double in,hs;

	hs=(double)h/GfxInfo.ordscl;
	tx1=x1>>3;tx2=x1&7;
	for(j=y1;j<=y2;j++)
	{
		addr=BPR*j+tx1;rest=tx2;
		for(i=x1;i<=x2;i++)
		{
			in=hs+derr;
			c=(int)in;derr=in-c;
			c=col[c&GfxInfo.absmaxcol];
			for(k=0;k<GfxInfo.depth;k++)
				if(c&(1<<k)) *(planes[k]+addr)|=(128>>rest);
			rest++;if(rest==8){rest=0;addr++;}
		}
	}
	sy=ay+(ay-y1);
	for(j=y1;j<=y2;j++,sy--)
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			addr=BPR*sy+tx1;rest=tx2;
			for(i=x1;i<=x2;i++)
			{
				in=hs+derr;
				c=(int)in;derr=in-c;
				c=col[c&GfxInfo.absmaxcol];
				for(k=0;k<GfxInfo.depth;k++)
					if(c&(1<<k)) *(planes[k]+addr)|=(128>>rest);
				rest++;if(rest==8){rest=0;addr++;}
			}
		}
	tx3=ax+(ax-x1);
	tx1=tx3>>3;tx2=tx3&7;
	for(j=y1;j<=y2;j++)
	{
		sx=tx3;
		addr=BPR*j+tx1;rest=tx2;
		for(i=x1;i<=x2;i++,sx--)
		{
			if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
			{
				in=hs+derr;
				c=(int)in;derr=in-c;
				c=col[c&GfxInfo.absmaxcol];
				for(k=0;k<GfxInfo.depth;k++)
					if(c&(1<<k)) *(planes[k]+addr)|=(128>>rest);
			}
			rest--;if(rest==-1){rest=7;addr--;}
		}
	}
	sy=ay+(ay-y1);
	for(j=y1;j<=y2;j++,sy--)
	{
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			sx=tx3;
			addr=BPR*sy+tx1;rest=tx2;
			for(i=x1;i<=x2;i++,sx--)
			{
				if(sx>=RenderInfo.xb1 && sx<=RenderInfo.xb2)
				{
					in=hs+derr;
					c=(int)in;derr=in-c;
					c=col[c&GfxInfo.absmaxcol];
					for(k=0;k<GfxInfo.depth;k++)
						if(c&(1<<k)) *(planes[k]+addr)|=(128>>rest);
				}
				rest--;if(rest==-1){rest=7;addr--;}
			}
		}
	}
}
