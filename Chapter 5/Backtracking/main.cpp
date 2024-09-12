#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool backtracking(vector<vector<bool>> visited, int i, int j, string destination, vector<vector<string>> cities) {
    if (cities[i][j] == destination) {
        return true;
    }

    if (i < 0 || i >= cities.size() || j < 0 || j >= cities[0].size() || visited[i][j]) return false;

    visited[i][j] = true;

    if (
        backtracking(visited, i + 1, j, destination, cities) ||
        backtracking(visited, i - 1, j, destination, cities) ||
        backtracking(visited, i, j + 1, destination, cities) ||
        backtracking(visited, i, j - 1, destination, cities)) {
            return true;
        }
    
    visited[i][j] = false;
    return false;

}

int main() {
    vector<vector<string>> cities = 
    {
        {"A", "", "C"},
        {"D", "" , "E"}, 
        {"F", "", "D"}
    };

    vector<vector<bool>> visited = {
        {false, false, false},
        {false, false, false},
        {false, false, false}
    };
    string destination = "F";
    for (int i=0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            if (!visited[i][j]) {
                bool result = backtracking(visited, i, j, destination, cities);
                if (result) {
                    cout << "Found destination: " << destination << endl;
                    break;
                }
            }
        }
    }

    return 0;
}