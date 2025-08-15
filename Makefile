main: main.cpp
	g++ main.cpp -Llib -Iinclude -lraylib -o main

clean:
	rm -f main
