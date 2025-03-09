#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Function to place schools
vector<int> placeSchools(vector<int> &X, vector<vector<int>> &S)
{
    unordered_set<int> uncovered(X.begin(), X.end()); // Set of all uncovered villages
    vector<int> vill_school;

    while (!uncovered.empty())
    {
        int maxElem = 0, best_village_index = -1;

        // Find the village covering the most uncovered villages
        for (int i = 0; i < S.size(); i++)
        {
            int count = 0;
            for (int j = 0; j < S[i].size(); j++)
            {
                if (uncovered.count(S[i][j])) // Check if village is uncovered
                    count++;
            }

            if (count > maxElem)
            {
                maxElem = count;
                best_village_index = i;
            }
        }

        // If no more villages can be covered, break (safety check)
        if (best_village_index == -1)
            break;

        // Place a school in this village
        vill_school.push_back(best_village_index + 1); // +1 to make it 1-based index

        // Remove covered villages from uncovered set
        for (int v : S[best_village_index])
        {
            uncovered.erase(v);
        }
    }

    return vill_school;
}

int main()
{
    int n = 10;
    vector<int> X = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int m = 4;
    vector<vector<int>> S = {{1, 2, 5, 6, 7}, {3, 4, 8, 9}, {2, 8, 9, 10}, {1, 3, 4, 8, 9, 10}};

    vector<int> vill_school = placeSchools(X, S);

    // Output the result
    cout << "The schools are placed at villages: ";
    for (int v : vill_school)
    {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
