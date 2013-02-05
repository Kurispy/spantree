spantree : graph.o main.o 
	g++ -ansi -Wall -g -o spantree  graph.o main.o 

graph.o : graph.cpp graph.h 
	g++ -ansi -Wall -g -c  graph.cpp

main.o : main.cpp graph.h 
	g++ -ansi -Wall -g -c  main.cpp

clean:
	rm -f spantree graph.o main.o 