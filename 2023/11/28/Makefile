# CXX := g++
# CXX := clang++

all: parseuint8.o parseuint8_rs.o unit benchmark

benchmark: benchmarks/benchmark.cpp parseuint8.o parseuint8_rs.o
	$(CXX) -std=c++17 -O3 -Wall -o benchmark benchmarks/benchmark.cpp parseuint8.o parseuint8_rs.o -Iinclude -Ibenchmarks

unit: tests/unit.cpp parseuint8.o parseuint8_rs.o parseuint8_rs.o
	$(CXX) -std=c++17 -Wall -Wextra -O3 parseuint8.o parseuint8_rs.o -o unit tests/unit.cpp -Iinclude

parseuint8.o: src/parseuint8.cpp include/parseuint8.h
	$(CXX) -std=c++17 -O3 -Wall -Wextra -Wconversion -c src/parseuint8.cpp -Iinclude

parseuint8_rs.o: src/parseuint8_rs.rs
	rustc -C opt-level=3 --crate-type=lib --emit obj src/parseuint8_rs.rs

clean:
	rm -f parseuint8.o parseuint8_rs.o unit benchmark benchmark-clang isaacs_files.txt
