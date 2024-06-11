runheap:
	g++ -std=c++17 main.cpp -o main.out
	./main.out
runfib:
	g++ -g -Wall -o dijkstra_fib d_fibonacci.cpp FibonacciHeap.cpp structuresfib.cpp -std=c++11
	./dijkstra_fib