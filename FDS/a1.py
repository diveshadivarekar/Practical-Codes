def remove_duplicates(lst):
    unique_list = []
    for item in lst:
        if item not in unique_list:
            unique_list.append(item)
    return unique_list

def intersection(list1, list2):
    common = []
    for student in list1:
        if student in list2:
            common.append(student)
    return common

def symmetric_difference(list1, list2):
    either_but_not_both = []
    for student in list1:
        if student not in list2:
            either_but_not_both.append(student)
    for student in list2:
        if student not in list1:
            either_but_not_both.append(student)
    return either_but_not_both

def neither_cricket_nor_badminton(total_students, cricket_list, badminton_list):
    students_playing_cricket_or_badminton = cricket_list + badminton_list
    students_playing_cricket_or_badminton = remove_duplicates(students_playing_cricket_or_badminton)
    neither = []
    for student in total_students:
        if student not in students_playing_cricket_or_badminton:
            neither.append(student)
    return neither

def cricket_and_football_not_badminton(cricket_list, football_list, badminton_list):
    cricket_and_football = []
    for student in cricket_list:
        if student in football_list and student not in badminton_list:
            cricket_and_football.append(student)
    return cricket_and_football

total_students = ["Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Hannah", "Isaac", "Jack"]
cricket_players = ["Alice", "Bob", "Charlie", "David", "Frank", "Grace"]
badminton_players = ["Bob", "Eve", "Frank", "Isaac"]
football_players = ["Alice", "David", "Frank", "Jack"]

cricket_players = remove_duplicates(cricket_players)
badminton_players = remove_duplicates(badminton_players)
football_players = remove_duplicates(football_players)

cricket_and_badminton = intersection(cricket_players, badminton_players)
print("Students who play both Cricket and Badminton:", cricket_and_badminton)

either_cricket_or_badminton = symmetric_difference(cricket_players, badminton_players)
print("Students who play either Cricket or Badminton but not both:", either_cricket_or_badminton)

neither = neither_cricket_nor_badminton(total_students, cricket_players, badminton_players)
print("Number of students who play neither Cricket nor Badminton:", len(neither))

cricket_and_football_not_badminton_list = cricket_and_football_not_badminton(cricket_players, football_players, badminton_players)
print("Students who play Cricket and Football but not Badminton:", cricket_and_football_not_badminton_list)
