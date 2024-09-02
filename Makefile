CC = cc

CFLAGS = -Wall -Wextra -Werror  -fsanitize=address -g3

NAME = ft_ls

HEAD = header/

SRCS = 	src/main.c \
		src/parsing.c \
		src/libft.c \
		src/util.c \
		src/execute.c\

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)


.DEFAULT_GOAL : all

all : $(NAME)
	
.c.o : $(SRCS)
	$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@ 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean :
	rm -rf $(OBJS) $(DEPS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

-include $(DEPS)

.PHONY : all re clean fclean bonus