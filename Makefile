#
main-1:	main-1.o
		g++ -o main-1 main-1.o

main-1.o:	main-1.cpp
		g++ -std=c++11 -g -c main-1.cpp
