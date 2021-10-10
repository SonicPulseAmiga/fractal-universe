/****h* FractalUniverse/FU-Func.c [1.68] *
*
*  NAME
*    FU-Func.c
*  COPYRIGHT
*    $VER: FU-Func.c 1.68 (24.10.01) © by Stefan Kost 2001-2001
*  FUNCTION
*    Fractal Functions
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

#define FU_FUNC_C
#include "FU-Includes.h"

//-- prototypes ---------------------------------------------------------------

void ChooseFracFunc(int init);

void PixelModifier0_0(void);
void PixelModifier0_1(void);
void PixelModifier0_2(void);
void PixelModifier0_3(void);
void PixelModifier0_4(void);
void PixelModifier0_5(void);
void PixelModifier1_0(void);
void PixelModifier1_1(void);
void PixelModifier1_2(void);
void PixelModifier1_3(void);
void PixelModifier1_4(void);
void PixelModifier1_5(void);

UWORD FuncCircle0(void);
UWORD FuncCircle1(void);
UWORD FuncCircle2(void);
UWORD FuncCircle3(void);
UWORD FuncCircle4(void);
UWORD FuncCircle5(void);
UWORD FuncCircle6(void);
UWORD FuncCircle7(void);

UWORD FuncFormula(void);

UWORD FuncNewton0_0(void);
UWORD FuncNewton1_0(void);
UWORD FuncNewton1_1(void);
UWORD FuncNewton2_0(void);
UWORD FuncNewton3_0(void);

UWORD FuncMJ(void);
UWORD FuncMJ_I(void);
UWORD FuncMJFn(void);
UWORD FuncMJPower(void);
UWORD FuncMJWar(void);
UWORD FuncSqrFn(void);
UWORD FuncMJMan(void);
UWORD FuncTrinomic(void);
UWORD FuncX3(void);
UWORD FuncX4(void);
UWORD FuncMagnet1(void);

//-- definitions --------------------------------------------------------------

void ChooseFracFunc(int init)
{
	register int i;
	FInfo tfi;
	UWORD (*tff)(void);
	char ffstr[20],sfstr[20];

	switch(init)
	{
		case 0:
			FractalInfo.par1.r=0.0;FractalInfo.par1.i=0.0;			/* alles auf 0 setzen */
			FractalInfo.par2.r=0.0;FractalInfo.par2.i=0.0;
			FractalInfo.par3.r=0.0;FractalInfo.par3.i=0.0;
			FractalInfo.par4.r=0.0;FractalInfo.par4.i=0.0;
			FractalInfo.tpar1=0;FractalInfo.tpar2=0;
			FractalInfo.tpar3=0;FractalInfo.tpar4=0;
			FractalInfo.parendi=0;FractalInfo.pickendi=0;FractalInfo.trigendi=0;
			FractalInfo.type=0;FractalInfo.init=0;
			break;
		case 1:
			tfi=FractalInfo;		/* FractalInfo retten */
			break;
		case 2:
			tfi=FractalInfo;		/* FractalInfo retten */
			tff=FracFunc;			/* FracFunc retten */
			break;
	}
	for(i=0;i<39;i++)
	{
		fd[0][i]=fd[1][i]=fd[2][i]=fd[3][i]=fd[4][i]=32;
	}
	fd[0][39]=fd[1][39]=fd[2][39]=fd[3][39]=fd[4][39]=0;

	matchnrff(&RunTime.fracfunc,ffstr);
	matchnrsf(&RunTime.subfunc,sfstr);
	sprintf(fd[0],"%s %s",ffstr,sfstr);
	switch(RunTime.fracfunc)
	{
		case 0:				/* InvCircle ... */
			FractalInfo.type=0;
			FractalInfo.bailout=10000.0;		/* Magnifyfactor */
			switch(RunTime.subfunc)
			{
				case 0:
					FracFunc=FuncCircle0;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=1;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					break;
				case 1:
					FracFunc=FuncCircle1;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=2.0;FractalInfo.par1.i=2.0;			/* Exponenten */
					FractalInfo.par2.r=3.0;FractalInfo.par2.i=3.0;			/* Exponenten */
					FractalInfo.parendi=15;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Exponent");
					break;
				case 2:
					FracFunc=FuncCircle2;
					if(init)
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=2.0;FractalInfo.par1.i=2.0;			/* Exponenten */
					FractalInfo.parendi=3;
					strcpy(fd[1],"par1 : Exponent");
					break;
				case 3:
					FracFunc=FuncCircle3;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=2.0;FractalInfo.par1.i=2.0;			/* Exponenten */
					FractalInfo.par2.r=3.0;FractalInfo.par2.i=3.0;			/* Exponenten */
					FractalInfo.parendi=15;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Exponent");
					break;
				case 4:
					FracFunc=FuncCircle4;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=2.0;FractalInfo.par1.i=2.0;			/* Exponenten */
					FractalInfo.par2.r=3.0;FractalInfo.par2.i=3.0;			/* Exponenten */
					FractalInfo.parendi=15;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Exponent");
					break;
				case 5:
					FracFunc=FuncCircle5;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=1;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					break;
				case 6:
					FracFunc=FuncCircle6;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=1;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					break;
				case 7:
					FracFunc=FuncCircle7;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=3.0;FractalInfo.par1.i=3.0;			/* Exponenten */
					FractalInfo.parendi=3;
					strcpy(fd[1],"par1 : Exponent");
					break;
			}
			break;
		case 1:				/* NormCircle ... */
			FractalInfo.type=2;
			FractalInfo.bailout=10000.0;		/* Magnifyfactor */
			switch(RunTime.subfunc)
			{
				case 0:
					FracFunc=FuncCircle0;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=1;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					break;
				case 1:
					FracFunc=FuncCircle1;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=2.0;FractalInfo.par1.i=2.0;			/* Exponenten */
					FractalInfo.par2.r=3.0;FractalInfo.par2.i=3.0;			/* Exponenten */
					FractalInfo.parendi=15;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Exponent");
					break;
				case 2:
					FracFunc=FuncCircle2;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=2.0;FractalInfo.par1.i=2.0;			/* Exponenten */
					FractalInfo.parendi=3;
					strcpy(fd[1],"par1 : Exponent");
					break;
				case 3:
					FracFunc=FuncCircle3;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=2.0;FractalInfo.par1.i=2.0;			/* Exponenten */
					FractalInfo.par2.r=3.0;FractalInfo.par2.i=3.0;			/* Exponenten */
					FractalInfo.parendi=15;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Exponent");
					break;
				case 4:
					FracFunc=FuncCircle4;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=2.0;FractalInfo.par1.i=2.0;			/* Exponenten */
					FractalInfo.par2.r=3.0;FractalInfo.par2.i=3.0;			/* Exponenten */
					FractalInfo.parendi=15;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Exponent");
					break;
				case 5:
					FracFunc=FuncCircle5;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=1;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					break;
				case 6:
					FracFunc=FuncCircle6;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=1;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					break;
				case 7:
					FracFunc=FuncCircle7;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.00;FractalInfo.y1=-1.00;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.00;
					FractalInfo.par1.r=3.0;FractalInfo.par1.i=3.0;			/* Exponenten */
					strcpy(fd[1],"par1 : Exponent");
					break;
			}
			break;
		case 2:				/* Formula ... */
			FractalInfo.type=2;
			FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
			FractalInfo.x1=-2.00;FractalInfo.y1=-2.00;
			FractalInfo.x2= 2.00;FractalInfo.y2= 2.00;
			if(!interpret()) FracFunc=FuncFormula;
			break;
		case 3:				/* InvNewton ... */
			FractalInfo.type=0;
			FractalInfo.bailout=0.0000000001;					/* Bailoutvalue */
			switch(RunTime.subfunc)
			{
				case 0:
					FracFunc=FuncNewton0_0;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r=4.0;FractalInfo.par1.i=0.0;		/* Exponent */
					FractalInfo.par2.r=1.0;FractalInfo.par2.i=1.0;		/* Factor 1 */
					FractalInfo.par3.r=1.5;FractalInfo.par3.i=0.0;		/* Factor 2 */
					FractalInfo.parendi=63;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Factor 1");
					strcpy(fd[3],"par3 : Factor 2");
					break;
				case 1:
					FracFunc=FuncNewton1_0;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r=4.0;FractalInfo.par1.i=0.0;		/* Exponent */
					FractalInfo.par2.r=1.0;FractalInfo.par2.i=1.0;		/* Factor 1 */
					FractalInfo.par3.r=1.5;FractalInfo.par3.i=0.0;		/* Factor 2 */
					FractalInfo.parendi=63;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Factor 1");
					strcpy(fd[3],"par3 : Factor 2");
					break;
				case 2:
					FracFunc=FuncNewton1_1;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r= 4.0;FractalInfo.par1.i=0.0;		/* Exponent */
					FractalInfo.par2.r= 1.0;FractalInfo.par2.i=1.0;		/* Factor 1 */
					FractalInfo.par3.r= 1.5;FractalInfo.par3.i=0.0;		/* Factor 2 */
					FractalInfo.par4.r=-0.5;FractalInfo.par4.i=0.5;		/* Startwert */
					FractalInfo.parendi=255;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Factor 1");
					strcpy(fd[3],"par3 : Factor 2");
					strcpy(fd[4],"par4 : Initial Value");
					break;
				case 3:
					FracFunc=FuncNewton2_0;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r=3.0;FractalInfo.par1.i=0.0;		/* Exponent 1 */
					FractalInfo.par2.r=5.0;FractalInfo.par2.i=0.0;		/* Exponent 2 */
					FractalInfo.par3.r=1.0;FractalInfo.par3.i=1.0;		/* Factor 1 */
					FractalInfo.par4.r= 1.5;FractalInfo.par4.i=0.0;		/* Factor 2 */
					FractalInfo.parendi=255;
					strcpy(fd[1],"par1 : Exponent 1");
					strcpy(fd[2],"par2 : Exponent 2");
					strcpy(fd[3],"par3 : Factor 1");
					strcpy(fd[4],"par4 : Factor 2");
					break;
				case 4:
					FracFunc=FuncNewton3_0;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r=3.0;FractalInfo.par1.i=0.0;		/* Exponent 1 */
					FractalInfo.par2.r=5.0;FractalInfo.par2.i=0.0;		/* Exponent 2 */
					FractalInfo.par3.r=1.0;FractalInfo.par3.i=1.0;		/* Factor 1 */
					FractalInfo.par4.r= 1.5;FractalInfo.par4.i=0.0;		/* Factor 2 */
					FractalInfo.parendi=255;
					strcpy(fd[1],"par1 : Exponent 1");
					strcpy(fd[2],"par2 : Exponent 2");
					strcpy(fd[3],"par3 : Factor 1");
					strcpy(fd[4],"par4 : Factor 2");
					break;
			}
			break;
		case 4:				/* NormNewton ... */
			FractalInfo.type=2;
			FractalInfo.bailout=0.0000000001;					/* Bailoutvalue */
			switch(RunTime.subfunc)
			{
				case 0:
					FracFunc=FuncNewton0_0;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r=4.0;FractalInfo.par1.i=0.0;		/* Exponent */
					FractalInfo.par2.r=1.0;FractalInfo.par2.i=1.0;		/* Factor 1 */
					FractalInfo.par3.r=1.5;FractalInfo.par3.i=0.0;		/* Factor 2 */
					FractalInfo.parendi=63;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Factor 1");
					strcpy(fd[3],"par3 : Factor 2");
					break;
				case 1:
					FracFunc=FuncNewton1_0;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r=4.0;FractalInfo.par1.i=0.0;		/* Exponent */
					FractalInfo.par2.r=1.0;FractalInfo.par2.i=1.0;		/* Factor 1 */
					FractalInfo.par3.r=1.5;FractalInfo.par3.i=0.0;		/* Factor 2 */
					FractalInfo.parendi=63;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Factor 1");
					strcpy(fd[3],"par3 : Factor 2");
					break;
				case 2:
					FracFunc=FuncNewton1_1;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r= 4.0;FractalInfo.par1.i=0.0;		/* Exponent */
					FractalInfo.par2.r= 1.0;FractalInfo.par2.i=1.0;		/* Factor 1 */
					FractalInfo.par3.r= 1.5;FractalInfo.par3.i=0.0;		/* Factor 2 */
					FractalInfo.par4.r=-0.5;FractalInfo.par4.i=0.5;		/* Startwert */
					FractalInfo.parendi=255;
					strcpy(fd[1],"par1 : Exponent");
					strcpy(fd[2],"par2 : Factor 1");
					strcpy(fd[3],"par3 : Factor 2");
					strcpy(fd[4],"par4 : Initial Value");
					break;
				case 3:
					FracFunc=FuncNewton2_0;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r=3.0;FractalInfo.par1.i=0.0;		/* Exponent 1 */
					FractalInfo.par2.r=5.0;FractalInfo.par2.i=0.0;		/* Exponent 2 */
					FractalInfo.par3.r=1.0;FractalInfo.par3.i=1.0;		/* Factor 1 */
					FractalInfo.par4.r= 1.5;FractalInfo.par4.i=0.0;		/* Factor 2 */
					FractalInfo.parendi=255;
					strcpy(fd[1],"par1 : Exponent 1");
					strcpy(fd[2],"par2 : Exponent 2");
					strcpy(fd[3],"par3 : Factor 1");
					strcpy(fd[4],"par4 : Factor 2");
					break;
				case 4:
					FracFunc=FuncNewton3_0;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r=3.0;FractalInfo.par1.i=0.0;		/* Exponent 1 */
					FractalInfo.par2.r=5.0;FractalInfo.par2.i=0.0;		/* Exponent 2 */
					FractalInfo.par3.r=1.0;FractalInfo.par3.i=1.0;		/* Factor 1 */
					FractalInfo.par4.r= 1.5;FractalInfo.par4.i=0.0;		/* Factor 2 */
					FractalInfo.parendi=255;
					strcpy(fd[1],"par1 : Exponent 1");
					strcpy(fd[2],"par2 : Exponent 2");
					strcpy(fd[3],"par3 : Factor 1");
					strcpy(fd[4],"par4 : Factor 2");
					break;
			}
			break;
		case 5:				/* InvFixPlaneC ... */
			FractalInfo.type=0;
			FractalInfo.bailout=4.0;								/* Bailoutvalue */
			switch(RunTime.subfunc)
			{
				case 0:
					FracFunc=FuncMJ;								/* Test Integer */
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.70;FractalInfo.y1=-1.70;
					FractalInfo.x2= 1.70;FractalInfo.y2= 1.70;
					FractalInfo.par1.r=-0.74543;FractalInfo.par1.i=0.11301;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 1:
					FracFunc=FuncMJFn;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.00;FractalInfo.y1=-4.00;
					FractalInfo.x2= 5.00;FractalInfo.y2= 4.00;
					FractalInfo.par1.r=-0.70219;FractalInfo.par1.i=0.31235;	/* C */
					FractalInfo.tpar1=0;									/* Trig-Funktion */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;FractalInfo.trigendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 2:
					FracFunc=FuncMJPower;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.0;FractalInfo.y1=-1.7;
					FractalInfo.x2= 1.8;FractalInfo.y2= 1.7;
					FractalInfo.par1.r=-0.269592;FractalInfo.par1.i=0.949020;	/* C */
					FractalInfo.par2.r=5.0;FractalInfo.par2.i=0.9;				/* Exponent */
					FractalInfo.parendi=15;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					strcpy(fd[2],"par2 : Exponent");
					break;
				case 3:
					FracFunc=FuncMJWar;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.80;FractalInfo.y1=-2.25;
					FractalInfo.x2= 1.45;FractalInfo.y2= 2.25;
					FractalInfo.par1.r=0.4543;FractalInfo.par1.i=0.01003;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 4:
					FracFunc=FuncMagnet1;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-20.0;FractalInfo.y1=-16.0;
					FractalInfo.x2= 20.0;FractalInfo.y2= 16.0;
					FractalInfo.par1.r=0.1;FractalInfo.par1.i=0.05;			/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 5:
					FracFunc=FuncSqrFn;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.0;FractalInfo.y1=-4.0;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.0;
					FractalInfo.par1.r=-0.244514;FractalInfo.par1.i=0.4710588;	/* C */
					FractalInfo.tpar1=1;										/* Trig-Funktion */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;FractalInfo.trigendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 6:
					FracFunc=FuncMJMan;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-12.0;FractalInfo.y1=-13.6;
					FractalInfo.x2= 32.0;FractalInfo.y2= 31.6;
					FractalInfo.par1.r=0.257053;FractalInfo.par1.i=-0.84;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 7:
					FracFunc=FuncTrinomic;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-10.0;FractalInfo.y1=-8.0;
					FractalInfo.x2= 10.0;FractalInfo.y2= 8.0;
					FractalInfo.par1.r=-0.10721;FractalInfo.par1.i=0.878431;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 8:
					FracFunc=FuncX3;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-20.0;FractalInfo.y1=-15.0;
					FractalInfo.x2= 20.0;FractalInfo.y2= 17.0;
					FractalInfo.par1.r=-0.601777;FractalInfo.par1.i=0.650450;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 9:
					FracFunc=FuncX4;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-3.0;FractalInfo.y1=-2.4;
					FractalInfo.x2= 3.0;FractalInfo.y2= 2.4;
					FractalInfo.par1.r=-0.427017;FractalInfo.par1.i=0.539781;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
			}
			break;
		case 6:				/* InvVarPlaneC ... */
			FractalInfo.type=1;
			FractalInfo.bailout=4.0;								/* Bailoutvalue */
			switch(RunTime.subfunc)
			{
				case 0:
					FracFunc=FuncMJ;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.5;FractalInfo.y1=-2.2;
					FractalInfo.x2= 4.0;FractalInfo.y2= 2.2;
					break;
				case 1:
					FracFunc=FuncMJFn;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-3.0;FractalInfo.y1=-15.0;
					FractalInfo.x2= 8.0;FractalInfo.y2=  8.0;
					FractalInfo.tpar1=0;									/* Trig-Funktion */
					FractalInfo.trigendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 2:
					FracFunc=FuncMJPower;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-3.3;FractalInfo.y1=-1.425;
					FractalInfo.x2= 1.8;FractalInfo.y2= 2.65;
					FractalInfo.par2.r=5.0;FractalInfo.par2.i=0.9;			/* Exponent */
					FractalInfo.parendi=12;
					FractalInfo.init=1;
					strcpy(fd[1],"par2 : Exponent");
					break;
				case 3:
					FracFunc=FuncMJWar;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-20.0;FractalInfo.y1=-16.0;
					FractalInfo.x2= 20.0;FractalInfo.y2= 16.0;
					break;
				case 4:
					FracFunc=FuncMagnet1;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-30.0;FractalInfo.y1=-12.8;
					FractalInfo.x2=  2.0;FractalInfo.y2= 12.8;
					break;
				case 5:
					FracFunc=FuncSqrFn;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-5.625;FractalInfo.y1=-4.5;
					FractalInfo.x2= 5.625;FractalInfo.y2= 4.5;
					FractalInfo.tpar1=1;							/* Trig-Funktion */
					FractalInfo.trigendi=1;
					break;
				case 6:
					FracFunc=FuncMJMan;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-3.0;FractalInfo.y1=-1.4;
					FractalInfo.x2= 1.5;FractalInfo.y2= 1.4;
					break;
				case 7:
					FracFunc=FuncTrinomic;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=1;
					FractalInfo.x1=-5.0;FractalInfo.y1=-3.5;
					FractalInfo.x2= 5.0;FractalInfo.y2= 4.5;
					break;
				case 8:
					FracFunc=FuncX3;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=1;
					FractalInfo.x1=-2.7;FractalInfo.y1=-2.16;
					FractalInfo.x2= 2.7;FractalInfo.y2= 2.16;
					break;
				case 9:
					FracFunc=FuncX4;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.5;FractalInfo.y1=-2.0;
					FractalInfo.x2= 2.5;FractalInfo.y2= 2.0;
					break;
				case 10:
					FracFunc=FuncMagnet1;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-30.0;FractalInfo.y1=-12.8;
					FractalInfo.x2=  2.0;FractalInfo.y2= 12.8;
					FractalInfo.init=1;
					break;
			}
			break;
		case 7:				/* NormFixPlaneC ... */
			FractalInfo.type=2;
			FractalInfo.bailout=4.0;								/* Bailoutvalue */
			switch(RunTime.subfunc)
			{
				case 0:
					FracFunc=FuncMJ;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.70;FractalInfo.y1=-1.70;
					FractalInfo.x2= 1.70;FractalInfo.y2= 1.70;
					FractalInfo.par1.r=-0.74543;FractalInfo.par1.i=0.11301;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 1:
					FracFunc=FuncMJFn;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.10;FractalInfo.y1=-1.50;
					FractalInfo.x2= 1.50;FractalInfo.y2= 1.50;
					FractalInfo.par1.r=-0.70219;FractalInfo.par1.i=0.31235;	/* C */
					FractalInfo.tpar1=0;									/* Trig-Funktion */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;FractalInfo.trigendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 2:
					FracFunc=FuncMJPower;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.0;FractalInfo.y1=-2.0;
					FractalInfo.x2= 2.0;FractalInfo.y2= 2.0;
					FractalInfo.par1.r=-0.269592;FractalInfo.par1.i=0.949020;	/* C */
					FractalInfo.par2.r=5.5;FractalInfo.par2.i=0.5;				/* Exponent */
					FractalInfo.parendi=15;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					strcpy(fd[2],"par2 : Exponent");
					break;
				case 3:
					FracFunc=FuncMJWar;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.80;FractalInfo.y1=-1.50;
					FractalInfo.x2= 1.45;FractalInfo.y2= 1.50;
					FractalInfo.par1.r=0.4543;FractalInfo.par1.i=0.01003;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 4:
					FracFunc=FuncMagnet1;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-6.0;FractalInfo.y1=-5.3;
					FractalInfo.x2= 6.0;FractalInfo.y2= 4.3;
					FractalInfo.par1.r=0.383113;FractalInfo.par1.i=-1.270819;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 5:
					FracFunc=FuncSqrFn;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.5;FractalInfo.y1=-1.75;
					FractalInfo.x2= 2.5;FractalInfo.y2= 1.75;
					FractalInfo.par1.r=-0.244514;FractalInfo.par1.i=0.4710588;	/* C */
					FractalInfo.tpar1=1;										/* Trig-Funktion */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;FractalInfo.trigendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 6:
					FracFunc=FuncMJMan;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.00;FractalInfo.y1=-1.85;
					FractalInfo.x2= 2.00;FractalInfo.y2= 1.85;
					FractalInfo.par1.r=0.257053;FractalInfo.par1.i=-0.84;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 7:
					FracFunc=FuncTrinomic;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.75;FractalInfo.y1=-1.75;
					FractalInfo.x2= 1.75;FractalInfo.y2= 1.75;
					FractalInfo.par1.r=-0.10721;FractalInfo.par1.i=0.878431;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 8:
					FracFunc=FuncX3;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.40;FractalInfo.y1=-1.30;
					FractalInfo.x2= 1.40;FractalInfo.y2= 1.30;
					FractalInfo.par1.r=-0.601777;FractalInfo.par1.i=0.650450;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
				case 9:
					FracFunc=FuncX4;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.00;FractalInfo.y1=-1.50;
					FractalInfo.x2= 2.00;FractalInfo.y2= 1.50;
					FractalInfo.par1.r=-0.427017;FractalInfo.par1.i=0.539781;	/* C */
					FractalInfo.parendi=3;FractalInfo.pickendi=1;
					strcpy(fd[1],"par1 : C");
					break;
			}
			break;
		case 8:				/* NormVarPlaneC ... */
			FractalInfo.type=3;
			FractalInfo.bailout=4.0;					/* Bailoutvalue */
			switch(RunTime.subfunc)
			{
				case 0:
					FracFunc=FuncMJ;		/* FuncMJ_I; */
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.0;FractalInfo.y1=-1.35;
					FractalInfo.x2= 1.0;FractalInfo.y2= 1.35;
					break;
				case 1:
					FracFunc=FuncMJFn;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.00;FractalInfo.y1=-1.35;
					FractalInfo.x2= 1.00;FractalInfo.y2= 1.35;
					FractalInfo.tpar1=0;									/* Trig-Funktion */
					FractalInfo.trigendi=1;
					break;
				case 2:
					FracFunc=FuncMJPower;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.0;FractalInfo.y1=-2.0;
					FractalInfo.x2= 2.0;FractalInfo.y2= 2.0;
					FractalInfo.par2.r=5.5;FractalInfo.par2.i=0.5;			/* Exponent */
					FractalInfo.parendi=12;
					FractalInfo.init=1;
					strcpy(fd[1],"par2 : Exponent");
					break;
				case 3:
					FracFunc=FuncMJWar;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.60;FractalInfo.y1=-1.40;
					FractalInfo.x2= 0.75;FractalInfo.y2= 1.40;
					break;
				case 4:
					FracFunc=FuncMagnet1;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.0;FractalInfo.y1=-2.5;
					FractalInfo.x2= 4.0;FractalInfo.y2= 2.5;
					break;
				case 5:
					FracFunc=FuncSqrFn;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.7;FractalInfo.y1=-2.5;
					FractalInfo.x2= 1.7;FractalInfo.y2= 2.5;
					FractalInfo.tpar1=1;							/* Trig-Funktion */
					FractalInfo.trigendi=1;
					break;
				case 6:
					FracFunc=FuncMJMan;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.00;FractalInfo.y1=-1.85;
					FractalInfo.x2= 2.00;FractalInfo.y2= 1.85;
					break;
				case 7:
					FracFunc=FuncTrinomic;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=1;
					FractalInfo.x1=-1.75;FractalInfo.y1=-1.75;
					FractalInfo.x2= 1.75;FractalInfo.y2= 1.75;
					break;
				case 8:
					FracFunc=FuncX3;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-1.40;FractalInfo.y1=-1.30;
					FractalInfo.x2= 1.40;FractalInfo.y2= 1.30;
					break;
				case 9:
					FracFunc=FuncX4;
					FractalInfo.mirrorx=0;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.00;FractalInfo.y1=-1.50;
					FractalInfo.x2= 2.00;FractalInfo.y2= 1.50;
					break;
				case 10:
					FracFunc=FuncMagnet1;
					FractalInfo.mirrorx=1;FractalInfo.mirrory=0;
					FractalInfo.x1=-2.0;FractalInfo.y1=-2.5;
					FractalInfo.x2= 4.0;FractalInfo.y2= 2.5;
					FractalInfo.init=1;
					break;
			}
			break;
	}
	switch(init)
	{
		case 0:
			RenderInfo.x1=FractalInfo.x1;RenderInfo.y1=FractalInfo.y1;
			RenderInfo.x2=FractalInfo.x2;RenderInfo.y2=FractalInfo.y2;
			RenderInfo.mirrorx=FractalInfo.mirrorx;RenderInfo.mirrory=FractalInfo.mirrory;
			RenderInfo.par1.r=FractalInfo.par1.r;RenderInfo.par1.i=FractalInfo.par1.i;
			RenderInfo.par2.r=FractalInfo.par2.r;RenderInfo.par2.i=FractalInfo.par2.i;
			RenderInfo.par3.r=FractalInfo.par3.r;RenderInfo.par3.i=FractalInfo.par3.i;
			RenderInfo.par4.r=FractalInfo.par4.r;RenderInfo.par4.i=FractalInfo.par4.i;
			RenderInfo.bailout=FractalInfo.bailout;
			RenderInfo.tpar1=FractalInfo.tpar1;RenderInfo.tpar2=FractalInfo.tpar2;
			RenderInfo.tpar3=FractalInfo.tpar3;RenderInfo.tpar4=FractalInfo.tpar4;
			RenderInfo.parendi=FractalInfo.parendi;
			RenderInfo.pickendi=FractalInfo.pickendi;
			RenderInfo.trigendi=FractalInfo.trigendi;
			break;
		case 1:
			FractalInfo=tfi;		/* FractalInfo retten */
			break;
		case 2:
			FractalInfo=tfi;		/* RenderInfo retten */
			FracFunc=tff;			/* FracFunc retten */
			break;			
	}
}

