a.out: main.c
	gcc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./a.out

clean:
	rm -rf a.out

exec:
	./a.out
