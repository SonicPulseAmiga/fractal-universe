/****h* FractalUniverse/FU-Rend.c [1.68] *
*
*  NAME
*    FU-Rend.c
*  COPYRIGHT
*    $VER: FU-Rend.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    Render Functions
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

#define FU_REND_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

UBYTE RenderSolid(void);
UBYTE RenderSquare(void);
UBYTE RenderFastSquare(void);
UBYTE RenderPreview(void);
void RenderTurbo(void);

//-- definitions --------------------------------------------------------------

UBYTE RenderSolid(void)
{
	register UWORD i,j,n;
	UWORD wx,wy,j2,i2;
	UBYTE rv=0;
	UWORD ax,ay;
	UWORD x1,y1,x2,y2;
	double xo;
	struct IntuiMessage *imsg;
	ULONG iclass;
	USHORT icode;
//	APTR iadr;

	derr=0.0;
	if(RenderInfo.outside==6) decompho=RenderInfo.outpar1/6.283185307;
	if(RenderInfo.inside==2) decomphi=RenderInfo.inpar1/6.283185307;
	wx=RenderInfo.xb2-RenderInfo.xb1;
	wy=RenderInfo.yb2-RenderInfo.yb1;
	xd=(RenderInfo.x2-RenderInfo.x1)/wx;
	yd=(RenderInfo.y2-RenderInfo.y1)/wy;

	if(RenderInfo.x1<0 && RenderInfo.x2>0 && RenderInfo.mirrory)
	{
		ax=RenderInfo.xb1+fabs((fabs(RenderInfo.x1)*wx/fabs(RenderInfo.x2-RenderInfo.x1)));
		n=ax-RenderInfo.xb1;
		RenderInfo.x1=-(n*xd);
		n=RenderInfo.xb2-ax;
		RenderInfo.x2=n*xd;
		if(fabs(RenderInfo.x1)>=fabs(RenderInfo.x2))
		{
			x1=RenderInfo.xb1;
			x2=ax;
		}
		else
		{
			x1=ax;
			x2=RenderInfo.xb2;
		}
	}
	else
	{
		x1=RenderInfo.xb1;
		x2=RenderInfo.xb2;
	}
	if(RenderInfo.y1<0 && RenderInfo.y2>0 && RenderInfo.mirrorx)
	{
		ay=RenderInfo.yb1+fabs((fabs(RenderInfo.y1)*wy/fabs(RenderInfo.y2-RenderInfo.y1)));
		n=ay-RenderInfo.yb1;
		RenderInfo.y1=-(n*yd);
		n=RenderInfo.yb2-ay;
		RenderInfo.y2=n*yd;
		if(fabs(RenderInfo.y1)>=fabs(RenderInfo.y2))
		{
			y1=RenderInfo.yb1;
			y2=ay;
		}
		else
		{
			y1=ay;
			y2=RenderInfo.yb2;
		}
	}
	else
	{
		y1=RenderInfo.yb1;
		y2=RenderInfo.yb2;
	}
	xo=RenderInfo.x1+(x1-RenderInfo.xb1)*xd;
	y=RenderInfo.y1+(y1-RenderInfo.yb1)*yd;
	j2=y1+(y2-y1);i2=x1+(x2-x1);
	for(j=y1;j<=j2;j++)
	{
		x=xo;
		for(i=x1;i<=i2;i++)
		{
			PixelModifier();PsetFunc(i,j,FracFunc(),ax,ay);
			x+=xd;
		}
		y+=yd;
		while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort))
		{
			iclass=imsg->Class;
			icode=imsg->Code;
			ReplyMsg(imsg);
			switch(iclass)
			{
				case IDCMP_RAWKEY:
					switch(icode)
					{
						case 0x45:					/* Berechnung abbrechen */
							rv=1;
							j=j2;
							break;
						case 0x25:				/* Hide Mousepointer */
							if(epointer) { ClearPointer(rwindow);epointer=0; }
							else { SetPointer(rwindow,Emptypointer,16,16,-6,0);epointer=1; }
							break;
						case 0x01:				/* 1 */
							RunTime.aktpal=0;cdata.pos=0;SetColorPalette();
							break;
						case 0x02:				/* 2 */
							RunTime.aktpal=1;cdata.pos=0;SetColorPalette();
							break;
						case 0x03:				/* 3 */
							RunTime.aktpal=2;cdata.pos=0;SetColorPalette();
							break;
						case 0x04:				/* 4 */
							RunTime.aktpal=3;cdata.pos=0;SetColorPalette();
							break;
						case 0x05:				/* 5 */
							RunTime.aktpal=4;cdata.pos=0;SetColorPalette();
							break;
						case 0x06:				/* 6 */
							RunTime.aktpal=5;cdata.pos=0;SetColorPalette();
							break;
						case 0x07:				/* 7 */
							RunTime.aktpal=6;cdata.pos=0;SetColorPalette();
							break;
						case 0x08:				/* 8 */
							RunTime.aktpal=7;cdata.pos=0;SetColorPalette();
							break;
						case 0x09:				/* 9 */
							RunTime.aktpal=8;cdata.pos=0;SetColorPalette();
							break;
						case 0x0A:				/* 0 */
							RunTime.aktpal=9;cdata.pos=0;SetColorPalette();
							break;
					}
					break;
			}
		}
	}
	if(epointer)
	{
		ClearPointer(rwindow);epointer=0;
	}
	return(rv);
}

