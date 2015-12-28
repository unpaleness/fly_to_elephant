CC         = g++
CFLAGS     = -std=c++11 -O2 -c -Wall -Wextra
LFLAGS     = -std=c++11
SOURCES    = code/main.cpp \
			 code/control.cpp \
             code/algorithm_brute_force.cpp \
             code/algorithm_genetic.cpp
OBJECTS    = $(SOURCES:code%.cpp=obj%.o)
EXECUTABLE = fly_to_elephant

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

$(OBJECTS):
	$(CC) $(CFLAGS) $(@:obj%.o=code%.cpp) -o $@

.PHONY: clean
clean:
	rm -rfv $(OBJECTS) $(EXECUTABLE)
