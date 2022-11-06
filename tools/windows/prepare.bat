@echo off

for %%F in (%0) do set CURRENT_DIR=%%~dpF
call %CURRENT_DIR%dev-environment.bat
rem set working_dir_root=D:\Projects\tanks
set TOOLS_LOCATION=%WORKING_DIR_ROOT%\tools\windows

rem set vcvarsall="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

set PATH=%TOOLS_LOCATION%;%PATH%

call %COMPILER_PATH% x64

rem call emacs
cd %WORKING_DIR_ROOT%
