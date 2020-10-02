/*
Given an array arr[], where each element represents the maximum number of steps that can be made forward from that element, the task is to print all possible paths that require the minimum number of jumps to reach the end of the given array starting from the first array element.

Note: If an element is 0, then there are no moves allowed from that element.

Examples:

Input: arr[] = {1, 1, 1, 1, 1}
Output:
0 ⇾ 1 ⇾ 2 ⇾ 3 ⇾4
Explanation:
In every step, only one jump is allowed.
Therefore, only one possible path exists to reach end of the array.

Input: arr[] = {3, 3, 0, 2, 1, 2, 4, 2, 0, 0}
Output:
0 ⇾ 3 ⇾ 5 ⇾ 6 ⇾ 9
0 ⇾ 3 ⇾ 5 ⇾ 7 ⇾ 9




Recommended: Please try your approach on {IDE} first, before moving on to the solution.
Approach: The idea is to use Dynamic Programming to solve this problem. Follow the steps below to solve the problem:

Initialize an array dp[] of size N, where dp[i] stores the minimum number of jumps required to reach the end of the array arr[N – 1] from the index i
Compute the minimum number of steps required for each index to reach the end of the array by iterating over indices N – 2 to 1. For each index, try out all possible steps that can be taken from that index, i.e. [1, arr[i]].
While trying out all the possible steps by iterating over [1, arr[i]], for each index, update and store the minimum value of dp[i + j].
Initialize a queue of Pair class instance, which stores the index of the current position and the path that has been traveled so far to reach that index.
Keep updating the minimum number of steps required and finally, print the paths corresponding to those required count of steps.
Below is the implementation of the above approach:
*/
// C++ program to implement the
// above approach


#include <bits/stdc++.h>
using namespace std;
 
// Pair Struct
struct Pair
{
     
    // Stores the current index
    int idx;
 
    // Stores the path
    // travelled so far
    string psf;
 
    // Stores the minimum jumps
    // required to reach the
    // last index from current index
    int jmps;
};
 
// Minimum jumps required to reach
// end of the array
void minJumps(int arr[], int dp[], int n)
{
    for(int i = 0; i < n; i++)
        dp[i] = INT_MAX;
 
    dp[n - 1] = 0;
 
    for(int i = n - 2; i >= 0; i--)
    {
         
        // Stores the maximum number
        // of steps that can be taken
        // from the current index
        int steps = arr[i];
        int min = INT_MAX;
 
        for(int j = 1; 
                j <= steps && i + j < n;
                j++) 
        {
             
            // Checking if index stays
            // within bounds
            if (dp[i + j] != INT_MAX && 
                dp[i + j] < min) 
            {
                 
                // Stores the minimum
                // number of jumps
                // required to jump
                // from (i + j)-th index
                min = dp[i + j];
            }
        }
         
        if (min != INT_MAX)
            dp[i] = min + 1;
    }
}
 
// Function to find all possible
// paths to reach end of array
// requiring minimum number of steps
void possiblePath(int arr[], int dp[], int n)
{
    queue<Pair> Queue;
    Pair p1 = { 0, "0", dp[0] };
    Queue.push(p1);
 
    while (Queue.size() > 0)
    {
        Pair tmp = Queue.front();
        Queue.pop();
 
        if (tmp.jmps == 0)
        {
            cout << tmp.psf << "\n";
            continue;
        }
 
        for(int step = 1; 
                step <= arr[tmp.idx]; 
                step++)
        {
            if (tmp.idx + step < n && 
                tmp.jmps - 1 == dp[tmp.idx + step])
            {
                 
                // Storing the neighbours
                // of current index element
                string s1 = tmp.psf + " -> " + 
                 to_string((tmp.idx + step));
                  
                Pair p2 = { tmp.idx + step, s1, 
                           tmp.jmps - 1 };
                           
                Queue.push(p2);
            }
        }
    }
}
 
// Function to find the minimum steps
// and corresponding paths to reach
// end of an array
void Solution(int arr[], int dp[], int size)
{
     
    // dp[] array stores the minimum jumps
    // from each position to last position
    minJumps(arr, dp, size);
 
    possiblePath(arr, dp, size);
}
 
// Driver Code
int main()
{
    int arr[] = { 3, 3, 0, 2, 1,
                  2, 4, 2, 0, 0 };
 
    int size = sizeof(arr) / sizeof(arr[0]);
    int dp[size];
 
    Solution(arr, dp, size);
}

/*
Output: 
0 -> 3 -> 5 -> 6 -> 9
0 -> 3 -> 5 -> 7 -> 9


Time Complexity: O(N2)
Auxiliary Space: O(N)
*/
 