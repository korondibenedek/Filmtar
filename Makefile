CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -g -std=c++11


OBJS = main.o filmtar.o menu.o film.o sajat_string.o
EXEC = filmtar

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Fájl szintű függőségek, hogy módosításkor újraforduljanak
main.o: main.cpp menu.h filmtar.h film.h sajat_string.h
filmtar.o: filmtar.cpp filmtar.h sajat_string.h film.h
menu.o: menu.cpp menu.h filmtar.h sajat_string.h film.h
film.o: film.cpp film.h sajat_string.h
sajat_string.o: sajat_string.cpp sajat_string.h

clean:
	rm -f $(OBJS) $(EXEC)