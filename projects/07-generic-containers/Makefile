CXX=clang++
CXXFLAGS=-std=c++23 -Werror -Wsign-conversion
TIDY_FLAGS=-checks=bugprone-*,-bugprone-easily-swappable-parameters,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=*
TIDY_CONFIG=-config='{CheckOptions: [{key: cppcoreguidelines-special-member-functions.AllowMissingMoveFunctions, value: true}]}'
TIDY_EXCLUDE=test.cpp StudentTest.cpp

# Header-only templates — no .cpp files for classes
# Only main.cpp and test.cpp are compiled.

all: demo
	./demo

demo: main.o
	$(CXX) $(CXXFLAGS) $^ -o demo

grade: test tidy

test: TestRunner.o student_test
	$(CXX) $(CXXFLAGS) TestRunner.o -o test
	./test

student_test: StudentTestRunner.o
	$(CXX) $(CXXFLAGS) $^ -o student_test
	@count=$$(grep -c '^[[:space:]]*TEST_CASE[[:space:]]*(' StudentTest.cpp); \
	if [ $$count -lt 20 ]; then \
		echo "ERROR: StudentTest.cpp must contain at least 20 test cases (found $$count)"; \
		exit 1; \
	fi
	./student_test

StudentTestRunner.o: StudentTest.cpp doctest.h
	$(CXX) $(CXXFLAGS) --compile StudentTest.cpp -o StudentTestRunner.o

TestRunner.o: test.cpp doctest.h
	$(CXX) $(CXXFLAGS) --compile test.cpp -o TestRunner.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) --compile main.cpp -o main.o

tidy:
	clang-tidy $(filter-out $(TIDY_EXCLUDE), $(wildcard *.cpp) $(wildcard *.hpp)) $(TIDY_FLAGS) $(TIDY_CONFIG) -- $(CXXFLAGS)

clean:
	rm -f *.o demo test student_test

.PHONY: all test clean tidy student_test grade
