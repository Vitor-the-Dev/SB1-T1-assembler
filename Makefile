# GCC used for compilation
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

# Montador means assembler in portuguese, this was done as project specifications
TARGET = Montador

SRCS = main.cpp \
       src/entities/scanner.cpp \
       src/entities/tokenizator.cpp \
       src/entities/readfilelines.cpp \
       src/domain/linker.cpp \
       src/domain/lexer.cpp \
       src/domain/assembler.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
