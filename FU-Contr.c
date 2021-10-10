/****h* FractalUniverse/FU-Contr.c [1.68] *
*
*  NAME
*    FU-Contr.c
*  COPYRIGHT
*    $VER: FU-Contr.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    The RenderControl & View Functions
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

#define FU_CONTR_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void mm_render(void);
void mm_view(void);
void mm_inspect(void);
void preprender(void);
void draw_info(UWORD mx,UWORD my);
void draw_orbit(void);

//-- globals ------------------------------------------------------------------

complex (*TrigFunc1)(complex p1,complex p2);
complex (*TrigFunc2)(complex p1,complex p2);
complex (*TrigFunc3)(complex p1,complex p2);
complex (*TrigFunc4)(complex p1,complex p2);

//-- definitions --------------------------------------------------------------

void mm_render(void)
{
	UBYTE erg=0;
	long rs,rf;

	preprender();
	if(!RunTime.rexxactive) ScreenToFront(rscreen);
	SetRast(&rrp[0],0);
	if(!RunTime.rexxactive) ActivateWindow(rwindow);
	if(RenderInfo.xb1>0)		/* falls Window, dann Rand zeichnen */
	{
		Move(&rrp[1],RenderInfo.xb1-1,max(RenderInfo.yb1-1,0));
		Draw(&rrp[1],RenderInfo.xb1-1,min(RenderInfo.yb2+1,GfxInfo.yres-1));
	}
	if(RenderInfo.xb2<GfxInfo.xres-1)
	{
		Move(&rrp[1],RenderInfo.xb2+1,max(RenderInfo.yb1-1,0));
		Draw(&rrp[1],RenderInfo.xb2+1,min(RenderInfo.yb2+1,GfxInfo.yres-1));
	}
	if(RenderInfo.yb1>0)
	{
		Move(&rrp[1],max(RenderInfo.xb1-1,0),RenderInfo.yb1-1);
		Draw(&rrp[1],min(RenderInfo.xb2+1,GfxInfo.xres-1),RenderInfo.yb1-1);
	}
	if(RenderInfo.yb2<GfxInfo.yres-1)
	{
		Move(&rrp[1],max(RenderInfo.xb1-1,0),RenderInfo.yb2+1);
		Draw(&rrp[1],min(RenderInfo.xb2+1,GfxInfo.xres-1),RenderInfo.yb2+1);
	}
	time(&rs);
	switch(RenderInfo.rendermode)
	{
		case 0: erg=RenderSolid();break;
		case 1:	erg=RenderSquare();break;
		case 2:	erg=RenderFastSquare();break;
		case 3:	erg=RenderPreview();break;
	}
	time(&rf);
	rendertime=difftime(rf,rs);
	opx1=RenderInfo.x1;opx2=RenderInfo.x2;
	opy1=RenderInfo.y1;opy2=RenderInfo.y2;
	opxb1=RenderInfo.xb1;opxb2=RenderInfo.xb2;
	opyb1=RenderInfo.yb1;opyb2=RenderInfo.yb2;
	RunTime.picavail=1;
	if(!erg)
	{
		if(RenderInfo.signal) DisplayBeep(rscreen);
		if(!RunTime.rexxactive)	mm_view();
	}
	else
	{
		ScreenToFront(mmscr);
		ActivateWindow(mmwin);
	}
}

