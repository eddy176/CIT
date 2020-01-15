all:	babbler

mandel:	babbler.c
	gcc -std=c99 -m64 -Os -I/usr/include/lua5.2 babbler.c /usr/lib/x86_64-linux-gnu/liblua5.2.so -lm -o babbler

clean:
	rm -f babbler babbler.o