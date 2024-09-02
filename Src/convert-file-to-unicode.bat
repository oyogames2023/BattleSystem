@echo off
setlocal enabledelayedexpansion

REM 定义文件扩展名
set "extensions=h cpp hpp json"

REM 遍历所有子目录
for /r %%f in (*.*) do (
    REM 获取文件扩展名
    set "ext=%%~xf"
    set "ext=!ext:~1!"

    REM 检查是否在我们定义的扩展名列表中
    for %%e in (%extensions%) do (
        if /i "!ext!"=="%%e" (
            REM 输出当前处理的文件
            echo Converting %%f to Unicode...
            
            REM 使用 powershell 转换编码为 UTF-8 (Unicode)
            powershell -Command "Get-Content -Path '%%f' | Set-Content -Path '%%f.tmp' -Encoding Unicode"
            
            REM 替换原始文件
            move /Y "%%f.tmp" "%%f"
        )
    )
)

echo All files have been converted to Unicode encoding.
pause
