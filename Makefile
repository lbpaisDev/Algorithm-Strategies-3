
p2: main.c
	gcc-8 -std=c11 -g -Wall -Wextra -O0 "main.c" -lm -o p2

clean: 
	rm p2
