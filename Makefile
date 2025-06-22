all: compile link

compile:
	g++ -Isrc/include -c main.cpp cell.cpp

link:
	g++ main.o cell.o -o main.exe -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

	