CC = gcc
CFLAGS = -g -O2 -msse3 -fPIC
LDFLAGS = -shared -lm

libcoul.so: coul_o3.c coul_o4.c coul_o5.c coul_sse.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)

clean:
	/bin/rm libcoul.so
