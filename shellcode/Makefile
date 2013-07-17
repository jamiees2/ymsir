CC=/usr/bin/gcc
CFLAGS= -ggdb3
COMMON=
OBJS=eggshell.o
EXECUTABLE=exploit

all: main

main: $(OBJS)
	@printf "\033[0mLinking \033[1;37m$@ \033[1;37m.\033[0m.\033[1;30m.\033[0m\r"
	@$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE) -pthread
	@printf "\033[0mLinked \033[1;37m$@\033[1;37m.\033[J\033[0m\n"

.c.o:
	@printf "\033[0m$< \033[1;30m->\033[0m $@ \033[1;30m[ ]\033[0m   \r"
	@$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@
	@printf "\033[0m$< \033[1;30m->\033[0m $@ \033[1;30m[\033[1;32mX\033[1;30m]\033[0m\n"

clean:
	@printf "\033[0mErasing the old files.\n"
	@rm -f *.o *~ core $(EXECUTABLE)

