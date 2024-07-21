#!make -f

# i change the clang compiler to ensure that all C++ support and libraries are automatically loaded.
CXX=clang++
# c++11: use the C++11 standard.
# -Werror: Treat all compiler warnings as errors.
# -Wsign-conversion: Warn about possible errors in sign conversion.
CXXFLAGS=-std=c++11 -Werror
# -Wsign-conversion
# Check for full memory leaks, Show all types of memory leaks, and Exit with exit code 99 in case of memory leak.
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp

# replace all the cpp files in SOURCES variable to .o
OBJECTS=$(subst .cpp,.o,$(SOURCES))

# run the demo exe that we create
run:   test demo
	./demo
	./test
# ./demo
# ./tidy
demo: Demo.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) $^ -o demo
# demo: Demo.o $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) $^ -o demo


test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test
	
