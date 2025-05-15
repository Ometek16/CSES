// Problem: Counting Rooms
// https://cses.fi/problemset/task/1192
// O(n * m) time complexity

#include <iostream>
#include <vector>
using namespace std;

const vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

void DFS(int x, int y, vector<vector<char>>& grid, vector<vector<int>>& visited) {
    if (x < 0 || x >= grid.size())
        return;
    if (y < 0 || y >= grid[0].size())
        return;
    if (visited[x][y])
        return;
    visited[x][y] = 1;
    if (grid[x][y] == '#')
        return;

    for (auto& move : moves)
        DFS(x + move.first, y + move.second, grid, visited);
}

// LeetCode: 200. Number of Islands
int numIslands(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, 0));

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                if (grid[i][j] == '#')
                    visited[i][j] = 1;
                else {
                    DFS(i, j, grid, visited);
                    ans++;
                }
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    cout << numIslands(grid) << '\n';
}