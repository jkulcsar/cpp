@echo off

rem Adds a word to the dictionary

if x%1==x goto NoWord

echo %1 >> unjumble.dat
type unjumble.dat | sort > unjumble.dat
goto Done

:NoWord
echo Usage: addword {word}

:Done
echo+
