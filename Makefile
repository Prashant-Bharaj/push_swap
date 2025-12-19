# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 22:55:07 by prasingh          #+#    #+#              #
#    Updated: 2025/12/19 22:55:07 by prasingh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes

SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = main.c \
			stack.c \
			operation_helpers.c \
			operations_a.c \
			operations_b.c \
			operations_both.c \
			validation.c \
			io.c \
			atoi.c \
			indexing.c \
			memory.c \
			stack_utils.c \
			sort_small.c \
			sort_large.c \
			rotation_helpers.c \
			insertion_helpers.c \
			lis.c \
			lis_helpers.c \
			cost.c \
			cost_helpers.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

