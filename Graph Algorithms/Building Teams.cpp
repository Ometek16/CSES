// Problem: Building Teams
// https://cses.fi/problemset/task/1668
// O(n * log(log(n))) time complexity

#include <iostream>
#include <vector>

using namespace std;

int Find(int a, vector<int>& fu) {
    if (fu[a] != a) {
        fu[a] = Find(fu[a], fu);
    }
    return fu[a];
}

void Union(int a, int b, vector<int>& fu) {
    fu[Find(a, fu)] = Find(b, fu);
}

void DFS(int node, int team, vector<vector<int>>& graph, vector<int>& teams) {
    teams[node] = team;
    for (auto& neighbour : graph[node]) {
        if (teams[neighbour] == -1) {
            DFS(neighbour, 3 - team, graph, teams);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> fu(n + 1);
    for (int i = 1; i <= n; i++) {
        fu[i] = i;
    }

    bool isBipartite = true;
    for (int i = 1; i <= n; i++) {
        for (auto& neighbour : graph[i]) {
            if (Find(i, fu) == Find(neighbour, fu))
                isBipartite = false;
            Union(graph[i][0], neighbour, fu);
        }
    }

    if (!isBipartite) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> team(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (team[i] == -1) {
            DFS(i, 1, graph, team);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << team[i] << " ";
    }
}