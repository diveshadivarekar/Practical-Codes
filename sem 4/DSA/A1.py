class TelephoneBook:
    def __init__(self, name, tel_no):
        self.name = name
        self.tel_no = tel_no

def Insertion_LinearProbing():
    hashtable = [None for i in range(10)]
    num_records = int(input("\nEnter number of records: "))
    for i in range(num_records):
        n = input("Enter name: ")
        t = int(input("Enter telephone no.: "))
        hashValue = t % 10
        j = 0
        while hashtable[hashValue] is not None:
            j += 1
            hashValue = (hashValue + 1) % 10
        hashtable[hashValue] = TelephoneBook(n, t)
    return hashtable

def Insertion_QuadProbing():
    hashtable = [None for i in range(10)]
    num_records = int(input("\nEnter number of records: "))
    for i in range(num_records):
        n = input("Enter name: ")
        t = int(input("Enter telephone no.: "))
        hashValue = t % 10
        j = 0
        while hashtable[hashValue] is not None:
            j += 1
            hashValue = (t % 10 + j * j) % 10
        hashtable[hashValue] = TelephoneBook(n, t)
    return hashtable

def Search_LinearProbing(hash_table, tel_no):
    comparisons = 0
    hash_value = tel_no % 10
    i = 0
    while hash_table[hash_value] is not None:
        comparisons += 1
        if hash_table[hash_value].tel_no == tel_no:
            return comparisons
        hash_value = (hash_value + 1) % 10
        i += 1
    return comparisons 

def Search_QuadProbing(hash_table, tel_no):
    comparisons = 0
    hash_value = tel_no % 10
    j = 0
    while hash_table[hash_value] is not None:
        comparisons += 1
        if hash_table[hash_value].tel_no == tel_no:
            return comparisons
        j += 1
        hash_value = (tel_no % 10 + j * j) % 10
    return comparisons

def Display(hash_table):
    print("-------------------------------")
    print("Index\tName\tTelephone No.")
    print("-------------------------------")
    for i, obj in enumerate(hash_table):
        if obj is None:
            print(f"{i}\t-\t-")
        else:
            print(f"{i}\t{obj.name}\t{obj.tel_no}")
    print("-------------------------------")

def main():
    hash_linear = [None for i in range(10)]
    hash_quad = [None for i in range(10)]
    print("-------------------------------")
    print("    Telephone Book Database")
    
    print("\nInserting data using Linear Probing...")
    hash_linear = Insertion_LinearProbing() 
    
    print("\nInserting data using Quadratic Probing...")
    hash_quad = Insertion_QuadProbing()

    print("\nHash Table using Linear Probing:")
    Display(hash_linear)
    
    print("\nHash Table using Quadratic Probing:")
    Display(hash_quad)
    
    tel_no_to_search = int(input("\nEnter telephone number to search for: "))
    
    linear_comparisons = Search_LinearProbing(hash_linear, tel_no_to_search)
    print(f"\nNumber of comparisons using Linear Probing: {linear_comparisons}")
    
    quad_comparisons = Search_QuadProbing(hash_quad, tel_no_to_search)
    print(f"Number of comparisons using Quadratic Probing: {quad_comparisons}")
    
    if linear_comparisons < quad_comparisons:
        print("\nLinear Probing is faster.")
    elif linear_comparisons > quad_comparisons:
        print("\nQuadratic Probing is faster.")
    else:
        print("\nBoth methods took the same number of comparisons.")

main()

