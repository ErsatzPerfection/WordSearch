This is my solution for the wordsearch kata.

It supports finding words that are contained entirely within other words 
as well as multiple instances of the same word as can be seen in test3.

I also wrote it in such a way that it should work on rectangles as well.

This uses only standard libraries and as such should be buildable with any C++ compiler.
On debian/ubuntu gcc and make are included in the package build-essentials
They can be acquired by running the following in the command line
	sudo apt-get update
	sudo apt-get install build-essential

Once built to run the program simply call the program with the name of the text file to solve for as an argument:
	
Alternatively if no argument is provided the program will ask for the name of the input file.