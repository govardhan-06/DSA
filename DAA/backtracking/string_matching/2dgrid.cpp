// C++ program to search a word in a 2D grid
#include <bits/stdc++.h>
using namespace std;

// This function searches for the given word
// in all 8 directions from the coordinate.
bool search2D(vector<vector<char>> grid, int row, int col, string word) {
    int m = grid.size();
    int n = grid[0].size();
    
    // return false if the given coordinate
    // does not match with first index char.
    if (grid[row][col] != word[0])
      return false;
 
    int len = word.size();
    
    // x and y are used to set the direction in which
    // word needs to be searched.
    vector<int>x = { -1, -1, -1, 0, 0, 1, 1, 1 };
    vector<int>y = { -1, 0, 1, -1, 1, -1, 0, 1 };
 
    // This loop will search in all the 8 directions
    // one by one. It will return true if one of the 
    // directions contain the word.
    for (int dir = 0; dir < 8; dir++) {
      
        // Initialize starting point for current direction
        int k, currX = row + x[dir], currY = col + y[dir];
 
        // First character is already checked, match remaining
        // characters
        for (k = 1; k < len; k++) {
          
            // break if out of bounds
            if (currX >= m || currX < 0 || currY >= n || currY < 0)
                break;
 
            if (grid[currX][currY] != word[k])
                break;
 
            //  Moving in particular direction
            currX += x[dir], currY += y[dir];
        }
 
        // If all character matched, then value of must
        // be equal to length of word
        if (k == len)
            return true;
    }
    
    // if word is not found in any direction,
    // then return false
    return false;
}

// This function calls search2D for each coordinate
vector<vector<int>>searchWord(vector<vector<char>>grid, string word){
    int m = grid.size();
    int n = grid[0].size();
    
    vector<vector<int>>ans;
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            
            // if the word is found from this coordinate,
            // then append it to result.
            if(search2D(grid, i, j, word)){
                ans.push_back({i, j});
            }
        }
    }
    
    return ans;
}

void printResult(vector<vector<int>> ans) {
    for (int i=0; i<ans.size(); i++) {
        cout << "{" << ans[i][0] << "," << ans[i][1] << "}" << " ";
    }
    cout<<endl;
}

int main() {
    vector<vector<char>> grid = 
    {{'a','b','a','b'},{'a','b','e','b'},{'e','b','e','b'}};
    string word = "abe";
    
    vector<vector<int>> ans = searchWord(grid, word);
    
    printResult(ans);
}
