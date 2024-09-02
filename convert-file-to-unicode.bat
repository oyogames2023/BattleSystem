@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

SET Extensions=-Include *.h, *.cpp

SET PowerShellCommand=powershell -NoProfile -Command

%PowerShellCommand% "Get-ChildItem -Path '.\Include', '.\Src' -Recurse -File %Extensions% | ForEach-Object { $content = Get-Content -Path $_.FullName; Set-Content -Path $_.FullName -Value $content -Encoding UTF8 }"

echo Convert done.
ENDLOCAL
