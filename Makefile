all:
	g++ -std=c++20 main.cpp -o main.out -I $(CURDIR)/include

run: all
	./main.out

clean:
	rm -f main.out