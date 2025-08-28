CC = cc

CFLAGS = -Wall -Wextra -I ./include -O0

DBG_FLAGS =		-g3 \
				# -fsanitize=address \
				# -pg \

SRC_DIR := ./src
BUILD_DIR:= ./build
CONFIG_DIR:= ${HOME}/.config/yatt
BIN_DIR:= ${HOME}/.local/bin

SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/term.c \
	  $(SRC_DIR)/words.c \
	  $(SRC_DIR)/stats.c \
	  $(SRC_DIR)/game.c \
	  $(SRC_DIR)/utils.c \
	  $(SRC_DIR)/input_log.c \
	  $(SRC_DIR)/options.c \
	  $(SRC_DIR)/keys.c \
	  $(SRC_DIR)/handle_args.c \
	  $(SRC_DIR)/parse_config.c \

OBJ = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRC:.c=.o))

NAME = yatt

LIBFT = libft/libft.a

all: $(NAME)

install: $(NAME)
	@mkdir -p $(CONFIG_DIR)
	@cp -n -v ./default.cfg $(CONFIG_DIR)/yatt.cfg
	@cp -fr  ./lang $(CONFIG_DIR)
	@cp -vf ./yatt $(BIN_DIR)/yatt

$(NAME): $(LIBFT) $(BUILD_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(DBG_FLAGS) $(OBJ) -o $(NAME) -L ./libft -lft -lncursesw

$(OBJ): $(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $^ -o $@

$(LIBFT):
	make -C libft/ bonus

$(BUILD_DIR):
	@mkdir -p $@

clean:
	rm -rf build/
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
.PHONY: all clean fclean re install
