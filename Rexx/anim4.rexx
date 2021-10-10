/* FU Arexxtester */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim[31m[24m';say;

SetIter '10';
if RC~=0 then call AppError('SetIter',RC);

xs1=-2.0;ys1=-2.5;xs2=4.0;ys2=2.5
xe1=1.8934;ye1=-1.7549;xe2=2.1944;ye2=-1.5196

frames=50

do i=0 to frames
	xstep=(xe2-xe1)/10
	ystep=(ye2-ye1)/10

	name='xh3:frames/MAGNETZOOM.'right(i,3,'0');
	say 'Working on : ' name;
	say 'Zoom       : ' xe1 ye1 xe2 ye2;

	SetZoom xe1 ye1 xe2 ye2;
	if RC~=0 then call AppError('SetZoom',RC);

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	xe1=xe1-xstep;
	xe2=xe2+xstep;
	ye1=ye1-ystep;
	ye2=ye2+ystep;

	if xe1<xs1 and xe2>xs2 and ye1<ys1 ans ye2>ys2 then i=frames
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
