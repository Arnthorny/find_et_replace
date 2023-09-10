CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
NAME = fetr
CFLAGS = -Wall -Werror -Wextra -pedantic

# builds your executable
all: main.h $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

#Implicit rule that automatically builds executable and .o files
$(NAME): $(OBJ)

# forces recompilation of all source files
re: oclean all

# deletes all Emacs and Vim temporary files along with the executable
clean:
	$(RM) *~ $(NAME) 

# deletes the object files
oclean:
	$(RM) $(OBJ) 

# deletes all Emacs and Vim temporary files, the executable, and the object files
fclean: clean oclean

.PHONY: all clean oclean fclean re
