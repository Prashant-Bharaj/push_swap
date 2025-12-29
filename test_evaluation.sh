#!/bin/bash

# Push_swap Evaluation Test Script
# Based on the official evaluation sheet

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
PUSH_SWAP="./push_swap"
CHECKER="./checker"
CHECKER_LINUX="./checker_linux"
CHECKER_MAC="./checker_Mac"
TIME_LIMIT=10

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Determine OS and checker
if [ -f "$CHECKER_LINUX" ]; then
    CHECKER_OS="$CHECKER_LINUX"
elif [ -f "$CHECKER_MAC" ]; then
    CHECKER_OS="$CHECKER_MAC"
elif [ -f "$CHECKER" ]; then
    CHECKER_OS="$CHECKER"
else
    CHECKER_OS=""
    echo -e "${YELLOW}Warning: No checker binary found. Some tests will be skipped.${NC}"
fi

# Helper functions
print_header() {
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}\n"
}

print_test() {
    echo -e "${YELLOW}Test: $1${NC}"
}

test_pass() {
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASSED_TESTS++))
    ((TOTAL_TESTS++))
}

test_fail() {
    echo -e "${RED}✗ FAIL${NC}"
    echo -e "${RED}  $1${NC}"
    ((FAILED_TESTS++))
    ((TOTAL_TESTS++))
}

test_error() {
    local expected="$1"
    local actual="$2"
    if [ "$actual" = "$expected" ]; then
        test_pass
    else
        test_fail "Expected: '$expected', Got: '$actual'"
    fi
}

test_empty() {
    local output="$1"
    if [ -z "$output" ]; then
        test_pass
    else
        test_fail "Expected empty output, got: '$output'"
    fi
}

test_stderr() {
    local stderr_file="$1"
    local expected="$2"
    if [ -s "$stderr_file" ]; then
        local content=$(cat "$stderr_file" | tr -d '\r')
        # Extract just the text part (without newline for comparison)
        local expected_text="Error"
        # Check if content is "Error" or "Error\n"
        if [ "$content" = "$expected_text" ] || [ "$content" = "${expected_text}"$'\n' ] || echo "$content" | grep -q "^${expected_text}$"; then
            test_pass
        else
            test_fail "Expected stderr: 'Error' or 'Error\\n', Got: '${content}'"
        fi
    else
        test_fail "Expected stderr output, but stderr is empty"
    fi
}

test_stderr_empty() {
    local stderr_file="$1"
    if [ ! -s "$stderr_file" ]; then
        test_pass
    else
        local content=$(cat "$stderr_file")
        test_fail "Expected empty stderr, got: '$content'"
    fi
}

# Check if push_swap exists
if [ ! -f "$PUSH_SWAP" ]; then
    echo -e "${RED}Error: $PUSH_SWAP not found. Please run 'make' first.${NC}"
    exit 1
fi

# Make sure push_swap is executable
chmod +x "$PUSH_SWAP"
if [ -n "$CHECKER_OS" ]; then
    chmod +x "$CHECKER_OS"
fi

print_header "PUSH_SWAP EVALUATION TEST SUITE"

# ============================================
# 1. README.md Compliance Check
# ============================================
print_header "1. README.md Compliance Check"

README_CHECK=0
if [ -f "README.md" ]; then
    if grep -q "^\*This project has been created as part of the 42 curriculum by" README.md; then
        echo -e "${GREEN}✓ First line format correct${NC}"
        ((README_CHECK++))
    else
        echo -e "${RED}✗ First line format incorrect${NC}"
    fi
    
    if grep -qi "^#.*[Dd]escription" README.md || grep -qi "^##.*[Dd]escription" README.md; then
        echo -e "${GREEN}✓ Description section found${NC}"
        ((README_CHECK++))
    else
        echo -e "${RED}✗ Description section not found${NC}"
    fi
    
    if grep -qi "^#.*[Ii]nstruction" README.md || grep -qi "^##.*[Ii]nstruction" README.md; then
        echo -e "${GREEN}✓ Instructions section found${NC}"
        ((README_CHECK++))
    else
        echo -e "${RED}✗ Instructions section not found${NC}"
    fi
    
    if grep -qi "^#.*[Rr]esource" README.md || grep -qi "^##.*[Rr]esource" README.md; then
        echo -e "${GREEN}✓ Resources section found${NC}"
        ((README_CHECK++))
    else
        echo -e "${RED}✗ Resources section not found${NC}"
    fi
    
    if [ $README_CHECK -eq 4 ]; then
        echo -e "\n${GREEN}README.md: PASS (4/4)${NC}"
    else
        echo -e "\n${RED}README.md: FAIL ($README_CHECK/4)${NC}"
    fi
