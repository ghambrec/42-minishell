
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/myLibft/include/my_libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>

# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define ITALIC "\033[3m"
# define NC "\033[0m"
# define GREY "\033[1;30m"

// typedef enum e_builtins
// {
// 	NO_BIN,
// 	BIN_ECHO,
// 	BIN_CD,
// 	BIN_PWD,
// 	BIN_EXPORT,
// 	BIN_UNSET,
// 	BIN_ENV,
// 	BIN_EXIT
// } t_buildins;

typedef enum e_token_type
{
	TT_CMD,
	TT_PIPE,
	TT_RE_INPUT,
	TT_RE_OUTPUT,
	TT_RE_APPEND,
	TT_HEREDOC,
	TT_AND,
	TT_OR,
	TT_PARENTESIS_OPEN,
	TT_PARENTESIS_CLOSE
}	t_token_type;


// hier noch ein error bool flag? zu beginn immer auf false und bei fehler auf true damit verkettungsoperatoren wissen
// ob befehl vorher erfolgreich bzw nicht erfolgreich war
typedef struct s_shell
{
	char	**env;
	int		exit_code;
}	t_shell;

typedef struct s_tokens
{
	t_token_type	token_type;
	char			**token;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_ast
{
	t_token_type	ttype;
	char			**cmd; // copy from t_tokens.token if its a command, otherwise NULL
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

void			ft_print2d(char **array2d);
t_tokens	*ft_newtoken(int token_type, char **token);
void			ft_printlist(t_tokens *token);


// TOKEN LIST
t_tokens	*ft_newtoken(int token_type, char **token);
void			ft_lstadd_back_token(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstlast_token(t_tokens *lst);
char			**get_commands(char **tokens);
char			**get_operator(char *operator);
void			split_token_type_set_type(
					char **all_tokens, t_tokens **token_list);
int				get_array_size(char **array);
void			handle_operator(
					char **all_tokens, t_tokens **token_list, int i);
int				get_token_type(char **token);
int				handle_redirects(
					char **all_tokens, t_tokens **token_list, int i);
char			**get_re_out(char **tokens);
char			**get_redirects_2d(char **all_tokens);
void			handle_commands(
					char **all_tokens, t_tokens **token_list, int i);
void			create_command_list(char *input, t_tokens **token_list);
void			copy_with_spaces(char *input, char *updatet_input);
char			*insert_spaces(char *input);
int				count_extra_spaces(char *input);
void			handle_operator_with_spaces(
					char *input, char *updatet_input, int *i, int *j);
void			handle_heredoc_and_append(
					char **all_tokens, t_tokens **token_list, int i);


// HANDLE_QUOTES
void			handle_quotes(char **command);
bool			handle_immediate_end(char **tokens, int i, char *merged);
void			merge_quotes(char **commands, int i);
void			shift_command_left(char **tokens, int i, int j);
char			*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);
void			merge_single_quotes(char **commands, int i);


//HANDLE ENVS
void			handle_envs(char **commands, int i);
void			handle_envs_in_string(char *string);
void			replace_env_vars(char *input, char *output);


// BOOL
bool			is_redirector(char *c);
bool			is_operator(char c);
bool			is_command(char *check);
bool			need_space(char c);
bool			is_heredoc_or_append(char c, char d);


// FREEING
void	free_split(char **split);

// EXECUTING
void	execute_command(char **cmd);

// BUILTINS
void		check_builtin(char **cmd);
void		builtin_echo(char **cmd);
void		builtin_pwd(void);
void		builtin_cd(char **cmd);

// SHELL-UTILS
t_shell		*get_shell(void);

// AST
void	ast_print(t_ast *ast);
t_ast	*ast_parse_logical_operator(t_tokens **tokens);
t_ast	*ast_create_tree(t_tokens **tokens);
t_ast	*ast_parse_pipe(t_tokens **tokens);
t_ast	*ast_parse_cmd(t_tokens **tokens);
t_ast	*ast_parse_parenthesis(t_tokens **tokens);
t_ast	*ast_create_node(t_token_type ttype, char **cmd, t_ast *left, t_ast *right);

#endif