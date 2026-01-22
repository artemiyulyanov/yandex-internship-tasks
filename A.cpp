#include <deque>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

std::vector<long long>* values = new std::vector<long long>();
std::vector<std::vector<int>>* adj_list;

const long long INF = 1e18;

long long find_longest_path(int n, int start) {
    std::vector<std::vector<long long>> dp(1 << n, std::vector<long long>(n, -INF));
    dp[1 << start][start] = values->at(start);

    for (int mask = 0; mask < (1<<n); mask++) {
        for (int v = 0; v < n; v++) {
            if (dp[mask][v] == -INF) continue;
            for (int u : adj_list->at(v)) {
                if (mask & (1<<u)) continue;
                dp[mask | (1<<u)][u] =
                    std::max(dp[mask | (1<<u)][u],
                        dp[mask][v] + values->at(u));
            }
        }
    }

    long long ans = 0;
    for (int mask = 0; mask < (1<<n); mask++) {
        for (int v = 0; v < n; v++) {
            ans = std::max(ans, dp[mask][v]);
        }
    }

    return ans;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string values_string;
    std::getline(std::cin, values_string);

    std::stringstream ss(values_string);
    long long num;

    while (ss >> num) {
        values->push_back(num);
    }

    adj_list = new std::vector<std::vector<int>>(n, std::vector<int>());

    for (int i = 0; i < m; i++) {
        int a, b;

        std::cin >> a >> b;

        adj_list->at(a-1).push_back(b-1);
        adj_list->at(b-1).push_back(a-1);
    }

    const long long ans = find_longest_path(n, 0);

    delete values;
    delete adj_list;

    std::cout << ans << std::endl;

    return 0;
}