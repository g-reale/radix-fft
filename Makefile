#---------------------------------
#			SETTINGS
#---------------------------------

# Compiler and compilation flags 
CC = g++
CFLAGS = -std=c++11 -Wall


# Specify the directory where your CPP files are located
SRCDIR = src

# Get all CPP files within the SRCDIR
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Include directory for HPP files
INCLUDEDIR = /include 

# Removes the trailing slashes in INCLUDEDIR (if they exist): $(INCLUDEDIR:%/=%)
# Formats each include directory with the -I flag for compilation: $(patsubst %,-I%,$(INCLUDEDIR:%/=%))
INCLUDES = $(patsubst %,-I%,$(INCLUDEDIR:%/=%))

# Aditional library dirs
LIBDIR = 

# Removes the trailing slashes in LIBDIR (if they exist): $(LIBDIR:%/=%)
# Formats each library directory with the -L flag for linking: $(patsubst %,-L%,$(LIBDIR:%/=%))
LINKDIR = $(patsubst %,-L%,$(LIBDIR:%/=%))


# Libraries for linking
LIBS = -lpulse-simple -lpulse -pthread -lncurses -lX11 -ljpeg

# Define the name of the executable
EXECUTABLE = bin/main




#---------------------------------
#			RULES
#---------------------------------

# Compiles the whole project
all: $(EXECUTABLE)

# Compiles the executable 
$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKDIR) -o $(EXECUTABLE) $(SOURCES) $(LIBS)

clean:
	rm -f $(EXECUTABLE)
.PHONY: clean