void PixelModifier0_0(void)						/* InvFix */
{
	rx=x/(x*x+y*y);
	ry=-y/(x*x+y*y);
}

void PixelModifier0_1(void)						/* InvVar ZeroInit */
{
	RenderInfo.par1.r=x/(x*x+y*y);
	RenderInfo.par1.i=-y/(x*x+y*y);
	rx=ry=0;
}

void PixelModifier0_2(void)						/* InvVar PixelInit */
{
	RenderInfo.par1.r=rx=x/(x*x+y*y);
	RenderInfo.par1.i=ry=-y/(x*x+y*y);
}

void PixelModifier0_3(void)						/* NormFix */
{
	rx=x;
	ry=y;
}

void PixelModifier0_4(void)						/* NormVar ZeroInit */
{
	RenderInfo.par1.r=x;
	RenderInfo.par1.i=y;
	rx=ry=0;
}

void PixelModifier0_5(void)						/* NormVar PixelInit */
{
	RenderInfo.par1.r=rx=x;
	RenderInfo.par1.i=ry=y;
}

void PixelModifier1_0(void)						/* InvFix */
{
	double tx,ty;

	rx=x-rotpx;ry=y-rotpy;
	tx=rx*rotx-ry*roty;
	ty=rx*roty+ry*rotx;
	tx+=rotpx;ty+=rotpy;
	rx= tx/(tx*tx+ty*ty);
	ry=-ty/(tx*tx+ty*ty);
}

