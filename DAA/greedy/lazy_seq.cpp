#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Lazy sequence problem
// Given a set U of n elements and m subsets S1, S2, ..., Sm of U, find the smallest subset of S that covers all elements of U

vector<int> findLazySeq(vector<int> &U, vector<vector<int>> &S)
{
    unordered_set<int> uncovered(U.begin(), U.end()); // Track uncovered elements
    vector<int> lazyseq;
    int m = S.size();

    while (!uncovered.empty())
    {
        int max_elements = 0, best_subset_index = -1;

        // Find the subset covering the most uncovered elements
        for (int i = 0; i < m; i++)
        {
            int count = 0;
            for (int elem : S[i])
            {
                if (uncovered.count(elem)) // Fast O(1) lookup
                    count++;
            }
            if (count > max_elements)
            {
                max_elements = count;
                best_subset_index = i;
            }
        }

        if (best_subset_index == -1) // No valid subset found
            break;

        // Remove elements of the best subset from uncovered set
        for (int elem : S[best_subset_index])
        {
            uncovered.erase(elem);
        }

        lazyseq.push_back(best_subset_index + 1); // Store 1-based index
    }

    return lazyseq;
}

int main()
{
    int n = 10;
    vector<int> U = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int m = 4;
    vector<vector<int>> S = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10}};
    vector<int> lazyseq = findLazySeq(U, S);
    cout << "The lazy sequence is: ";
    for (int i = 0; i < lazyseq.size(); i++)
    {
        cout << lazyseq[i] << " ";
    }
    return 0;
}