# ---------------------- Variables ---------------------------------------------

# Executables
NAME = sed_is_for_losers
TEST_NAME = test_replace

# Directories
OBJS_DIR = objs
SRCSDIR = srcs
INCDIR = includes

# SRCs (Explicit to avoid linking two mains together)
CORE_SRCS = srcs/replace.cpp
MAIN_SRCS = srcs/main.cpp $(CORE_SRCS)
TEST_SRCS = srcs/test_main.cpp srcs/test_replace.cpp $(CORE_SRCS)

# OBJs
MAIN_OBJS = $(patsubst srcs/%.cpp,$(OBJS_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS = $(patsubst srcs/%.cpp,$(OBJS_DIR)/%.o,$(TEST_SRCS))

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
 $(NAME): $(MAIN_OBJS)
	@echo "$(YELLOW)Linking Object Files to make $(NAME)...$(RESET)"
	@c++ $(FLAGS) $(MAIN_OBJS) -o $(NAME)
	@echo "$(GREEN)Done! Execute ./$(NAME)$(RESET)"

 $(TEST_NAME): $(TEST_OBJS)
	@echo "$(YELLOW)Linking Object Files to make $(TEST_NAME)...$(RESET)"
	@c++ $(FLAGS) $(TEST_OBJS) -o $(TEST_NAME)
	@echo "$(GREEN)Done!$(RESET)"

# ---------------------- Compiling ---------------------------------------------
 $(OBJS_DIR)/%.o: srcs/%.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@c++ $(FLAGS) -c $< -o $@

# ---------------------- Testing -----------------------------------------------
test: $(TEST_NAME)
	@echo "$(YELLOW)Running tests...$(RESET)"
	@./$(TEST_NAME)
	@echo "$(GREEN)Tests finished$(RESET)"

# ---------------------- Cleaning ----------------------------------------------
clean:
	@echo "$(CYAN)Cleaning Object Files...$(RESET)"
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executables$(RESET)"
	@rm -f $(NAME) $(TEST_NAME)
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

run: $(NAME)
	@./$(NAME)

valgrind: $(NAME)
	@echo "$(YELLOW)Running $(NAME) under Valgrind...$(RESET)"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME)
	@echo "$(GREEN)Valgrind finished$(RESET)"

.PHONY: all clean fclean re run valgrind test
