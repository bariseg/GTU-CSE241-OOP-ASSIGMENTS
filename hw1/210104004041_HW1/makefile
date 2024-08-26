all: clean compile run

compile: main.cpp util.cpp util.hpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o program main.cpp util.cpp -std=c++11

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./program
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f program