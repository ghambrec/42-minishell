
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/myLibft/include/my_libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_token_type
{
	tt_CMD,
	tt_PIPE,
	tt_RE_INPUT,
	tt_RE_OUTPUT,
	tt_RE_APPEND,
	tt_HEREDOC,
	tt_AND,
	tt_OR,
	tt_PARENTESIS_OPEN,
	tt_PARENTESIS_CLOSE
};

typedef struct s_token_type
{
	enum e_token_type	token_type;
	char				**token;
	struct s_token_type	*next;
}	t_token_type;

void			ft_print2d(char **array2d);
t_token_type	*ft_newtoken(int token_type, char **token);
void			ft_printlist(t_token_type *token);


//Token List
t_token_type	*ft_newtoken(int token_type, char **token);
void			ft_lstadd_back_token(t_token_type **lst, t_token_type *new);
t_token_type	*ft_lstlast_token(t_token_type *lst);
char			**get_commands(char **tokens);
char			**get_operator(char *operator);
void			split_token_type_set_type(
					char **all_tokens, t_token_type **token_list);
int				get_array_size(char **array);
void			handle_operator(
					char **all_tokens, t_token_type **token_list, int i);
int				get_token_type(char **token);
int				handle_redirects(
					char **all_tokens, t_token_type **token_list, int i);
char			**get_re_out(char **tokens);
char			**get_redirects_2d(char **all_tokens);
void			handle_commands(
					char **all_tokens, t_token_type **token_list, int i);
void			create_command_list(char *input, t_token_type **token_list);

//HandleQuotesZ
void			handle_quotes_and_envs(t_token_type *token_list);
char			*get_quote_string(char **command, int i);
void			handle_doule_quotes(char **command, int i);
char			*remove_char(char *string, char c);
int				c_count(char *string, char c);

//Bool
bool			is_redirector(char *c);
bool			is_operator(char c);
bool			is_command(char *check);

// FREEING
void	free_split(char **split);

// EXECUTING
void	execute_command(char **cmd);

#endif