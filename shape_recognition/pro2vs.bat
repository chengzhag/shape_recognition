::该脚本的功能是将当前文件夹下及其子文件夹下的qt pro文件转换为vs vcxproj文件，
::并将所生成的vcxproj文件中qt的绝对路径替换成QTDIR环境变量
@echo off
if "%QTDIR%"=="" (
    @echo "QTDIR" environment variable is not configured
    pause
    exit
)
set bootDir=%cd%
set tagName=temp
set tagSubEx=bat
set file=%tagName%.%tagSubEx%
@echo %cd%
for /r %%i in (*.pro) DO (
    @echo %%i
    call :create %%i
)
pause
cd %bootDir%
set delFile=del.bat
rem set /a flag=0
echo @echo off>%delFile%
rem echo set flag=^0>>%delFile%
echo for /r %%%%j in (*%file%) DO (>>%delFile%
echo call :delete %%%%j>>%delFile%
echo )>>%delFile%
rem echo set /a flag+=^1>>%delFile%
echo :delete>>%delFile%
echo del %%1>>%delFile%
call %delFile%
cd %bootDir%
del %delFile%
exit
:wait
if %flag% equ 1 (
@echo flag=%flag%
pause
del %delFile%
exit
) else (
@echo this is working
pause
goto wait
)
:create
cd %~dp1
echo @echo off>%file%
echo set expQTDIR=%%QTDIR%%>>%file%
echo %%QTDIR%%\bin\qmake -tp vc>>%file%
echo set tagEx=vcxproj>>%file%
echo for /r %%%%j in (*.vcxproj) DO (>>%file%
echo call :replace %%%%j>>%file%
echo )>>%file%
echo :replace>>%file%
echo setlocal Enabledelayedexpansion>>%file%
echo ren %%1 a.%%tagEx%%>>%file%
echo for /f "tokens=*" %%%%s in (a.%%tagEx%%) do (>>%file%
echo set var=%%%%s>>%file%
echo set var=!var:%%expQTDIR%%=%%%%QTDIR%%%%!>>%file%
echo echo !var!^>^>b.%%tagEx%%>>%file%
echo )>>%file%
echo del %%~nx1>>%file%
echo ren b.%%tagEx%% %%~nx1>>%file%
echo del a.%%tagEx%%>>%file%
echo endlocal>>%file%
echo exit>>%file%
start %file%
:continue