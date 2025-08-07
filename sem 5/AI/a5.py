import matplotlib.pyplot as plt
import networkx as nx
import heapq

# Define the graph
graph = {
    'A': {'B': 1, 'C': 4},
    'B': {'A': 1, 'C': 2, 'D': 5},
    'C': {'A': 4, 'B': 2, 'D': 1},
    'D': {'B': 5, 'C': 1, 'E': 3},
    'E': {'D': 3}
}

# Dijkstra's algorithm
def dijkstra(graph, start, goal):
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    parent = {node: None for node in graph}
    queue = [(0, start)]
    visited = set()

    while queue:
        dist, current = heapq.heappop(queue)

        if current in visited:
            continue
        visited.add(current)

        if current == goal:
            break

        for neighbor, weight in graph[current].items():
            new_dist = dist + weight
            if new_dist < distances[neighbor]:
                distances[neighbor] = new_dist
                parent[neighbor] = current
                heapq.heappush(queue, (new_dist, neighbor))

    # Build path from goal to start
    path = []
    node = goal
    while node:
        path.append(node)
        node = parent[node]
    return path[::-1]

# Visualization
def animate_dijkstra(graph, path, start, end):
    G = nx.Graph()
    for u in graph:
        for v, w in graph[u].items():
            G.add_edge(u, v, weight=w)

    pos = nx.spring_layout(G, seed=42)
    plt.figure(figsize=(8, 6))
    nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=800, font_weight='bold')
    edge_labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

    # Color nodes based on their role
    colors = []
    for node in G.nodes():
        if node == start:
            colors.append('green')
        elif node == end:
            colors.append('blue')
        elif node in path:
            colors.append('red')
        else:
            colors.append('lightblue')

    nx.draw_networkx_nodes(G, pos, nodelist=G.nodes(), node_color=colors, node_size=800)

    # Highlight path edges
    path_edges = list(zip(path, path[1:]))
    nx.draw_networkx_edges(G, pos, edgelist=path_edges, edge_color='red', width=3)

    plt.title("Dijkstra's Algorithm: Shortest Path from {} to {}".format(start, end))
    plt.show()

# Run the algorithm and visualize
if __name__ == "__main__":
    start = 'A'
    end = 'E'
    path = dijkstra(graph, start, end)
    animate_dijkstra(graph, path, start, end)