else
    echo -e "${RED}✗ README.md not found${NC}"
fi

# ============================================
# 2. Error Management (push_swap)
# ============================================
print_header "2. Error Management (push_swap)"

# Test 1: Non-numeric parameters
print_test "Non-numeric parameters"
stdout_file=$(mktemp)
stderr_file=$(mktemp)
"$PUSH_SWAP" "abc" "123" > "$stdout_file" 2> "$stderr_file"
test_stderr "$stderr_file" "Error"$'\n'
rm -f "$stdout_file" "$stderr_file"

# Test 2: Duplicate numeric parameter
print_test "Duplicate numeric parameter"
stdout_file=$(mktemp)
stderr_file=$(mktemp)
"$PUSH_SWAP" "1" "2" "1" > "$stdout_file" 2> "$stderr_file"
test_stderr "$stderr_file" "Error"$'\n'
rm -f "$stdout_file" "$stderr_file"

# Test 3: Number greater than MAXINT
print_test "Number greater than MAXINT"
stdout_file=$(mktemp)
stderr_file=$(mktemp)
"$PUSH_SWAP" "2147483648" > "$stdout_file" 2> "$stderr_file"
test_stderr "$stderr_file" "Error"$'\n'
rm -f "$stdout_file" "$stderr_file"

# Test 4: Number less than MININT
print_test "Number less than MININT"
stdout_file=$(mktemp)
stderr_file=$(mktemp)
"$PUSH_SWAP" "-2147483649" > "$stdout_file" 2> "$stderr_file"
test_stderr "$stderr_file" "Error"$'\n'
rm -f "$stdout_file" "$stderr_file"

# Test 5: No parameters
print_test "No parameters (should be silent)"
stdout_file=$(mktemp)
stderr_file=$(mktemp)
"$PUSH_SWAP" > "$stdout_file" 2> "$stderr_file"
exit_code=$?
output=$(cat "$stdout_file")
stderr_output=$(cat "$stderr_file")
if [ -z "$output" ] && [ -z "$stderr_output" ] && [ $exit_code -eq 0 ]; then
    test_pass
else
    test_fail "Expected silent exit, got stdout: '$output', stderr: '$stderr_output', exit: $exit_code"
fi
rm -f "$stdout_file" "$stderr_file"

# ============================================
# 3. Identity Tests (Already Sorted)
# ============================================
print_header "3. Identity Tests (Already Sorted)"

# Test 1: Single number
print_test "Single number (42)"
output=$("$PUSH_SWAP" "42" 2>&1)
test_empty "$output"

# Test 2: Two numbers (sorted)
print_test "Two numbers sorted (2 3)"
output=$("$PUSH_SWAP" "2" "3" 2>&1)
test_empty "$output"

# Test 3: Three numbers (sorted)
print_test "Three numbers sorted (0 1 2 3)"
output=$("$PUSH_SWAP" "0" "1" "2" "3" 2>&1)
test_empty "$output"

# Test 4: Ten numbers (sorted)
print_test "Ten numbers sorted (0-9)"
output=$("$PUSH_SWAP" "0" "1" "2" "3" "4" "5" "6" "7" "8" "9" 2>&1)
test_empty "$output"

# Test 5: Random sorted values (5-9 numbers)
print_test "Random sorted values (5 numbers)"
output=$("$PUSH_SWAP" "-5" "-2" "0" "3" "7" 2>&1)
test_empty "$output"

# ============================================
# 4. Simple Version (Size 3)
# ============================================
print_header "4. Simple Version (Size 3)"

if [ -z "$CHECKER_OS" ]; then
    echo -e "${YELLOW}Skipping checker tests (no checker binary)${NC}"
