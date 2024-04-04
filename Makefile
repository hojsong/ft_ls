CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP

NAME = ft_ls

HEAD = header/

SRCS = 	src/main.c \
		src/parsing.c \
		src/libft.c \
		src/util.c \
		src/execute.c\

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

-include $(DEPS)

.DEFAULT_GOAL : all

all : $(NAME)
	
# .c.o :
# 	$(CC) $(CFLAG) -I $(HEAD) -c $< -o $@ 

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) -o $(NAME) $(OBJS)

clean :
	rm -rf $(OBJS) $(DEPS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean bonus