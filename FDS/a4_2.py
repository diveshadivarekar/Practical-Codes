def binary_search(roll_numbers, target):
    low = 0
    high = len(roll_numbers) - 1
    while low <= high:
        mid = (low + high) // 2
        if roll_numbers[mid] == target:
            return mid
        elif roll_numbers[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    return -1

def fibonacci_search(roll_numbers, target):
    fib_m2 = 0  # (m-2)'th Fibonacci number
    fib_m1 = 1  # (m-1)'th Fibonacci number
    fib_m = fib_m2 + fib_m1  # m'th Fibonacci number

    n = len(roll_numbers)
    while fib_m < n:
        fib_m2 = fib_m1
        fib_m1 = fib_m
        fib_m = fib_m2 + fib_m1

    offset = -1
    while fib_m > 1:
        i = min(offset + fib_m2, n - 1)

        if roll_numbers[i] < target:
            fib_m = fib_m1
            fib_m1 = fib_m2
            fib_m2 = fib_m - fib_m1
            offset = i
        elif roll_numbers[i] > target:
            fib_m = fib_m2
            fib_m1 = fib_m1 - fib_m2
            fib_m2 = fib_m - fib_m1
        else:
            return i

    if fib_m1 and offset + 1 < n and roll_numbers[offset + 1] == target:
        return offset + 1

    return -1

# Input: Roll numbers of students who attended the training program
roll_numbers = [103, 102, 101, 104, 106, 105]
roll_numbers.sort()  # Sort the list for binary and Fibonacci search

# Input: Roll number to search
target_roll_number = int(input("Enter roll number to search: "))

# Binary Search
binary_result = binary_search(roll_numbers, target_roll_number)
if binary_result != -1:
    print(f"Binary Search: Student with roll number {target_roll_number} attended the training program (Index: {binary_result}).")
else:
    print(f"Binary Search: Student with roll number {target_roll_number} did not attend the training program.")

# Fibonacci Search
fibonacci_result = fibonacci_search(roll_numbers, target_roll_number)
if fibonacci_result != -1:
    print(f"Fibonacci Search: Student with roll number {target_roll_number} attended the training program (Index: {fibonacci_result}).")
else:
    print(f"Fibonacci Search: Student with roll number {target_roll_number} did not attend the training program.")
