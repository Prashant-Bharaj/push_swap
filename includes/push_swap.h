/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:49:47 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/20 11:49:47 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack_node
{
	int					value;
	int					index;
	int					cost;
	int					lis;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}	t_stack_node;

typedef struct s_stack
{
	t_stack_node	*top;
	int				size;
}	t_stack;

typedef struct s_data
{
	t_stack	*a;
	t_stack	*b;
	int		size;
	int		*arr;
}	t_data;

/* Stack operations */
t_stack_node	*create_node(int value);
void			push_node(t_stack *stack, t_stack_node *node);
t_stack_node	*pop_node(t_stack *stack);
void			init_stack(t_stack *stack);
void			free_stack(t_stack *stack);

/* Stack utilities */
int				check_stack_is_sorted(t_stack *stack);
int				get_min_value_in_stack(t_stack *stack);
int				get_max_value_in_stack(t_stack *stack);
int				find_position_of_value(t_stack *stack, int value);

/* Operation helpers */
t_stack_node	*get_last_node(t_stack *stack);
void			swap_top_two_nodes(t_stack *stack);
void			rotate_stack_forward(t_stack *stack);
void			rotate_stack_backward(t_stack *stack);

/* Stack A operations */
void			sa(t_stack *a);
void			ra(t_stack *a);
void			rra(t_stack *a);
void			pa(t_stack *a, t_stack *b);

/* Stack B operations */
void			sb(t_stack *b);
void			rb(t_stack *b);
void			rrb(t_stack *b);
void			pb(t_stack *a, t_stack *b);

/* Both stacks operations */
void			ss(t_stack *a, t_stack *b);
void			rr(t_stack *a, t_stack *b);
void			rrr(t_stack *a, t_stack *b);

/* Validation */
int				validate_args(int argc, char **argv);
int				has_duplicates(int *arr, int size);

/* I/O */
void			ft_putstr(char *str);

/* String to integer */
int				ft_atoi(const char *str);

/* Indexing */
void			index_stack(t_stack *stack);

/* Memory management */
void			error_exit(t_data *data, char *message);
void			free_data(t_data *data);

/* Sorting */
void			sort_three_elements(t_stack *a);
void			sort_small_stack(t_data *data);
void			sort_large_stack(t_data *data);

/* LIS (Longest Increasing Subsequence) */
int				*find_lis_sequence(t_stack *stack, int *lis_size);
int				is_in_lis(t_stack_node *node, int *lis_arr, int lis_size);
void			calculate_lis(t_stack *stack);
int				*get_index_array(t_stack *stack, int *size);
int				find_max_index(int *dp, int size);
void			compute_dp_table(int *arr, int *dp, int *prev, int size);
int				*build_lis_array(int *arr, int *prev, int max_idx, int lis_size);

/* Cost calculation */
int				find_target_position(t_stack *a, int value);
int				calculate_cost(t_stack_node *node_b, t_stack *a, t_stack *b);
void			calculate_costs(t_stack *a, t_stack *b);
t_stack_node	*find_cheapest_node(t_stack *b);
int				get_rotation_cost(t_stack *stack, t_stack_node *node);
int				find_smallest_greater_value(t_stack *a, int value);
int				ft_abs(int n);

/* Insertion helpers */
void			prepare_and_insert_element(t_data *data, t_stack_node *cheapest);

/* Rotation helpers */
int				calculate_rotation_count(int pos, int size);
void			execute_rotation_operations(t_data *data, int rot_a, int rot_b);
void			rotate_to_minimum_value(t_stack *a);

#endif