UBYTE RenderSquare(void)
{
	register WORD st;
	register UWORD h,h1;
	UWORD wx,wy,h2,h3,h4;
	double rx1,ry1,rx2,ry2;
	UWORD ax,ay,x1,y1,x2,y2;
	register UWORD mx1,my1,mx2,my2;
	UWORD mx,my;
	UBYTE rv=0;
	BYTE as;
	struct IntuiMessage *imsg;
	ULONG iclass;
	USHORT icode;
//	APTR iadr;

	derr=0.0;
	if(RenderInfo.outside==6) decompho=RenderInfo.outpar1/6.283185307;
	if(RenderInfo.inside==2) decomphi=RenderInfo.inpar1/6.283185307;
	wx=RenderInfo.xb2-RenderInfo.xb1;
	wy=RenderInfo.yb2-RenderInfo.yb1;
	xd=(RenderInfo.x2-RenderInfo.x1)/wx;
	yd=(RenderInfo.y2-RenderInfo.y1)/wy;

	if(RenderInfo.x1<0 && RenderInfo.x2>0 && RenderInfo.mirrory)
	{
		ax=RenderInfo.xb1+fabs((fabs(RenderInfo.x1)*wx/fabs(RenderInfo.x2-RenderInfo.x1)));
		h=ax-RenderInfo.xb1;
		RenderInfo.x1=-(h*xd);
		h=RenderInfo.xb2-ax;
		RenderInfo.x2=h*xd;
		if(fabs(RenderInfo.x1)>=fabs(RenderInfo.x2))
		{
			x1=RenderInfo.xb1;
			x2=ax;
		}
		else
		{
			x1=ax;
			x2=RenderInfo.xb2;
		}
	}
	else
	{
		x1=RenderInfo.xb1;
		x2=RenderInfo.xb2;
	}
	if(RenderInfo.y1<0 && RenderInfo.y2>0 && RenderInfo.mirrorx)
	{
		ay=RenderInfo.yb1+fabs((fabs(RenderInfo.y1)*wy/fabs(RenderInfo.y2-RenderInfo.y1)));
		h=ay-RenderInfo.yb1;
		RenderInfo.y1=-(h*yd);
		h=RenderInfo.yb2-ay;
		RenderInfo.y2=h*yd;
		if(fabs(RenderInfo.y1)>=fabs(RenderInfo.y2))
		{
			y1=RenderInfo.yb1;
			y2=ay;
		}
		else
		{
			y1=ay;
			y2=RenderInfo.yb2;
		}
	}
	else
	{
		y1=RenderInfo.yb1;
		y2=RenderInfo.yb2;
	}

	mx=x1+(x2-x1)/2;my=y1+(y2-y1)/2;
	sb[0].x1=x1;sb[0].y1=y1;sb[0].x2=mx;sb[0].y2=my;
	sb[1].x1=mx;sb[1].y1=y1;sb[1].x2=x2;sb[1].y2=my;
	sb[2].x1=mx;sb[2].y1=my;sb[2].x2=x2;sb[2].y2=y2;
	sb[3].x1=x1;sb[3].y1=my;sb[3].x2=mx;sb[3].y2=y2;
	st=3;

	while(st>-1)
	{
		as=0;
		x=rx1=RenderInfo.x1+((mx1=sb[st].x1)-RenderInfo.xb1)*xd;y=ry1=RenderInfo.y1+((my1=sb[st].y1)-RenderInfo.yb1)*yd;
		rx2=RenderInfo.x1+((mx2=sb[st].x2)-RenderInfo.xb1)*xd;ry2=RenderInfo.y1+((my2=sb[st].y2)-RenderInfo.yb1)*yd;
		PixelModifier();h1=FracFunc();
		x=rx2;PixelModifier();h2=FracFunc();
		y=ry2;PixelModifier();h3=FracFunc();
		x=rx1;PixelModifier();h4=FracFunc();
		if(h1==h2 && h2==h3 && h3==h4)
		{
			h=h1;
			while(h==h1 && x<rx2) { PixelModifier();h=FracFunc();x+=xd; }
			x=rx2;
			while(h==h1 && y>ry1) { PixelModifier();h=FracFunc();y-=yd; }
			y=ry1;
			while(h==h1 && x>rx1) { PixelModifier();h=FracFunc();x-=xd; }
			x=rx1;
			while(h==h1 && y<ry2) { PixelModifier();h=FracFunc();y+=yd; }
			if(h==h1) as=-1;
		}
		if(as)								/* scheint alles die gl. Farbe zu sein */
		{
			RectFunc(mx1,my1,mx2,my2,h,ax,ay);st--;
		}
		else
		{
			if(mx2-mx1<2 && my2-my1<2)			/* kleiner gehts nicht */
			{
				PsetFunc(mx1,my1,h1,ax,ay);
				PsetFunc(mx2,my1,h2,ax,ay);
				PsetFunc(mx2,my2,h3,ax,ay);
				PsetFunc(mx1,my2,h4,ax,ay);
				st--;
			}
			else
			{
				if(my2-my1<2)				/* nur x-teilen */
				{
					mx=mx1+((mx2-mx1)>>1);
					sb[st+1].x1=mx+1;
					sb[st+1].y1=sb[st].y1;
					sb[st+1].x2=sb[st].x2;
					sb[st+1].y2=sb[st].y2;
					sb[st++].x2=mx;
				}
				else
				{
					if(mx2-mx1<2)					/* nur y-teilen */
					{
						my=my1+((my2-my1)>>1);
						sb[st+1].y1=my+1;
						sb[st+1].x1=sb[st].x1;
						sb[st+1].x2=sb[st].x2;
						sb[st+1].y2=sb[st].y2;
						sb[st++].y2=my;
					}
					else						/* würfeln */
					{
						my=my1+((my2-my1)>>1);	/* oben links nach oben rechts */
						mx=mx1+((mx2-mx1)>>1);
						sb[st].y2=my;
						sb[st+1].y2=my;
						sb[st+1].x1=mx+1;
						sb[st+1].y1=sb[st].y1;
						sb[st+1].x2=sb[st].x2;
						sb[st].x2=mx;

						st+=2;					/* oben links nach unten links */
						sb[st].x1=sb[st-2].x1;
						sb[st].y1=my+1;
						sb[st].x2=sb[st-2].x2;
						sb[st++].y2=my2;

						sb[st].x1=sb[st-2].x1;	/* oben rechts nach unten rechts */
						sb[st].y1=my+1;
						sb[st].x2=sb[st-2].x2;
						sb[st].y2=my2;
					}
				}
			}
		}
		while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort))
		{
			iclass=imsg->Class;
			icode=imsg->Code;
			ReplyMsg(imsg);
			switch(iclass)
			{
				case IDCMP_RAWKEY:
					switch(icode)
					{
						case 0x45:					/* Berechnung abbrechen */
							rv=1;st=-1;
							break;
						case 0x25:				/* Hide Mousepointer */
							if(epointer) { ClearPointer(rwindow);epointer=0; }
							else { SetPointer(rwindow,Emptypointer,16,16,-6,0);epointer=1; }
							break;
						case 0x01:				/* 1 */
							RunTime.aktpal=0;cdata.pos=0;SetColorPalette();
							break;
						case 0x02:				/* 2 */
							RunTime.aktpal=1;cdata.pos=0;SetColorPalette();
							break;
						case 0x03:				/* 3 */
							RunTime.aktpal=2;cdata.pos=0;SetColorPalette();
							break;
						case 0x04:				/* 4 */
							RunTime.aktpal=3;cdata.pos=0;SetColorPalette();
							break;
						case 0x05:				/* 5 */
							RunTime.aktpal=4;cdata.pos=0;SetColorPalette();
							break;
						case 0x06:				/* 6 */
							RunTime.aktpal=5;cdata.pos=0;SetColorPalette();
							break;
						case 0x07:				/* 7 */
							RunTime.aktpal=6;cdata.pos=0;SetColorPalette();
							break;
						case 0x08:				/* 8 */
							RunTime.aktpal=7;cdata.pos=0;SetColorPalette();
							break;
						case 0x09:				/* 9 */
							RunTime.aktpal=8;cdata.pos=0;SetColorPalette();
							break;
						case 0x0A:				/* 0 */
							RunTime.aktpal=9;cdata.pos=0;SetColorPalette();
							break;
					}
					break;
			}
		}
	}
	if(epointer)
	{
		ClearPointer(rwindow);epointer=0;
	}
	return(rv);
}

