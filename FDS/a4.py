def linear_search(roll_numbers, target):
    for index in range(len(roll_numbers)):
        if roll_numbers[index] == target:
            return index
    return -1

def sentinel_search(roll_numbers, target):
    n = len(roll_numbers)
    last = roll_numbers[-1]
    roll_numbers[-1] = target

    index = 0
    while roll_numbers[index] != target:
        index += 1

    roll_numbers[-1] = last  # Restore the last element

    if index < n - 1 or roll_numbers[-1] == target:
        return index
    return -1

# Input: Roll numbers of students who attended the training program
roll_numbers = [103, 102, 101, 104, 106, 105]

# Input: Roll number to search
target_roll_number = int(input("Enter roll number to search: "))

# Linear Search
linear_result = linear_search(roll_numbers, target_roll_number)
if linear_result != -1:
    print(f"Linear Search: Student with roll number {target_roll_number} attended the training program (Index: {linear_result}).")
else:
    print(f"Linear Search: Student with roll number {target_roll_number} did not attend the training program.")

# Sentinel Search
sentinel_result = sentinel_search(roll_numbers, target_roll_number)
if sentinel_result != -1:
    print(f"Sentinel Search: Student with roll number {target_roll_number} attended the training program (Index: {sentinel_result}).")
else:
    print(f"Sentinel Search: Student with roll number {target_roll_number} did not attend the training program.")
