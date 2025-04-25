all: rfserver rfs

server: rfserver.c
	gcc rfserver.c -o rfserver

rfs: rfs.c
	gcc rfs.c -o rfs

clean:
	rm -f ./rfs ./rfserver