/* $VER: FU ArexxAnim : Iter2
 */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim : Iter2[31m[24m';say;

zyklen=5
SetIter zyklen;
if RC~=0 then call AppError('SetIter',RC);

SetInside 'MagnifyReIm 500 -1'
if RC~=0 then call AppError('SetInside',RC);

SetFormula 'NormVarPlaneC Mandel'
if RC~=0 then call AppError('SetFormula',RC);

x1=-0.11267605633803;x2=0.0;
y1=-0.70459290187891;y2=-0.60313152400835;
SetZoom x1 y1 x2 y2;
if RC~=0 then call AppError('SetZoom',RC);

frames=150

do i=0 to frames
	name='swap:frames/iter2.'right(i,3,'0');
	say 'Working on : ' name;

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	zyklen=zyklen+1;
	SetIter zyklen;
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
