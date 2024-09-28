Clang-Tidy  -extra-arg=-std=c99 ..\app.c >> .\TODO_CLANG-TIDY.txt
cppcheck ..\app.c --output-file=TODO_CPPCHECK.txt
