CC = g++
GTEST_DIR = gtest
CPPFLAGS = -I${GTEST_DIR}/include -I${GTEST_DIR}
XPPFLAGS = -Wall -pedantic -g
TESTFILES = $(GTEST_DIR)/src/gtest-postfix.cc \
			$(GTEST_DIR)/src/gtest-regex_match.cc \
			$(GTEST_DIR)/src/gtest-expand.cc

all: main.out test.out

obj/main.o:
	$(CC) -c $(XPPFLAGS) main.cpp -o obj/main.o

main.out: obj/regex.o obj/main.o
	$(CC) -o main.out obj/main.o obj/regex.o

obj/regex.o: regex.cpp
	$(CC) -c $(XPPFLAGS) regex.cpp -o obj/regex.o

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h 

obj/gtest-all.o: 
	g++ $(CPP_FLAGS) -c ${GTEST_DIR}/src/gtest-all.cc -o obj/gtest-all.o

obj/gtest_main.o: 
	g++ $(CPP_FLAGS) -c ${GTEST_DIR}/src/gtest_main.cc -o obj/gtest_main.o

obj/gtest_main.a: obj/gtest-all.o obj/gtest_main.o
	ar -rv obj/libgtest.a obj/gtest-all.o obj/gtest_main.o

test.out: obj/gtest_main.a $(TESTFILES)
	g++ $(CPPFLAGS) $(TESTFILES) obj/libgtest.a obj/regex.o -o testcases.out -lgtest -lpthread

clean:
	rm obj/*.o
	rm obj/*.a
	rm *.out
	
