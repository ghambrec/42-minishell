
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/myLibft/include/my_libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>

# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define ITALIC "\033[3m"
# define NC "\033[0m"
# define GREY "\033[1;30m"
# define PURPLE "\033[0;35m"

# ifndef PRINT_TREE
#  define PRINT_TREE 0
# endif

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

typedef struct	s_redirection
{
	t_token_type			ttype;
	char					*filename;
	struct s_redirection	*next; // wird z.b. gebraucht fuer [< infile grep "hallo" >outfile1 >outfile2] TODO: test, does this work?
}	t_redirection;

typedef struct	s_ast
{
	t_token_type	ttype;
	char			**cmd;
	t_redirection	*redirect;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_quote_state
{
	char	*input;
	int		j;
	bool	in_single_quotes;
	bool	in_double_quotes;
}	t_quote_state;

void			ft_print2d(char **array2d);
void	ft_print2d_gha(char **array2d);
t_tokens		*ft_newtoken(int token_type, char **token);
void			ft_printlist(t_tokens *token);
char			*ft_strcpy(char *dest, const char *src);

// TOKEN LIST
t_tokens		*ft_newtoken(int token_type, char **token);
void			ft_lstadd_back_token(t_tokens **lst, t_tokens *new);
t_tokens		*ft_lstlast_token(t_tokens *lst);
char			**get_commands(char **tokens);
char			**get_operator(char *operator);
void			create_token_list(
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
char			**split_into_tokens(char *input);

// HANDLE_QUOTES
void			handle_quotes(t_tokens **tokenList);
char			*remove_quotes(char *commands);

//HANDLE ENVS
void			handle_envs(char **commands, int i);
void			handle_envs_in_string(char *string);
char			*replace_env_vars(char *output);


// BOOL
bool			is_redirector(char *c);
bool			is_operator(char c);
bool			is_command(char *check);
bool			need_space(char c);
bool			is_heredoc_or_append(char c, char d);
bool			is_in_quotes(char *input, int i);

// FREEING
void	free_split(char **split);
void	free_tokens(t_tokens *tokens);
void	free_ast(t_ast *ast);

// EXECUTING
void	execute_command(char **cmd);

// BUILTINS
void		check_builtin(char **cmd);
void		builtin_echo(char **cmd);
void		builtin_pwd(void);
void		builtin_cd(char **cmd);

// SHELL-UTILS
t_shell		*get_shell(void);

// Errors
bool	parsing_errors(char *input);

// AST
void	ast_print(t_ast *ast);
t_ast	*ast_parse_logical_operator(t_tokens **tokens);
t_ast	*ast_create_tree(t_tokens **tokens);
t_ast	*ast_parse_pipe(t_tokens **tokens);
t_ast	*ast_parse_cmd(t_tokens **tokens);
t_ast	*ast_parse_parenthesis(t_tokens **tokens);
void	ast_parse_redirections(t_ast *cmd, t_tokens **tokens);
t_ast	*ast_create_node(t_token_type ttype, char **cmd, t_ast *left, t_ast *right);
char	**ast_dup_tokens(char **tokens);
void	ast_add_redirection(t_ast *ast, t_token_type ttype, char **token);

// EXECUTION
void	exec_ast(t_ast *ast);

#endif