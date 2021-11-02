# -*-Makefile-*-
all : main
	clear
	./main

main: Account.o Savings.o Checkings.o Transaction.o main.o
	g++ Account.o main.o Savings.o Checkings.o Transaction.o -o main

Account.o : Account.cpp Account.h
	g++ -c -std=c++17 Account.cpp

Savings.o: Savings.cpp Savings.h
	g++ -c -std=c++17 Savings.cpp

main.o: main.cpp Savings.h Checkings.h Transaction.h Account.h
	g++ -c -std=c++17 main.cpp

Checkings.o: Checkings.cpp Checkings.h
	g++ -c -std=c++17 Checkings.cpp

Transaction.o: Transaction.cpp Transaction.h Checkings.h
	g++ -c -std=c++17 Transaction.cpp

clean:
	rm -f *.o main
	clear
