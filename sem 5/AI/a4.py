import matplotlib.pyplot as plt
import numpy as np

def draw_chessboard(solution):
    n = len(solution)

    board = np.zeros((n, n))
    board[1::2, ::2] = 1 
    board[::2, 1::2] = 1  

    fig, ax = plt.subplots()
    ax.imshow(board, cmap='gray', interpolation='nearest')

    for col, row in enumerate(solution):
        ax.text(col, row, '♛', fontsize=28, ha='center', va='center', color='red')

    ax.set_xticks(np.arange(n))
    ax.set_yticks(np.arange(n))
    ax.set_xticklabels(np.arange(1, n + 1))
    ax.set_yticklabels(np.arange(1, n + 1))
    ax.set_xticks(np.arange(-.5, n, 1), minor=True)
    ax.set_yticks(np.arange(-.5, n, 1), minor=True)
    ax.grid(which="minor", color="black", linestyle='-', linewidth=2)
    ax.tick_params(which="minor", size=0)
    ax.set_title(f'{n}-Queens Problem Solution')
    plt.show()

def is_safe(board, row, col):

    for i in range(col):
        if board[row][i] == 1:
            return False

    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False

    for i, j in zip(range(row, N, 1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False

    return True

def solve_n_queens_util(board, col):
    if col >= N:
        return True

    for i in range(N):
        if is_safe(board, i, col):

            board[i][col] = 1

            if solve_n_queens_util(board, col + 1):
                return True

            board[i][col] = 0

    return False

def solve_n_queens(n):

    board = [[0 for _ in range(n)] for _ in range(n)]

    if not solve_n_queens_util(board, 0):
        print("Solution does not exist")
        return None

    solution = [0] * n
    for col in range(n):
        for row in range(n):
            if board[row][col] == 1:
                solution[col] = row
    return solution


if __name__ == "__main__":
    N = 8
    
    solution_positions = solve_n_queens(N)

    if solution_positions:
        print(f"Found a solution for the {N}-Queens problem:")
        print(solution_positions)

        draw_chessboard(solution_positions)