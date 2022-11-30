run:
	./bin/pass_gen

release:
	clang src/main.c -std=c17 -Ofast -o bin/pass_gen

debug:
	clang src/main.c -std=c17 -g -o bin/pass_gen

clean:
	rm -r bin/pass_gen

copy: release
	cp ./bin/pass_gen ~/Coding/Hyperfine/C
