# TODO: remove later - "-Wno-writable-strings"
# TODO: Investigate "-nodefaultlibs"; Without it, on Windows 11, the Windows defender detects it as Wacatac.B!ml trojan
$CommonCompilerFlags = @(
    "-g",
    "-gcodeview",
    "-fno-rtti",
    "-O0",
    "-Werror",
    "-Wall",
    "-Wno-unused-variable",
    "-Wno-microsoft-anon-tag",
    "-Wno-writable-strings",
    "-nodefaultlibs",
    "-DWIN32_DEBUG",
    "-DWIN32_DEBUG_SOUND");

$CommonLinkerFlags = @(
    "-l", "user32.lib",
    "-l", "gdi32.lib",
    "-l", "winmm.lib");

$GameName = 'tanks.exe';

$BuildDir  = "$WorkingDirRoot\build";
$SourceDir = "$WorkingDirRoot\src";

function IsInGitRepo
{
    param(
        [Parameter(Mandatory=$true)]
        [string]$Directory
    )

    try
    {
        Set-Location -Path $Directory -ErrorAction Stop;
        git rev-parse --is-inside-work-tree;

        return 0;
    }
    catch
    {
        return 1;
    }
}

function Build
{
    param(
        [Parameter(Mandatory=$true)]
        [string]$workingDirectory,
        [string]$entryPoint
    )

    $clangExecutable = (Get-Command -Name clang -CommandType Application).Source `
        | Select-Object -First 1;

    $clangArguments = @(
        $CommonCompilerFlags
        $CommonLinkerFlags
        "$entryPoint"
        "-o${GameName}"
    );

    $setLocationStatus = Set-Location -Path "$workingDirectory";
    if ($setLocationStatus -ne $null)
    {
        Write-Host "Failed to change location to $workingDirectory";
        return 1;
    }

    $buildStatus = & "$clangExecutable" @clangArguments;

    return $buildStatus;
}

function main
{
    $scriptDir = $PSScriptRoot;

    $isInGitRepo = IsInGitRepo -Directory "$scriptDir";
    if (-not $isInGitRepo) { return 1; }

    $gitRoot = git rev-parse --show-toplevel;
    $workingDir = "${gitRoot}/build";
    $sourceDir = "${gitRoot}/src";
    $buildTargetFilepath = "${sourceDir}/platform-layer/windows/win-32.cpp";

    Remove-Item "$workingDir"    `
        -Recurse -Force -Verbose `
        -ErrorAction SilentlyContinue;
    New-Item -Path "$workingDir" -ItemType Directory -Force;

    $buildStatus = Build -workingDirectory "$workingDir" `
        -entryPoint "$buildTargetFilepath";
    if ($buildStatus -ne $null)
    {
        return 2;
    }

    return 0;
}

main;
