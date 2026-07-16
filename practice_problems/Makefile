# Makefile for compiling and running any C++ program using threads
# Usage: make run FILE=your_cpp_file (without .cpp extension)

CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall

# Default target
run:
	$(CXX) $(CXXFLAGS) $(FILE).cpp -o $(FILE)
	./$(FILE)

# Clean up executables
clean:
	rm -f $(FILE)
cleanall:
	rm -f *.o *.out *.exe
