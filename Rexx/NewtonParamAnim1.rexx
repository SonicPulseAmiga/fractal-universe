/* $VER: FU ArexxAnim : NewtonParam
 */

options results

ADDRESS REXX_FU

say '[4m[32mFU-ArexxAnim : NewtonParam[31m[24m';say;

SetFormula 'NormNewton' '"Newton 0.0"'
if RC~=0 then call AppError('SetFormula',RC);

SetZoom '-2.38 -4.0 7.6 4.0';
if RC~=0 then call AppError('SetZoom',RC);

SetInside 'Normal 0 -1'
if RC~=0 then call AppError('SetInside',RC);

SetOutside 'Stripes -1 -1'
if RC~=0 then call AppError('SetInside',RC);

SetIter '1000';
if RC~=0 then call AppError('SetIter',RC);

SetParam '1 3.0 0.0';
if RC~=0 then call AppError('SetParam',RC);

SetParam '3 2.0 0.0';
if RC~=0 then call AppError('SetParam',RC);

frames=100
par2rs=-2.0;
par2re=0.7;
par2rst=(par2re-par2rs)/frames;
par2i=0.0;

do i=0 to frames
	name='swap:frames/pic.'right(i,3,'0');
	say 'Working on : ' name;

	SetParam '2' par2rs par2i;
	if RC~=0 then call AppError('SetParam',RC);

	RenderPicture;
	if RC~=0 then call AppError('RenderPicture',RC);

	SavePicture name '2'
	if RC~=0 then call AppError('SavePicture',RC);

	par2rs=par2rs+par2rst;
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
	exit
return
