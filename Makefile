NAME = minishell

GCOMMANDS_C = command_executions.c redirections.c pipes.c child_process_tracker.c heredoc.c heredoc_expand.c

PROMPT_C = prompt.c get_path.c check_executable.c\

BUILTINS_C =  built_ins.c built_ins_helpers.c export.c export_aux.c env_export_aux.c unset.c env.c env_aux.c exit.c exit_aux.c cd.c\

UTILS_C = error_and_exit_handler.c utils.c gets.c frees.c cleans.c remove_indexs.c\

PARSER_C = parser.c split_out_quotes.c ft_strjoin3.c its_what.c\
			ft_lstutils.c ft_lstutils2.c ft_split_aux.c ft_split_shell_lst.c aux_split_list.c


LIBFT_DIRECTORY = libft/
LIBFT_HEADER = $(LIBFT_DIRECTORY)libft.h
LIBFT = $(LIBFT_DIRECTORY)libft.a

HEADER_LIST = minishell.h
HEADER_DIRECTORY = ./
HEADERS = $(addprefix $(HEADER_DIRECTORY), $(HEADER_LIST))

UTILS_LIST = $(UTILS_C)
UTILS_DIRECTORY = utils/
UTILS = $(addprefix $(UTILS_DIRECTORY), $(UTILS_LIST))

GCOMMANDS_LIST = $(GCOMMANDS_C)
GCOMMANDS_DIRECTORY = geral_commands/
GCOMMANDS = $(addprefix $(GCOMMANDS_DIRECTORY), $(GCOMMANDS_LIST))

BUILTINS_LIST = $(BUILTINS_C)
BUILTINS_DIRECTORY = built_ins/
BUILTINS = $(addprefix $(BUILTINS_DIRECTORY), $(BUILTINS_LIST))

PROMPT_LIST = $(PROMPT_C)
PROMPT_DIRECTORY = prompt/
PROMPT = $(addprefix $(PROMPT_DIRECTORY), $(PROMPT_LIST))

PARSER_LIST = $(PARSER_C)
PARSER_DIRECTORY = parser/
PARSER = $(addprefix $(PARSER_DIRECTORY), $(PARSER_LIST))

SRCS_LIST = main.c signals.c $(PROMPT) $(BUILTINS) $(GCOMMANDS) $(UTILS) $(PARSER)
SRCS_DIRECTORY = srcs/
SRC = $(addprefix $(SRCS_DIRECTORY), $(SRCS_LIST))

OBJECT_LIST = $(SRCS_LIST:.c=.o)
OBJECTS_DIRECTORY = objects/
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECT_LIST))

CC = cc
CFLAGS = -g -Wall -Werror -Wextra #-fsanitize=address

LIBS = -L$(LIBFT_DIRECTORY) -lft -lreadline -ltermcap
INCLUDES = -I./srcs -I./libft/ -I/usr/include/readline


# COLORS
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RESET   = \033[0m

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@if $(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBS) -o $(NAME); \
	then \
		make norm -s; \
		echo "[" "$(GREEN)OK$(RESET)" "] | $(NAME) created!"; \
	else \
		echo "[" "$(RED)Error$(RESET)" "] | An error occurred while creating pipex."; \
		make clean > /dev/null 2>&1; \
		echo "[" "$(RED)Error$(RESET)" "] | All objects Cleaned."; \
	fi

$(OBJECTS_DIRECTORY):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Creating objects..."
	@mkdir -p $(OBJECTS_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(PROMPT_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(BUILTINS_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(GCOMMANDS_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(UTILS_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(PARSER_DIRECTORY)
	@echo "[" "$(GREEN)OK$(RESET)" "] | Objects ready!"

$(OBJECTS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling libft..."
	@make -sC $(LIBFT_DIRECTORY)  > /dev/null 2>&1
	@echo "[" "$(GREEN)OK$(RESET)" "] | Libft ready!"

clean:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing object files...$(RESET)"
	@rm -rf $(OBJECTS_DIRECTORY)
	@make -sC $(LIBFT_DIRECTORY) clean > /dev/null 2>&1
	@echo "[" "$(GREEN)OK$(RESET)" "] | Object files removed."

fclean: clean
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing binary files...$(RESET)"
	@rm -rf $(NAME)
	@make -sC $(LIBFT_DIRECTORY) fclean > /dev/null 2>&1
	@rm -rf $(MLX)
	@rm -rf .norminette.log
	@echo "[" "$(GREEN)OK$(RESET)" "] | Binary file removed."

norm:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Norminetting...$(RESET)"
	@if norminette srcs/ libft/ > .norminette.log ; then \
	    if grep -q "Error!" .norminette.log; then \
	        echo "[" "$(RED)!!$(RESET)" "] | Norminette found errors.$(RESET)"; \
	        grep "Error!" .norminette.log | awk '{print "[ " "$(RED)!!$(RESET)" " ] | " $$0}'; \
	    else \
	        echo "[" "$(GREEN)OK$(RESET)" "] | Norminette passed!"; \
	    fi; \
	else \
	    echo "[" "$(RED)XX$(RESET)" "] | Norminette Error!"; \
		norminette srcs/ libft/ | awk '/Error!/ {print "[ " "$(RED)!!$(RESET)" " ] | " $$0}'; \
	fi

re: fclean
	clear && make -s

run: $(NAME)
	./$(NAME)

#--trace-children=yes
DEFAULT_SUPP := $(shell find /usr -path "*/valgrind/default.supp" 2>/dev/null | head -1)

VALGRIND_BASE_FLAGS = --track-fds=yes \
                      --leak-check=full \
                      --show-leak-kinds=all \
                      --errors-for-leak-kinds=all

VALGRIND_FLAGS = $(VALGRIND_BASE_FLAGS) \
                 --suppressions=suppress_readline.supp \

ifneq ($(DEFAULT_SUPP),)
VALGRIND_FLAGS += --suppressions=$(DEFAULT_SUPP)
endif

VALGRIND_FULL_FLAGS = $(VALGRIND_FLAGS) \
                      --trace-children=yes \
                      --track-origins=yes

val: $(NAME)
	valgrind $(VALGRIND_FLAGS) ./$(NAME)

val_full: $(NAME)
	valgrind $(VALGRIND_FULL_FLAGS) ./$(NAME)

val_full_errocommand: $(NAME)
	valgrind $(VALGRIND_FLAGS) --trace-children=yes --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re
