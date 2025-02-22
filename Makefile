
# ---------- MAIN ---------- #
NAME = minishell
CC = cc
INCLUDE_DIR = ./inc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR)

# ---------- LIB ---------- #
LIB_DIR = ./lib
LIBFT_DIR = $(LIB_DIR)/myLibft
LIBFT_NAME = libft.a
LIBFT_FULL = $(LIBFT_DIR)/$(LIBFT_NAME)

# ---------- SOURCES ---------- #
VPATH = ./src
SOURCES =	main.c execute_command.c freeing.c

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
	@rm -f $(NAME_CHECKER)
	@if [ -d $(LIBFT_DIR) ]; then \
		make fclean -C $(LIBFT_DIR); \
	fi

re: fclean all

# test rule - compile without flags
test: CFLAGS = -I $(INCLUDE_DIR)
test: $(NAME)

del: fclean
	@echo "$(RED)Removing library folder$(NC)"
	@rm -rf $(LIB_DIR)

.PHONY: all clean fclean re test del
