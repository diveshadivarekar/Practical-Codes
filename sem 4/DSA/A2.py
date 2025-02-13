class Dictionary:
    def __init__(self, size=10, with_replacement=False):
        self.size = size
        self.table = [[] for _ in range(size)] 
        self.with_replacement = with_replacement

    def _hash(self, key):
        return key % self.size
    
    def insert(self, key, value):
        index = self._hash(key)
        bucket = self.table[index]
        
        if self.with_replacement:
            for idx, (existing_key, _) in enumerate(bucket):
                if existing_key == key:
                    bucket[idx] = (key, value)
                    print(f"Key '{key}' updated with new value '{value}' (with replacement).")
                    return
        else:
            for (existing_key, _) in bucket:
                if existing_key == key:
                    print(f"Key '{key}' already exists (no replacement).")
                    return
        
        bucket.append((key, value))
        print(f"Key '{key}' inserted with value '{value}'.")

    def find(self, key):
        index = self._hash(key)
        bucket = self.table[index]
        
        for k, v in bucket:
            if k == key:
                return v
        
        return None
    
    def delete(self, key):
        index = self._hash(key)
        bucket = self.table[index]
        
        for idx, (existing_key, _) in enumerate(bucket):
            if existing_key == key:
                del bucket[idx]
                print(f"Key '{key}' deleted.")
                return True
        
        print(f"Key '{key}' not found to delete.")
        return False 

    def display(self):
        print("\nCurrent Hash Table:")
        for index, bucket in enumerate(self.table):
            if bucket:
                print(f"Index {index}: {bucket}")
            else:
                print(f"Index {index}: Empty")


def menu_driven():
    replacement_choice = input("Do you want to use chaining with replacement? (y/n): ").lower()
    with_replacement = True if replacement_choice == 'y' else False
    
    dict_obj = Dictionary(size=10, with_replacement=with_replacement)

    while True:
        print("\nMenu:")
        print("1. Insert (key, value)")
        print("2. Find (key)")
        print("3. Delete (key)")
        print("4. Display Dictionary")
        print("5. Exit")
        
        choice = input("\nEnter your choice (1/2/3/4/5): ")

        if choice == '1':
            try:
                key = int(input("Enter key (integer): "))
                value = input("Enter value (string): ")
                dict_obj.insert(key, value)
            except ValueError:
                print("Invalid input. Key must be an integer.")

        elif choice == '2':
            try:
                key = int(input("Enter key to find (integer): "))
                result = dict_obj.find(key)
                if result is not None:
                    print(f"Value for key '{key}' is: {result}")
                else:
                    print(f"Key '{key}' not found.")
            except ValueError:
                print("Invalid input. Key must be an integer.")

        elif choice == '3':
            try:
                key = int(input("Enter key to delete (integer): "))
                dict_obj.delete(key)
            except ValueError:
                print("Invalid input. Key must be an integer.")

        elif choice == '4':
            dict_obj.display()

        elif choice == '5':
            print("Exiting...")
            break
        
        else:
            print("Invalid choice. Please try again.")

menu_driven()

