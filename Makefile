#program name
NAME = minishell

#cc compiler with all flags
FLAGS = -g -Wall -Wextra  -Werror 
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

UNAME_S := $(shell uname -s)

# Detect operating system
UNAME_S := $(shell uname -s)

# Define memory test commands
VALGRIND_CMD = valgrind \
	-q \
    --suppressions=readline.supp \
    --leak-check=full \
    --show-leak-kinds=all \
	./minishell

ASAN_CMD = ASAN_OPTIONS=detect_leaks=1 ./minishell

# Suppression file content
define READLINE_SUPP
{
   ignore_readline_leaks
   Memcheck:Leak
   ...
   obj:/**/libreadline.so*
}
endef
export READLINE_SUPP

# Set the appropriate command based on OS
ifeq ($(UNAME_S),Linux)
	MEMTEST_CMD = $(VALGRIND_CMD)
else ifeq ($(UNAME_S),Darwin)
	MEMTEST_CMD = $(ASAN_CMD)
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


#Function to check and update suppression file
check_supp:
	@if [ ! -f readline.supp ] || ! grep -q "ignore_readline_leaks" readline.supp; \
	then \
		echo "$$READLINE_SUPP" > readline.supp; \
		echo "Created/Updated readline.supp"; \
	fi


memtest: clear check_supp
	@echo "$$READLINE_SUPP" > readline.supp
	@$(MEMTEST_CMD)

# Separate targets remain unchanged
memtest-linux: clear
	@$(VALGRIND_CMD)

memtest-mac: clear
	@$(ASAN_CMD)

# Add to PHONY targets
.PHONY: all clean fclean re clear memtest memtest-linux memtest-mac