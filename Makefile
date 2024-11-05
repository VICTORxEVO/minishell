#program name
NAME = minishell

#cc compiler with all flags
FLAGS = -g3 #-Wall -Wextra -Werror 
LDFLAGS = -lreadline

# Directories
SRC_DIR := source
OBJ_DIR := objects

# Source and Object Files
SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


#include header
INC= -I./includes

#debuging
ifeq ($(DEBUG), GDB)
	FLAGS += -g
else ifeq ($(DEBUG), ALL)
	FLAGS += -g3 -fsanitize=address
endif

.PHONY: all clean fclean re clear

all: $(NAME)


$(NAME): $(OBJ)
		@cc $(FLAGS) $(OBJ) $(INC) -o $@ $(LDFLAGS)
		@echo "compiling"
		@sleep 0.5
		@echo "$(NAME) is ready"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(@D)
		@cc $(FLAGS) $(INC) -c $< -o $@

clean:
		@rm -rf $(OBJ_DIR)
		@echo "cleaning..."


fclean: clean
		@rm -f $(NAME)
		@echo "cleaning program..."


re: fclean all

clear: re clean

bclear: all clean

run:
	@$(MAKE) --no-print-directory re
	@./minishell

norm :
		@norminette $(SRC) includes/