all: clean compile run

compile: main.cpp OperatingSystem/OperatingSystem.cpp FileSystemEntity/FileSystemEntity.cpp Directory/Directory.cpp File/File.cpp OperatingSystem/OperatingSystem.h FileSystemEntity/FileSystemEntity.h Directory/Directory.h File/File.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o program main.cpp OperatingSystem/OperatingSystem.cpp FileSystemEntity/FileSystemEntity.cpp Directory/Directory.cpp File/File.cpp -std=c++11

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