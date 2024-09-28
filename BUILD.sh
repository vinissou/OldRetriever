# tested on Debian, Alpine Linux and OpenBSD(more on that later) for now
# TODO change to cc on OpenBSD
dos2unix *
dos2unix modules/*
gcc -Wall -Wextra -pedantic -std=c99 -O3 app.c -o retriever
