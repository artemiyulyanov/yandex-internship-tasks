#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    std::vector<long long> h(N);

    for (int i = 0; i < N; i++) std::cin >> h[i];

    std::vector<int> res(N, -1);
    std::stack<int> st[2];

    for (int i = N - 1; i >= 0; i--) {
        int parity = i % 2;

        while (!st[parity].empty() && h[st[parity].top()] <= h[i]) {
            st[parity].pop();
        }

        if (!st[parity].empty()) {
            res[i] = st[parity].top() - i;
        }

        st[parity].push(i);
    }

    for (int i = 0; i < N; i++) {
        std::cout << res[i] << " ";
    }

    std::cout << "\n";

    return 0;
}
