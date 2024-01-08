cls

del *.exe

del *.obj

del Log.txt

cl.exe .\*.cpp /c /EHsc

::rc.exe /i ..\..\..\include ..\..\..\resource\OGL.rc

link.exe *.obj *.res /SUBSYSTEM:WINDOWS user32.lib gdi32.lib kernel32.lib
