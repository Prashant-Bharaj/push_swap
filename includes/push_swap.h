/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prasingh <prasingh@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:49:47 by prasingh          #+#    #+#             */
/*   Updated: 2025/12/21 15:27:03 by prasingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/*
** Push_swap: A sorting algorithm project that sorts integers using two stacks
** (stack A and stack B) with limited operations (push, swap, rotate, reverse rotate).
** This header file defines the data structures and functions needed to implement
** an efficient sorting algorithm.
*/

/*
** t_stack_node: Represents a single node in a doubly-linked list stack.
** Each node stores:
** - value: The actual integer value from input
** - index: The sorted position of this value (used for optimization)
** - cost: Total number of operations needed to insert this node from stack B into
**         its optimal position in stack A. This is calculated by:
**         * Finding the target insertion position in stack A (smallest value > node's value)
**         * Calculating rotations needed for stack A (to bring target to top)
**         * Calculating rotations needed for stack B (to bring this node to top)
**         * Optimizing for combined operations: if both stacks rotate same direction,
**           cost = max(|rot_a|, |rot_b|) using rr/rrr; otherwise cost = |rot_a| + |rot_b|
**         The node with minimum cost is always inserted next to minimize total operations.
**         Used exclusively in large stack sorting algorithm (sort_large_stack).
** - lis: Flag indicating if this node is part of the Longest Increasing Subsequence
** - next/prev: Pointers for doubly-linked list traversal (enables efficient rotations)
*/
typedef struct s_stack_node
{
	int					value;
	int					index;
	int					cost;
	int					lis;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}	t_stack_node;

/*
** t_stack: Represents a stack data structure using a doubly-linked list.
** - top: Pointer to the topmost node (most recently pushed element)
** - size: Current number of elements in the stack
** We use a doubly-linked list instead of an array because rotations
** are more efficient (O(1) vs O(n)) and we need to traverse both ways.
*/
typedef struct s_stack
{
	t_stack_node	*top;
	int				size;
}	t_stack;

/*
** t_data: Main data structure holding all information needed for sorting.
** - a: Stack A (contains the numbers to be sorted)
** - b: Stack B (temporary storage stack, initially empty)
** - size: Total number of integers to sort
** - arr: Array representation of input (used for validation and indexing)
** This structure is passed around to avoid using global variables.
*/
typedef struct s_data
{
	t_stack	*a;
	t_stack	*b;
	int		size;
	int		*arr;
}	t_data;

/* =============================================================================
** STACK OPERATIONS
** Basic stack manipulation functions - create, push, pop, initialize, cleanup
** ============================================================================= */

/* Creates a new stack node with the given value. Allocates memory and initializes
** all fields to default values. Returns NULL on allocation failure. */
t_stack_node	*create_node(int value);

/* Adds a node to the top of the stack. Updates stack size and maintains
** the doubly-linked list structure. Used internally by push operations. */
void			push_node(t_stack *stack, t_stack_node *node);

/* Removes and returns the top node from the stack. Updates stack size.
** Used internally by pop operations (pa, pb). Returns NULL if stack is empty. */
t_stack_node	*pop_node(t_stack *stack);

/* Initializes an empty stack by setting top to NULL and size to 0.
** Must be called before using a new stack structure. */
void			init_stack(t_stack *stack);

/* Frees all memory allocated for nodes in the stack. Used for cleanup
** to prevent memory leaks. Sets stack to empty state after freeing. */
void			free_stack(t_stack *stack);

/* =============================================================================
** STACK UTILITIES
** Helper functions to query and inspect stack state
** ============================================================================= */

/* Checks if stack is sorted in ascending order (smallest at top).
** Returns 1 if sorted, 0 otherwise. Used to determine if sorting is complete. */
int				check_stack_is_sorted(t_stack *stack);

/* Finds the minimum value in the stack. Used to determine final rotation
** needed to complete sorting (rotate until min is at top). */
int				get_min_value_in_stack(t_stack *stack);

/* Finds the maximum value in the stack. Used in insertion algorithms
** to find target positions for elements from stack B. */
int				get_max_value_in_stack(t_stack *stack);

/* Returns the position (0-indexed from top) of a node with the given value.
** Used to calculate rotation costs for moving elements to specific positions. */
int				find_position_of_value(t_stack *stack, int value);

/* =============================================================================
** OPERATION HELPERS
** Internal functions that implement the core stack manipulations
** These are used by the public operations (sa, ra, rra, etc.)
** ============================================================================= */

/* Gets the bottom node of the stack. Used in rotations to move elements
** from top to bottom or vice versa efficiently. */
t_stack_node	*get_last_node(t_stack *stack);

/* Swaps the positions of the top two nodes. Implements the swap operation
** (sa/sb) without printing the command. Used internally by sa, sb, ss. */
void			swap_top_two_nodes(t_stack *stack);

/* Rotates stack forward: top element moves to bottom (clockwise rotation).
** Implements ra/rb without printing. Used by ra, rb, rr operations. */
void			rotate_stack_forward(t_stack *stack);

