# Makefile:  Build 'qs' querystring tool

prefix=/usr/local

# all:  just build qs
all: test qs

# qs:  build binary; simple recipe
qs: main.c src/aux.c src/kv.c src/uri.c
	cc -O3 -I include -o qs  main.c src/aux.c src/kv.c src/uri.c
	strip qs

install: qs
	install qs ${prefix}/bin/qs

test_kv: src/test_kv.c src/kv.c
	cc -I include -o test_kv  src/test_kv.c src/kv.c

test_uri: src/test_uri.c src/uri.c
	cc -I include -o test_uri  src/test_uri.c src/uri.c

test: test_kv test_uri
	./test_kv && rm test_kv
	./test_uri && rm test_uri

clean:
	rm -f a.out *.o
	rm -f qs test_kv test_uri

# eof