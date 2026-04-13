

jogo: actions.o prints.o click.o buttons.o game.o engine/main.c 
	gcc -Wall -ggdb $^ -o $@ -lncursesw

mac: actions.o prints.o click.o buttons.o game.o engine/main.c 
	gcc -Wall -g $^ -o jogo -lncurses

actions.o: engine/actions.c 
	gcc -Wall -ggdb $^ -c -o $@

prints.o: engine/prints.c
	gcc -Wall -ggdb $^ -c -o $@ 

click.o: engine/click.c
	gcc -Wall -ggdb $^ -c -o $@ 

buttons.o: engine/buttons.c
	gcc -Wall -ggdb $^ -c -o $@ 

game.o: engine/game.c
	gcc -Wall -ggdb $^ -c -o $@ 


# testes: actions.o prints.o click.o buttons.o game.o tests/test_main.c
#	gcc -Wall -g $^ -o test_solitario -lncurses -I/opt/homebrew/include -L/opt/homebrew/lib -lcunit

clean:
	-rm -f actions.o prints.o click.o buttons.o game.o jogo