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
1. Run `make` command to make an excutable file `push_swap`.
2. The values which we want to push to the stack will be passed as an argument to the `push_swap` excutable file.
3. The first value will be pushed first, and then second and so on.
4. For example `./push_swap 1 2 3 4` here `1` will be pushed in first and result will be all elements will be already in the sorted order
5. now to cross verify for the checker
6. Run `make bonus` it will create `checker` program, which we can use to verify our output.
7. we can use  `./push_swap 1 2 3 4 | ./checker 1 2 3 4`

# Feature list
1. Generate the optimal number of allowed operation to sort the elements with stacks.
2. Store the generated numbers back to stack `a`.
3. Print the exact steps on the standard output.
4. With the checker program, we can verify wether printed sequence of operations is valid or not.

# Technical choices
1. Used struct for creating doubly linked list and storing the node.
2. Used struct to store the information about top a s_datand sotre the size of the stack
3. used struct to store the information of both stacks and the input elements

# Algorithm:
1. if there is two or three elements do the small sort.
2. if more than three then use LIS (longest increasing sub-sequence) and move everything which is not a part of LIS to stack `b`.
3. do the cost optimization based on the insert cost optimization.
4. for cost optimization check the distance and that many move we have to make to insert the respective element.
5. we will calculate the cost for each element in b.
6. whichever element have the minimum cost, we will insert that element.
