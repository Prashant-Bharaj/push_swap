# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 22:55:07 by prasingh          #+#    #+#              #
#    Updated: 2025/12/21 17:48:43 by prasingh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes

SRC_DIR = src
BONUS_DIR = bonus
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
			rotation_helpers_2.c \
			insertion_helpers.c \
			lis.c \
			lis_helpers.c \
			lis_helpers_2.c \
			cost.c \
			cost_helpers.c

SHARED_FILES = stack.c \
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
			rotation_helpers_2.c \
			insertion_helpers.c \
			lis.c \
			lis_helpers.c \
			lis_helpers_2.c \
			cost.c \
			cost_helpers.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

BONUS_FILES = checker.c \
			checker_utils.c \
			checker_io.c \
			checker_ops.c

BONUS_CHECKER_SRC = $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
BONUS_CHECKER_OBJ = $(BONUS_CHECKER_SRC:$(BONUS_DIR)/%.c=$(OBJ_DIR)/bonus_%.o)
SHARED_OBJ = $(addprefix $(OBJ_DIR)/, $(SHARED_FILES:%.c=%.o))
BONUS_OBJ = $(BONUS_CHECKER_OBJ) $(SHARED_OBJ)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/bonus_%.o: $(BONUS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(SHARED_OBJ) $(BONUS_CHECKER_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re

