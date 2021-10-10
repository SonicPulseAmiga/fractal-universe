/******************************************************************************
** FU-FUNC-FORMULA.h                                                         **
**---------------------------------------------------------------------------**
** Fractal Functions                                                         **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 04.02.1994                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

UWORD FuncFormula(void)
{
	UWORD h=0,ix;
	register UWORD n,m;
	register UBYTE k=0,br;

	ix=GetVarIX("Z");						/* Index for Z -> Orbit */
	uv[0].z.r=rx;uv[0].z.i=ry;				/* Setting PIXEL to x & y */
	bofabs=999.99;bofz=0;
	for(m=0;m<lmops;m++) *mabus[m].e=mabus[m].MathFunc(*mabus[m].p1,*mabus[m].p2);
	ob[0].r=uv[ix].z.r;ob[0].i=uv[ix].z.i;	/* Orbit */
	for(n=1;n<RenderInfo.z;n++)
	{
		for(m=0;m<lmopi;m++) *mabui[m].e=mabui[m].MathFunc(*mabui[m].p1,*mabui[m].p2);
		br=0;
		switch(bailt)
		{
			case 1:
				if(uv[baill].z.r<uv[bailr].z.r) br=1;
				break;
			case 2:
				if(uv[baill].z.r<=uv[bailr].z.r) br=1;
				break;
			case 3:
				if(uv[baill].z.r==uv[bailr].z.r) br=1;
				break;
			case 4:
				if(uv[baill].z.r>=uv[bailr].z.r) br=1;
				break;
			case 5:
				if(uv[baill].z.r>uv[bailr].z.r) br=1;
				break;
			case 6:
				if(uv[baill].z.r!=uv[bailr].z.r) br=1;
				break;
		}
		if(!br)
		{
			ob[n].r=uv[ix].z.r;ob[n].i=uv[ix].z.i;					/* Orbit */
			if(uv[ix].z.r*uv[ix].z.r+uv[ix].z.i*uv[ix].z.i<bofabs)	/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=uv[ix].z.r*uv[ix].z.r+uv[ix].z.i*uv[ix].z.i;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(uv[ix].z.r,uv[ix].z.i,uv[ix].z.r*uv[ix].z.r,uv[ix].z.i*uv[ix].z.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(uv[ix].z.r,uv[ix].z.i,uv[ix].z.r*uv[ix].z.r,uv[ix].z.i*uv[ix].z.i); }
	return((UWORD)(h/GfxInfo.palscl));
}
