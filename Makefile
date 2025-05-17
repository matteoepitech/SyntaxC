##
## DEL PROJECT, 2025
## Makefile
## File description:
## Syntax C Makefile
##

GREEN		:= \033[0;32m
YELLOW		:= \033[0;33m
RED    		:= \033[0;31m
RESET		:= \033[0m

SRC		:= $(shell find src -name "*.c")
OBJ		:= $(SRC:.c=.o)
NAME		:= syntaxc
COMPIL		:= gcc
CFLAGS		:= -Wall -Wextra -Werror -Wpedantic -I./include/ -g

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(GREEN)[SYNTAXC] Starting compilation...$(RESET)\n"
	@$(COMPIL) $(CFLAGS) -o $(NAME) $(OBJ)
	@printf "$(GREEN)[SYNTAXC]  Compilation done!$(RESET)\n"

%.o: %.cpp
	@printf "$(YELLOW)[SYNTAXC]  Compiling $<...$(RESET)\n"
	@$(COMPIL) $(CFLAGS) -c $< -o $@
	@printf "$(GREEN)[SYNTAXC]  Compiled $< successfully!$(RESET)\n"

clean:
	@printf "$(RED)[SYNTAXC]  Cleaning object files...$(RESET)\n"
	@rm -f $(OBJ)

fclean: clean
	@printf "$(RED)[SYNTAXC]  Removing executable...$(RESET)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
