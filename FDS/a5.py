def selection_sort(arr):
    n = len(arr)
    for i in range(n):
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]

def display_top_five_scores(arr):
    print("Top five scores:", arr[-5:])

# Input: First year percentages of students
percentages = [76.5, 88.2, 45.0, 92.1, 67.4, 80.5, 55.3, 70.8, 91.0, 65.7]

# Sorting using Selection Sort
selection_sorted = percentages.copy()
selection_sort(selection_sorted)
print("Sorted percentages using Selection Sort:")
print(selection_sorted)
display_top_five_scores(selection_sorted)

# Sorting using Bubble Sort
bubble_sorted = percentages.copy()
bubble_sort(bubble_sorted)
print("\nSorted percentages using Bubble Sort:")
print(bubble_sorted)
display_top_five_scores(bubble_sorted)
