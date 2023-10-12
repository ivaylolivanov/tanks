$global:ScriptPath = $MyInvocation.MyCommand.Path;
$global:CurrentDir = Split-Path $ScriptPath -Parent;

$global:DevEnvironment = Join-Path "$CurrentDir" "dev-environment.ps1";
. "$DevEnvironment";

$global:ToolsLocation  = Join-Path "$WorkingDirRoot" "tools\windows";

$env:PATH = "$ToolsLocation;$env:PATH";
Set-Location "$WorkingDirRootRoot";