/* Rotates stack backward: bottom element moves to top (counter-clockwise).
** Implements rra/rrb without printing. Used by rra, rrb, rrr operations. */
void			rotate_stack_backward(t_stack *stack);

/* =============================================================================
** STACK A OPERATIONS
** Push_swap operations that manipulate stack A and print the command
** These functions match the push_swap specification requirements
** ============================================================================= */

/* Swap first two elements of stack A. Prints "sa\n" to stdout. */
void			sa(t_stack *a);

/* Rotate stack A (shift all elements up, top becomes bottom). Prints "ra\n". */
void			ra(t_stack *a);

/* Reverse rotate stack A (shift all elements down, bottom becomes top).
** Prints "rra\n". */
void			rra(t_stack *a);

/* Push top element from stack B to stack A. Prints "pa\n".
** Does nothing if stack B is empty. */
void			pa(t_stack *a, t_stack *b);

/* =============================================================================
** STACK B OPERATIONS
** Push_swap operations that manipulate stack B and print the command
** ============================================================================= */

/* Swap first two elements of stack B. Prints "sb\n" to stdout. */
void			sb(t_stack *b);

/* Rotate stack B (shift all elements up, top becomes bottom). Prints "rb\n". */
void			rb(t_stack *b);

/* Reverse rotate stack B (shift all elements down, bottom becomes top).
** Prints "rrb\n". */
void			rrb(t_stack *b);

/* Push top element from stack A to stack B. Prints "pb\n".
** Used to move elements from A to B during sorting. Does nothing if A is empty. */
void			pb(t_stack *a, t_stack *b);

/* =============================================================================
** BOTH STACKS OPERATIONS
** Simultaneous operations on both stacks (optimization: save one command)
** ============================================================================= */

/* Swap top two elements of both stacks A and B simultaneously. Prints "ss\n".
** More efficient than calling sa and sb separately. */
void			ss(t_stack *a, t_stack *b);

/* Rotate both stacks A and B forward simultaneously. Prints "rr\n".
** Optimizes rotations when both stacks need the same rotation direction. */
void			rr(t_stack *a, t_stack *b);

/* Reverse rotate both stacks A and B simultaneously. Prints "rrr\n".
** Optimizes reverse rotations when both stacks need the same rotation. */
void			rrr(t_stack *a, t_stack *b);

/* =============================================================================
** VALIDATION
** Input validation functions to ensure valid input before processing
** ============================================================================= */

/* Validates command-line arguments. Checks that each argument is a valid integer
** (can contain optional +/- sign followed by digits only). Returns 1 if valid, 0 otherwise.
** Prevents crashes from invalid input. */
int				validate_args(int argc, char **argv);

/* Checks if the input array contains duplicate values. Returns 1 if duplicates found,
** 0 otherwise. Push_swap requires unique integers, so duplicates must be rejected. */
int				has_duplicates(int *arr, int size);

/* =============================================================================
** I/O AND CONVERSION
** Input/output and string conversion functions
** ============================================================================= */

/* Writes a string to stdout using write syscall. Used to print operation commands.
** Custom implementation (no printf) as per 42 project requirements. */
void			ft_putstr(char *str);

/* Converts a string to an integer. Handles optional sign (+/-) and whitespace.
** Returns 0 on overflow (values outside INT_MIN to INT_MAX range).
** Custom implementation of atoi as per 42 project requirements. */
int				ft_atoi(const char *str);

/* =============================================================================
** INDEXING
** Assigns relative positions to stack elements for efficient sorting
** ============================================================================= */

/* Assigns an index to each node based on its value's position in sorted order.
** Smallest value gets index 0, largest gets index (size-1). This normalization
** simplifies the sorting algorithm by working with indices instead of actual values. */
void			index_stack(t_stack *stack);

/* =============================================================================
** MEMORY MANAGEMENT
** Error handling and resource cleanup functions
** ============================================================================= */

/* Handles errors by printing error message, freeing all allocated memory,
** and exiting with status 1. Prevents memory leaks on error conditions. */
void			error_exit(t_data *data, char *message);

/* Frees all dynamically allocated memory: both stacks, stack structures,
** and the input array. Should be called before program termination to prevent leaks. */
void			free_data(t_data *data);

/* =============================================================================
** SORTING ALGORITHMS
** Main sorting functions for different input sizes
** ============================================================================= */

/* Sorts exactly 3 elements in stack A using an optimized decision tree.
** Tests all possible arrangements and applies the minimal sequence of operations.
** Used as a base case in the sorting algorithm. */
void			sort_three_elements(t_stack *a);

/* Main entry point for sorting small stacks (2-3 elements).
** Uses simple algorithms optimized for small input sizes. */
void			sort_small_stack(t_data *data);

/* Main entry point for sorting large stacks (4+ elements).
** Uses LIS (Longest Increasing Subsequence) algorithm to minimize operations:
** 1. Keep LIS in stack A, push rest to B
** 2. Calculate optimal insertion costs
** 3. Insert elements from B back to A in optimal order
** This approach minimizes the total number of operations. */
void			sort_large_stack(t_data *data);

