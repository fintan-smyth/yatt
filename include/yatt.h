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

typedef struct s_typer
{
	t_word			*wordlist;
	t_lang			lang;
	char			c;
	int				is_correct;
	int				num_words;
	int				wordno;
	int				inputs_count;
	int				incorrect_inputs;
	size_t			start_time;
	size_t			end_time;
	struct termios	g_term_original;
}	t_typer;
void	store_term_settings(t_typer *tester);

void	set_term_settings(t_typer *tester);
void	reset_term_settings(t_typer *tester);

t_word	*new_wordnode(char *str);
t_word	*wordlist_add_back(t_word **lst, t_word *word);
void	clear_wordlist(t_word **wordlist);
void	print_wordlist(t_word *wordlist, int wordno);
void 	print_keyboard(t_typer *tester);
void	select_words(t_typer *tester);

void	run_game(t_typer *tester);
void	game_loop(t_typer *tester);

void	check_input(t_typer *tester, char c, t_word *cur_word);
double	calculate_raw_wpm(t_typer *tester);
double	calculate_net_wpm(t_typer *tester);
double	calculate_adj_wpm(t_typer *tester);
double	calculate_accuracy(t_typer *tester);
int		display_stats(t_typer *tester);

size_t	get_time_ms(void);

#endif // YATT_H
