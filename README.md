[![Linux Build test](https://github.com/vinissou/OldRetriever/actions/workflows/linux_test.yml/badge.svg)](https://github.com/vinissou/OldRetriever/actions/workflows/linux_test.yml) [![Windows Build Test](https://github.com/vinissou/OldRetriever/actions/workflows/win_build.yml/badge.svg)](https://github.com/vinissou/OldRetriever/actions/workflows/win_build.yml)

# OldRetriever

An old project for quick searching really huge text files, the code is a mess with a lot unfinished features and experiments but it actually works in a brute force kind of way. And it has some weird features that are useful sometimes, like searching between limiters (like {}, (), etc), the positions of the search term in the file and returning a whole line and a range of characters ignoring lines. 

It's so simple, that just for fun I once tested in OpenWatcom and was able to compile it all the way to ancient MS-DOS versions and Windows 3.1. I might do that again one of these days, but I need to set up a lot of virtual machines for that. 

I stopped working on it when I discovered that Silver Search existed (https://github.com/ggreer/the_silver_searcher) and nowadays I use ripgrep-all for most of my file searching needs (https://github.com/phiresky/ripgrep-all), so even if I had finished it would be kinda redundant.


I provided a release with the compiled executables, if you like to run weird EXEs from the internet in your computer.



## Building 
In Windows, Linux or BSDs¹, just compile BUILD.c and run it. 

More systems will be added later.

For building on Windows: I recommend using the mingw-winlibs-llvm-ucrt package from Scoop, it's the most painless way to install compilers on Windows. 

¹NetBSD and OpenBSD have some minor I/O problems that I'm working on.


## Testing
I use the free IMDB databases files to test it: 
https://datasets.imdbws.com/

I will provide the list of commands here, once the project is more mature.

