// Problem: Labyrinth
// https://cses.fi/problemset/task/1193
// O(n * m) time complexity

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
const vector<char> moveCharsRev = {'L', 'R', 'D', 'U'};

vector<vector<int>> BFS(int x, int y, vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> Q;

    Q.push({x, y});
    dist[x][y] = 0;

    while (!Q.empty()) {
        auto [x, y] = Q.front();
        Q.pop();

        for (auto& move : moves) {
            int newX = x + move.first;
            int newY = y + move.second;

            if (newX < 0 || newX >= n || newY < 0 || newY >= m)
                continue;
            if (dist[newX][newY] != -1)
                continue;
            if (grid[newX][newY] == '#')
                continue;

            dist[newX][newY] = dist[x][y] + 1;
            Q.push({newX, newY});
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
    vector<vector<char>> grid(n, vector<char>(m));
    pair<int, int> start, end;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'A') {
                start = {i, j};
            } else if (grid[i][j] == 'B') {
                end = {i, j};
            }
        }
    }

    vector<vector<int>> dist = BFS(start.first, start.second, grid);

    if (dist[end.first][end.second] == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        cout << dist[end.first][end.second] << '\n';
        vector<char> path;

        while (dist[end.first][end.second] != 0) {
            for (int i = 0; i < 4; i++) {
                auto& move = moves[i];
                int newX = end.first + move.first;
                int newY = end.second + move.second;

                if (newX < 0 || newX >= n || newY < 0 || newY >= m)
                    continue;

                if (dist[newX][newY] == dist[end.first][end.second] - 1) {
                    path.push_back(moveCharsRev[i]);
                    end = {newX, newY};
                    break;
                }
            }
        }

        reverse(path.begin(), path.end());
        for (char c : path) {
            cout << c;
        }
    }
}