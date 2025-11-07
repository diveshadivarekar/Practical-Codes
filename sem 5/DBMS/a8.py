import mysql.connector

# MySQL connection settings
DB_CONFIG = {
    "host": "localhost",
    "user": "root",             # your MySQL username
    "password": "root",         # your MySQL password
    "database": "todo_app"      # your database name
}

# Connect to MySQL
def get_connection():
    return mysql.connector.connect(**DB_CONFIG)

# Create tasks table if it doesn't exist
def create_table():
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS tasks (
            id INT AUTO_INCREMENT PRIMARY KEY,
            description VARCHAR(255) NOT NULL
        )
    """)
    conn.commit()
    cursor.close()
    conn.close()

# Add a new task
def add_task():
    description = input("Enter task description: ").strip()
    if not description:
        print("Task cannot be empty.")
        return

    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute("INSERT INTO tasks (description) VALUES (%s)", (description,))
    conn.commit()
    print("Task added.")
    cursor.close()
    conn.close()

# View all tasks
def view_tasks():
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute("SELECT id, description FROM tasks")
    rows = cursor.fetchall()
    if not rows:
        print("No tasks found.")
    else:
        print("\nYour To-Do List:")
        for row in rows:
            print(f"{row[0]}. {row[1]}")
    cursor.close()
    conn.close()

# Update a task
def update_task():
    view_tasks()
    try:
        task_id = int(input("Enter task ID to update: "))
        new_desc = input("Enter new description: ").strip()
        if not new_desc:
            print("Description cannot be empty.")
            return
    except ValueError:
        print("Invalid input.")
        return

    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute("UPDATE tasks SET description = %s WHERE id = %s", (new_desc, task_id))
    if cursor.rowcount == 0:
        print("Task ID not found.")
    else:
        print("Task updated.")
    conn.commit()
    cursor.close()
    conn.close()

# Delete a task
def delete_task():
    view_tasks()
    try:
        task_id = int(input("Enter task ID to delete: "))
    except ValueError:
        print("Invalid input.")
        return

    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute("DELETE FROM tasks WHERE id = %s", (task_id,))
    if cursor.rowcount == 0:
        print("Task ID not found.")
    else:
        print("Task deleted.")
    conn.commit()
    cursor.close()
    conn.close()

# Main loop
def main():
    create_table()
    while True:
        print("\n--- To-Do App ---")
        print("1. View Tasks")
        print("2. Add Task")
        print("3. Update Task")
        print("4. Delete Task")
        print("5. Exit")

        choice = input("Choose an option (1-5): ").strip()

        if choice == "1":
            view_tasks()
        elif choice == "2":
            add_task()
        elif choice == "3":
            update_task()
        elif choice == "4":
            delete_task()
        elif choice == "5":
            print("Goodbye.")
            break
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()