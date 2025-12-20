*This project has been created as part of the 42 curriculum by prasingh*

# Pushswap

# Description# Pushswap
    Push swap is an algorithmic problem, which states that sort the elements of stack A.
    we have the following this provide for the sortation:
    1. There is stack B, which can be used store number from stack A.
    2. Allowed operations:
        - ra, rb : shift up all elements of stack A by 1. the first element becomes the last one. like clockwise rotation.
        In the following illustration 3 is first element and it becomes the last element.

        **Visualization of `ra` (rotate A):**
        ```
        Before:                 After:
        Stack A:                Stack A:
        ┌─────┐                 ┌─────┐
        │  3  │  ← top          │  2  │  ← top
        ├─────┤                 ├─────┤
        │  2  │                 │  1  │
        ├─────┤                 ├─────┤
        │  1  │                 │  5  │
        ├─────┤                 ├─────┤
        │  5  │                 │  4  │
        ├─────┤                 ├─────┤
        │  4  │  ← bottom       │  3  │  ← bottom
        └─────┘                 └─────┘
        
        Operation: ra
        Result: Top element (3) moves to bottom, all others shift up
        ```
        - pa, pb : push top element of stack a and push to stack b, and vice verse for pb.
        - rra, rrb : revese ra and rb
        - rr : ra and rb at the same time.
        - rrr : reverse of rr 
        - sa, sb : wap first two elements of stack a and b respectively. 
        - ss : sa and sb at the same time. Do nothing if there is 1 element or none.

# Instruction
    - in case of testing very big numbers, its good to create file, because in terminal only few of them we can see after pasting res of them simply not be visible. 

    ```bash
        mapfile -t N < <(cat test_500.txt | tr -d '\r' | grep -v '^$'); ./push_swap "${N[@]}" | ./checker_linux "${N[@]}"
    ```
# Resources
    - https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/description/
    - https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/editorial/

# Usage

# Feature list

# Technical choices


