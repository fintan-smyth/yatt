/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yatt.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:59:14 by fsmyth            #+#    #+#             */
/*   Updated: 2025/07/04 00:04:12 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YATT_H
# define YATT_H

# include "libft.h"
# include <fcntl.h>
# include <termios.h>
# include <time.h>
# include <sys/time.h>
# include <errno.h>

# define ESC 27
# define BACKSPACE 127
# define BUFSIZE 256
# define POLL_NS 50000000
# define POLL_US 50000

# define MIN_WIDTH_SMALL 43
# define MIN_HEIGHT_SMALL 17
# define MIN_WIDTH_FULL 53
# define MIN_HEIGHT_FULL 19

# define BLACK 0
# define RED 1
# define GREEN 2
# define YELLOW 3
# define BLUE 4
# define MAGENTA 5
# define CYAN 6
# define WHITE 7

enum {
	M_WORDS = 0,
	M_NUMBERS,
	M_PUNC,
	M_LANG,
	M_KMODE,
	M_KEYCOLS,
	M_MAX,
};

enum {
	K_UP = 1,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
};

typedef enum {
	P_COMMA = 1,
	P_FSTOP = 2,
	P_SQUOTE = 4,
	P_DQUOTE = 8,
	P_PAREN = 16,
	P_BRACK = 32,
	P_BRACE = 64,
	P_ANGBRACK = 128,
	P_EXCLAM = 256,
	P_QUEST = 512,
	P_MAX = 1024,
}	e_punc;

typedef struct s_lang
{
	char	*name;
	char	**words;
	size_t	size;
}	t_lang;

typedef struct s_word t_word;

struct s_word
{
	t_word	*next;
	t_word	*prev;
	char	word[128];
	int		len;
	int		pos;
	char	input_buf[BUFSIZE];
};

typedef struct s_env
{
	struct termios	g_term_original;
	int				win_width;
	int				win_height;
	int				min_width;
	int				min_height;
}	t_env;

typedef struct s_options
{
	int		num_words;
	t_list	*lang_paths;
	t_list	*cur_lang;
	int		fingers[128];
	int		kmode;
	int		punc;
	u_int	punc_flags;
	int		numbers;
	int		full_keyboard;
}	t_options;

typedef struct s_menu
{
	int	selected;
	int	no_entries;
}	t_menu;

typedef struct s_typer
{
	t_word			*wordlist;
	t_word			*render_start;
	t_word			*cur_word;
	t_lang			lang;
	t_options		options;
	unsigned char	c;
	int				is_correct;
	int				cur_word_idx;
	int				inputs_count;
	int				incorrect_inputs;
	size_t			start_time;
	size_t			end_time;
	t_env			*env;
	int				last_display_cutoff;
	t_menu			menu_state;
}	t_typer;

void	store_term_settings(t_env *env);
void	set_term_settings(t_env *env);
void	reset_term_settings(t_env *env);
int		set_winsize(t_env *env);
void	cleanup(t_typer *tester);

char	*extract_lang_name(char *lang_path);
t_lang	load_language_file(char	*filename);
void	cleanup_lang(t_lang *lang);
t_word	*new_wordnode(char *str);
t_word	*wordlist_add_back(t_word **lst, t_word *word);
void	clear_wordlist(t_word **wordlist);
int		print_wordlist(t_typer *tester);
int		print_keyboard(t_typer *tester, int y, t_word *cur_word);
int 	print_keyboard_full(t_typer *tester, int y, t_word *cur_word);
void	select_words(t_typer *tester);

void	run_game(t_typer *tester);
void	game_loop(t_typer *tester);
void		render_game(t_typer *tester);

void	check_input(t_typer *tester, char c, t_word *cur_word);
double	calculate_raw_wpm(t_typer *tester);
double	calculate_net_wpm(t_typer *tester);
double	calculate_adj_wpm(t_typer *tester);
double	calculate_accuracy(t_typer *tester);
void	print_stats(t_typer *tester, int line);
void	render_stats(t_typer *tester);
int		stats_screen(t_typer *tester);

size_t	get_time_ms(void);
int		max_int(int a, int b);
int		ft_output_len(char *str);
int		clamp_int(int num, int min, int max);
int		print_str_centred(char *str, int row, int width);
void	draw_borders(t_typer *tester);
int		kbhit(void);
int		get_escape_char(char *sequence);
void	render_too_small(t_typer *tester);
int		win_too_small(t_env *env);
char	getchar_nb(t_typer *tester, void (*render)(t_typer *));
void	surround_string(char *str, char *set);
void	exec_render_func(t_typer *tester, void (*render)(t_typer *));

void	setup_default_fingers(t_options *tester);
void	pick_key_cols(t_typer *tester);
void	print_keyboard_picker(t_typer *tester);
void	render_options(t_typer *tester);

#endif // YATT_H
