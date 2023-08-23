# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Libraries to link
LIBS = -lpthread -lcurl -lssl -lcrypto

# Source files
SRCS = \
    CUrlDownloader.cpp \
    HTTPProtocol.cpp \
    FileVerify.cpp \
    main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = QuickDownloader

# Default target
all: $(TARGET)

# Rule for generating object files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for generating the executable
$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Clean
clean:
    rm -f $(OBJS) $(TARGET)
