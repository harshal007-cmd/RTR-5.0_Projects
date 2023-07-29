cls

del *.obj
del *.exe
del *.txt

cl.exe /c /EHsc  /I ..\Include\ *.cpp

rc.exe /I ..\Include\ ..\Resource\Window.rc

link.exe *.obj \Resource\windoe.res user32.lib gdi32.lib kernel32.lib /OUT:..\bin\%~1.exe

del *.obj

..\bin\%~1.exe

