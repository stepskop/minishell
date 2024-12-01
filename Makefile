# Pipes, Redirections
#PIPES_DIR = pipes/
#PIPES_SRC = pipes.c

# Commands, built-in stuff
BUILTINS_DIR = builtins/
BUILTINS_SRC = echo.c pwd.c cd.c env.c run_builtins.c

# Signals
SIGNALS_DIR = signals/
SIGNALS_SRC = signal.c

# Exec
EXEC_DIR = exec/
EXEC_SRC = execve.c utils.c

# Path
PATH_DIR = path/
PATH_SRC = path.c a_split.c asterisk01.c asterisk02.c

# Utilites
UTILS_DIR = utils/
UTILS_SRC = sh_split_q.c utils001.c utils002.c utils003.c

# Lexer
LEXER_DIR = lexer/
LEXER_SRC = lexer.c utils.c

# Error
ERROR_DIR = error/
ERROR_SRC = error.c

SRC_DIR = ./src/
SRCS = 	$(addprefix $(BUILTINS_DIR), $(BUILTINS_SRC)) \
		$(addprefix $(UTILS_DIR), $(UTILS_SRC)) \
		$(addprefix $(SIGNALS_DIR), $(SIGNALS_SRC)) \
		$(addprefix $(EXEC_DIR), $(EXEC_SRC)) \
		$(addprefix $(PATH_DIR), $(PATH_SRC)) \
		$(addprefix $(LEXER_DIR), $(LEXER_SRC)) \
		$(addprefix $(ERROR_DIR), $(ERROR_SRC)) \
		$(MAIN)

MAIN = minishell.c

# Included headers
INCLUDE_DIR = ./include/
INCLUDE_SRC = minishell.h

INCLUDES = $(addprefix $(INCLUDE_DIR), $(INCLUDE_SRC))

HEADERS = $(addprefix -I, $(INCLUDE_DIR))

NAME = minishell
# NAME = sksh

CCFLAGS = -g -Wall -Werror -Wextra

CC = cc

OBJ_DIR = ./build/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LIBFT_DIR = ./lib/libft/
LIBFT = $(LIBFT_DIR)libft.a

LIB_DIRS = $(addprefix -L, $(LIBFT_DIR))
LIB_HEADERS = $(addprefix -I, $(LIBFT_DIR))
LIBS = -lft -lreadline

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJS) $(HEADERS) $(LIB_DIRS) $(LIB_HEADERS) $(LIBS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)
	mkdir -p $(OBJ_DIR)$(UTILS_DIR)
	mkdir -p $(OBJ_DIR)$(SIGNALS_DIR)
	mkdir -p $(OBJ_DIR)$(EXEC_DIR)
	mkdir -p $(OBJ_DIR)$(PATH_DIR)
	mkdir -p $(OBJ_DIR)$(LEXER_DIR)
	mkdir -p $(OBJ_DIR)$(ERROR_DIR)

$(OBJ_DIR)%o: $(SRC_DIR)%c $(INCLUDES)
	$(CC) $(CCFLAGS) $(HEADERS) $(LIB_HEADERS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

