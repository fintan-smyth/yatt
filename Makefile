CC = cc

CFLAGS = -Wall -Wextra -I ./include

DBG_FLAGS =		-g3 \
				# -fsanitize=address \

SRC_DIR := ./src

BUILD_DIR:= ./build

SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/term.c \
	  $(SRC_DIR)/words.c \
	  $(SRC_DIR)/stats.c \
	  $(SRC_DIR)/game.c \
	  $(SRC_DIR)/utils.c \
	  $(SRC_DIR)/options.c \

OBJ = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRC:.c=.o))

NAME = yatt

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(BUILD_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(DBG_FLAGS) $(OBJ) -o $(NAME) -L ./libft -lft

$(OBJ): $(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $^ -o $@

$(LIBFT):
	make -C libft/ bonus

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf build/
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
.PHONY: all clean fclean re mand bonus
