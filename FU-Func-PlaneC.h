/******************************************************************************
** FU-FUNC-PLANEC.h                                                          **
**---------------------------------------------------------------------------**
** Fractal Functions                                                         **
** for Fractal Universe                                                      **
**---------------------------------------------------------------------------**
** Version : V 1.2                                                           **
** Date    : 04.02.1993                                                      **
** Author  : Stefan Kost                                                     **
******************************************************************************/

UWORD FuncMJ(void)
{
	register double a;
	register complex_f z,w;
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;

	w.r=(z.r=rx)*z.r;w.i=(z.i=ry)*z.i;
	ob[0].r=z.r;ob[0].i=z.i;				/* Orbit */
	bofabs=999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		z.i=2.0*z.r*z.i+RenderInfo.par1.i;
		w.r=(z.r=w.r-w.i+RenderInfo.par1.r)*z.r;
		a=w.r+(w.i=z.i*z.i);
		if(a<=RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(z.r,z.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncMJ_I(void)
{
	register double a;
	register complex_i z,w,c;
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;
	LONG bailout=(LONG)(RenderInfo.bailout*2048.0);

	w.r=(z.r=(LONG)(rx*2048.0))*z.r;w.i=(z.i=(LONG)(ry*2048.0))*z.i;
	c.r=(LONG)(RenderInfo.par1.r*2048.0);c.i=(LONG)(RenderInfo.par1.i*2048.0);
	ob[0].r=rx;ob[0].i=ry;					/* Orbit */
	bofabs=999999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		z.i=((z.r*z.i)>>10)+c.i;
		w.r=((z.r=w.r-w.i+c.r)*z.r)>>11;
		a=w.r+(w.i=(z.i*z.i)>>11);
		if(a<=bailout)
		{
			ob[n].r=(double)z.r/2048.0;ob[n].i=(double)z.i/2048.0;	/* Orbit */
			if(a<bofabs)											/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor((double)z.r/2048.0,(double)z.i/2048.0,(double)w.r/2048.0,(double)w.i/2048.0,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor((double)z.r/2048.0,(double)z.i/2048.0,(double)w.r/2048.0,(double)w.i/2048.0); }
	return((UWORD)(h/GfxInfo.palscl));
}


UWORD FuncMJFn(void)
{
	register double a;
	register complex w,z,f,g;
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;

	w.r=(z.r=rx)*z.r;w.i=(z.i=ry)*z.i;
	ob[0].r=z.r;ob[0].i=z.i;				/* Orbit */
	bofabs=999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		f.r=w.r-w.i;									/* f=z^2 */
		f.i=2.0*z.r*z.i;
		z=TrigFunc1(z,z);								/* z=fn(z) */
		g.r=f.r+z.r+RenderInfo.par1.r;					/* z=z+f+c */
		w.i=(z.i=f.i+z.i+RenderInfo.par1.i)*z.i;
		a=(w.r=(z.r=g.r)*z.r)+w.i;
		if(a<RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(z.r,z.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncMJPower(void)
{
	register double a;
	register complex z,w;
	register complex h1,h2;
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;

	w.r=(z.r=rx)*z.r;w.i=(z.i=ry)*z.i;
	ob[0].r=z.r;ob[0].i=z.i;				/* Orbit */
	bofabs=999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		h1.r=log(w.r+w.i)/2.0;		/* z=cplx_pow(z,p2); */
		h1.i=atan2(z.i,z.r);
		h2.r=RenderInfo.par2.r*h1.r-RenderInfo.par2.i*h1.i;
		h2.i=RenderInfo.par2.r*h1.i+RenderInfo.par2.i*h1.r;
		w.r=(z.r=exp(h2.r)*cos(h2.i)+RenderInfo.par1.r)*z.r;
		a=w.r+(w.i=(z.i=exp(h2.r)*sin(h2.i)+RenderInfo.par1.i)*z.i);
		if(a<RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(z.r,z.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncMJWar(void)
{
	register double a;
	register complex z,w,b[2];
	UWORD h=0;
	UBYTE k=0,l=0;
	register UWORD n;

	w.r=(z.r=b[0].r=b[1].r=rx)*z.r;w.i=(z.i=b[0].i=b[1].i=ry)*z.i;
	ob[0].r=z.r;ob[0].i=z.i;				/* Orbit */
	bofabs=999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		z.i=b[l].i=2.0*z.r*z.i+b[l].i+RenderInfo.par1.i;
		w.r=(z.r=b[l].r=w.r-w.i+b[l].r+RenderInfo.par1.r)*z.r;
		a=w.r+(w.i=z.i*z.i);
		l=(l+1)%2;
		if(a<RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(z.r,z.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncSqrFn(void)
{
	register double a;
	register complex w,e;
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;

	e.r=rx;e.i=ry;
	ob[0].r=e.r;ob[0].i=e.i;				/* Orbit */
	bofabs=999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		e=TrigFunc1(e,e);
		w.r=e.r*e.r;w.i=e.i*e.i;
		e.i=2.0*e.r*e.i+RenderInfo.par1.i;
		w.r=(e.r=w.r-w.i+RenderInfo.par1.r)*e.r;
		a=w.r+(w.i=e.i*e.i);
		if(a<RenderInfo.bailout)
		{
			ob[n].r=e.r;ob[n].i=e.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(e.r,e.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(e.r,e.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncMJMan(void)					/* echtes Apfelmännchen !? */
{
	register double a;
	register complex z,w;
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;

	w.r=(z.r=rx)*z.r;w.i=(z.i=ry)*z.i;
	ob[0].r=z.r;ob[0].i=z.i;				/* Orbit */
	bofabs=999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		z.i=(1.0+RenderInfo.par1.r)*z.r*z.i-RenderInfo.par1.i;
		w.r=(z.r=w.r-w.i-RenderInfo.par1.r)*z.r;
		a=w.r+(w.i=z.i*z.i);
		if(a<RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(z.r,z.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncTrinomic(void)				/* TrinomicLogo !? */
{
	register double a;
	register complex z,w;
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;

	w.r=(z.r=rx)*z.r;w.i=(z.i=ry)*z.i;
	ob[0].r=z.r;ob[0].i=z.i;				/* Orbit */
	bofabs=999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		z.r=2.0*z.r*z.i+RenderInfo.par1.r;
		w.i=(z.i=w.r-w.i+RenderInfo.par1.i)*z.i;
		a=w.i+(w.r=z.r*z.r);
		if(a<RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(z.r,z.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncX3(void)
{
	register double a;
	register complex z,w;
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;

	w.r=(z.r=rx)*z.r;w.i=(z.i=ry)*z.i;
	ob[0].r=z.r;ob[0].i=z.i;				/* Orbit */
	bofabs=999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		z.i=z.i*(3.0*w.r-w.i)+RenderInfo.par1.i;
		w.r=(z.r=z.r*(w.r-3.0*w.i)+RenderInfo.par1.r)*z.r;
		a=w.r+(w.i=z.i*z.i);
		if(a<RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(z.r,z.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncX4(void)
{
	register double a;
	register complex z,w;
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;

	w.r=(z.r=rx)*z.r;w.i=(z.i=ry)*z.i;
	ob[0].r=z.r;ob[0].i=z.i;				/* Orbit */
	bofabs=999.99;bofz=0;					/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		z.i=4.0*z.r*z.i*(w.r-w.i)+RenderInfo.par1.i;
		w.r=(z.r=w.r*w.r-6.0*w.r*w.i+w.i*w.i+RenderInfo.par1.r)*z.r;
		a=w.r+(w.i=z.i*z.i);
		if(a<RenderInfo.bailout)
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(z.r,z.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}

UWORD FuncMagnet1(void)
{
	UWORD h=0;
	UBYTE k=0;
	register UWORD n;
	register complex z,w,h1,h2;
	register double a,t;

	z.r=rx;z.i=ry;
	ob[0].r=z.r;ob[0].i=z.i;				/* Orbit */
	bofabs=999.99;bofz=0		;			/* bei Inside=BoF60 | BoF61 */
	for(n=1;n<RenderInfo.z;n++)
	{
		h1.r=z.r*z.r-z.i*z.i+RenderInfo.par1.r-1.0;
		h1.i=2.0*z.r*z.i+RenderInfo.par1.i;
		h2.r=z.r+z.r+RenderInfo.par1.r-2.0;
		h2.i=z.i+z.i+RenderInfo.par1.i;
		t=h2.r*h2.r+h2.i*h2.i;
		z.r=(h1.r*h2.r+h1.i*h2.i)/t;
		z.i=(h1.i*h2.r-h2.i*h1.r)/t;
		t=z.r*z.r-z.i*z.i;
		w.i=(z.i=2.0*z.r*z.i)*z.i;
		a=w.i+(w.r=(z.r=t)*z.r);
		if((a<10000.0)&&((fabs(z.r-1.0)+fabs(z.i))>0.01))
		{
			ob[n].r=z.r;ob[n].i=z.i;	/* Orbit */
			if(a<bofabs)				/* bei Inside=BoF60 | BoF61 */
			{
				bofabs=a;bofz=n;
			}
		}
		else
		{
			h=GetOutsideColor(z.r,z.i,w.r,w.i,n);
			obanz=n;n=RenderInfo.z;k=1;
		}
	}
	if(!k) { obanz=n;h=GetInsideColor(z.r,z.i,w.r,w.i); }
	return((UWORD)(h/GfxInfo.palscl));
}
