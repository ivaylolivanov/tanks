@echo off

set SOURCE_DIR=%WORKING_DIR_ROOT%\src
set BUILD_DIR=%WORKING_DIR_ROOT%\build

rem NOTE:
rem These example flags are left so we can have a reference for
rem what will in the future be necessary.
rem
rem set COMMON_COMPILER_FLAGS=-nologo -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -FC -Z7
rem set COMMON_LINKER_FLAGS= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib
set COMMON_COMPILER_FLAGS=-g -gcodeview
set COMMON_LINKER_FLAGS=-l user32.lib -l gdi32.lib -l winmm.lib

mkdir %BUILD_DIR%
pushd %BUILD_DIR%

del %BUILD_DIR%\*.pdb > NUL 2> NUL

clang %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%^
      %SOURCE_DIR%\platform-layer\windows\win-32.cpp^
      -o win-32.exe -v

popd
