@echo off
setlocal enabledelayedexpansion

:: Get the current directory where the batch file is executed
set SCRIPT_DIR=%~dp0

:: Define the root directory and output directory using the script directory
set ROOT_DIR=%SCRIPT_DIR%Protos
set OUTPUT_DIR=%ROOT_DIR%\CPlusPlus

:: Define the paths for protoc.exe
set PROTOC=%SCRIPT_DIR%Bin\Windows\protoc.exe
set PROTO_PATHS=Common;Combat;Item;Config

:: Include the root directory itself
set INCLUDE_PATHS=-I"%ROOT_DIR%"

:: Build the include paths based on proto subdirectories
for %%p in (%PROTO_PATHS%) do (
    set INCLUDE_PATHS=!INCLUDE_PATHS! -I"%ROOT_DIR%\%%p"
)

echo INCLUDE_PATHS: !INCLUDE_PATHS!

:: Compile all .proto files recursively
for /r "%ROOT_DIR%" %%f in (*.proto) do (
    echo Compiling %%f...
    "%PROTOC%" --cpp_out="%OUTPUT_DIR%" !INCLUDE_PATHS! "%%f"
)

echo Compilation finished!
