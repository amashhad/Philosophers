NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf
SRC			=	main inits monitor routine time_manager print_utils general_utils safe_inits free_func
SRCS		=	$(addsuffix .c, $(SRC))
OBJ_DIR		=	obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC:=.o))


all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) $(CFLAGS) -pthread -o $(NAME)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJ_DIR)
fclean: clean
				$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
