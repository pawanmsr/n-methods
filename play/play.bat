@REM compile and run on Windows
@echo off

@REM use prefix for idenfication
set prefix=
set file_extension=.cpp
set binary_extension=.exe

if [%1]==[] (
    echo Provide the problem number such as a, b, . . .
    exit 1
)

set filename=%prefix%%1%file_extension%
set binary=%1%binary_extension%

g++ --std=c++2a -DLOCAL %filename% -o %binary%
