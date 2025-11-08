CC = gcc
CFLAGS = -Iinclude -O2 -lm

SRC = src/main.c src/matrix.c src/svd.c src/image_utils.c
OUT = svd_compress

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)

