NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address 

INC = philosophers.h
SRC = philo.c\
	parsing.c\
	utils.c\
	thread_executer.c\
	eat_think_sleep.c\
	check_death.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;92mPhilo is ready.\033[0m"

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

f: all clean
	clear
	@echo "\033[0;92mPhilo is ready.\033[0m"

clean:
	rm -f $(OBJ)
	@echo "\033[0;93mObject files removed.\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[0;93mThe object files and the executable are removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re f
