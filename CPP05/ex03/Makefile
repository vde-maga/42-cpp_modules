# ---------------------- Variables ---------------------------------------------

NAME     = intern

# Directories
OBJS_DIR = obj
SRCDIR   = src
INCDIR   = include

# Compiler & Flags
CXX      = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g -I$(INCDIR)
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

# Sources & Objects
SRCS = $(shell find $(SRCDIR) -type f -name '*.cpp')
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))

# Colors
GREEN  = \033[0;32m
RED    = \033[0;31m
YELLOW = \033[0;33m
CYAN   = \033[0;36m
RESET  = \033[0m

# ---------------------- Default -----------------------------------------------

all: $(NAME)

# ---------------------- Linking -----------------------------------------------
$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking Object Files to make $(NAME)...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Done! Execute ./$(NAME)$(RESET)"

# ---------------------- Compiling ---------------------------------------------
$(OBJS_DIR)/%.o: $(SRCDIR)/%.cpp | $(OBJS_DIR)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# ---------------------- Cleaning ----------------------------------------------
clean:
	@echo "$(CYAN)Cleaning Object Files...$(RESET)"
	@rm -rf $(OBJS_DIR)
	@echo "$(CYAN)Cleaning Shrubbery Forms...$(RESET)"
	@rm -rf *shrubbery
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executable$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

run: re
	@./$(NAME)

valgrind: re
	@echo "$(YELLOW)Running $(NAME) under Valgrind...$(RESET)"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME)
	@echo "$(GREEN)Valgrind finished$(RESET)"

.PHONY: all clean fclean re run valgrind