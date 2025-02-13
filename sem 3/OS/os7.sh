#!/bin/bash

echo "----- UNIX Process Management Demonstration -----"

# Demonstrating `ps` command to show running processes
echo "Running Processes:"
ps

# Fork: Using subshells to demonstrate the creation of a child process
echo "Forking a new child process using subshell..."
(
    # This is the child process (subshell)
    echo "Inside child process (PID: $$)"
    sleep 2
    echo "Child process completed!"
) &  # Run in the background
CHILD_PID=$!

# Wait: Wait for the child process to complete
echo "Waiting for child process to complete (PID: $CHILD_PID)..."
wait $CHILD_PID
echo "Child process has finished."

# Demonstrating `exec`: Replace current shell process with another command
echo "Executing 'ls' command using exec (this will replace the current shell process)"
exec ls

# The script will not reach here due to `exec` replacing the shell
echo "This will not be printed since exec replaces the current process."
