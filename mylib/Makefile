GNL_DIR = get_next_line
LIBFT_DIR = libft
PRINTF_DIR = ft_printf

LIB_NAME = mylib.a

GREEN       	= \033[0;92m
YELLOW 			= \033[0;33m
BLUE       		= \033[0;94m
RESET       	= \033[0m

all: $(LIB_NAME)

$(LIB_NAME): gnl libft printf
	# @echo "Creating library: $(LIB_NAME)"
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Creating library:$(RESET)\n" "LIBFT"
	@ar rcs $(LIB_NAME) $(PRINTF_DIR)/src/*.o $(GNL_DIR)/src/*.o $(LIBFT_DIR)/*.o
	# @echo "Library creation completed."
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Library creation completed:$(RESET)\n" "LIBFT"

gnl:
	# @echo "Compiling GNL..."
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiling GNL...$(RESET)\n" "GNL"
	@$(MAKE) -C $(GNL_DIR) --no-print-directory --silent

libft:
	# @echo "Compiling Libft..."
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiling Libft...$(RESET)\n" "LIBFT"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory --silent

printf:
	# @echo "Compiling Printf..."
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiling Printf...$(RESET)\n" "PRINTF"
	@$(MAKE) -C $(PRINTF_DIR) --no-print-directory --silent

clean:
	# @echo "Cleaning GNL, Libft and Printf object files..."
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Cleaning GNL, Libft and Printf object files...$(RESET)\n" "MYLIB"
	@$(MAKE) -C $(GNL_DIR) clean --no-print-directory --silent
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory --silent
	@$(MAKE) -C $(PRINTF_DIR) clean --no-print-directory --silent
	# @echo "Clean complete."
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Clean complete.$(RESET)\n" "MYLIB"

fclean: clean
	# @echo "Cleaning library and binaries..."
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Cleaning library and binaries...$(RESET)\n" "MYLIB"
	@$(MAKE) -C $(GNL_DIR) fclean --no-print-directory --silent
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory --silent
	@$(MAKE) -C $(PRINTF_DIR) fclean --no-print-directory --silent
	@rm -f $(LIB_NAME)
	# @echo "Full clean complete."
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Full clean complete.$(RESET)\n" "MYLIB"

re: fclean all
	# @echo "Recompilation complete."
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Recompilation complete.$(RESET)\n" "MYLIB"

.PHONY: all gnl libft printf clean fclean re