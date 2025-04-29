## Copyright Julian Bottiglione 2025
## Hylozoa Engine test makefile 

all: build tests_run

build:
	cmake -B build/
	cmake --build build/
	make -C build/

tests_run:
	./build/testSuite

.PHONY: build tests_run