void mm_view(void)
{
	struct IntuiMessage *imsg;
	ULONG iclass;
	USHORT icode;
	UBYTE quit=0;
	register UWORD i,j;
	double x1,y1,x2,y2;
	UWORD xb1,yb1,xb2,yb2,wx,wy,mirrorx,mirrory;
	struct ColorSet32 tcolors32;

	preprender();
	ScreenToFront(rscreen);
	ActivateWindow(rwindow);
	ModifyIDCMP(rwindow,IDCMP_MOUSEBUTTONS|IDCMP_RAWKEY);

	cdata.pos=0;
	cdata.cycling=0;
	wx=RenderInfo.xb2-RenderInfo.xb1;
	wy=RenderInfo.yb2-RenderInfo.yb1;
	xd=(RenderInfo.x2-RenderInfo.x1)/wx;
	yd=(RenderInfo.y2-RenderInfo.y1)/wy;
	mirrorx=RenderInfo.mirrorx;RenderInfo.mirrorx=0;
	mirrory=RenderInfo.mirrory;RenderInfo.mirrory=0;
	tcolors32.NumColors=GfxInfo.realcol;
	tcolors32.FirstColor=0;
	tcolors32.Terminator=0;

	while(!quit)
	{
		while(imsg=GT_GetIMsg(rwindow->UserPort))
		{
			iclass	=imsg->Class;
			icode	=imsg->Code;
			GT_ReplyIMsg(imsg);
			if(iclass==IDCMP_RAWKEY)
			{
				switch(icode)
				{
					case 0x42:
					case 0x40:				/* Space */
						cdata.cycling=1-cdata.cycling;
						break;
					case 0x45:				/* ESC */
						quit=1;
						break;
					case 0x25:				/* Hide Mousepointer */
						if(epointer) { ClearPointer(rwindow);epointer=0; }
						else { SetPointer(rwindow,Emptypointer,1,16,0,0);epointer=1; }
						break;
					case 0x4C:				/* Cursor Up */
						if(cdata.rate>0) cdata.rate--;
						break;
					case 0x4D:				/* Cursor Down */
						if(cdata.rate<8) cdata.rate++;
						break;
					case 0x4E:				/* Cursor Right */
						cdata.dir=1;
						break;
					case 0x4F:				/* Cursor Left */
						cdata.dir=0;
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
					case 0x1D:				/* 1 auf Zehnerblock */
						ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
						RenderInfo.y1+=wy*yd;
						RenderInfo.y2+=4.0*yd;
						yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb1=yb1;
						ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
						RenderInfo.x2-=wx*xd;
						RenderInfo.x1-=4.0*xd;
						xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb2=xb2;
						break;
					case 0x1E:				/* 2 */
						ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
						RenderInfo.y1+=wy*yd;
						RenderInfo.y2+=4.0*yd;
						yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb1=yb1;
						break;
					case 0x1F:				/* 3 */
						ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
						RenderInfo.y1+=wy*yd;
						RenderInfo.y2+=4.0*yd;
						yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb1=yb1;
						ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
						RenderInfo.x1+=wx*xd;
						RenderInfo.x2+=4.0*xd;
						xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb1=xb1;
						break;
					case 0x2F:				/* 6 */
						ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
						RenderInfo.x1+=wx*xd;
						RenderInfo.x2+=4.0*xd;
						xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb1=xb1;
						break;
					case 0x3F:				/* 9 */
						ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
						RenderInfo.y2-=wy*yd;
						RenderInfo.y1-=4.0*yd;
						yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb2=yb2;
						ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
						RenderInfo.x1+=wx*xd;
						RenderInfo.x2+=4.0*xd;
						xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb1=xb1;
						break;
					case 0x3E:				/* 8 */
						ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
						RenderInfo.y2-=wy*yd;
						RenderInfo.y1-=4.0*yd;
						yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb2=yb2;
						break;
					case 0x3D:				/* 7 */
						ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
						RenderInfo.y2-=wy*yd;
						RenderInfo.y1-=4.0*yd;
						yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb2=yb2;
						ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
						RenderInfo.x2-=wx*xd;
						RenderInfo.x1-=4.0*xd;
						xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb2=xb2;
						break;
					case 0x2D:				/* 4 */
						ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
						RenderInfo.x2-=wx*xd;
						RenderInfo.x1-=4.0*xd;
						xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb2=xb2;
						break;
				}
			}
			if(iclass==IDCMP_MOUSEBUTTONS) quit=1;
		}
		if((custom.joy1dat&512)&&((custom.joy1dat&1)^(custom.joy1dat&2)>>1))		/* links hinten */
		{
			ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
			RenderInfo.y1+=wy*yd;
			RenderInfo.y2+=4.0*yd;
			yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb1=yb1;
			ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
			RenderInfo.x2-=wx*xd;
			RenderInfo.x1-=4.0*xd;
			xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb2=xb2;
		}
		if((custom.joy1dat&1)^(custom.joy1dat&2)>>1)		/* hinten */
		{
			ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
			RenderInfo.y1+=wy*yd;
			RenderInfo.y2+=4.0*yd;
			yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb1=yb1;
		}
		if((custom.joy1dat&2)&&((custom.joy1dat&1)^(custom.joy1dat&2)>>1))		/* rechts hinten */
		{
			ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
			RenderInfo.y1+=wy*yd;
			RenderInfo.y2+=4.0*yd;
			yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb1=yb1;
			ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
			RenderInfo.x1+=wx*xd;
			RenderInfo.x2+=4.0*xd;
			xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb1=xb1;
		}
		if(custom.joy1dat&2)		/* rechts */
		{
			ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
			RenderInfo.x1+=wx*xd;
			RenderInfo.x2+=4.0*xd;
			xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb1=xb1;
		}
		if((custom.joy1dat&2)&&((custom.joy1dat&256)^(custom.joy1dat&512)>>1))		/* rechts vorn */
		{
			ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
			RenderInfo.y2-=wy*yd;
			RenderInfo.y1-=4.0*yd;
			yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb2=yb2;
			ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
			RenderInfo.x1+=wx*xd;
			RenderInfo.x2+=4.0*xd;
			xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb1=xb1;
		}
		if((custom.joy1dat&256)^(custom.joy1dat&512)>>1)		/* vorn */
		{
			ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
			RenderInfo.y2-=wy*yd;
			RenderInfo.y1-=4.0*yd;
			yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb2=yb2;
		}
		if((custom.joy1dat&512)&&((custom.joy1dat&256)^(custom.joy1dat&512)>>1))		/* links vorn */
		{
			ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
			RenderInfo.y2-=wy*yd;
			RenderInfo.y1-=4.0*yd;
			yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb2=yb2;
			ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
			RenderInfo.x2-=wx*xd;
			RenderInfo.x1-=4.0*xd;
			xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb2=xb2;
		}
		if(custom.joy1dat&512)		/* links */
		{
			ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
			RenderInfo.x2-=wx*xd;
			RenderInfo.x1-=4.0*xd;
			xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb2=xb2;
		}
		if(cdata.cycling)
		{
			if(GfxInfo.palbits<5)
			{
				LoadRGB4(rvp,&colors4[RunTime.aktpal][cdata.pos],GfxInfo.realcol);
				MakeVPort(view,rvp);MrgCop(view);LoadView(view);
			}
			if(GfxInfo.palbits>4)
			{
				j=cdata.pos;
				for(i=0;i<GfxInfo.realcol;i++)
				{
					tcolors32.Entry[i].r=colors32[RunTime.aktpal].Entry[j].r;
					tcolors32.Entry[i].g=colors32[RunTime.aktpal].Entry[j].g;
					tcolors32.Entry[i].b=colors32[RunTime.aktpal].Entry[j].b;
					j++;if(j==GfxInfo.realcol) j=0;
				}
//				printf("pos : %d\n",cdata.pos);
//				printf("j   : %d\n",j);getch();
				LoadRGB32(rvp,(ULONG *)(&tcolors32));
			}
			if(cdata.dir) cdata.pos=(UBYTE)(cdata.pos+1)%GfxInfo.realcol;
			else cdata.pos=(UBYTE)(cdata.pos-1)%GfxInfo.realcol;
			Delay(cdata.rate);
		}
	}
	if(epointer)
	{
		ClearPointer(rwindow);epointer=0;
	}
	RenderInfo.mirrorx=mirrorx;RenderInfo.mirrory=mirrory;
	ModifyIDCMP(rwindow,IDCMP_RAWKEY);
	ScreenToFront(mmscr);
	ActivateWindow(mmwin);
}

