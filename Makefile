
NAME = pipex
SRC =	Pipex_M.c Pipex_utils_1.c Pipex_utils_2.c Pipex_utils_3.c
SRC_BONUS = Multiple_Pipex.c Multiple_Pipex_utils_1.c Multiple_Pipex_utils_2.c Multiple_Pipex_utils_3.c Pipex_utils_1.c Pipex_utils_2.c Pipex_utils_3.c get_next_line.c get_next_line_utils.c
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)
R        := $(shell tput -Txterm setaf 1)
G        := $(shell tput -Txterm setaf 2)
Y       := $(shell tput -Txterm setaf 3)

all: $(NAME)
	@echo $(G) "ALL functions are done!"

$(NAME): $(OBJS)
	@echo $(Y) Compiling: $< ... Done!
	@cc $(CFLAGS) $(OBJS) -o $@

%.o: %.c Pipex.h
	@echo $(Y) Compiling: $< ... Done!
	@cc $(CFLAGS) -c $<

bonus: ${OBJS_BONUS}
	@echo $(Y) Compiling: $< ... Done!
	@cc $(CFLAGS) $(OBJS_BONUS) -o $(NAME)

clean:
	@echo $(R) Cleaned
	@rm -f $(OBJS)

fclean: clean
	@echo $(R) Fully cleaned
	@rm -f $(NAME) $(OBJS_BONUS)

re: fclean all

.PHONY: clean fclean re bonus all