CC = g++
GTEST_DIR = gtest
CPPFLAGS = -I${GTEST_DIR}/include -I${GTEST_DIR}
TESTFILES = $(GTEST_DIR)/src/gtest-postfix.cc \
			$(GTEST_DIR)/src/gtest-regex_match.cc \
			$(GTEST_DIR)/src/gtest-expand.cc

all: main test

main: regex main.cpp
	$(CC) -o main.out main.cpp obj/regex.o

regex: regex.cpp
	$(CC) -c -Wall -pedantic regex.cpp -o obj/regex.o

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h 

gtest-all.o: 
	g++ $(CPP_FLAGS) -c ${GTEST_DIR}/src/gtest-all.cc -o obj/gtest-all.o

gtest_main.o: 
	g++ $(CPP_FLAGS) -c ${GTEST_DIR}/src/gtest_main.cc -o obj/gtest_main.o

gtest_main.a: gtest-all.o gtest_main.o
	ar -rv obj/libgtest.a obj/gtest-all.o obj/gtest_main.o

test: gtest_main.a $(TESTFILES)
	g++ $(CPPFLAGS) $(TESTFILES) obj/libgtest.a obj/regex.o -o testcases.out -lgtest -lpthread

clean:
	rm obj/*.o
	rm obj/*.a
	rm *.out
	
