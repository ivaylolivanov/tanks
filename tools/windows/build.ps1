# TODO: remove later - "-Wno-writable-strings"
$CommonCompilerFlags = "-g", "-gcodeview", "-fno-rtti", "-O0", "-Werror", "-Wall", "-Wno-unused-variable", "-Wno-microsoft-anon-tag", "-Wno-writable-strings";
$CommonLinkerFlags   = "-l", "user32.lib", "-l", "gdi32.lib", "-l", "winmm.lib";

$BuildDir  = "$WorkingDirRoot\build";
$SourceDir = "$WorkingDirRoot\src";

if (!(Test-Path $BuildDir))
{
    New-Item -ItemType Directory -Path "$BuildDir";
}

Set-Location $BuildDir;

Remove-Item "$BuildDir\*.pdb" -ErrorAction SilentlyContinue;

clang @($CommonCompilerFlags)                        `
      @($CommonLinkerFlags)                          `
      "$SourceDir\platform-layer\windows\win-32.cpp" `
      -o tanks.exe -v;

Set-Location ..;
