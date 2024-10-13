CC= g++ -std=c++17
APPNAME= poke327
SOURCES= Screen/screen.cpp \
		 PokemonData/PokemonData.cpp \
		 Parser/fileParser.cpp \
		 Map/biome.cpp \
		 Map/map.cpp \
		 Map/mapGeneration.cpp \
		 Map/point.cpp \
		 Map/worldGeneration.cpp \
		 Data-Structures/priorityQueue.cpp \
		 Characters/NPCMovement.cpp \
		 Characters/playerMovement.cpp \
		 Battles/battles.cpp \
		 Pokemon/Pokemon.cpp \
		 poke327.cpp
BINDIR= bin
OBJECTS = $(SOURCES:%.cpp=$(BINDIR)/%.o)
TARGET= $(BINDIR)/$(APPNAME)
CCFLAGS= -Wall -Werror

.PHONY: clean all

all: $(TARGET)

$(TARGET): bin $(OBJECTS) 
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(TARGET) -lcurses

bin/%.o: src/%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

# Create a bin directory which mirrors the source directory
bin: 
	mkdir bin 
	for dir in src/*; do \
		if [ -d $${dir} ]; then \
			mkdir bin/$${dir##*/}; \
		fi \
	done
	
clean:
	rm -rf bin