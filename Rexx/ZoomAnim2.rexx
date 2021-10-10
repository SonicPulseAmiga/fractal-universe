/* $VER: FU ArexxAnim : Zoom2
 */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim : Zoom2[31m[24m';say;

/* which formula ?? */
SetFormula 'NormVarPlaneC Magnet1p'
if RC~=0 then call AppError('SetFormula',RC);

SetInside 'Normal 0 -1'
if RC~=0 then call AppError('SetInside',RC);

SetOutside 'Stripes -1 -1'
if RC~=0 then call AppError('SetInside',RC);

SetIter '500';
if RC~=0 then call AppError('SetIter',RC);

xs1=-1.77993697;ys1=-0.0166376552;xs2=-1.7469221245;ys2=0.0166376552
xe1=-1.7863294368;ye1=-0.0003070386;xe2=-1.7857169573;ye2=0.0003070386

frames=100
x1step=(xe1-xs1)/frames
x2step=(xe2-xs2)/frames
y1step=(ye1-ys1)/frames
y2step=(ye2-ys2)/frames

say 'Steps      : ' x1step y1step x2step y2step;

do i=0 to frames
	name='swap:frames/zoom2.'right(i,3,'0');
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
