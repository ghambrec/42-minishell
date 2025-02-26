
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/myLibft/include/my_libft.h"
# include <errno.h>
# include <limits.h>
// #include <readline/readline.h>
// #include <readline/history.h>

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