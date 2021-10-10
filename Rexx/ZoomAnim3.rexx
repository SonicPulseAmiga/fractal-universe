/* $VER: FU ArexxAnim : Zoom3
 * Formula : magnet
 */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim : Zoom3[31m[24m';say;

/* which formula ?? */
SetFormula 'NormVarPlaneC Magnet1z'
if RC~=0 then call AppError('SetFormula',RC);

SetInside 'Normal 0 -1'
if RC~=0 then call AppError('SetInside',RC);

SetOutside 'Stripes -1 -1'
if RC~=0 then call AppError('SetInside',RC);

SetIter '100';
if RC~=0 then call AppError('SetIter',RC);

xs1=-2.0;ys1=-2.5;xs2=4.0;ys2=2.5
xe1=1.8934;ye1=-1.7549;xe2=2.1944;ye2=-1.5196

frames=100
x1step=(xe1-xs1)/frames
x2step=(xe2-xs2)/frames
y1step=(ye1-ys1)/frames
y2step=(ye2-ys2)/frames

say 'Steps      : ' x1step y1step x2step y2step;

do i=0 to frames
	x1step=(xe1-xs1)/10
	x2step=(xe2-xs2)/10
	y1step=(ye1-ys1)/10
	y2step=(ye2-ys2)/10

	name='swap:frames/zoom3.'right(i,3,'0');
	say 'Working on : ' name;
	say 'Zoom       : ' xs1 ys1 xs2 ys2;

	SetZoom xs1 ys1 xs2 ys2;
	if RC~=0 then call AppError('SetZoom',RC);

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	xs1=xs1+x1step;
	xs2=xs2+x2step;
	ys1=ys1+y1step;
	ys2=ys2+y2step;
end

ActivateFU;
if RC~=0 then call AppError('ActivateFU',RC);

ExitFU;
if RC~=0 then call AppError('ExitFU',RC);

exit

AppError:procedure
	cmd=arg(1);
	ret=arg(2);
	say '[4m[33mApplication Error[31m[24m';say;
	say 'Command 'cmd' failed with Returncode 'ret;
	select
		when ret='1' then say '	=> unknown command';
		when ret='2' then say '	=> unknown parameter';
		otherwise say '	=> unknown returncode';
	end
	say;
return
