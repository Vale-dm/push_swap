CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= push_swap

SRC_PATH = src/
OBJ_PATH = obj/
INCLUDE_PATH = includes/
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC		= main.c \
		input_check.c input_check_utils.c \
		initialization.c \
		stack.c \
		swap.c push.c rotate.c reverse_rotate.c \
		sort_tiny.c sort.c \
		position.c cost.c do_move.c \
		utils.c main_utils.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I$(INCLUDE_PATH) -I$(LIBFT_DIR)

all: $(OBJ_PATH) $(LIBFT) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re