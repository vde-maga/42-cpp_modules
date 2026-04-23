# ---------------------- Variables ---------------------------------------------

# Executable
NAME = harlFilter

# Directories
OBJS_DIR = objs
SRCSDIR = srcs
INCDIR = includes

# SRCs
SRCS = $(shell find $(SRCSDIR) -name '*.cpp' -print)

# OBJs
OBJS = $(patsubst $(SRCSDIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))

# Compiling Flags
FLAGS = -Wall -Werror -Wextra -std=c++98 -g -I$(INCDIR)
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

# Colors
GREEN         = \033[0;32m
RED           = \033[0;31m
YELLOW        = \033[0;33m
CYAN          = \033[0;36m
RESET         = \033[0m

# ---------------------- Default -----------------------------------------------

all: $(NAME)

# ---------------------- Linking -----------------------------------------------
$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking Object Files to make $(NAME)...$(RESET)"
	@c++ $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Done! Execute ./$(NAME)$(RESET)"

# ---------------------- Compiling ---------------------------------------------
$(OBJS_DIR)/%.o: $(SRCSDIR)/%.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@c++ $(FLAGS) -c $< -o $@

# ---------------------- Cleaning ----------------------------------------------
clean:
	@echo "$(CYAN)Cleaning Object Files...$(RESET)"
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executable$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

# ---------------------- Argument handling for run and valgrind ----------------
# Positional args after the target: make run arg1 arg2 ...
ARGS_FROM_GOALS := $(filter-out run valgrind,$(MAKECMDGOALS))
# Prefer explicit ARGS variable if fornecida
ARGS_TO_PASS := $(if $(ARGS),$(ARGS),$(ARGS_FROM_GOALS))

# Prevent Make errors when extra words are passed after the target
%:
	@:

# ---------------------- Run with arguments -----------------------------------
# Usage:
# 1) make run ARGS="Olá mundo!"
# 2) make run Olá mundo!
run: all
	@echo "$(YELLOW)Running $(NAME) with args: $(ARGS_TO_PASS)$(RESET)"
	@./$(NAME) $(ARGS_TO_PASS)

# ---------------------- Valgrind with arguments -------------------------------
# Usage:
# 1) make valgrind ARGS="arg1 arg2"
# 2) make valgrind arg1 arg2
valgrind: $(NAME)
	@echo "$(YELLOW)Running $(NAME) under Valgrind with args: $(ARGS_TO_PASS)$(RESET)"
	@valgrind $(VALGRIND_FLAGS) -- ./$(NAME) $(ARGS_TO_PASS)
	@echo "$(GREEN)Valgrind finished$(RESET)"

.PHONY: all clean fclean re run valgrind

