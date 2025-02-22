#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool dfs(int curr, std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<bool>& inStack) {
    visited[curr] = true;
    inStack[curr] = true;

    for (auto& n : graph[curr]) {
        if (!visited[n] && dfs(n, graph, visited, inStack)) {
            return true;
        }
        else if (inStack[n]) {
            return true;
        }
    }
    inStack[curr] = false;
    return false;
}

bool hasCycle(int V, std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(V + 1, false);
    std::vector<bool> inStack(V + 1, false);

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            if (dfs(i, graph, visited, inStack)) {
                return true;
            }
        }
    }
    return false;
}


int main() {
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 0; t < T; t++) {
        int V, E;
        std::cin >> V >> E;

        std::vector<std::vector<int>> graph(V + 1);

        for (int i = 0; i < E; i++) {
            int x, y, w;
            std::cin >> x >> y >> w;
            graph[x].push_back(y);
        }

        if (hasCycle(V, graph)) {
            std::cout << "true" << " ";
        }
        else {
            std::cout << "false" << " ";
        }
    }

    return 0;
}
