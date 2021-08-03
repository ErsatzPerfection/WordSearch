HOW TO RUN:
Once built to run the program simply call the program with the name of the text file to solve for as an argument, alternatively if no argument is provided the program will ask for the name of the input file.
I have included a makefile which when run with "make" will build the solution and run my test cases.

REQUIREMENTS:
This uses only standard libraries and as such should be buildable with any C++ compiler.
On debian/ubuntu g++and make are included in the package build-essentials
They can be acquired by running the following in the command line
	sudo apt-get update
	sudo apt-get install build-essential

FEATURES:
It supports finding words that are contained entirely within other words 
as well as multiple instances of the same word as can be seen in test3.
I also wrote it in such a way that it should work on rectangles as well.