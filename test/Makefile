CC         = g++
CFLAGS     = -std=c++11 -O2 -c -Wall -Wextra
LFLAGS     = -std=c++11 -lboost_unit_test_framework
SOURCES    = code/algorithm_test.cpp
             # code/algorithm_brute_force_test.cpp
             # code/algorithm_genetic_test.cpp
OBJECTS    = $(SOURCES:code%.cpp=obj%.o)
EXECUTABLE = fly_to_elephant_test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

$(OBJECTS):
	$(CC) $(CFLAGS) $(@:obj%.o=code%.cpp) -o $@

.PHONY: clean
clean:
	rm -rfv $(OBJECTS) $(EXECUTABLE)
