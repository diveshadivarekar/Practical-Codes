import math

AI = 'O'
HUMAN = 'X'

def print_board(board):
    print("\n")
    for row in range(3):
        print(f" {board[row][0]} | {board[row][1]} | {board[row][2]} ")
        if row != 2:
            print("---|---|---")
    print("\n")

def is_moves_left(board):
    for i in range(3):
        for j in range(3):
            if board[i][j] == ' ':
                return True
    return False

def evaluate(b):

    for row in range(3):
        if b[row][0] == b[row][1] and b[row][1] == b[row][2]:
            if b[row][0] == AI:
                return 10
            elif b[row][0] == HUMAN:
                return -10

    for col in range(3):
        if b[0][col] == b[1][col] and b[1][col] == b[2][col]:
            if b[0][col] == AI:
                return 10
            elif b[0][col] == HUMAN:
                return -10

    if b[0][0] == b[1][1] and b[1][1] == b[2][2]:
        if b[0][0] == AI:
            return 10
        elif b[0][0] == HUMAN:
            return -10

    if b[0][2] == b[1][1] and b[1][1] == b[2][0]:
        if b[0][2] == AI:
            return 10
        elif b[0][2] == HUMAN:
            return -10

    return 0

def minimax(board, depth, is_max, alpha, beta):
    score = evaluate(board)

    if score == 10:
        return score - depth

    if score == -10:
        return score + depth

    if not is_moves_left(board):
        return 0

    if is_max:
        best = -math.inf
        for i in range(3):
            for j in range(3):
                if board[i][j] == ' ':
                    board[i][j] = AI
                    best = max(best, minimax(board, depth + 1, not is_max, alpha, beta))
                    alpha = max(alpha, best)
                    board[i][j] = ' '
                    if beta <= alpha:
                        return best
        return best
    else:
        best = math.inf
        for i in range(3):
            for j in range(3):
                if board[i][j] == ' ':
                    board[i][j] = HUMAN
                    best = min(best, minimax(board, depth + 1, not is_max, alpha, beta))
                    beta = min(beta, best)
                    board[i][j] = ' '
                    if beta <= alpha:
                        return best
        return best

def find_best_move(board):
    best_val = -math.inf
    best_move = (-1, -1)

    for i in range(3):
        for j in range(3):
            if board[i][j] == ' ':
                board[i][j] = AI
                move_val = minimax(board, 0, False, -math.inf, math.inf)
                board[i][j] = ' '
                if move_val > best_val:
                    best_move = (i, j)
                    best_val = move_val
    return best_move

if __name__ == "__main__":
    board = [[' ' for _ in range(3)] for _ in range(3)]
    
    print("Welcome to Tic-Tac-Toe!")
    print("You are 'X', the AI is 'O'.")

    while True:
        print_board(board)

        while True:
            try:
                row, col = map(int, input("Enter your move (row col): ").split())
                if 0 <= row <= 2 and 0 <= col <= 2 and board[row][col] == ' ':
                    board[row][col] = HUMAN
                    break
                else:
                    print("Invalid move. Try again.")
            except ValueError:
                print("Invalid input. Please enter row and column as two numbers.")

        score = evaluate(board)
        if score == -10 or score == 10 or not is_moves_left(board):
            break

        print("AI is thinking...")
        ai_move = find_best_move(board)
        if ai_move != (-1, -1):
            board[ai_move[0]][ai_move[1]] = AI
            print(f"AI plays at: {ai_move[0]} {ai_move[1]}")
        
        score = evaluate(board)
        if score == -10 or score == 10 or not is_moves_left(board):
            break

    print_board(board)
    final_score = evaluate(board)
    if final_score == 10:
        print("🤖 AI Wins! Better luck next time.")
    elif final_score == -10:
        print("🎉 Congratulations! You Win!")
    else:
        print("🤝 It's a Draw!")