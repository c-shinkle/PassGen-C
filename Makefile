all:
	clang src/main.c -o bin/pass_gen

clean:
	rm -r bin/pass_gen
