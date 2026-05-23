CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -DMEMTRACE

SRCS = main.cpp film.cpp filmtar.cpp menu.cpp sajat_string.cpp memtrace.cpp 
OBJS = $(SRCS:.cpp=.o)
EXEC = filmtar_app

TEST_SRCS = test.cpp film.cpp filmtar.cpp menu.cpp sajat_string.cpp memtrace.cpp 
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXEC = filmtar_test

.PHONY: all clean test

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC) $(TEST_EXEC)