# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g3

SRC = ft_isalpha.c \
	  ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_strlen.c \
	  ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_strlcpy.c \
	  ft_strlcat.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strncmp.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strnstr.c \
	  ft_atoi.c \
	  ft_calloc.c \
	  ft_match_wc.c \
	  ft_strdup.c \
	  ft_strnum.c \
	  ft_strndup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_iswhitespace.c \
	  ft_strwhitespace.c \
	  get_next_line_bonus.c\
	  ft_printf/format_char_bonus.c \
	  ft_printf/format_hex_bonus.c \
	  ft_printf/format_int_bonus.c \
	  ft_printf/format_ptr_bonus.c \
	  ft_printf/format_str_bonus.c \
	  ft_printf/format_unsigned_bonus.c \
	  ft_printf/format_utils_bonus.c \
	  ft_printf/parse_format_bonus.c \
	  ft_printf/utils_bonus.c \
	  ft_printf/ft_printf_bonus.c \
	  ft_qsort.c \
	  ft_strcmp.c \
	  ft_lst_to_arr.c \
	  ft_strtol.c \
	  ft_extend_line.c \

OBJ = $(SRC:.c=.o)

BONUS_SRC = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstdel_next.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lst_exists.c \

BONUS_OBJ = $(BONUS_SRC:.c=.o)

NAME = libft.a

all: $(NAME) bonus

# Link object files to create the executable
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

clean: 
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all
.PHONY: all clean fclean re bonus
