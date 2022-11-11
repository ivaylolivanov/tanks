@echo off

for %%F in (%0) do set CURRENT_DIR=%%~dpF
call %CURRENT_DIR%dev-environment.bat
set TOOLS_LOCATION=%WORKING_DIR_ROOT%\tools\windows

set PATH=%TOOLS_LOCATION%;%PATH%

cd %WORKING_DIR_ROOT%