void mm_inspect(void)
{
	struct IntuiMessage *imsg;
	ULONG iclass;
	USHORT icode;
	UBYTE quit=0;
	double x1,y1,x2,y2;
	UWORD xb1,yb1,xb2,yb2,mirrorx,mirrory;
	UWORD mx,my,wx,wy;
	UBYTE mb=0;

	preprender();
	ScreenToFront(rscreen);
	ActivateWindow(rwindow);
	ModifyIDCMP(rwindow,IDCMP_MOUSEBUTTONS|IDCMP_RAWKEY|IDCMP_MOUSEMOVE);
	wx=RenderInfo.xb2-RenderInfo.xb1;
	wy=RenderInfo.yb2-RenderInfo.yb1;
	xd=(RenderInfo.x2-RenderInfo.x1)/wx;
	yd=(RenderInfo.y2-RenderInfo.y1)/wy;
	mirrorx=RenderInfo.mirrorx;RenderInfo.mirrorx=0;
	mirrory=RenderInfo.mirrory;RenderInfo.mirrory=0;

	InspectInfo.ox=Modes[RunTime.rscreenmode].OScans[GfxInfo.oscan].MaxX;		/* Orbit- & Inspectwindow Size & Pos. */
	InspectInfo.oy=Modes[RunTime.rscreenmode].OScans[GfxInfo.oscan].MaxY;
	switch(RenderInfo.obsize)
	{
		case 0:
			InspectInfo.ox=(UWORD)((double)InspectInfo.ox*0.5);
			InspectInfo.oy=(UWORD)((double)InspectInfo.oy*0.5);
			break;
		case 1:
			InspectInfo.ox=(UWORD)((double)InspectInfo.ox*0.375);
			InspectInfo.oy=(UWORD)((double)InspectInfo.oy*0.375);
			break;
		case 2:
			InspectInfo.ox=(UWORD)((double)InspectInfo.ox*0.25);
			InspectInfo.oy=(UWORD)((double)InspectInfo.oy*0.25);
			break;
	}
	InspectInfo.obxh=InspectInfo.ox>>1;InspectInfo.obyh=InspectInfo.oy>>1;
	OWindowTags[2].ti_Data=OWindowTags[ 9].ti_Data=OWindowTags[11].ti_Data=InspectInfo.ox+10;
	OWindowTags[3].ti_Data=OWindowTags[10].ti_Data=OWindowTags[12].ti_Data=InspectInfo.oy+15;
	OWindowTags[0].ti_Data=GfxInfo.xres-10-InspectInfo.ox;
	OWindowTags[1].ti_Data=GfxInfo.yres-15-InspectInfo.oy;
	IWindowTags[1].ti_Data=GfxInfo.yres-60;
	InspectInfo.dcol=GetDarkestCol();
	InspectInfo.bcol=GetBrightestCol();
	if((owindow=OpenWindowTagList(NULL,OWindowTags)))
	{
		orp=*owindow->RPort;
		SetAPen(&orp,InspectInfo.bcol);SetBPen(&orp,InspectInfo.dcol);
		SetRast(&orp,InspectInfo.dcol);
	}
	else { Message(mess[5]);quit=1; }
	if((iwindow=OpenWindowTagList(NULL,IWindowTags)))
	{
		irp=*iwindow->RPort;
		SetAPen(&irp,InspectInfo.bcol);SetBPen(&irp,InspectInfo.dcol);
		SetRast(&irp,InspectInfo.dcol);
	}
	else { Message(mess[5]);quit=1; }
	while(!quit)
	{
		WaitPort(rwindow->UserPort);
		while(imsg=GT_GetIMsg(rwindow->UserPort))
		{
			iclass	=imsg->Class;
			icode	=imsg->Code;
			mx		=imsg->MouseX;
			my		=imsg->MouseY;
			GT_ReplyIMsg(imsg);
			if(iclass==IDCMP_RAWKEY)
			{
				switch(icode)
				{
					case 0x45:				/* ESC */
						quit=1;
						break;
					case 0x25:				/* Hide Mousepointer */
						if(epointer) { ClearPointer(rwindow);epointer=0; }
						else { SetPointer(rwindow,Emptypointer,1,16,0,0);epointer=1; }
						break;
					case 0x01:				/* 1 */
						RunTime.aktpal=0;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x02:				/* 2 */
						RunTime.aktpal=1;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x03:				/* 3 */
						RunTime.aktpal=2;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x04:				/* 4 */
						RunTime.aktpal=3;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x05:				/* 5 */
						RunTime.aktpal=4;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x06:				/* 6 */
						RunTime.aktpal=5;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x07:				/* 7 */
						RunTime.aktpal=6;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x08:				/* 8 */
						RunTime.aktpal=7;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x09:				/* 9 */
						RunTime.aktpal=8;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x0A:				/* 0 */
						RunTime.aktpal=9;cdata.pos=0;SetColorPalette();
						InspectInfo.dcol=GetDarkestCol();
						InspectInfo.bcol=GetBrightestCol();
						break;
					case 0x1D:				/* 1 auf Zehnerblock */
						ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
						RenderInfo.y1+=wy*yd;
						RenderInfo.y2+=4.0*yd;
						yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb1=yb1;
						ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
						RenderInfo.x2-=wx*xd;
						RenderInfo.x1-=4.0*xd;
						xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb2=xb2;
						break;
					case 0x1E:				/* 2 */
						ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
						RenderInfo.y1+=wy*yd;
						RenderInfo.y2+=4.0*yd;
						yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb1=yb1;
						break;
					case 0x1F:				/* 3 */
						ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
						RenderInfo.y1+=wy*yd;
						RenderInfo.y2+=4.0*yd;
						yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb1=yb1;
						ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
						RenderInfo.x1+=wx*xd;
						RenderInfo.x2+=4.0*xd;
						xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb1=xb1;
						break;
					case 0x2F:				/* 6 */
						ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
						RenderInfo.x1+=wx*xd;
						RenderInfo.x2+=4.0*xd;
						xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb1=xb1;
						break;
					case 0x3F:				/* 9 */
						ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
						RenderInfo.y2-=wy*yd;
						RenderInfo.y1-=4.0*yd;
						yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb2=yb2;
						ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
						RenderInfo.x1+=wx*xd;
						RenderInfo.x2+=4.0*xd;
						xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb1=xb1;
						break;
					case 0x3E:				/* 8 */
						ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
						RenderInfo.y2-=wy*yd;
						RenderInfo.y1-=4.0*yd;
						yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb2=yb2;
						break;
					case 0x3D:				/* 7 */
						ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
						RenderInfo.y2-=wy*yd;
						RenderInfo.y1-=4.0*yd;
						yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
						RenderTurbo();
						RenderInfo.y1=y1;RenderInfo.y2=y2;
						RenderInfo.yb2=yb2;
						ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
						RenderInfo.x2-=wx*xd;
						RenderInfo.x1-=4.0*xd;
						xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb2=xb2;
						break;
					case 0x2D:				/* 4 */
						ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
						x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
						RenderInfo.x2-=wx*xd;
						RenderInfo.x1-=4.0*xd;
						xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
						RenderTurbo();
						RenderInfo.x1=x1;RenderInfo.x2=x2;
						RenderInfo.xb2=xb2;
						break;
				}
			}
			if(iclass==IDCMP_MOUSEBUTTONS)
			{
				if(!(icode&1) && !(icode&128))
				{
					mb=1;
					if(mx>=RenderInfo.xb1 && mx<=RenderInfo.xb2 && my>=RenderInfo.yb1 && my<=RenderInfo.yb2)
					{
						draw_info(mx,my);
						draw_orbit();
					}
				}
				else mb=0;
			}
			if(mb && iclass==IDCMP_MOUSEMOVE)
			{
				if(mx>=RenderInfo.xb1 && mx<=RenderInfo.xb2 && my>=RenderInfo.yb1 && my<=RenderInfo.yb2)
				{
					draw_info(mx,my);
					draw_orbit();
				}
			}
		}
		if((custom.joy1dat&512)&&((custom.joy1dat&1)^(custom.joy1dat&2)>>1))		/* links hinten */
		{
			ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
			RenderInfo.y1+=wy*yd;
			RenderInfo.y2+=4.0*yd;
			yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb1=yb1;
			ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
			RenderInfo.x2-=wx*xd;
			RenderInfo.x1-=4.0*xd;
			xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb2=xb2;
		}
		if((custom.joy1dat&1)^(custom.joy1dat&2)>>1)		/* hinten */
		{
			ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
			RenderInfo.y1+=wy*yd;
			RenderInfo.y2+=4.0*yd;
			yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb1=yb1;
		}
		if((custom.joy1dat&2)&&((custom.joy1dat&1)^(custom.joy1dat&2)>>1))		/* rechts hinten */
		{
			ScrollRaster(&rrp[0],0,4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1+4.0*yd;y2=RenderInfo.y2+4.0*yd;
			RenderInfo.y1+=wy*yd;
			RenderInfo.y2+=4.0*yd;
			yb1=RenderInfo.yb1;RenderInfo.yb1=RenderInfo.yb2-4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb1=yb1;
			ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
			RenderInfo.x1+=wx*xd;
			RenderInfo.x2+=4.0*xd;
			xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb1=xb1;
		}
		if(custom.joy1dat&2)		/* rechts */
		{
			ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
			RenderInfo.x1+=wx*xd;
			RenderInfo.x2+=4.0*xd;
			xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb1=xb1;
		}
		if((custom.joy1dat&2)&&((custom.joy1dat&256)^(custom.joy1dat&512)>>1))		/* rechts vorn */
		{
			ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
			RenderInfo.y2-=wy*yd;
			RenderInfo.y1-=4.0*yd;
			yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb2=yb2;
			ScrollRaster(&rrp[0],4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1+4.0*xd;x2=RenderInfo.x2+4.0*xd;
			RenderInfo.x1+=wx*xd;
			RenderInfo.x2+=4.0*xd;
			xb1=RenderInfo.xb1;RenderInfo.xb1=RenderInfo.xb2-4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb1=xb1;
		}
		if((custom.joy1dat&256)^(custom.joy1dat&512)>>1)		/* vorn */
		{
			ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
			RenderInfo.y2-=wy*yd;
			RenderInfo.y1-=4.0*yd;
			yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb2=yb2;
		}
		if((custom.joy1dat&512)&&((custom.joy1dat&256)^(custom.joy1dat&512)>>1))		/* links vorn */
		{
			ScrollRaster(&rrp[0],0,-4,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			y1=RenderInfo.y1-4.0*yd;y2=RenderInfo.y2-4.0*yd;
			RenderInfo.y2-=wy*yd;
			RenderInfo.y1-=4.0*yd;
			yb2=RenderInfo.yb2;RenderInfo.yb2=RenderInfo.yb1+4;
			RenderTurbo();
			RenderInfo.y1=y1;RenderInfo.y2=y2;
			RenderInfo.yb2=yb2;
			ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
			RenderInfo.x2-=wx*xd;
			RenderInfo.x1-=4.0*xd;
			xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb2=xb2;
		}
		if(custom.joy1dat&512)		/* links */
		{
			ScrollRaster(&rrp[0],-4,0,RenderInfo.xb1,RenderInfo.yb1,RenderInfo.xb2,RenderInfo.yb2);
			x1=RenderInfo.x1-4.0*xd;x2=RenderInfo.x2-4.0*xd;
			RenderInfo.x2-=wx*xd;
			RenderInfo.x1-=4.0*xd;
			xb2=RenderInfo.xb2;RenderInfo.xb2=RenderInfo.xb1+4;
			RenderTurbo();
			RenderInfo.x1=x1;RenderInfo.x2=x2;
			RenderInfo.xb2=xb2;
		}
	}
	if(epointer)
	{
		ClearPointer(rwindow);epointer=0;
	}
	RenderInfo.mirrorx=mirrorx;RenderInfo.mirrory=mirrory;
	ModifyIDCMP(rwindow,IDCMP_RAWKEY);
	if(owindow) CloseWindow(owindow);
	if(iwindow) CloseWindow(iwindow);
	ScreenToFront(mmscr);
	ActivateWindow(mmwin);
}

void preprender()
{
	register UWORD i;

	AssignGfxFuncs();
	if(FractalInfo.trigendi&1)
	{
		switch(RenderInfo.tpar1)
		{
			case  0: TrigFunc1=cplx_sin;break;
			case  1: TrigFunc1=cplx_cos;break;
			case  2: TrigFunc1=cplx_tan;break;
			case  3: TrigFunc1=cplx_sinh;break;
			case  4: TrigFunc1=cplx_cosh;break;
			case  5: TrigFunc1=cplx_tanh;break;
			case  6: TrigFunc1=cplx_log;break;
			case  7: TrigFunc1=cplx_exp;break;
			case  8: TrigFunc1=cplx_abs;break;
			case  9: TrigFunc1=cplx_real;break;
			case 10: TrigFunc1=cplx_imag;break;
			case 11: TrigFunc1=cplx_swap;break;
			case 12: TrigFunc1=cplx_inv;break;
		}
		for(i=0;i<fn1ps;i++) mabus[fn1bs[i]].MathFunc=TrigFunc1;
		for(i=0;i<fn1pi;i++) mabui[fn1bi[i]].MathFunc=TrigFunc1;
	}
	if(FractalInfo.trigendi&2)
	{
		switch(RenderInfo.tpar2)
		{
			case  0: TrigFunc2=cplx_sin;break;
			case  1: TrigFunc2=cplx_cos;break;
			case  2: TrigFunc2=cplx_tan;break;
			case  3: TrigFunc2=cplx_sinh;break;
			case  4: TrigFunc2=cplx_cosh;break;
			case  5: TrigFunc2=cplx_tanh;break;
			case  6: TrigFunc2=cplx_log;break;
			case  7: TrigFunc2=cplx_exp;break;
			case  8: TrigFunc2=cplx_abs;break;
			case  9: TrigFunc2=cplx_real;break;
			case 10: TrigFunc2=cplx_imag;break;
			case 11: TrigFunc2=cplx_swap;break;
			case 12: TrigFunc2=cplx_inv;break;
		}
		for(i=0;i<fn2ps;i++) mabus[fn2bs[i]].MathFunc=TrigFunc2;
		for(i=0;i<fn2pi;i++) mabui[fn2bi[i]].MathFunc=TrigFunc2;
	}
	if(FractalInfo.trigendi&3)
	{
		switch(RenderInfo.tpar3)
		{
			case  0: TrigFunc3=cplx_sin;break;
			case  1: TrigFunc3=cplx_cos;break;
			case  2: TrigFunc3=cplx_tan;break;
			case  3: TrigFunc3=cplx_sinh;break;
			case  4: TrigFunc3=cplx_cosh;break;
			case  5: TrigFunc3=cplx_tanh;break;
			case  6: TrigFunc3=cplx_log;break;
			case  7: TrigFunc3=cplx_exp;break;
			case  8: TrigFunc3=cplx_abs;break;
			case  9: TrigFunc3=cplx_real;break;
			case 10: TrigFunc3=cplx_imag;break;
			case 11: TrigFunc3=cplx_swap;break;
			case 12: TrigFunc3=cplx_inv;break;
		}
		for(i=0;i<fn3ps;i++) mabus[fn3bs[i]].MathFunc=TrigFunc3;
		for(i=0;i<fn3pi;i++) mabui[fn3bi[i]].MathFunc=TrigFunc3;
	}
	if(FractalInfo.trigendi&4)
	{
		switch(RenderInfo.tpar4)
		{
			case  0: TrigFunc4=cplx_sin;break;
			case  1: TrigFunc4=cplx_cos;break;
			case  2: TrigFunc4=cplx_tan;break;
			case  3: TrigFunc4=cplx_sinh;break;
			case  4: TrigFunc4=cplx_cosh;break;
			case  5: TrigFunc4=cplx_tanh;break;
			case  6: TrigFunc4=cplx_log;break;
			case  7: TrigFunc4=cplx_exp;break;
			case  8: TrigFunc4=cplx_abs;break;
			case  9: TrigFunc4=cplx_real;break;
			case 10: TrigFunc4=cplx_imag;break;
			case 11: TrigFunc4=cplx_swap;break;
			case 12: TrigFunc4=cplx_inv;break;
		}
		for(i=0;i<fn4ps;i++) mabus[fn4bs[i]].MathFunc=TrigFunc4;
		for(i=0;i<fn4pi;i++) mabui[fn4bi[i]].MathFunc=TrigFunc4;
	}
	if((int)RenderInfo.rot!=0)
	{
		rotx=cos(RenderInfo.rot*3.14159265359/180.0);
		roty=sin(RenderInfo.rot*3.14159265359/180.0);
		rotpx=RenderInfo.x1+(RenderInfo.x2-RenderInfo.x1)/2.0;
		rotpy=RenderInfo.y1+(RenderInfo.y2-RenderInfo.y1)/2.0;
	}
	switch(FractalInfo.type)
	{
		case 0:
			if((int)RenderInfo.rot==0) PixelModifier=PixelModifier0_0;
			else PixelModifier=PixelModifier1_0;
			break;
		case 1:
			if(FractalInfo.init==0)
				if((int)RenderInfo.rot==0) PixelModifier=PixelModifier0_1;
				else PixelModifier=PixelModifier1_1;
			else
				if((int)RenderInfo.rot==0) PixelModifier=PixelModifier0_2;
				else PixelModifier=PixelModifier1_2;
			break;
		case 2:
			if((int)RenderInfo.rot==0) PixelModifier=PixelModifier0_3;
			else PixelModifier=PixelModifier1_3;
			break;
		case 3:
			if(FractalInfo.init==0)
				if((int)RenderInfo.rot==0) PixelModifier=PixelModifier0_4;
				else PixelModifier=PixelModifier1_4;
			else
				if((int)RenderInfo.rot==0) PixelModifier=PixelModifier0_5;
				else PixelModifier=PixelModifier1_5;
			break;
	}
	if(ob && oldobsize) FreeMem(ob,oldobsize);
	oldobsize=RenderInfo.z*sizeof(complex);
	if(!(ob=(complex *)AllocMem(oldobsize,MEMF_ANY))) Message(mess[4]);
	uv[1].z.r=RenderInfo.par1.r;
	uv[1].z.i=RenderInfo.par1.i;
	uv[2].z.r=RenderInfo.par2.r;
	uv[2].z.i=RenderInfo.par2.i;
	uv[3].z.r=RenderInfo.par3.r;
	uv[3].z.i=RenderInfo.par3.i;
	uv[4].z.r=RenderInfo.par4.r;
	uv[4].z.i=RenderInfo.par4.i;
	uv[5].z.r=RenderInfo.bailout;
}

void draw_info(UWORD mx,UWORD my)
{
	char str[30];

	SetAPen(&irp,InspectInfo.bcol);SetBPen(&irp,InspectInfo.dcol);
	SetRast(&irp,InspectInfo.dcol);
	x=RenderInfo.x1+(mx-RenderInfo.xb1)*xd;
	y=RenderInfo.y1+(my-RenderInfo.yb1)*yd;
	sprintf(str," sx : %4d",mx);		Move(&irp,7, 9);Text(&irp,str,10);
	sprintf(str," sy : %4d",my);		Move(&irp,7,17);Text(&irp,str,10);
	sprintf(str,"  x : %14.12lf",x);	Move(&irp,7,25);Text(&irp,str,20);
	sprintf(str,"  y : %14.12lf",y);	Move(&irp,7,33);Text(&irp,str,20);
	PixelModifier();
	sprintf(str,"col : %5d",FracFunc());Move(&irp,7,41);Text(&irp,str,11);
}

void draw_orbit(void)
{
	register UWORD n;
	double obx1,oby1,obx2,oby2,obxs,obxm,obys,obym;
	UWORD obcol,obct;
	UWORD aktx,akty;

	obx1=obx2=ob[0].r;
	oby1=oby2=ob[0].i;
	for(n=1;n<obanz;n++)
	{
		if(ob[n].r<obx1) obx1=ob[n].r;
		if(ob[n].r>obx2) obx2=ob[n].r;
		if(ob[n].i<oby1) oby1=ob[n].i;
		if(ob[n].i>oby2) oby2=ob[n].i;
	}
	obxm=obx1+(obx2-obx1)/2.0;
	obym=oby1+(oby2-oby1)/2.0;
	obxs=(obx2-obx1)/(double)(InspectInfo.ox-2);
	obys=(oby2-oby1)/(double)(InspectInfo.oy-2);
	SetRast(&orp,InspectInfo.dcol);
	obcol=InspectInfo.bcol;obct=RenderInfo.obstep;
	SetAPen(&orp,obcol);
	for(n=0;n<obanz;n++)
	{
		obct--;
		if(!obct)
		{
			obcol=(obcol+1)&GfxInfo.absmaxcol;
			obct=RenderInfo.obstep;
			SetAPen(&orp,obcol);
		}
		aktx=InspectInfo.obxh+(WORD)((ob[n].r-obxm)/obxs);
		akty=InspectInfo.obyh+(WORD)((ob[n].i-obym)/obys);
		if(!RenderInfo.obconnect) WritePixel(&orp,aktx,akty);
		else
		{
			if(n) Draw(&orp,aktx,akty);
			else Move(&orp,aktx,akty);
		}
	}
}
