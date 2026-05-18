# ---------------------- Variables ---------------------------------------------

NAME = Polymorphism

OBJS_DIR = objs
SRCSDIR = srcs
INCDIR = includes

SRCS = $(shell find $(SRCSDIR) -name '*.cpp' -print)
OBJS = $(patsubst $(SRCSDIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))

FLAGS = -Wall -Werror -Wextra -std=c++98 -g -I$(INCDIR)
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

GREEN  = \033[0;32m
RED    = \033[0;31m
YELLOW = \033[0;33m
CYAN   = \033[0;36m
RESET  = \033[0m

# ---------------------- Build -------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@c++ $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCSDIR)/%.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@c++ $(FLAGS) -c $< -o $@

# ---------------------- Clean -------------------------------------------------

clean:
	@echo "$(CYAN)Cleaning...$(RESET)"
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

run: all
	@./$(NAME)

valgrind: $(NAME)
	@echo "$(YELLOW)Running Valgrind...$(RESET)"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME)
	@echo "$(GREEN)Done!$(RESET)"

.PHONY: all clean fclean re run valgrind