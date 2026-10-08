cls

del *.exe

g++ -mwindows -m64 -static -Wall -Wextra Template.cpp ListBoxWindow.cpp StatusBarWindow.cpp -o Template.exe
