main: main.o n-queens.o
	g++ -o main main.o n-queens.o
	clear

main.o: main.cpp n-queens.h

n-queens.o: n-queens.cpp n-queens.h

clean:
	rm -f main.o n-queens.o 