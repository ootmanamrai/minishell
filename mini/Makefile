CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
NAME = minishell
SRCS = main.c linkd_list.c utils.c utils1.c parss.c utils2.c utils3.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)
$(NAME): $(OBJS)
	@make all -C ./libft
	$(CC)  $(CFLAGS) $(OBJS) ./libft/libft.a -lreadline  -o $(NAME)  
	
clean:
	@rm -f $(OBJS)
	@make clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	@ rm -f ./libft/libft.a
re: fclean all
