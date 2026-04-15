# ---------------------- Variables ---------------------------------------------

# Executable
NAME = account

# Directories
OBJS_DIR = objs

# SRCs
SRCS =	tests.cpp \
	Account.cpp

# OBJs
OBJS = $(patsubst srcs/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))

# Compiling Flags
FLAGS = -Wall -Werror -Wextra -std=c++98

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
$(OBJS_DIR)/%.o: srcs/%.cpp
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

run: all clean
	./$(NAME)

.PHONY: all clean fclean re run
