#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void dfs(int curr, std::vector<std::vector<int>>& graph, std::vector<bool>& visited) {
    visited[curr] = true;

    for (auto& n : graph[curr]) {
        if (!visited[n]) {
            dfs(n, graph, visited);
        }
    }
}

int countComponents(int X, int Y, std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(X, false);

    int count = 0;

    for (int i = 0; i < X; i++) {
        if (!visited[i]) {
            count++;
            dfs(i, graph, visited);
        }
    }
    return count;
}


int main() {
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    std::vector<int> results;
    for (int t = 0; t < T; t++) {
        int X, Y;
        std::cin >> X >> Y;

        std::vector<std::vector<int>> graph(X);

        for (int i = 0; i < Y; i++) {
            int u, v;
            std::cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int result = countComponents(X, Y, graph);
        results.push_back(result);
    }

    for (int i = 0; i < results.size(); i++) {
        std::cout << results[i] << (i == results.size() - 1 ? "" : " ");
    }

    return 0;
}
