#program name
NAME = XXXXXXX

#cc compiler with all flags
CCF = cc -Wall -Wextra -Werror

# Directories
SRC_DIR := source
OBJ_DIR := objects

# Source and Object Files
SRC := $(shell find $(SRC_DIR) -type f )
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


#include header
INC= -I./includes

#debuging
ifeq ($(DEBUG), GDB)
	CCF += -g
else ifeq ($(DEBUG), ALL)
	CCF += -g3 -fsanitize=address
endif

.PHONY: all clean fclean re clear

all: $(NAME)


$(NAME): $(OBJ)
		@$(CCF) $(OBJ) $(INC) -o $@
		@echo "compiling"
		@sleep 0.5
		@echo "$(NAME) is ready"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(@D)
		@$(CCF) $(INC) -c $< -o $@

clean:
		@rm -rf $(OBJ_DIR)
		@echo "cleaning..."


fclean: clean
		@rm -f $(NAME)
		@echo "cleaning program..."


re: fclean all

clear: re clean

bclear: all clean

norm :
		@norminette $(SRC) includes/