@echo off

set SOURCE_DIR=%WORKING_DIR_ROOT%\src
set BUILD_DIR=%WORKING_DIR_ROOT%\build

set COMMON_COMPILER_FLAGS=-nologo -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -FC -Z7
set COMMON_LINKER_FLAGS= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib

mkdir %BUILD_DIR%
pushd %BUILD_DIR%

del %BUILD_DIR%\*.pdb > NUL 2> NUL

cl %COMMON_COMPILER_FLAGS% %SOURCE_DIR%\platform-layer\windows\win-32.cpp^
  /link %COMMON_LINKER_FLAGS%

popd
