from collections import deque

def BFS(graph, start, end):
    search_queue = deque()
    visited = []
    search_queue.append(graph[start])
    pre = {}
    for i in graph[start]:
        if pre.get(i) is None:
            pre.update({i: start})

    while search_queue:
        nodes = search_queue.popleft()
        for node in nodes:
            if node not in visited:
                visited.append(node)
                if node == end:
                    print("found")
                    path = []
                    path.append(node)
                    p = node
                    while True:
                        p = pre.get(p)
                        if p is not None:
                            path.append(p)
                        else:
                            break
                    path.reverse()
                    return path
                subnodes = graph.get(node, [])
                for i in subnodes:
                    if pre.get(i) is None:
                        pre.update({i: node})
                search_queue.append(subnodes)
            else:
                continue

    print("Not found")
    return None

                


if __name__ == "__main__":
    graph = {
        'A': ['D', 'E', 'C'],
        'B': ['C', 'H'],
        'D': ['F'],
        'F': ['G'],
        'E': ['G'],
        'C': ['I'],
        'I': ['K'],
        'H': ['J'],
        'J': ['L']
    }
    print(BFS(graph, 'A', 'G'))
