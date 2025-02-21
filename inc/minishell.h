
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/myLibft/include/my_libft.h"
# include <errno.h>
# include <limits.h>
// #include <readline/readline.h>
// #include <readline/history.h>


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
	CMD,
	PIPE,
	RE_INPUT,
	RE_OUTPUT,
	RE_APPEND,
	HEREDOC,
	AND,
	OR
} t_token_type;


// hier noch ein error bool flag? zu beginn immer auf false und bei fehler auf true damit verkettungsoperatoren wissen
// ob befehl vorher erfolgreich bzw nicht erfolgreich war
typedef struct s_shell
{
	char	**env;
	int		exit_code;
} t_shell;

typedef struct s_tokens
{
	t_token_type	token_type;
	char			**token;
	struct s_ctbl	*next;
} t_tokens;

typedef struct s_current_token
{
	t_tokens	*current;
} t_current_token;


typedef struct s_ast
{
	t_token_type	ttype;
	char			**cmd; // copy from t_tokens.token, if its a command otherwise NULL
	struct s_ast	*left;
	struct s_ast	*right;
} t_ast;

// FREEING
void	free_split(char **split);

// EXECUTING
void	execute_command(char **cmd);

// BUILTINS
void		check_builtin(char *program);
void		builtin_echo(char **cmd);
void		builtin_pwd(void);
void		builtin_cd(char **cmd);

// SHELL-UTILS
t_shell		*get_shell(void);

#endif