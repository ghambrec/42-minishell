
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/myLibft/include/my_libft.h"
# include <stdio.h>
# include <stdbool.h>
// # include <readline/readline.h>
// # include <readline/history.h>

enum e_tokens
{
	CMD,
	PIPE,
	RE_INPUT,
	RE_OUTPUT,
	RE_APPEND,
	HEREDOC,
	AND,
	OR
};

typedef struct s_tokens
{
	enum e_tokens	token_type;
	char			**token;
	struct s_tokens	*next;
}	t_tokens;

void		ft_print2d(char **array2d);
t_tokens	*ft_newtoken(int token_type, char **token);
void		ft_printlist(t_tokens *token);


//Token List
t_tokens	*ft_newtoken(int token_type, char **token);
void		ft_lstadd_back_token(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstlast_token(t_tokens *lst);
char		**get_commands(char **tokens);
char		**get_operator(char *operator);
void		split_tokens_set_type(char **all_tokens, t_tokens **token_list);
int			get_array_size(char **array);
void		handle_operator(char **all_tokens, t_tokens **token_list, int i);
int			get_token_type(char **token);
int			handle_redirects(char **all_tokens, t_tokens **token_list, int i);
char		**get_re_out(char **tokens);
char		**get_redirects_2d(char **all_tokens);
void		handle_commands(char **all_tokens, t_tokens **token_list, int i);
void		create_command_list(char *input, t_tokens **token_list);


//Bool
bool		is_redirector(char *c);
bool		is_operator(char c);
bool		is_command(char *check);

#endif