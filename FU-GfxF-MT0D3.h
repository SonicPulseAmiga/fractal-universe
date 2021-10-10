/******************************************************************************
** FU-GFXF-MT0D3.h                                                           **
**---------------------------------------------------------------------------**
** Graphical Functions for ModeTypes=0 & Dither=3                            **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 04.02.1994                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

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
