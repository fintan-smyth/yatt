/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:59:14 by fsmyth            #+#    #+#             */
/*   Updated: 2025/06/29 17:46:58 by fsmyth           ###   ########.fr       */
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

typedef struct s_lang
{
	char	**words;
	size_t	size;
}	t_lang;

typedef struct s_word t_word;

struct s_word
{
	t_word	*next;
	t_word	*prev;
	char	*word;
	int		len;
	int		pos;
	char	input_buf[BUFSIZE];
};

typedef struct s_env
{
	struct termios	g_term_original;
	int				win_width;
	int				win_height;

}	t_env;

typedef struct s_typer
{
	t_word			*wordlist;
	t_word			*render_start;
	t_lang			lang;
	char			c;
	int				is_correct;
	int				num_words;
	int				cur_word_idx;
	int				inputs_count;
	int				incorrect_inputs;
	size_t			start_time;
	size_t			end_time;
	t_env			*env;
	int				last_display_cutoff;
}	t_typer;

void	store_term_settings(t_env *env);
void	set_term_settings(t_env *env);
void	reset_term_settings(t_env *env);
void	set_winsize(t_env *env);

t_word	*new_wordnode(char *str);
t_word	*wordlist_add_back(t_word **lst, t_word *word);
void	clear_wordlist(t_word **wordlist);
int		print_wordlist(t_typer *tester);
void 	print_keyboard(t_typer *tester, int y);
void	select_words(t_typer *tester);

int		run_game(t_typer *tester);
void	game_loop(t_typer *tester);
int		render_game(t_typer *tester, int finished);

void	check_input(t_typer *tester, char c, t_word *cur_word);
double	calculate_raw_wpm(t_typer *tester);
double	calculate_net_wpm(t_typer *tester);
double	calculate_adj_wpm(t_typer *tester);
double	calculate_accuracy(t_typer *tester);
int		display_stats(t_typer *tester, int line);

size_t	get_time_ms(void);
int		max_int(int a, int b);

#endif // YATT_H
