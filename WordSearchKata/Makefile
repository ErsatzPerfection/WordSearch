all: clean wordsearch test
wordsearch:
	g++ WordSearchKata.cpp -o wordsearch
clean:
	rm -rf wordsearch
test:
	./wordsearch test1.txt > t1a.txt
	./wordsearch test2.txt > t2a.txt
	./wordsearch test3.txt > t3a.txt
	./wordsearch test4.txt > t4a.txt
	diff answer1.txt t1a.txt
	diff answer2.txt t2a.txt
	diff answer3.txt t3a.txt
	diff answer4.txt t4a.txt