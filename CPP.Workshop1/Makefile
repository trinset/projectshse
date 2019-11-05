all: app

app: main.o my_sum.o
	g++ main.o my_sum.o

main.o: main.cpp
	g++ -c main.cpp

my_sum.o: my_sum.cpp
	g++ -c my_sum.cpp
