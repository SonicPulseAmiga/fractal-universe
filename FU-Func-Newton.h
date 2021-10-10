/******************************************************************************
** FU-FUNC-NEWTON.h                                                          **
**---------------------------------------------------------------------------**
** Fractal Functions                                                         **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 08.02.1994                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

UWORD FuncNewton0_0(void)							/* f(z)=z^p1-1 */
{
	register UWORD n;
	register complex z,f1,f2,zu,zo,h1,h2;
	register double tmp;
	UBYTE k=0;
	UWORD h=0;

	z.r=rx;z.i=ry;
	ob[0].r=z.r;ob[0].i=z.i;								/* Orbit */
	f2.r=f1.r=RenderInfo.par1.r;f2.i=f1.i=RenderInfo.par1.i;f2.r-=1.0;
	for(n=1;n<RenderInfo.z;n++)
	{
		h1.r=log(z.r*z.r+z.i*z.i)/2.0;						/* h1=cplx_pow(z,f2); */
		h1.i=atan2(z.i,z.r);
		h2.r=f2.r*h1.r-f2.i*h1.i;
		h2.i=f2.r*h1.i+f2.i*h1.r;
		h1.r=exp(h2.r)*cos(h2.i);
		h1.i=exp(h2.r)*sin(h2.i);
		zo.r=(h1.r*z.r-h1.i*z.i)-1.0;						/* zo=(h1*z)-[1.0,0.0] */
		zo.i=h1.r*z.i+h1.i*z.r;
		zu.r=(f1.r*h1.r-f1.i*h1.i)+RenderInfo.par2.r;		/* zu=h1*f1+par2 */
		zu.i=(f1.r*h1.i+f1.i*h1.r)+RenderInfo.par2.i;
		tmp=zu.r*zu.r+zu.i*zu.i;							/* h2=zo/zu */
		h2.r=(zo.r*zu.r+zo.i*zu.i)/tmp;
		h2.i=(zo.i*zu.r-zu.i*zo.r)/tmp;
		z.r-=RenderInfo.par3.r*h2.r-RenderInfo.par3.i*h2.i;	/* z=z-par3*h2 */
		z.i-=RenderInfo.par3.r*h2.i+RenderInfo.par3.i*h2.r;
		if((zo.r*zo.r+zo.i*zo.i)>RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,z.r*z.r,z.i*z.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) obanz=n;
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncNewton1_0(void)							/* f(z)=z^p1-c */
{
	register UWORD n;
	register complex z,f1,f2,zu,zo,h1,h2;
	register double tmp;
	UWORD h=0;
	UBYTE k=0;

	z.r=rx;z.i=ry;
	ob[0].r=z.r;ob[0].i=z.i;								/* Orbit */
	f2.r=f1.r=RenderInfo.par1.r;f2.i=f1.i=RenderInfo.par1.i;f2.r-=1.0;
	for(n=1;n<RenderInfo.z;n++)
	{
		h1.r=log(z.r*z.r+z.i*z.i)/2.0;						/* h1=cplx_pow(z,f2); */
		h1.i=atan2(z.i,z.r);
		h2.r=f2.r*h1.r-f2.i*h1.i;
		h2.i=f2.r*h1.i+f2.i*h1.r;
		h1.r=exp(h2.r)*cos(h2.i);
		h1.i=exp(h2.r)*sin(h2.i);
		zo.r=(h1.r*z.r-h1.i*z.i)-rx;						/* zo=(h1*z)-c */
		zo.i=(h1.r*z.i+h1.i*z.r)-ry;
		zu.r=(f1.r*h1.r-f1.i*h1.i)+RenderInfo.par2.r;		/* zu=h1*f1+par2 */
		zu.i=(f1.r*h1.i+f1.i*h1.r)+RenderInfo.par2.i;
		tmp=zu.r*zu.r+zu.i*zu.i;							/* h2=zo/zu */
		h2.r=(zo.r*zu.r+zo.i*zu.i)/tmp;
		h2.i=(zo.i*zu.r-zu.i*zo.r)/tmp;
		z.r-=RenderInfo.par3.r*h2.r-RenderInfo.par3.i*h2.i;	/* z=z-par3*h2 */
		z.i-=RenderInfo.par3.r*h2.i+RenderInfo.par3.i*h2.r;
		if((zo.r*zo.r+zo.i*zo.i)>RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,z.r*z.r,z.i*z.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) obanz=n;
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncNewton1_1(void)							/* f(z)=z^p1-z */
{
	register UWORD n;
	register complex z,f1,f2,zu,zo,h1,h2;
	register double tmp;
	UWORD h=0;
	UBYTE k=0;

	z.r=RenderInfo.par4.r;z.i=RenderInfo.par4.i;
	ob[0].r=z.r;ob[0].i=z.i;								/* Orbit */
	f2.r=f1.r=RenderInfo.par1.r;f2.i=f1.i=RenderInfo.par1.i;f2.r-=1.0;
	for(n=1;n<RenderInfo.z;n++)
	{
		h1.r=log(z.r*z.r+z.i*z.i)/2.0;						/* h1=cplx_pow(z,f2); */
		h1.i=atan2(z.i,z.r);
		h2.r=f2.r*h1.r-f2.i*h1.i;
		h2.i=f2.r*h1.i+f2.i*h1.r;
		h1.r=exp(h2.r)*cos(h2.i);
		h1.i=exp(h2.r)*sin(h2.i);
		zo.r=(h1.r*z.r-h1.i*z.i)-rx;						/* zo=(h1*z)-c */
		zo.i=(h1.r*z.i+h1.i*z.r)-ry;
		zu.r=(f1.r*h1.r-f1.i*h1.i)+RenderInfo.par2.r;		/* zu=h1*f1+par2 */
		zu.i=(f1.r*h1.i+f1.i*h1.r)+RenderInfo.par2.i;
		tmp=zu.r*zu.r+zu.i*zu.i;							/* h2=zo/zu */
		h2.r=(zo.r*zu.r+zo.i*zu.i)/tmp;
		h2.i=(zo.i*zu.r-zu.i*zo.r)/tmp;
		z.r-=RenderInfo.par3.r*h2.r-RenderInfo.par3.i*h2.i;	/* z=z-par3*h2 */
		z.i-=RenderInfo.par3.r*h2.i+RenderInfo.par3.i*h2.r;
		if((zo.r*zo.r+zo.i*zo.i)>RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,z.r*z.r,z.i*z.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) obanz=n;
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncNewton2_0(void)							/* f(z)=z^p1-[1.0,0.0]+z^p2-[1.0,0.0] */
{
	register UWORD n;
	register complex z,zua,zub,zoa,zob,h1a,h1b,h2;
	complex f1a,f1b,f2a,f2b;
	register double tmp;
	UWORD h=0;
	UBYTE k=0;

	z.r=rx;z.i=ry;
	ob[0].r=z.r;ob[0].i=z.i;								/* Orbit */
	f2a.r=f1a.r=RenderInfo.par1.r;f2a.i=f1a.i=RenderInfo.par1.i;f2a.r-=1.0;
	f2b.r=f1b.r=RenderInfo.par2.r;f2b.i=f1b.i=RenderInfo.par2.i;f2b.r-=1.0;
	for(n=1;n<RenderInfo.z;n++)
	{
		h1a.r=log(z.r*z.r+z.i*z.i)/2.0;						/* z2a=cplx_pow(z,f2a); */
		h1a.i=atan2(z.i,z.r);
		h2.r=f2a.r*h1a.r-f2a.i*h1a.i;
		h2.i=f2a.r*h1a.i+f2a.i*h1a.r;
		h1a.r=exp(h2.r)*cos(h2.i);
		h1a.i=exp(h2.r)*sin(h2.i);
		h1b.r=log(z.r*z.r+z.i*z.i)/2.0;						/* z2b=cplx_pow(z,f2b); */
		h1b.i=atan2(z.i,z.r);
		h2.r=f2b.r*h1b.r-f2b.i*h1b.i;
		h2.i=f2b.r*h1b.i+f2b.i*h1b.r;
		h1b.r=exp(h2.r)*cos(h2.i);
		h1b.i=exp(h2.r)*sin(h2.i);
		zoa.r=(h1a.r*z.r-h1a.i*z.i)-1.0;					/* zoa=(h1a*z)-[1.0,0.0] */
		zoa.i=h1a.r*z.i+h1a.i*z.r;
		zua.r=(f1a.r*h1a.r-f1a.i*h1a.i)+RenderInfo.par3.r;	/* zua=h1a*f1a+par2 */
		zua.i=(f1a.r*h1a.i+f1a.i*h1a.r)+RenderInfo.par3.i;
		zob.r=(h1b.r*z.r-h1b.i*z.i)-1.0;					/* zob=(h1b*z)-[1.0,0.0] */
		zob.i=h1b.r*z.i+h1b.i*z.r;
		zub.r=(f1b.r*h1b.r-f1b.i*h1b.i)+RenderInfo.par3.r;	/* zub=h1b*f1b+par2 */
		zub.i=(f1b.r*h1b.i+f1b.i*h1b.r)+RenderInfo.par3.i;
		zoa.r+=zob.r;zoa.i+=zob.i;							/* zoa=zoa+zob */
		zua.r+=zub.r;zua.i+=zub.i;							/* zua=zua+zub */
		tmp=zua.r*zua.r+zua.i*zua.i;						/* h2=zo/zu */
		h2.r=(zoa.r*zua.r+zoa.i*zua.i)/tmp;
		h2.i=(zoa.i*zua.r-zua.i*zoa.r)/tmp;
		z.r-=RenderInfo.par4.r*h2.r-RenderInfo.par4.i*h2.i;	/* z=z-par3*h2 */
		z.i-=RenderInfo.par4.r*h2.i+RenderInfo.par4.i*h2.r;
		if((zoa.r*zoa.r+zoa.i*zoa.i)>RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,z.r*z.r,z.i*z.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) obanz=n;
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncNewton3_0(void)								/* f(z)=z^p1-c+z^p2-c */
{
	register UWORD n;
	register complex z,zua,zub,zoa,zob,h1a,h1b,h2;
	complex f1a,f1b,f2a,f2b;
	register double tmp;
	UWORD h=0;
	UBYTE k=0;

	z.r=rx;z.i=ry;
	ob[0].r=z.r;ob[0].i=z.i;								/* Orbit */
	f2a.r=f1a.r=RenderInfo.par1.r;f2a.i=f1a.i=RenderInfo.par1.i;f2a.r-=1.0;
	f2b.r=f1b.r=RenderInfo.par2.r;f2b.i=f1b.i=RenderInfo.par2.i;f2b.r-=1.0;
	for(n=1;n<RenderInfo.z;n++)
	{
		h1a.r=log(z.r*z.r+z.i*z.i)/2.0;						/* z2a=cplx_pow(z,f2a); */
		h1a.i=atan2(z.i,z.r);
		h2.r=f2a.r*h1a.r-f2a.i*h1a.i;
		h2.i=f2a.r*h1a.i+f2a.i*h1a.r;
		h1a.r=exp(h2.r)*cos(h2.i);
		h1a.i=exp(h2.r)*sin(h2.i);
		h1b.r=log(z.r*z.r+z.i*z.i)/2.0;						/* z2b=cplx_pow(z,f2b); */
		h1b.i=atan2(z.i,z.r);
		h2.r=f2b.r*h1b.r-f2b.i*h1b.i;
		h2.i=f2b.r*h1b.i+f2b.i*h1b.r;
		h1b.r=exp(h2.r)*cos(h2.i);
		h1b.i=exp(h2.r)*sin(h2.i);
		zoa.r=(h1a.r*z.r-h1a.i*z.i)-rx;						/* zoa=(h1a*z)-z */
		zoa.i=(h1a.r*z.i+h1a.i*z.r)-ry;
		zua.r=(f1a.r*h1a.r-f1a.i*h1a.i)+RenderInfo.par3.r;	/* zua=h1a*f1a+par2 */
		zua.i=(f1a.r*h1a.i+f1a.i*h1a.r)+RenderInfo.par3.i;
		zob.r=(h1b.r*z.r-h1b.i*z.i)-rx;						/* zob=(h1b*z)-z */
		zob.i=(h1b.r*z.i+h1b.i*z.r)-ry;
		zub.r=(f1b.r*h1b.r-f1b.i*h1b.i)+RenderInfo.par3.r;	/* zub=h1b*f1b+par2 */
		zub.i=(f1b.r*h1b.i+f1b.i*h1b.r)+RenderInfo.par3.i;
		zoa.r+=zob.r;zoa.i+=zob.i;							/* zoa=zoa+zob */
		zua.r+=zub.r;zua.i+=zub.i;							/* zua=zua+zub */
		tmp=zua.r*zua.r+zua.i*zua.i;						/* h2=zo/zu */
		h2.r=(zoa.r*zua.r+zoa.i*zua.i)/tmp;
		h2.i=(zoa.i*zua.r-zua.i*zoa.r)/tmp;
		z.r-=RenderInfo.par4.r*h2.r-RenderInfo.par4.i*h2.i;	/* z=z-par3*h2 */
		z.i-=RenderInfo.par4.r*h2.i+RenderInfo.par4.i*h2.r;
		if((zoa.r*zoa.r+zoa.i*zoa.i)>RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,z.r*z.r,z.i*z.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) obanz=n;
	return((UWORD)(h/GfxInfo.palscl));
}
