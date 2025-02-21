
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

typedef struct s_shell
{
	char	**env;
	int		exit_code;
} t_shell;

typedef struct s_tokens
{
	int				id;
	enum e_tokens	token_type;
	char			**token;
	struct s_ctbl	*next;
} t_tokens;


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