UBYTE RenderFastSquare(void)
{
	register WORD st;
	register UWORD h,h1;
	UWORD wx,wy,h2,h3,h4;
	double rx1,ry1,rx2,ry2;
	UWORD ax,ay,x1,y1,x2,y2;
	register UWORD mx1,my1,mx2,my2;
	UWORD mx,my;
	UBYTE rv=0;
	BYTE as;
	struct IntuiMessage *imsg;
	ULONG iclass;
	USHORT icode;
//	APTR iadr;

	derr=0.0;
	if(RenderInfo.outside==6) decompho=RenderInfo.outpar1/6.283185307;
	if(RenderInfo.inside==2) decomphi=RenderInfo.inpar1/6.283185307;
	wx=RenderInfo.xb2-RenderInfo.xb1;
	wy=RenderInfo.yb2-RenderInfo.yb1;
	xd=(RenderInfo.x2-RenderInfo.x1)/wx;
	yd=(RenderInfo.y2-RenderInfo.y1)/wy;

	if(RenderInfo.x1<0 && RenderInfo.x2>0 && RenderInfo.mirrory)
	{
		ax=RenderInfo.xb1+fabs((fabs(RenderInfo.x1)*wx/fabs(RenderInfo.x2-RenderInfo.x1)));
		h=ax-RenderInfo.xb1;
		RenderInfo.x1=-(h*xd);
		h=RenderInfo.xb2-ax;
		RenderInfo.x2=h*xd;
		if(fabs(RenderInfo.x1)>=fabs(RenderInfo.x2))
		{
			x1=RenderInfo.xb1;
			x2=ax;
		}
		else
		{
			x1=ax;
			x2=RenderInfo.xb2;
		}
	}
	else
	{
		x1=RenderInfo.xb1;
		x2=RenderInfo.xb2;
	}
	if(RenderInfo.y1<0 && RenderInfo.y2>0 && RenderInfo.mirrorx)
	{
		ay=RenderInfo.yb1+fabs((fabs(RenderInfo.y1)*wy/fabs(RenderInfo.y2-RenderInfo.y1)));
		h=ay-RenderInfo.yb1;
		RenderInfo.y1=-(h*yd);
		h=RenderInfo.yb2-ay;
		RenderInfo.y2=h*yd;
		if(fabs(RenderInfo.y1)>=fabs(RenderInfo.y2))
		{
			y1=RenderInfo.yb1;
			y2=ay;
		}
		else
		{
			y1=ay;
			y2=RenderInfo.yb2;
		}
	}
	else
	{
		y1=RenderInfo.yb1;
		y2=RenderInfo.yb2;
	}

	mx=x1+(x2-x1)/2;my=y1+(y2-y1)/2;
	sb[0].x1=x1;sb[0].y1=y1;sb[0].x2=mx;sb[0].y2=my;
	sb[1].x1=mx;sb[1].y1=y1;sb[1].x2=x2;sb[1].y2=my;
	sb[2].x1=mx;sb[2].y1=my;sb[2].x2=x2;sb[2].y2=y2;
	sb[3].x1=x1;sb[3].y1=my;sb[3].x2=mx;sb[3].y2=y2;
	st=3;

	while(st>-1)
	{
		as=0;
		mx1=sb[st].x1;mx2=sb[st].x2;my1=sb[st].y1;my2=sb[st].y2;
		rx1=RenderInfo.x1+(mx1-RenderInfo.xb1)*xd;ry1=RenderInfo.y1+(my1-RenderInfo.yb1)*yd;
		rx2=RenderInfo.x1+(mx2-RenderInfo.xb1)*xd;ry2=RenderInfo.y1+(my2-RenderInfo.yb1)*yd;
		x=rx1;y=ry1;PixelModifier();h1=FracFunc();
		x=rx2;PixelModifier();h2=FracFunc();
		y=ry2;PixelModifier();h3=FracFunc();
		x=rx1;PixelModifier();h4=FracFunc();
		if(h1==h2 && h2==h3 && h3==h4)
		{
			x+=(rx2-rx1)/2.0;
			PixelModifier();h=FracFunc();
			if(h==h1)
			{
				y=ry1;
				PixelModifier();h=FracFunc();
				if(h==h1)
				{
					y+=(ry2-ry1)/2.0;x=rx1;
					PixelModifier();h=FracFunc();
					if(h==h1)
					{
						x=rx2;
						PixelModifier();h=FracFunc();
						if(h==h1) as=-1;
					}
				}
			}
		}
		if(as)								/* scheint alles die gl. Farbe zu sein */
		{
			RectFunc(mx1,my1,mx2,my2,h,ax,ay);
			st--;
		}
		else
		{
			if(mx2-mx1<2 && my2-my1<2)			/* kleiner gehts nicht */
			{
				PsetFunc(mx1,my1,h1,ax,ay);
				PsetFunc(mx2,my1,h2,ax,ay);
				PsetFunc(mx2,my2,h3,ax,ay);
				PsetFunc(mx1,my2,h4,ax,ay);
				st--;
			}
			else
			{
				if(mx2-mx1<2)					/* nur y-teilen */
				{
					my=my1+((my2-my1)>>1);
					sb[st+1].x1=sb[st].x1;
					sb[st+1].y1=my+1;
					sb[st+1].x2=sb[st].x2;
					sb[st+1].y2=sb[st].y2;
					sb[st].y2=my;st++;
				}
				else
				{
					if(my2-my1<2)				/* nur x-teilen */
					{
						mx=mx1+((mx2-mx1)>>1);
						sb[st+1].x1=mx+1;
						sb[st+1].y1=sb[st].y1;
						sb[st+1].x2=sb[st].x2;
						sb[st+1].y2=sb[st].y2;
						sb[st].x2=mx;st++;
					}
					else						/* würfeln */
					{
						my=my1+((my2-my1)>>1);	/* oben links nach oben rechts */
						mx=mx1+((mx2-mx1)>>1);
						sb[st].y2=my;
						sb[st+1].x1=mx+1;
						sb[st+1].y1=sb[st].y1;
						sb[st+1].x2=sb[st].x2;
						sb[st+1].y2=my;
						sb[st].x2=mx;

						st+=2;					/* oben links nach unten links */
						sb[st].x1=sb[st-2].x1;
						sb[st].y1=my+1;
						sb[st].x2=sb[st-2].x2;
						sb[st].y2=my2;

						st++;					/* oben rechts nach unten rechts */
						sb[st].x1=sb[st-2].x1;
						sb[st].y1=my+1;
						sb[st].x2=sb[st-2].x2;
						sb[st].y2=my2;
					}
				}
			}
		}
		while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort))
		{
			iclass=imsg->Class;
			icode=imsg->Code;
			ReplyMsg(imsg);
			switch(iclass)
			{
				case IDCMP_RAWKEY:
					switch(icode)
					{
						case 0x45:					/* Berechnung abbrechen */
							rv=1;
							st=-1;
							break;
						case 0x25:				/* Hide Mousepointer */
							if(epointer) { ClearPointer(rwindow);epointer=0; }
							else { SetPointer(rwindow,Emptypointer,16,16,-6,0);epointer=1; }
							break;
						case 0x01:				/* 1 */
							RunTime.aktpal=0;cdata.pos=0;SetColorPalette();
							break;
						case 0x02:				/* 2 */
							RunTime.aktpal=1;cdata.pos=0;SetColorPalette();
							break;
						case 0x03:				/* 3 */
							RunTime.aktpal=2;cdata.pos=0;SetColorPalette();
							break;
						case 0x04:				/* 4 */
							RunTime.aktpal=3;cdata.pos=0;SetColorPalette();
							break;
						case 0x05:				/* 5 */
							RunTime.aktpal=4;cdata.pos=0;SetColorPalette();
							break;
						case 0x06:				/* 6 */
							RunTime.aktpal=5;cdata.pos=0;SetColorPalette();
							break;
						case 0x07:				/* 7 */
							RunTime.aktpal=6;cdata.pos=0;SetColorPalette();
							break;
						case 0x08:				/* 8 */
							RunTime.aktpal=7;cdata.pos=0;SetColorPalette();
							break;
						case 0x09:				/* 9 */
							RunTime.aktpal=8;cdata.pos=0;SetColorPalette();
							break;
						case 0x0A:				/* 0 */
							RunTime.aktpal=9;cdata.pos=0;SetColorPalette();
							break;
					}
					break;
			}
		}
	}
	if(epointer)
	{
		ClearPointer(rwindow);epointer=0;
	}
	return(rv);
}

