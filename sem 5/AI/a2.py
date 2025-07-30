import matplotlib.pyplot as plt
import networkx as nx
import matplotlib.animation as animation
import heapq

G = nx.Graph()

nodes = ['A', 'B', 'C', 'D', 'E', 'F']
G.add_nodes_from(nodes)

pos = {
    'A': (1, 2),
    'B': (2, 1),
    'C': (2, 3),
    'D': (4, 0),
    'E': (0, 3),
    'F': (1, 3.5)
}

edges = {
    ('A', 'B'): 1,
    ('A', 'C'): 1,
    ('B', 'D'): 2,
    ('B', 'E'): 3,
    ('C', 'F'): 2,
    ('E', 'F'): 1
}

for (u, v), w in edges.items():
    G.add_edge(u, v, weight=w)

heuristics = {
    'A': 4,
    'B': 2,
    'C': 5,
    'D': 0,
    'E': 6,
    'F': 6
}

def astar_search(graph, start, goal):
    frontier = []
    heapq.heappush(frontier, (heuristics[start], 0, start, [start]))
    visited = set()
    steps = []

    while frontier:
        est_total_cost, cost_so_far, current, path = heapq.heappop(frontier)
        steps.append((list(visited), list(frontier), current, list(path)))

        if current == goal:
            return path, steps

        if current in visited:
            continue

        visited.add(current)

        for neighbor in graph.neighbors(current):
            if neighbor not in visited:
                g = cost_so_far + graph[current][neighbor]['weight']
                f = g + heuristics[neighbor]
                heapq.heappush(frontier, (f, g, neighbor, path + [neighbor]))

    return [], steps

final_path, steps = astar_search(G, 'A', 'D')

fig, ax = plt.subplots(figsize=(8, 6))

def update(i):
    ax.clear()
    visited, frontier, current, path = steps[i]

    nx.draw(G, pos, ax=ax, with_labels=True, node_color='lightgray', node_size=800, font_size=12)
    
    edge_labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

    for node in G.nodes:
        ax.text(pos[node][0], pos[node][1] - 0.2, f"h={heuristics[node]}",
                horizontalalignment='center', fontsize=9, color='orange')

    nx.draw_networkx_nodes(G, pos, nodelist=visited, node_color='lightblue', node_size=800)

    if current:
        nx.draw_networkx_nodes(G, pos, nodelist=[current], node_color='green', node_size=800)

    frontier_nodes = [item[2] for item in frontier]
    nx.draw_networkx_nodes(G, pos, nodelist=frontier_nodes, node_color='yellow', node_size=800)

    path_edges = list(zip(path, path[1:]))
    nx.draw_networkx_edges(G, pos, edgelist=path_edges, edge_color='red', width=2)

    ax.set_title(f"A* Traversal - Step {i+1}/{len(steps)}", fontsize=14)
    ax.axis('off')

ani = animation.FuncAnimation(fig, update, frames=len(steps), interval=1000, repeat=False)

plt.show()