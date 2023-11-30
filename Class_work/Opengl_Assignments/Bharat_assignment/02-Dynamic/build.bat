cls

del *.obj
del *.exe
del *.txt

cl.exe /c /EHsc  /I ..\..\Include\ *.cpp

rc.exe /I ..\..\Include\ ..\..\Resources\Window.rc

rc.exe /I ..\Include\ ..\..\Resources\Anamika_.rc

link.exe *.obj ..\..\Resources\window.res user32.lib gdi32.lib kernel32.lib /OUT:..\..\bin\%~1.exe

del *.obj

..\..\bin\%~1.exe

