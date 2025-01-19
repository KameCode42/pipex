NAME		= pipex
LIBFT		= ./libraries/libft/libft.a

LIBC		= ar rcs
CC			= gcc
RM			= rm -f

FLAGS		= -Wall -Wextra -Werror -Iinc

SRCS 		= ./src/check_error.c \
			./src/find_path.c \
			./src/init_pipex.c \
			./src/pipex.c \

OBJS 		= $(SRCS:.c=.o)

.c.o:
			@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all :		$(LIBFT) $(NAME)

$(NAME) :	${OBJS} ${LIBFT} 
			@echo "Building pipex..."
			@${CC} ${OBJS} ${LIBFT} $(FLAGS) -o ${NAME}

$(LIBFT) :
			@echo "Building libft..."
			@make -C libraries/libft > /dev/null 2>&1

clean:
			@echo "Cleaning..."
			@rm -f $(OBJS)
			@make clean -C libraries/libft > /dev/null 2>&1

fclean:		clean
			@echo "Cleaning all..."
			@rm -f $(NAME)
			@make fclean -C libraries/libft > /dev/null 2>&1

re: 		fclean all
