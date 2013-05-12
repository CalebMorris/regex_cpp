main: regex main.cpp
	g++ -o main.out main.cpp obj/regex.o

regex: regex.cpp
	g++ -c -Wall -pedantic regex.cpp -o obj/regex.o

clean:
	rm obj/*.o
	rm *.out