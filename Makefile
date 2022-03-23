
all:
	clang++ q3.cpp -pthread -o q3
	clang++ semtest.cpp -pthread -o semtest
	clang++ settest.cpp -pthread -o settest

clean:
	rm -f q3 *~
	rm -f semtest *~
test:
	clang++ -fsanitize=thread q3.cpp -pthread -o q3
	clang++ -fsanitize=thread semtest.cpp -pthread -o semtest
	clang++ -fsanitize=thread settest.cpp -pthread -o settest