/* 
** LIS (LONGEST INCREASING SUBSEQUENCE)
** Functions to find and mark the longest increasing subsequence
** The LIS algorithm is key to optimizing large stack sorting: by keeping
** the longest already-sorted sequence, we minimize the number of elements
** we need to move and re-insert, thus reducing total operations.
*/

/* Finds the longest increasing subsequence in the stack using dynamic programming.
** Returns an array of indices representing the LIS, and sets lis_size to the length.
** This identifies which elements should stay in stack A during sorting. */
int				*find_lis_sequence(t_stack *stack, int *lis_size);

/* Checks if a node's index is part of the LIS array. Returns 1 if yes, 0 otherwise.
** Used to determine which elements to keep in stack A vs push to stack B. */
int				is_in_lis(t_stack_node *node, int *lis_arr, int lis_size);

/* Calculates and marks which nodes are part of the LIS by setting their lis flag.
** This preprocessing step optimizes the sorting algorithm by identifying elements
** that are already in optimal relative positions. */
void			calculate_lis(t_stack *stack);

/* Extracts the index values from stack nodes into an array. Used as input
** for the LIS dynamic programming algorithm. Sets size to stack size. */
int				*get_index_array(t_stack *stack, int *size);

/* Finds the index of the maximum value in the DP table. Used to determine
** where the longest increasing subsequence ends. */
int				find_max_index(int *dp, int size);

/* Computes the dynamic programming table for LIS algorithm. Fills dp array
** with lengths of LIS ending at each position, and prev array with previous
** indices for reconstruction. This is the core of the LIS algorithm. */
void			compute_dp_table(int *arr, int *dp, int *prev, int size);

/* Reconstructs the LIS array by backtracking through the prev array.
** Returns an array containing the indices that form the longest increasing subsequence.
** This allows us to know which elements to preserve during sorting. */
int				*build_lis_array(int *arr, int *prev, int max_idx, int lis_size);

/* =============================================================================
** COST CALCULATION
** Functions to calculate and find optimal insertion costs
** These functions determine which element from stack B should be inserted
** next into stack A to minimize the total number of operations.
** ============================================================================= */

/* Finds the target position in stack A where a value from stack B should be inserted.
** The target is the smallest value in A that is greater than the given value.
** If no such value exists, targets the minimum value (for wrapping around).
** Returns the target value, not the position. */
int				find_target_position(t_stack *a, int value);

/* Calculates the total cost (number of operations) needed to insert node_b from
** stack B into its optimal position in stack A. Considers rotation costs for both
** stacks and optimizes for combined rotations (rr, rrr) when possible.
** Returns the total cost as an integer. */
int				calculate_cost(t_stack_node *node_b, t_stack *a, t_stack *b);

/* Calculates and stores the insertion cost for every node in stack B.
** Updates each node's cost field. This preprocessing allows us to quickly
** identify the cheapest element to insert next. */
void			calculate_costs(t_stack *a, t_stack *b);

/* Finds the node in stack B with the minimum insertion cost.
** This is the element that should be inserted next to minimize operations.
** Returns a pointer to the cheapest node, or NULL if stack B is empty. */
t_stack_node	*find_cheapest_node(t_stack *b);

/* Calculates rotation cost to bring a node to the top of the stack.
** Returns positive number if forward rotations are needed, negative for reverse.
** Considers both directions and returns the cheaper option (if pos > size/2,
** reverse rotation is cheaper, so returns negative cost). */
int				get_rotation_cost(t_stack *stack, t_stack_node *node);

/* Finds the smallest value in stack A that is greater than the given value.
** Returns INT_MAX if no such value exists. Used to find insertion targets
** for elements from stack B. */
int				find_smallest_greater_value(t_stack *a, int value);

/* Returns the absolute value of an integer. Used in cost calculations
** to compare rotation costs regardless of direction. */
int				ft_abs(int n);

/* =============================================================================
** INSERTION HELPERS
** Functions to prepare stacks and insert elements optimally
** ============================================================================= */

/* Prepares both stacks for insertion by rotating them to optimal positions,
** then inserts the cheapest element from stack B into stack A.
** This function orchestrates the optimal insertion of a single element. */
void			prepare_and_insert_element(t_data *data, t_stack_node *cheapest);

/* =============================================================================
** ROTATION HELPERS
** Functions to calculate and execute rotations efficiently
** ============================================================================= */

/* Calculates the number of rotations needed to bring an element at position 'pos'
** to the top. Returns negative for forward rotations, positive for reverse.
** Considers both directions and returns the cheaper option (fewer operations). */
int				calculate_rotation_count(int pos, int size);

/* Executes the necessary rotations on both stacks to prepare for insertion.
** Optimizes by using combined rotations (rr, rrr) when both stacks need
** rotation in the same direction, then handles remaining rotations separately.
** This minimizes the total number of commands printed. */
void			execute_rotation_operations(t_data *data, int rot_a, int rot_b);

/* Rotates stack A until the minimum value is at the top. This is the final
** step in sorting - once all elements are in stack A, we rotate to ensure
** the smallest value is at the top (completing the sort in ascending order). */
void			rotate_to_minimum_value(t_stack *a);

#endif
