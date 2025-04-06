#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int optimalBST(const vector<int>& keys, const vector<int>& prob, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0));

    vector<vector<int>> sum(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        sum[i][i] = prob[i];
        for (int j = i + 1; j < n; ++j) {
            sum[i][j] = sum[i][j - 1] + prob[j];
        }
    }

    for (int len = 1; len <= n; ++len) {  
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][j] = prob[i];
            } else {
                dp[i][j] = INT_MAX;
                for (int r = i; r <= j; ++r) {
                    int cost = (r > i ? dp[i][r - 1] : 0) +
                               (r < j ? dp[r + 1][j] : 0) +
                               sum[i][j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;
    
    vector<int> keys(n);
    vector<int> prob(n);
    
    cout << "Enter the sorted keys: ";
    for (int i = 0; i < n; ++i) {
        cin >> keys[i];
    }
    
    cout << "Enter the probabilities: ";
    for (int i = 0; i < n; ++i) {
        cin >> prob[i];
    }

    int minCost = optimalBST(keys, prob, n);
    cout << "Minimum cost to construct the optimal BST: " << minCost << endl;

    return 0;
}