UBYTE RenderPreview(void)
{
	register UWORD i,j,k,l,n,j2,i2;
	UWORD wx,wy;
	UBYTE rv=0;
	UWORD ax,ay;
	UWORD x1,y1,x2,y2;
	double xc1,yc1,xd4,yd4,xo,yo;
	struct IntuiMessage *imsg;
	ULONG iclass;
	USHORT icode;
//	APTR iadr;

// DEBUG
	MSG1("PixelModifier : 0x%08lx",PixelModifier);
	MSG1("PsetFunc      : 0x%08lx",PsetFunc);
	MSG1("FracFunc      : 0x%08lx",FracFunc);
// DEBUG


	derr=0.0;
	if(RenderInfo.outside==6) decompho=RenderInfo.outpar1/6.283185307;
	if(RenderInfo.inside==2) decomphi=RenderInfo.inpar1/6.283185307;
	wx=RenderInfo.xb2-RenderInfo.xb1;
	wy=RenderInfo.yb2-RenderInfo.yb1;
	xd=(RenderInfo.x2-RenderInfo.x1)/wx;
	yd=(RenderInfo.y2-RenderInfo.y1)/wy;

	if(RenderInfo.x1<0 && RenderInfo.x2>0 && RenderInfo.mirrory)
	{
		ax=RenderInfo.xb1+fabs((fabs(RenderInfo.x1)*wx/fabs(RenderInfo.x2-RenderInfo.x1)));
		n=ax-RenderInfo.xb1;
		RenderInfo.x1=-(n*xd);
		n=RenderInfo.xb2-ax;
		RenderInfo.x2=n*xd;
		if(fabs(RenderInfo.x1)>=fabs(RenderInfo.x2))
		{
			x1=RenderInfo.xb1;
			x2=ax;
		}
		else
		{
			x1=ax;
			x2=RenderInfo.xb2;
		}
	}
	else
	{
		x1=RenderInfo.xb1;
		x2=RenderInfo.xb2;
	}
	if(RenderInfo.y1<0 && RenderInfo.y2>0 && RenderInfo.mirrorx)
	{
		ay=RenderInfo.yb1+fabs((fabs(RenderInfo.y1)*wy/fabs(RenderInfo.y2-RenderInfo.y1)));
		n=ay-RenderInfo.yb1;
		RenderInfo.y1=-(n*yd);
		n=RenderInfo.yb2-ay;
		RenderInfo.y2=n*yd;
		if(fabs(RenderInfo.y1)>=fabs(RenderInfo.y2))
		{
			y1=RenderInfo.yb1;
			y2=ay;
		}
		else
		{
			y1=ay;
			y2=RenderInfo.yb2;
		}
	}
	else
	{
		y1=RenderInfo.yb1;
		y2=RenderInfo.yb2;
	}
	xd4=xd*4.0;yd4=yd*4.0;
	xc1=RenderInfo.x1;yc1=RenderInfo.y1;
	xo=(x1-RenderInfo.xb1)*xd;yo=(y1-RenderInfo.yb1)*yd;
	j2=y1+(y2-y1);i2=x1+(x2-x1);
	for(l=0;l<4;l++)
	{
		for(k=0;k<4;k++)
		{
			y=yc1+yo;
			for(j=y1+l;j<=j2;j+=4)
			{
				x=xc1+xo;
				for(i=x1+k;i<=i2;i+=4)
				{
					PixelModifier();
					PsetFunc(i,j,FracFunc(),ax,ay);
					x+=xd4;
				}
				y+=yd4;
				while(imsg=(struct IntuiMessage *)GetMsg(rwindow->UserPort))
				{
					iclass=imsg->Class;
					icode=imsg->Code;
					ReplyMsg(imsg);
					switch(iclass)
					{
						case IDCMP_RAWKEY:
							switch(icode)
							{
								case 0x45:					/* Berechnung abbrechen */
									rv=1;j=j2;
									k=l=4;
									break;
								case 0x25:				/* Hide Mousepointer */
									if(epointer) { ClearPointer(rwindow);epointer=0; }
									else { SetPointer(rwindow,Emptypointer,16,16,-6,0);epointer=1; }
									break;
								case 0x01:				/* 1 */
									RunTime.aktpal=0;cdata.pos=0;SetColorPalette();
									break;
								case 0x02:				/* 2 */
									RunTime.aktpal=1;cdata.pos=0;SetColorPalette();
									break;
								case 0x03:				/* 3 */
									RunTime.aktpal=2;cdata.pos=0;SetColorPalette();
									break;
								case 0x04:				/* 4 */
									RunTime.aktpal=3;cdata.pos=0;SetColorPalette();
									break;
								case 0x05:				/* 5 */
									RunTime.aktpal=4;cdata.pos=0;SetColorPalette();
									break;
								case 0x06:				/* 6 */
									RunTime.aktpal=5;cdata.pos=0;SetColorPalette();
									break;
								case 0x07:				/* 7 */
									RunTime.aktpal=6;cdata.pos=0;SetColorPalette();
									break;
								case 0x08:				/* 8 */
									RunTime.aktpal=7;cdata.pos=0;SetColorPalette();
									break;
								case 0x09:				/* 9 */
									RunTime.aktpal=8;cdata.pos=0;SetColorPalette();
									break;
								case 0x0A:				/* 0 */
									RunTime.aktpal=9;cdata.pos=0;SetColorPalette();
									break;
							}
							break;
					}
				}
			}
			xc1+=xd;
		}
		xc1=RenderInfo.x1;
		yc1+=yd;
	}
	if(epointer)
	{
		ClearPointer(rwindow);epointer=0;
	}
	return(rv);
}

void RenderTurbo(void)
{
	register UWORD i,j;
	register double xo;

	derr=0.0;
	if(RenderInfo.outside==6) decompho=RenderInfo.outpar1/6.283185307;
	if(RenderInfo.inside==2) decomphi=RenderInfo.inpar1/6.283185307;
	xo=RenderInfo.x1+(RenderInfo.xb1-RenderInfo.xb1)*xd;
	y=RenderInfo.y1+(RenderInfo.yb1-RenderInfo.yb1)*yd;
	for(j=RenderInfo.yb1;j<=RenderInfo.yb2;j++)
	{
		x=xo;
		for(i=RenderInfo.xb1;i<=RenderInfo.xb2;i++)
		{
			PixelModifier();
			PsetFunc(i,j,FracFunc(),0,0);
			x+=xd;
		}
		y+=yd;
	}
}
