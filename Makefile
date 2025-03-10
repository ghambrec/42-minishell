
# ---------- MAIN ---------- #
NAME := minishell
CC := cc
INCLUDE_DIR := ./inc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR) -g

# ---------- LIB ---------- #
LIB_DIR = ./lib
LIBFT_DIR = $(LIB_DIR)/myLibft
LIBFT_NAME = libft.a
LIBFT_FULL = $(LIBFT_DIR)/$(LIBFT_NAME)

# ---------- SOURCES ---------- #
SOURCE_DIRS = src \
				src/builtins \
				src/shell_utils \
				src/ast \
				src/parsing \
				src/freeing

VPATH = $(SOURCE_DIRS)

SOURCES = main.c main2.c

# SHELL_UTILS
SOURCES += get_shell.c

# PARSING
SOURCES += bools.c \
			commands.c \
			create_tokens.c \
			dquotes.c \
			envs.c \
			insert_spaces.c \
			operator.c \
			redirects.c \
			remove_quotes.c \
			split_tokens.c \
			token_list.c \
			utils.c \
			utils2.c \
			check_errors.c

# FREEING
SOURCES += free_split.c \
			free_tokens.c

# AST
SOURCES += ast_create_node.c \
			ast_create_tree.c \
			ast_parse_functions.c \
			ast_print.c \
			ast_dup_tokens.c \
			ast_add_redirection.c

# BUILTINS
SOURCES += check_builtin.c \
			builtin_echo.c \
			builtin_pwd.c \
			builtin_cd.c

# EXECUTING
SOURCES += execute_command.c

# ---------- OBJECTS ---------- #
OBJECT_DIR = obj
OBJECTS = $(addprefix $(OBJECT_DIR)/, $(SOURCES:.c=.o))

# ---------- COLORS AND STUFF ---------- #
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
NC = \033[0m

# ---------- RULES ---------- #
all: $(NAME)

$(NAME): checkMyLibft $(LIBFT_NAME) $(OBJECTS)
	@echo "$(YELLOW)Compiling $(NAME)...$(NC)"
	@cc $(CFLAGS) $(OBJECTS) $(LIBFT_FULL) $(MLX_FULL) -lreadline -o $(NAME)
	@if [ -f $(NAME) ]; then \
		echo "$(CYAN)--------------------------------------$(NC)"; \
		echo "$(GREEN)BUILD PROCESS COMPLETED SUCCESSFULLY!$(NC)"; \
		echo "$(CYAN)--------------------------------------$(NC)"; \
	else \
		echo "$(RED)failed to compile $(NAME)$(NC)"; \
		exit 1; \
	fi

checkMyLibft:
	@if [ -d $(LIBFT_DIR) ]; then \
		echo "$(GREEN)myLibft already exists$(NC)"; \
	else \
		echo "$(YELLOW)Downloading myLibft...$(NC)"; \
		mkdir -p $(LIB_DIR); \
		curl -L -o $(LIBFT_DIR).zip https://github.com/ghambrec/42-myLibft/archive/refs/heads/master.zip > /dev/null 2>&1; \
		unzip -o $(LIBFT_DIR).zip > /dev/null 2>&1; \
		mv 42-myLibft-master $(LIBFT_DIR); \
		rm $(LIBFT_DIR).zip; \
		if [ -d $(LIBFT_DIR) ]; then \
			echo "$(GREEN)myLibft downloaded$(NC)"; \
		else \
			echo "$(RED)Error downloading myLibft$(NC)"; \
			exit 1; \
		fi \
	fi	

$(LIBFT_NAME):
	@if [ ! -d $(LIBFT_DIR) ]; then \
		echo "$(RED)myLibft folder doesnt exist! Run 'make checkMyLibft' first to download myLibft$(NC)"; \
	else \
		echo "$(YELLOW)Creating $(LIBFT_NAME)...$(NC)"; \
		make -C $(LIBFT_DIR) > $(LIBFT_DIR)/make_log.txt; \
		if [ -f $(LIBFT_DIR)/$(LIBFT_NAME) ]; then \
			echo "$(GREEN)$(LIBFT_NAME) successfully created$(NC)"; \
		else \
			echo "$(RED)failed to compile $(LIBFT_DIR)$(NC)"; \
			exit 1; \
		fi \
	fi

$(OBJECT_DIR)/%.o: %.c | $(OBJECT_DIR)
	@printf "$(YELLOW)Compiling $(CYAN)$<\n$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJECT_DIR):
	@echo "$(YELLOW)Creating $(OBJECT_DIR) directory$(NC)"
	@mkdir -p $(OBJECT_DIR)

clean:
	@echo "$(RED)Cleaning object files$(NC)"
	@rm -rf $(OBJECT_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)$(NC)"
	@rm -f $(NAME)
	@if [ -d $(LIBFT_DIR)/objects ]; then \
		make fclean -C $(LIBFT_DIR); \
	fi

re: fclean all

# test rule	- compile without flags
test: CFLAGS = -I $(INCLUDE_DIR)
test: all

# tree rule	- print the ast in the terminal
tree: CFLAGS += -DPRINT_TREE=1 -I $(INCLUDE_DIR)
tree: clean all

# deug rule - compile with fsanitize
debug: CFLAGS += -g -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
debug: clean all

# del rule	- remove lib folder
del: fclean
	@echo "$(RED)Removing library folder$(NC)"
	@rm -rf $(LIB_DIR)

.PHONY: all clean fclean re test del tree
