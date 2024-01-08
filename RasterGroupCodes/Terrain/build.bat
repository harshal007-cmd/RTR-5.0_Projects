cls

del *.exe

del *.obj

del Log.txt

cl.exe .\Terrain.cpp /c /EHsc /I..\..\..\include 

::rc.exe /i ..\..\..\include ..\..\..\resource\OGL.rc

link.exe *.obj ..\..\..\resource\*.res /SUBSYSTEM:WINDOWS user32.lib gdi32.lib kernel32.lib
