del *.txt
Clang-Tidy  -extra-arg=-std=c99 ..\src\app.c >> .\TODO_CLANG-TIDY.txt
cppcheck ..\src\app.c --output-file=TODO_CPPCHECK.txt
