
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/myLibft/include/my_libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <signal.h>

# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define ITALIC "\033[3m"
# define GREY "\033[1;30m"
# define PURPLE "\033[0;35m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLACK "\033[0;30m"
# define NC "\033[0m"
# define CLEAR_LINE "\033[2K"


# ifndef PRINT_TREE
#  define PRINT_TREE 0
# endif

# define PIPE_READ 0
# define PIPE_WRITE 1

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
	char	**envp;
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
void			ft_print2d_gha(char **array2d);
t_tokens		*ft_newtoken(int token_type, char **token);
void			ft_printlist(t_tokens *token);
char			*ft_strcpy(char *dest, const char *src);

// INPUT HANDLING
void	handle_input(char *input);
void	handle_tty_input(void);
void	handle_nontty_input(void);


// TOKEN LIST
t_tokens		*ft_newtoken(int token_type, char **token);
void			ft_lstadd_back_token(t_tokens **lst, t_tokens *new);
t_tokens		*ft_lstlast_token(t_tokens *lst);
int				get_token_type(char **token);
int				handle_redirects(
					char **all_tokens, t_tokens **token_list, int *i);
char			**get_re_out(char **tokens);
char			**get_redirects_2d(char **all_tokens);
void			handle_commands(
					char **all_tokens, t_tokens **token_list, int *i);
int				create_command_list(char *input, t_tokens **token_list);
char			*insert_spaces(char *input);
int				handle_heredoc_and_append(
					char **all_tokens, t_tokens **token_list, int *i);
char			**split_into_tokens(char *input);
void			handle_operator(char **all_tokens,
					t_tokens **token_list, int *i);
char			*ft_getenv(char *env_key);
char			**ft_sort_2d_strings(char **strings2d);
void 			replace_char(char *str, char old_char, char new_char);

// HANDLE_QUOTES
void			handle_quotes(t_tokens **tokenList);
char			*remove_quotes(char *commands);
void			check_quotes(char c, t_quote_state *state);

//HANDLE ENVS
char			*replace_env_vars(char *output);

//Join Commands
void			join_commands(t_tokens *token_list);

// BOOL
bool			is_redirector(char *c);
bool			is_operator(char c);
bool			is_command(char *check);
bool			need_space(char c);
bool			is_heredoc_or_append(char c, char d);
bool			is_in_quotes(char *input, int i);

// FREEING
void			free_split(char **split);
void			free_tokens(t_tokens *tokens);
void			free_ast(t_ast *ast);

// BUILTINS
bool			check_builtin(char **cmd);
int				builtin_echo(char **cmd);
int				builtin_pwd(void);
int				builtin_cd(char **cmd);
int				builtin_export(char **cmd);
int				builtin_env(char **cmd);
int				builtin_unset(char **cmd);
void			builtin_exit(char **cmd);

// SHELL-UTILS
t_shell			*get_shell(void);
int				init_shell(int argc, char **argv, char **envp);
int	exit_shell(t_shell *shell, bool call_exit);

// Errors
bool			parsing_errors(char *input);
int				env_error(char *key, char *builtin);
int				check_for_parse_errors(t_tokens *token);


// AST
void			ast_print(t_ast *ast);
t_ast			*ast_parse_logical_operator(t_tokens **tokens);
t_ast			*ast_create_tree(t_tokens **tokens);
t_ast			*ast_parse_pipe(t_tokens **tokens);
t_ast			*ast_parse_cmd(t_tokens **tokens);
t_ast			*ast_parse_parenthesis(t_tokens **tokens);
void			ast_parse_redirections(t_ast *cmd, t_tokens **tokens);
t_ast			*ast_create_node(t_token_type ttype, char **cmd,
					t_ast *left, t_ast *right);
void			ast_add_redirection(t_ast *ast, t_token_type ttype,
					char **token);
bool			is_redirection(t_token_type ttype);

// EXECUTION
void			execute_command(char **cmd);
int				open_redirections(t_redirection *redirect);
void			exec_ast(t_ast *ast);
int				exec_cmd(t_ast *ast);
int				exec_builtin(t_ast *ast);
int				exec_pipe(t_ast *ast);
int				redirect_heredoc(t_redirection *redirect);

// SIGNALS
void	init_signals(void);
void	set_sigaction(int signum, void (*handler)(int));
void	handle_sigint_interactive(int signum);
void	handle_sigint_child(int signum);

#endif