else
    # Test 1: "2 1 0"
    print_test "ARG=\"2 1 0\""
    ARG="2 1 0"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    "$PUSH_SWAP" $ARG > "$stdout_file" 2> "$stderr_file"
    instruction_count=$(wc -l < "$stdout_file" | tr -d ' ')
    checker_output=$(cat "$stdout_file" | "$CHECKER_OS" $ARG 2>&1)
    if [ "$checker_output" = "OK" ] && [ "$instruction_count" -le 3 ] && [ ! -s "$stderr_file" ]; then
        echo -e "${GREEN}✓ PASS (Instructions: $instruction_count)${NC}"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo -e "${RED}  Checker: '$checker_output', Instructions: $instruction_count${NC}"
        ((FAILED_TESTS++))
    fi
    ((TOTAL_TESTS++))
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 2: Random 3 values (multiple permutations)
    print_test "Random 3 values (5 permutations)"
    for i in {1..5}; do
        ARG=$(shuf -i 0-100 -n 3 | tr '\n' ' ' | sed 's/ $//')
        stdout_file=$(mktemp)
        stderr_file=$(mktemp)
        "$PUSH_SWAP" $ARG > "$stdout_file" 2> "$stderr_file"
        instruction_count=$(wc -l < "$stdout_file" | tr -d ' ')
        checker_output=$(cat "$stdout_file" | "$CHECKER_OS" $ARG 2>&1)
        if [ "$checker_output" = "OK" ] && [ "$instruction_count" -le 3 ] && [ ! -s "$stderr_file" ]; then
            echo -e "  ${GREEN}Permutation $i: PASS (Instructions: $instruction_count)${NC}"
        else
            echo -e "  ${RED}Permutation $i: FAIL (Checker: '$checker_output', Instructions: $instruction_count)${NC}"
            ((FAILED_TESTS++))
        fi
        ((TOTAL_TESTS++))
        rm -f "$stdout_file" "$stderr_file"
    done
fi

# ============================================
# 5. Another Simple Version (Size 5)
# ============================================
print_header "5. Another Simple Version (Size 5)"

if [ -z "$CHECKER_OS" ]; then
    echo -e "${YELLOW}Skipping checker tests (no checker binary)${NC}"
