#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parents;
    vector<int> dist;

public:
    UnionFind(int n) : parents(n), dist(n, 0) {
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
    }

    int find(int v) {
        if (parents[v] == v) {
            return v;
        }

        return parents[v] = find(parents[v]);
    }

    bool unite(int v, int u) {
        int vParent = find(v);
        int uParent = find(u);

        if (vParent == uParent) {
            return false;
        }

        if (dist[vParent] < dist[uParent]) {
            swap(vParent, uParent);
        }
        
        parents[uParent] = vParent;
        dist[vParent] += dist[uParent];
        return true;
    }
};



int main() {
    
}
