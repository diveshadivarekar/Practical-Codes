def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def display_top_five_scores(arr):
    print("Top five scores:", arr[-5:])

# Input: First year percentages of students
percentages = [76.5, 88.2, 45.0, 92.1, 67.4, 80.5, 55.3, 70.8, 91.0, 65.7]

# Sorting using Quick Sort
sorted_percentages = quick_sort(percentages)
print("Sorted percentages using Quick Sort:")
print(sorted_percentages)

# Displaying top five scores
display_top_five_scores(sorted_percentages)
