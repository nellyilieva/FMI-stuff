#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool dfs(int curr, vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& inStack, stack<int>& topoStack) {
    if (inStack[curr]) {
        return true; // Cycle detected
    }

    if (visited[curr]) {
        return false; // Already visited node
    }

    // Mark the node as visiting
    visited[curr] = true;
    inStack[curr] = true;

    // Visit all neighbors
    for (int neighbor : graph[curr]) {
        if (dfs(neighbor, graph, visited, inStack, topoStack)) {
            return true; // Cycle found in deeper DFS call
        }
    }

    // Mark the node as fully processed
    inStack[curr] = false;
    topoStack.push(curr); // Add node to the topological sort stack
    return false;
}

vector<int> findOrder(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph(n);

     for (auto& e : edges) {
        graph[e[0]].push_back(e[1]);
     }

     vector<bool> visited(n, false);
     vector<bool> inStack(n, false);
     stack<int> topoStack;

     for (int i = 0; i < n; ++i) {
         if (!visited[i]) {
             if (dfs(i, graph, visited, inStack, topoStack)) {
                 return {}; // Cycle detected, return empty vector
             }
         }
     }

     vector<int> result;
     while (!topoStack.empty()) {
         result.push_back(topoStack.top());
         topoStack.pop();
     }

     return result;
}

int main() {

}
