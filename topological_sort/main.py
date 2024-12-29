import collections


# Each item in adj is a list of
def topological_sort(adj: list[list[int]]):
    # indegree is the number of edges going into a vertex
    # this is used to determine the number of dependencies a vertex has
    v = len(adj)
    indegree = [0] * v
    for vertices in adj:
        for vertex in vertices:
            indegree[vertex] += 1

    deque = collections.deque()
    for i in indegree:
        # a vertex with 0 indegree means that are no incoming edges to that vertex
        # this means that it doesn't depend on any other vertex
        if i == 0:
            deque.append(i)

    result = []
    while deque:
        node = deque.popleft()
        result.append(node)

        for adjacent in adj[node]:
            indegree[adjacent] -= 1
            # if the indegree of the adjacent vertex is 0, it means that the vertex has no more dependencies
            if indegree[adjacent] == 0:
                deque.append(adjacent)

    assert len(result) == v, "Not a DAG"

    return result


result = topological_sort([[1, 3], [2], [], []])
print(result)
