#program name
NAME = minishell

#cc compiler with all flags
FLAGS = -g3 -Wall -Wextra #-Werror 
# CCF = cc -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline

# Directories
SRC_DIR := source
OBJ_DIR := objects

# Source and Object Files
SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_TEST := $(filter-out $(SRC_DIR)/minishell.c, $(SRC))
OBJ_TEST :=$(SRC_TEST:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#include header
INC= -I./includes

#debuging
ifeq ($(DEBUG), GDB)
	FLAGS += -g
else ifeq ($(DEBUG), ALL)
	FLAGS += -g3 -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ)
		@cc $(FLAGS) $(OBJ) $(INC) -o $@ $(LDFLAGS)
		@echo "compiling"
		@sleep 0.5
		@echo "$(NAME) is ready"

test: $(OBJ_TEST)
		@cc $(FLAGS) $(OBJ_TEST) $(INC) -o $(NAME) $(LDFLAGS)
		@echo "compiling test"
		@sleep 0.5
		@echo "$(NAME) test is ready"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(@D)
		@cc $(FLAGS) $(INC) -c $< -o $@

clean:
		@rm -rf $(OBJ_DIR)
		@echo "cleaning..."

tclean:
		@rm -rf $(OBJ_DIR)
		@echo "cleaning test..."

fclean: clean
		@rm -f $(NAME)
		@echo "cleaning program..."

tfclean: tclean
		@rm -f $(NAME)
		@echo "cleaning test program..."

re: fclean all

tre: tfclean test

clear: re clean

tclear: tre test

bclear: all clean

run:
	@$(MAKE) --no-print-directory re
	@./minishell

norm :
		@norminette $(SRC) includes/

.PHONY: all clean fclean re clear