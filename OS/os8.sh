#!/bin/bash

# Function to display the menu
display_menu() {
    echo "----- Select Mathematical Operation -----"
    echo "1. Addition"
    echo "2. Subtraction"
    echo "3. Multiplication"
    echo "4. Division"
    echo "5. Exit"
}

# Function to perform addition
addition() {
    echo "Result: $(($1 + $2))"
}

# Function to perform subtraction
subtraction() {
    echo "Result: $(($1 - $2))"
}

# Function to perform multiplication
multiplication() {
    echo "Result: $(($1 * $2))"
}

# Function to perform division
division() {
    if [ $2 -eq 0 ]; then
        echo "Error: Division by zero is not allowed."
    else
        echo "Result: $(($1 / $2))"
    fi
}

while true; do
    display_menu
    echo "Enter your choice: "
    read choice

    if [ "$choice" -eq 5 ]; then
        echo "Exiting the program."
        break
    fi

    echo "Enter the first number: "
    read num1

    echo "Enter the second number: "
    read num2

    case $choice in
        1) addition $num1 $num2 ;;
        2) subtraction $num1 $num2 ;;
        3) multiplication $num1 $num2 ;;
        4) division $num1 $num2 ;;
        *) echo "Invalid choice. Please select a valid operation." ;;
    esac

    echo "------------------------------------"
done
