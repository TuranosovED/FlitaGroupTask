@echo off
 
set /p Count="Count of elements: "
set /p Iterator="Count of interations: "
set Iterator1=%Iterator%
:loop
if %Iterator%==0 goto end
set /a Iterator=Iterator-1
.\generator.exe %Count% &&.\gravity
goto loop
:end

:loop1
if %Iterator1%==0 goto end1
set /a Iterator1=Iterator1-1
.\generator.exe %Count% &&.\shaker.exe
goto loop1
:end1