# 6A. Q-learning agent exploring a maze (no dataset needed)
import numpy as np

maze = np.array([[0, 0, 0, 1, 0],      # 0 = free, 1 = wall
                 [1, 1, 0, 1, 0],
                 [0, 0, 0, 0, 0],
                 [0, 1, 1, 1, 0],
                 [0, 0, 0, 0, 0]])
start, goal = (0, 0), (4, 4)
moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]          # up, down, left, right
Q = np.zeros((5, 5, 4))
alpha, gamma, eps = 0.1, 0.9, 0.2

def step(s, a):
    r, c = s[0] + moves[a][0], s[1] + moves[a][1]
    if not (0 <= r < 5 and 0 <= c < 5) or maze[r, c] == 1:
        return s, -5                                 # hit wall: stay, penalty
    return (r, c), (100 if (r, c) == goal else -1)   # goal reward / step cost

for ep in range(2000):                               # training
    s = start
    while s != goal:
        a = np.random.randint(4) if np.random.rand() < eps else Q[s].argmax()
        s2, r = step(s, a)
        Q[s][a] += alpha * (r + gamma * Q[s2].max() - Q[s][a])
        s = s2

s, path = start, [start]                             # test: follow best actions
while s != goal and len(path) < 30:
    s, _ = step(s, Q[s].argmax()); path.append(s)
print("Learned path:", path)
