@echo off
 
set /p Count="Count of elements: "

.\generator.exe %Count%
.\gravity
.\shaker