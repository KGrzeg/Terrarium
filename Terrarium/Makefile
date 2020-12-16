PREFIX=[Path_to_SFML]

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')

build: ## Build the binary
	g++ -c -g $(SOURCES) -I$(PREFIX)/include
	g++ $(shell find $(SOURCEDIR) -name '*.o') -o Terrarium.out -L$(PREFIX)/lib -lsfml-graphics -lsfml-window -lsfml-system
	#g++ -g -L$(PREFIX)/lib -I$(PREFIX)/include -lsfml-graphics -lsfml-window -lsfml-system -o rcktsim.out main.cpp
	
run: build ## Build and run the binary
	LD_LIBRARY_PATH=$(PREFIX)/lib ./Terrarium.out

debug: build
	gdb ./Terrarium.out

.PHONY: help
help: ## Print this message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

