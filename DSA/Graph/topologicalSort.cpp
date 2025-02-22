#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void topological_dfs(int current, vector<bool>& visited, vector<int>& stack, vector<vector<int>>& graph)
{
    visited[current] = true;

    // Visit all the neighbors
    for (int neighbor : graph[current])
    {
        if (!visited[neighbor])
        {
            topological_dfs(neighbor, visited, stack, graph);
        }
    }
    stack.push_back(current); // Add to stack when done processing
}

vector<int> topological_sort(int n, vector<vector<int>>& graph)
{
    vector<int> stack;
    vector<bool> visited(n, false);

    // Perform DFS for each node in the graph
    for (int i = 0; i < n; i++)
    {
        if (!visited[i]) // If the node hasn't been visited
        {
            topological_dfs(i, visited, stack, graph);
        }
    }

    // Reverse the stack to get the topological order
    reverse(stack.begin(), stack.end());

    return stack;
}

int main()
{
    
}