void PixelModifier1_1(void)						/* InvVar ZeroInit */
{
	double tx,ty;

	rx=x-rotpx;ry=y-rotpy;
	tx=rx*rotx-ry*roty;
	ty=rx*roty+ry*rotx;
	tx+=rotpx;ty+=rotpy;
	RenderInfo.par1.r= tx/(tx*tx+ty*ty);
	RenderInfo.par1.i=-ty/(tx*tx+ty*ty);
	rx=ry=0;
}

void PixelModifier1_2(void)						/* InvVar PixelInit */
{
	double tx,ty;

	rx=x-rotpx;ry=y-rotpy;
	tx=rx*rotx-ry*roty;
	ty=rx*roty+ry*rotx;
	tx+=rotpx;ty+=rotpy;
	RenderInfo.par1.r=rx= tx/(tx*tx+ty*ty);
	RenderInfo.par1.i=rx=-ty/(tx*tx+ty*ty);
}

void PixelModifier1_3(void)						/* NormFix */
{
	double tx,ty;

	rx=x-rotpx;ry=y-rotpy;
	tx=rx*rotx-ry*roty;
	ty=rx*roty+ry*rotx;
	rx=tx+rotpx;ry=ty+rotpy;
}

void PixelModifier1_4(void)						/* NormVar ZeroInit */
{
	double tx,ty;

	rx=x-rotpx;ry=y-rotpy;
	tx=rx*rotx-ry*roty;
	ty=rx*roty+ry*rotx;
	RenderInfo.par1.r=tx+rotpx;
	RenderInfo.par1.i=ty+rotpy;
	rx=ry=0;
}

void PixelModifier1_5(void)						/* NormVar PixelInit */
{
	double tx,ty;

	rx=x-rotpx;ry=y-rotpy;
	tx=rx*rotx-ry*roty;
	ty=rx*roty+ry*rotx;
	RenderInfo.par1.r=rx=tx+rotpx;
	RenderInfo.par1.i=ry=ty+rotpy;
}

#include "FU-FUNC-CIRCLE.h"
#include "FU-FUNC-FORMULA.h"
#include "FU-FUNC-NEWTON.h"
#include "FU-FUNC-PLANEC.h"
