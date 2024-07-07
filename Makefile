
OUT_DIR			= ./
SRC_DIR			= src/
INPUT_DIR		= $(SRC_DIR)input_handling/
INPUT_PARSE_DIR = $(SRC_DIR)input_parsing/
HELPERS_DIR 	= $(SRC_DIR)helpers/
EXEC_DIR 		= $(SRC_DIR)command_execution/
EXEC_PATHS_DIR 	= $(EXEC_DIR)paths/
BUILTIN_DIR 	= $(SRC_DIR)builtins/

SRC_FILES = 	$(SRC_DIR)main.c \
				$(SRC_DIR)signals.c \
				$(INPUT_DIR)lexing_helpers.c \
				$(INPUT_DIR)tokenizer.c  \
				$(INPUT_DIR)error_checking.c \
				$(INPUT_PARSE_DIR)command_parser.c \
				$(INPUT_PARSE_DIR)command_parser_helper.c \
				$(INPUT_PARSE_DIR)command_parser_utils.c \
				$(HELPERS_DIR)freeing.c \
				$(HELPERS_DIR)exit_code.c \
				$(HELPERS_DIR)variable_expansion.c \
				$(HELPERS_DIR)quotations.c \
				$(HELPERS_DIR)quotations_utils.c \
				$(EXEC_DIR)execution.c \
				$(EXEC_DIR)organiser.c \
				$(EXEC_PATHS_DIR)path_helper.c \
				$(EXEC_PATHS_DIR)path_helper2.c \
				$(EXEC_DIR)executions_checks.c \
				$(EXEC_DIR)execution_2.c \
				$(EXEC_DIR)execution_helper.c \
				$(EXEC_DIR)execution_heredoc.c \
				$(EXEC_DIR)execution_heredoc_helpers.c \
				$(BUILTIN_DIR)builtins.c \
				$(BUILTIN_DIR)ft_cd.c \
				$(BUILTIN_DIR)ft_cd_2.c \
				$(BUILTIN_DIR)ft_echo.c \
				$(BUILTIN_DIR)ft_env_utils.c \
				$(BUILTIN_DIR)ft_env.c \
				$(BUILTIN_DIR)ft_exit.c \
				$(BUILTIN_DIR)ft_export.c \
				$(BUILTIN_DIR)ft_export_utils.c \
				$(BUILTIN_DIR)ft_sort_printenv.c \
				$(BUILTIN_DIR)ft_pwd.c \
				$(BUILTIN_DIR)ft_unset.c \

GREEN       	= \033[0;92m
YELLOW 			= \033[0;33m
BLUE       		= \033[0;94m
RESET       	= \033[0m

EXEC			= minishell
CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror -Iincludes
EXTRAFLAGS 		= -lreadline -lncurses	

LIBDIR 			= mylib
LIB 			= mylib.a

OBJ_DIR	= objs/
OBJ_FILES = $(addprefix $(OBJ_DIR), $(notdir $(SRC_FILES:.c=.o)))

all: $(OBJ_DIR) $(LIBDIR)/$(LIB) $(EXEC)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(EXEC): $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $(EXEC) $(OBJ_FILES) $(LIB) $(EXTRAFLAGS)
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Built Minishell executable successfully! $(RESET)\n" "Minishell"
	


$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Minishell"

$(OBJ_DIR)%.o : $(INPUT_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Minishell"

$(OBJ_DIR)%.o : $(INPUT_PARSE_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Minishell"

$(OBJ_DIR)%.o : $(HELPERS_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Minishell"

$(OBJ_DIR)%.o : $(EXEC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Minishell"

$(OBJ_DIR)%.o : $(EXEC_PATHS_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Minishell"

$(OBJ_DIR)%.o : $(BUILTIN_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Minishell"

$(OBJ_DIR)%.o : $(OUT_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Minishell"

$(LIBDIR)/$(LIB):
	@$(MAKE) -s -C $(LIBDIR)
	@cp $(LIBDIR)/$(LIB) .

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBDIR) clean
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Cleaned object_files!$(RESET)\n" "Minishell"

fclean: clean
	@rm -f $(LIB)
	@$(MAKE) -s -C $(LIBDIR) fclean
	@rm -f $(EXEC)
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Cleaned executable!$(RESET)\n" "Minishell"

re: fclean all
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Minishell executable rebuilt!$(RESET)\n" "Minishell"

.PHONY: all bonus clean fclean re