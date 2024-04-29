@echo off
cd /d "Frontend\code"

rem Compile all .cpp files and generate main.exe
g++ *.cpp -o main.exe

rem Check if compilation was successful
if %errorlevel% neq 0 (
    echo Compilation failed.
) else (
    echo Compilation successful. main.exe created.
)

pause
