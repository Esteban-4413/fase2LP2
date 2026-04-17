

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


# TESTES

TEST_FILES = tests/test_main.c tests/test_actions.c tests/test_game.c tests/test_buttons.c

testes: actions.o prints.o click.o buttons.o game.o $(TEST_FILES)
	gcc -Wall -g $^ -o test_solitario -lncurses -I/opt/homebrew/include -L/opt/homebrew/lib -lcunit
	./test_solitario


clean:
	-rm -f actions.o prints.o click.o buttons.o game.o jogo test_solitario