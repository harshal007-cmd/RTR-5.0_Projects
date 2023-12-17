cls

del *.obj
del *.exe
del *.txt

cl.exe /c /EHsc  /I ..\Include\ *.cpp


link.exe *.obj /OUT:%~1.exe

del *.obj

%~1.exe

