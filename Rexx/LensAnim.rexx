/* $VER: FU ArexxAnim : Lens
 */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim : Lens[31m[24m';say;

SetIter '50';
if RC~=0 then call AppError('SetIter',RC);

x1=-2.5;y1=-1.5;x2=1.0;y2=1.5
SetZoom x1 y1 x2 y2;
if RC~=0 then call AppError('SetZoom',RC);

xl=1.0;yl=0.5
xlstep=-0.1;ylstep=-0.05

frames=30

do i=0 to frames
	name='swap:frames/Lens.'right(i,3,'0');
	say 'Working on : ' name;
	say 'Lens Position : ' xl yl;

	SetParam '1' xl yl; 
	if RC~=0 then call AppError('SetParam',RC);

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	xl=xl+xlstep;
	yl=yl+ylstep;
end

ActivateFU;
if RC~=0 then call AppError('ActivateFU',RC);

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
