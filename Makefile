CC = g++
CFLAGS = -std=c++11 -Wall

# Specify the directory where your CPP files are located
SRCDIR = src

# Get all CPP files within the SRCDIR
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Define the name of the executable
EXECUTABLE = bin/main

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

