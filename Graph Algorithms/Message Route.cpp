// Problem: Message Route
// https://cses.fi/problemset/task/1667
// O(n + m) time complexity

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> BFS(int start, vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> dist(n, -1);
    queue<int> Q;

    Q.push(start);
    dist[start] = 1;

    while (!Q.empty()) {
        auto curr = Q.front();
        Q.pop();

        for (auto& neighbour : graph[curr]) {
            if (dist[neighbour] != -1)
                continue;

            dist[neighbour] = dist[curr] + 1;
            Q.push(neighbour);
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>());
    for (int j = 0; j < m; j++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> dist = BFS(1, graph);

    if (dist[n] == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        int end = n;
        cout << dist[end] << '\n';
        vector<int> path = {end};

        while (dist[end] != 1) {
            for (auto& neighbour : graph[end]) {
                if (dist[neighbour] == dist[end] - 1) {
                    path.push_back(neighbour);
                    end = neighbour;
                    break;
                }
            }
        }

        reverse(path.begin(), path.end());
        for (auto x : path) {
            cout << x << " ";
        }
    }
}