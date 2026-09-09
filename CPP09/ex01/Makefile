# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME        = RPN
NAME_TEST   = RPN_test

# Directories
SRC_DIR     = src
INC_DIR     = include
OBJ_DIR     = obj

# Source Files
SRCS        = $(SRC_DIR)/RPN.cpp $(SRC_DIR)/main.cpp
TEST_SRCS   = $(SRC_DIR)/RPN.cpp $(SRC_DIR)/main_test.cpp

# Object Files
OBJS        = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJS   = $(TEST_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Compiler and Flags
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98 -pedantic -I$(INC_DIR)
RM          = rm -rf

# Colors (POSIX compliant using printf)
_GREEN      = \033[0;32m
_RED        = \033[0;31m
_YELLOW     = \033[0;33m
_CYAN       = \033[0;36m
_BOLD       = \033[1m
_RESET      = \033[0m

# **************************************************************************** #
#                                   DEFAULT                                    #
# **************************************************************************** #

.PHONY: all test clean fclean re run test_run valgrind valgrind_test

all: $(NAME)

test: $(NAME_TEST)

# **************************************************************************** #
#                                   COMPILING                                  #
# **************************************************************************** #

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@printf "$(_CYAN)$(_BOLD)Compiling: $(_RESET)$(_YELLOW)%s$(_RESET)\n" "$<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# **************************************************************************** #
#                                   LINKING                                    #
# **************************************************************************** #

$(NAME): $(OBJS)
	@printf "$(_YELLOW)$(_BOLD)Linking: $(_RESET)$(_GREEN)%s$(_RESET)\n" "$(NAME)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@printf "$(_GREEN)$(_BOLD)Success! Run with: make run$(_RESET)\n"

$(NAME_TEST): $(TEST_OBJS)
	@printf "$(_YELLOW)$(_BOLD)Linking Tests: $(_RESET)$(_GREEN)%s$(_RESET)\n" "$(NAME_TEST)"
	@$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $(NAME_TEST)
	@printf "$(_GREEN)$(_BOLD)Success! Run with: make test_run$(_RESET)\n"

# **************************************************************************** #
#                                   CLEANING                                   #
# **************************************************************************** #

clean:
	@printf "$(_CYAN)$(_BOLD)Cleaning object files...$(_RESET)\n"
	@$(RM) $(OBJ_DIR)
	@printf "$(_GREEN)$(_BOLD)Clean complete.$(_RESET)\n"

fclean: clean
	@printf "$(_RED)$(_BOLD)Removing executables...$(_RESET)\n"
	@$(RM) $(NAME) $(NAME_TEST)
	@printf "$(_GREEN)$(_BOLD)Full clean complete.$(_RESET)\n"

re: fclean all

# **************************************************************************** #
#                                   EXECUTION                                  #
# **************************************************************************** #

run: $(NAME)
	@printf "$(_CYAN)$(_BOLD)Running $(NAME)...$(_RESET)\n"
	@./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"

test_run: $(NAME_TEST)
	@printf "$(_CYAN)$(_BOLD)Running TDD Suite...$(_RESET)\n"
	@./$(NAME_TEST)

valgrind: $(NAME)
	@printf "$(_YELLOW)$(_BOLD)Running Valgrind on $(NAME)...$(_RESET)\n"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"

valgrind_test: $(NAME_TEST)
	@printf "$(_YELLOW)$(_BOLD)Running Valgrind on Tests...$(_RESET)\n"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./$(NAME_TEST)