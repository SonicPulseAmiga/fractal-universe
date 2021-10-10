/******************************************************************************
** FU-GFXF-MT0D4.h                                                           **
**---------------------------------------------------------------------------**
** Graphical Functions for ModeTypes=0 & Dither=4                            **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 04.02.1994                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

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
	sy=ay+(ay-y1);
	for(j=y1;j<=y2;j++,sy--)
	{
		if(sy>=RenderInfo.yb1 && sy<=RenderInfo.yb2)
		{
			sx=tx3;
			addr=BPR*sy+tx1;rest=tx2;
			for(i=x1;i<=x2;i++,sx--)
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
