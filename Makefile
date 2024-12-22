#program name
NAME = minishell

#cc compiler with all flags
FLAGS = -Wall -Wextra -Werror 
LDFLAGS = -lreadline

# Directories
SRC_DIR := source
OBJ_DIR := objects

# Source and Object Files
SRC :=	./source/clear/clear1.c \
		./source/clear/clear.c \
		./source/clear/galloc.c \
		./source/clear/pexit.c \
		./source/minishell.c \
		./source/external/ft_strlcat.c \
		./source/external/ft_itoa.c \
		./source/external/ft_isascii.c \
		./source/external/ft_strrchr.c \
		./source/external/ft_isdigit.c \
		./source/external/ft_strcmp.c \
		./source/external/ft_strtrim.c \
		./source/external/ft_strnstr.c \
		./source/external/ft_putstr_fd.c \
		./source/external/ft_split_malloc.c \
		./source/external/ft_strchr.c \
		./source/external/ft_strjoin.c \
		./source/external/ft_isalpha.c \
		./source/external/ft_memcpy.c \
		./source/external/ft_strdup.c \
		./source/external/ft_substr.c \
		./source/external/ft_striteri.c \
		./source/external/ft_strlcpy.c \
		./source/external/ft_atoi.c \
		./source/external/ft_strlen.c \
		./source/external/ft_isprint.c \
		./source/external/ft_split.c \
		./source/external/ft_isalnum.c \
		./source/external/ft_strncmp.c \
		./source/utils/utils_r0.c \
		./source/utils/utils_r5.c \
		./source/utils/utils_r1.c \
		./source/utils/utils_r4.c \
		./source/utils/utils_r3.c \
		./source/utils/signals.c \
		./source/parser/expanding1.c \
		./source/parser/parsing.c \
		./source/parser/heredoc.c \
		./source/parser/cmd1.c \
		./source/parser/cmd.c \
		./source/parser/final_touching.c \
		./source/parser/expanding.c \
		./source/parser/Utils/utils.c \
		./source/parser/expanding2.c \
		./source/parser/env.c \
		./source/parser/lexer.c \
		./source/execution/execution1.c \
		./source/execution/execution.c \
		./source/execution/redirections/ifd.c \
		./source/execution/redirections/redirection.c \
		./source/execution/builtin/ft_cd.c \
		./source/execution/redirections/ofd.c \
		./source/execution/builtin/ft_export_utils.c \
		./source/execution/builtin/ft_unset.c \
		./source/execution/builtin/ft_export_utils2.c \
		./source/execution/builtin/ft_pwd.c \
		./source/execution/builtin/ft_exit.c \
		./source/execution/builtin/ft_export.c \
		./source/execution/builtin/builtin.c \
		./source/execution/builtin/ft_echo.c \
		./source/execution/builtin/ft_env.c \
		./source/execution/utils/utils.c \
		./source/execution/utils/forker.c

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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

memtest-linux: clear
	@$(VALGRIND_CMD)

memtest-mac: clear
	@$(ASAN_CMD)

# Add to PHONY targets
.PHONY: all clean fclean re clear memtest memtest-linux memtest-mac