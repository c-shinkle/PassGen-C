run:
	./bin/pass_gen

build:
	clang src/main.c -std=c17 -Ofast -o bin/pass_gen

debug:
	clang src/main.c -std=c17 -g -o bin/pass_gen

clean:
	rm -r bin/pass_gen
