You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.
•	   0 means the cell is empty, so you can pass through,
•	   1 means the cell contains a cherry that you can pick up and pass through, or
•	   -1 means the cell contains a thorn that blocks your way.
Return the maximum number of cherries you can collect by following the rules below:
•	Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
•	 After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
•	When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
•	If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
 

Example 1:
Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
Output: 5
Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.


Example 2:
Input: grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
Output: 0


Constraints:
n == grid.length
n == grid[i].length
1 <= n <= 50
grid[i][j] is -1, 0, or 1.
grid[0][0] != -1
grid[n - 1][n - 1] != -1


     **************************************
     **************************************
SOLUTION:

***Algorithm:-
Step1: Storing maximum no. of cherries collected in each cell for two paths: down-right and up-left.
Step2: Checking if the starting cell (0, 0) and the ending cell (n - 1, n - 1) are not thorns (-1). If either of them is a thorn, return 0.
Step3: Initializing setting dp[0][0][0] the starting cell, which can be either 0 or 1.
Step4: Using a loop to iterate over k from 1 to 2n – 2. Using nested loops to iterate over possible cell positions (i, j) within the grid. Ensuring that i + j equals k.
Step5: Checking if the current cell (i, k - i) or (j, k - j) contains a thorn (-1). If yes skip this cell.
Step6: Calculating the number of cherries that can be collected at this cell. If i=j, both paths meet at this cell, and the cherry is counted only once.
Step7: Initialize max_val=0.
Step8: Using nested loops to iterate over possible previous cell positions (pi, pj). We can only move left or up (pi, pj could be -1) or stay at the same cell (pi, pj could be 0).
Step9: Checking if previous cell positions (i + pi, j + pj) are within the grid bounds, and update max_val to the maximum cherries collected.
Step10: Update dp[k % 2][i][j] with the maximum cherries collected at the current cell, max_val + cherries.
Step11: After the loop, return the maximum cherries collected at the starting and ending cell (i.e., dp[(2 * n - 2) % 2][n - 1][n - 1]).

***Code:-

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cherryPickup(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] == -1 || grid[n - 1][n - 1] == -1) {
        return 0;
    }

    vector<vector<vector<int>> dp(2, vector<vector<int>>(n, vector<int>(n, 0)));
    dp[0][0][0] = grid[0][0];

    for (int k = 1; k < 2 * n - 1; k++) {
        for (int i = min(n - 1, k); i >= max(0, k - n + 1); i--) {
            for (int j = min(n - 1, k); j >= max(0, k - n + 1); j--) {
                if (grid[i][k - i] == -1 || grid[j][k - j] == -1) {
                    continue;
                }

                int cherries = (i == j) ? grid[i][k - i] : grid[i][k - i] + grid[j][k - j];
                int max_val = 0;

                for (int pi : {-1, 0, -1}) {
                    for (int pj : {-1, 0, -1}) {
                        if (i + pi >= 0 && j + pj >= 0) {
                            max_val = max(max_val, dp[(k - 1) % 2][i + pi][j + pj]);
                        }
                    }
                }

                dp[k % 2][i][j] = max_val + cherries;
            }
        }
    }

    return max(0, dp[(2 * n - 2) % 2][n - 1][n - 1]);
}

int main() {
    vector<vector<int>> grid1 = {{0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
    cout << cherryPickup(grid1) << endl;  // Output: 5

    vector<vector<int>> grid2 = {{1, 1, -1}, {1, -1, 1}, {-1, 1, 1}};
    cout << cherryPickup(grid2) << endl;  // Output: 0

    return 0;
}
