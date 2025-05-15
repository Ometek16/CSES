// Problem: Building Roads
// https://cses.fi/problemset/task/1666
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> fu(n + 1);
    for (int i = 1; i <= n; i++) {
        fu[i] = i;
    }

    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        Union(a, b, fu);
    }

    for (int i = 1; i <= n; i++) {
        fu[i] = Find(i, fu);
    }

    int cnt = 0;
    int any_node = 0;
    for (int i = 1; i <= n; i++) {
        if (fu[i] == i) {
            cnt++;
            any_node = i;
        }
    }

    cout << cnt - 1 << "\n";
    for (int i = 1; i <= n; i++) {
        if (fu[i] == i && i != any_node) {
            cout << any_node << " " << i << "\n";
        }
    }
}