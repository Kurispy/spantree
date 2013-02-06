spantree : graph.o main.o 
	g++ -ansi -Wall -O3 -o spantree  graph.o main.o 

graph.o : graph.cpp graph.h 
	g++ -ansi -Wall -O3 -c graph.cpp

main.o : main.cpp graph.h 
	g++ -ansi -Wall -O3 -c main.cpp

clean:
	rm -f spantree graph.o main.o 