else
    # Test 1: "1 5 2 4 3"
    print_test "ARG=\"1 5 2 4 3\""
    ARG="1 5 2 4 3"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    "$PUSH_SWAP" $ARG > "$stdout_file" 2> "$stderr_file"
    instruction_count=$(wc -l < "$stdout_file" | tr -d ' ')
    checker_output=$(cat "$stdout_file" | "$CHECKER_OS" $ARG 2>&1)
    if [ "$checker_output" = "OK" ] && [ "$instruction_count" -le 12 ] && [ ! -s "$stderr_file" ]; then
        if [ "$instruction_count" -eq 8 ]; then
            echo -e "${GREEN}✓ PASS - Excellent! (Instructions: $instruction_count)${NC}"
        else
            echo -e "${GREEN}✓ PASS (Instructions: $instruction_count)${NC}"
        fi
        ((PASSED_TESTS++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo -e "${RED}  Checker: '$checker_output', Instructions: $instruction_count${NC}"
        ((FAILED_TESTS++))
    fi
    ((TOTAL_TESTS++))
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 2: Random 5 values (multiple permutations)
    print_test "Random 5 values (10 permutations)"
    for i in {1..10}; do
        ARG=$(shuf -i 0-100 -n 5 | tr '\n' ' ' | sed 's/ $//')
        stdout_file=$(mktemp)
        stderr_file=$(mktemp)
        "$PUSH_SWAP" $ARG > "$stdout_file" 2> "$stderr_file"
        instruction_count=$(wc -l < "$stdout_file" | tr -d ' ')
        checker_output=$(cat "$stdout_file" | "$CHECKER_OS" $ARG 2>&1)
        if [ "$checker_output" = "OK" ] && [ "$instruction_count" -le 12 ] && [ ! -s "$stderr_file" ]; then
            echo -e "  ${GREEN}Permutation $i: PASS (Instructions: $instruction_count)${NC}"
            ((PASSED_TESTS++))
        else
            echo -e "  ${RED}Permutation $i: FAIL (Checker: '$checker_output', Instructions: $instruction_count)${NC}"
            ((FAILED_TESTS++))
        fi
        ((TOTAL_TESTS++))
        rm -f "$stdout_file" "$stderr_file"
    done
fi

# ============================================
# 6. Middle Version (100 values)
# ============================================
print_header "6. Middle Version (100 values)"

if [ -z "$CHECKER_OS" ]; then
    echo -e "${YELLOW}Skipping checker tests (no checker binary)${NC}"
else
    print_test "100 random values (5 permutations)"
    total_instructions=0
    passed_permutations=0
    
    for i in {1..5}; do
        ARG=$(shuf -i 0-1000 -n 100 | tr '\n' ' ' | sed 's/ $//')
        stdout_file=$(mktemp)
        stderr_file=$(mktemp)
        timeout $TIME_LIMIT "$PUSH_SWAP" $ARG > "$stdout_file" 2> "$stderr_file"
        exit_code=$?
        
        if [ $exit_code -eq 124 ]; then
            echo -e "  ${RED}Permutation $i: TLE (Time Limit Exceeded)${NC}"
            ((FAILED_TESTS++))
        else
            instruction_count=$(wc -l < "$stdout_file" | tr -d ' ')
            checker_output=$(cat "$stdout_file" | "$CHECKER_OS" $ARG 2>&1)
            
            if [ "$checker_output" = "OK" ] && [ ! -s "$stderr_file" ]; then
                total_instructions=$((total_instructions + instruction_count))
                ((passed_permutations++))
                echo -e "  ${GREEN}Permutation $i: PASS (Instructions: $instruction_count)${NC}"
                ((PASSED_TESTS++))
            else
                echo -e "  ${RED}Permutation $i: FAIL (Checker: '$checker_output', Instructions: $instruction_count)${NC}"
                ((FAILED_TESTS++))
            fi
        fi
        ((TOTAL_TESTS++))
        rm -f "$stdout_file" "$stderr_file"
    done
    
    if [ $passed_permutations -gt 0 ]; then
        avg_instructions=$((total_instructions / passed_permutations))
        echo -e "\n${BLUE}Average instructions: $avg_instructions${NC}"
        
        if [ $avg_instructions -lt 700 ]; then
            echo -e "${GREEN}Rating: 5/5 (Excellent!)${NC}"
        elif [ $avg_instructions -lt 900 ]; then
            echo -e "${GREEN}Rating: 4/5 (Very Good)${NC}"
        elif [ $avg_instructions -lt 1100 ]; then
            echo -e "${YELLOW}Rating: 3/5 (Good)${NC}"
        elif [ $avg_instructions -lt 1300 ]; then
            echo -e "${YELLOW}Rating: 2/5 (Acceptable)${NC}"
        elif [ $avg_instructions -lt 1500 ]; then
            echo -e "${RED}Rating: 1/5 (Needs Improvement)${NC}"
        else
            echo -e "${RED}Rating: 0/5 (Failed)${NC}"
        fi
    fi
fi

# ============================================
# 7. Advanced Version (500 values)
# ============================================
print_header "7. Advanced Version (500 values)"

if [ -z "$CHECKER_OS" ]; then
    echo -e "${YELLOW}Skipping checker tests (no checker binary)${NC}"
else
    print_test "500 random values (3 permutations)"
    total_instructions=0
    passed_permutations=0
    
    for i in {1..3}; do
        ARG=$(shuf -i 0-10000 -n 500 | tr '\n' ' ' | sed 's/ $//')
        stdout_file=$(mktemp)
        stderr_file=$(mktemp)
        timeout $TIME_LIMIT "$PUSH_SWAP" $ARG > "$stdout_file" 2> "$stderr_file"
        exit_code=$?
        
        if [ $exit_code -eq 124 ]; then
            echo -e "  ${RED}Permutation $i: TLE (Time Limit Exceeded)${NC}"
            ((FAILED_TESTS++))
        else
            instruction_count=$(wc -l < "$stdout_file" | tr -d ' ')
            checker_output=$(cat "$stdout_file" | "$CHECKER_OS" $ARG 2>&1)
            
            if [ "$checker_output" = "OK" ] && [ ! -s "$stderr_file" ]; then
                total_instructions=$((total_instructions + instruction_count))
                ((passed_permutations++))
                echo -e "  ${GREEN}Permutation $i: PASS (Instructions: $instruction_count)${NC}"
                ((PASSED_TESTS++))
            else
                echo -e "  ${RED}Permutation $i: FAIL (Checker: '$checker_output', Instructions: $instruction_count)${NC}"
                ((FAILED_TESTS++))
            fi
        fi
        ((TOTAL_TESTS++))
        rm -f "$stdout_file" "$stderr_file"
    done
    
    if [ $passed_permutations -gt 0 ]; then
        avg_instructions=$((total_instructions / passed_permutations))
        echo -e "\n${BLUE}Average instructions: $avg_instructions${NC}"
        
        if [ $avg_instructions -lt 5500 ]; then
            echo -e "${GREEN}Rating: 5/5 (Excellent!)${NC}"
        elif [ $avg_instructions -lt 7000 ]; then
            echo -e "${GREEN}Rating: 4/5 (Very Good)${NC}"
        elif [ $avg_instructions -lt 8500 ]; then
            echo -e "${YELLOW}Rating: 3/5 (Good)${NC}"
        elif [ $avg_instructions -lt 10000 ]; then
            echo -e "${YELLOW}Rating: 2/5 (Acceptable)${NC}"
        elif [ $avg_instructions -lt 11500 ]; then
            echo -e "${RED}Rating: 1/5 (Needs Improvement)${NC}"
        else
            echo -e "${RED}Rating: 0/5 (Failed)${NC}"
        fi
    fi
fi

# ============================================
# 8. Bonus - Checker Error Management
# ============================================
print_header "8. Bonus - Checker Error Management"

if [ ! -f "$CHECKER" ] && [ -z "$CHECKER_OS" ]; then
    echo -e "${YELLOW}Skipping checker tests (no checker binary)${NC}"
else
    CHECKER_TO_USE="$CHECKER"
    if [ -n "$CHECKER_OS" ]; then
        CHECKER_TO_USE="$CHECKER_OS"
    fi
    
    # Test 1: Non-numeric parameters
    print_test "Checker: Non-numeric parameters"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    echo "" | "$CHECKER_TO_USE" "abc" "123" > "$stdout_file" 2> "$stderr_file"
    test_stderr "$stderr_file" "Error"$'\n'
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 2: Duplicate numeric parameter
    print_test "Checker: Duplicate numeric parameter"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    echo "" | "$CHECKER_TO_USE" "1" "2" "1" > "$stdout_file" 2> "$stderr_file"
    test_stderr "$stderr_file" "Error"$'\n'
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 3: Number greater than MAXINT
    print_test "Checker: Number greater than MAXINT"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    echo "" | "$CHECKER_TO_USE" "2147483648" > "$stdout_file" 2> "$stderr_file"
    test_stderr "$stderr_file" "Error"$'\n'
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 4: No parameters
    print_test "Checker: No parameters (should be silent)"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    echo "" | "$CHECKER_TO_USE" > "$stdout_file" 2> "$stderr_file"
    exit_code=$?
    output=$(cat "$stdout_file")
    stderr_output=$(cat "$stderr_file")
    if [ -z "$output" ] && [ -z "$stderr_output" ] && [ $exit_code -eq 0 ]; then
        test_pass
    else
        test_fail "Expected silent exit, got stdout: '$output', stderr: '$stderr_output', exit: $exit_code"
    fi
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 5: Invalid instruction
    print_test "Checker: Invalid instruction"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    echo -e "invalid\n" | "$CHECKER_TO_USE" "1" "2" "3" > "$stdout_file" 2> "$stderr_file"
    test_stderr "$stderr_file" "Error"$'\n'
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 6: Instruction with spaces
    print_test "Checker: Instruction with spaces before/after"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    echo -e " sa\n" | "$CHECKER_TO_USE" "1" "2" "3" > "$stdout_file" 2> "$stderr_file"
    test_stderr "$stderr_file" "Error"$'\n'
    rm -f "$stdout_file" "$stderr_file"
    
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    echo -e "sa \n" | "$CHECKER_TO_USE" "1" "2" "3" > "$stdout_file" 2> "$stderr_file"
    test_stderr "$stderr_file" "Error"$'\n'
    rm -f "$stdout_file" "$stderr_file"
fi

# ============================================
# 9. Bonus - Checker False Tests
# ============================================
print_header "9. Bonus - Checker False Tests"

if [ ! -f "$CHECKER" ] && [ -z "$CHECKER_OS" ]; then
    echo -e "${YELLOW}Skipping checker tests (no checker binary)${NC}"
else
    CHECKER_TO_USE="$CHECKER"
    if [ -n "$CHECKER_OS" ]; then
        CHECKER_TO_USE="$CHECKER_OS"
    fi
    
    # Test 1: Specific false test
    print_test "Checker: False test (0 9 1 8 2 7 3 6 4 5 with sa, pb, rrr)"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    printf "sa\npb\nrrr\n" | "$CHECKER_TO_USE" "0" "9" "1" "8" "2" "7" "3" "6" "4" "5" > "$stdout_file" 2> "$stderr_file"
    output=$(cat "$stdout_file" | tr -d '\r\n' | head -c 2)
    if [ "$output" = "KO" ] && [ ! -s "$stderr_file" ]; then
        test_pass
    else
        test_fail "Expected 'KO', got: '$(cat $stdout_file)'"
    fi
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 2: Random false tests
    print_test "Checker: Random false tests (5 permutations)"
    for i in {1..5}; do
        ARG=$(shuf -i 0-20 -n 5 | tr '\n' ' ' | sed 's/ $//')
        stdout_file=$(mktemp)
        stderr_file=$(mktemp)
        printf "sa\npb\n" | "$CHECKER_TO_USE" $ARG > "$stdout_file" 2> "$stderr_file"
        output=$(cat "$stdout_file" | tr -d '\r\n' | head -c 2)
        if [ "$output" = "KO" ] && [ ! -s "$stderr_file" ]; then
            echo -e "  ${GREEN}Permutation $i: PASS${NC}"
            ((PASSED_TESTS++))
        else
            echo -e "  ${RED}Permutation $i: FAIL (Expected 'KO', got: '$(cat $stdout_file)')${NC}"
            ((FAILED_TESTS++))
        fi
        ((TOTAL_TESTS++))
        rm -f "$stdout_file" "$stderr_file"
    done
fi

# ============================================
# 10. Bonus - Checker Right Tests
# ============================================
print_header "10. Bonus - Checker Right Tests"

if [ ! -f "$CHECKER" ] && [ -z "$CHECKER_OS" ]; then
    echo -e "${YELLOW}Skipping checker tests (no checker binary)${NC}"
else
    CHECKER_TO_USE="$CHECKER"
    if [ -n "$CHECKER_OS" ]; then
        CHECKER_TO_USE="$CHECKER_OS"
    fi
    
    # Test 1: Already sorted (no instructions)
    print_test "Checker: Already sorted (0 1 2, no instructions)"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    printf "" | "$CHECKER_TO_USE" "0" "1" "2" > "$stdout_file" 2> "$stderr_file"
    output=$(cat "$stdout_file" | tr -d '\r\n' | head -c 2)
    if [ "$output" = "OK" ] && [ ! -s "$stderr_file" ]; then
        test_pass
    else
        test_fail "Expected 'OK', got: '$(cat $stdout_file)'"
    fi
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 2: Specific right test
    print_test "Checker: Right test (0 9 1 8 2 with specific instructions)"
    stdout_file=$(mktemp)
    stderr_file=$(mktemp)
    printf "pb\nra\npb\nra\nsa\nra\npa\npa\n" | "$CHECKER_TO_USE" "0" "9" "1" "8" "2" > "$stdout_file" 2> "$stderr_file"
    output=$(cat "$stdout_file" | tr -d '\r\n' | head -c 2)
    if [ "$output" = "OK" ] && [ ! -s "$stderr_file" ]; then
        test_pass
    else
        test_fail "Expected 'OK', got: '$(cat $stdout_file)'"
    fi
    rm -f "$stdout_file" "$stderr_file"
    
    # Test 3: Random right tests (using push_swap output)
    print_test "Checker: Random right tests (5 permutations using push_swap output)"
    for i in {1..5}; do
        ARG=$(shuf -i 0-20 -n 5 | tr '\n' ' ' | sed 's/ $//')
        push_swap_output=$("$PUSH_SWAP" $ARG 2>&1)
        stdout_file=$(mktemp)
        stderr_file=$(mktemp)
        echo "$push_swap_output" | "$CHECKER_TO_USE" $ARG > "$stdout_file" 2> "$stderr_file"
        output=$(cat "$stdout_file" | tr -d '\r\n' | head -c 2)
        if [ "$output" = "OK" ] && [ ! -s "$stderr_file" ]; then
            echo -e "  ${GREEN}Permutation $i: PASS${NC}"
            ((PASSED_TESTS++))
        else
            echo -e "  ${RED}Permutation $i: FAIL (Expected 'OK', got: '$(cat $stdout_file)')${NC}"
            ((FAILED_TESTS++))
        fi
        ((TOTAL_TESTS++))
        rm -f "$stdout_file" "$stderr_file"
    done
fi

# ============================================
# Summary
# ============================================
print_header "TEST SUMMARY"

echo -e "Total Tests: $TOTAL_TESTS"
echo -e "${GREEN}Passed: $PASSED_TESTS${NC}"
echo -e "${RED}Failed: $FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}═══════════════════════════════════════${NC}"
    echo -e "${GREEN}  ALL TESTS PASSED! 🎉${NC}"
    echo -e "${GREEN}═══════════════════════════════════════${NC}"
    exit 0
else
    echo -e "\n${RED}═══════════════════════════════════════${NC}"
    echo -e "${RED}  SOME TESTS FAILED${NC}"
    echo -e "${RED}═══════════════════════════════════════${NC}"
    exit 1
fi
