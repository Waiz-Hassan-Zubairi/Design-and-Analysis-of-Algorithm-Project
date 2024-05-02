#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
using namespace std;
struct Box
{
    int len;
    int brd;

    Box(int l, int b) : len(l), brd(b)
    {
    }
};
void readFile(string& fileName, int& n, vector<pair<Box, int>>& boxes)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    file >> n;
    string line;
    int l1, b1, l2, b2, p;
    getline(file, line);
    while (getline(file, line))
    {
        if (sscanf_s(line.c_str(), "(%d,%d),{%d}", &l1, &b1, &p) == 3)
        {
            boxes.emplace_back(Box(l1, b1), p);
        }
        else if (sscanf_s(line.c_str(), "(%d,%d),(%d,%d),{%d}", &l1, &b1, &l2, &b2, &p) == 5)
        {
            boxes.emplace_back(Box(l1, b1), p);
            boxes.emplace_back(Box(l2, b2), p);
        }
        else
        {
            cerr << "Error reading line: " << line << endl;
            exit(EXIT_FAILURE);
        }
    }
}
int bottomUpDynamicProgramming(vector<pair<Box, int>>& boxes, int n, vector<int>& path)
{
    vector<int> memo(n + 1, -1);
    vector<int> lastBoxIndex(n + 1, -1);
    memo[0] = 0;
    for (int i = 1; i <= n; i=i+1)
    {
        int maxProfit = INT_MIN;
        int lastBox = -1;
        int j = 0;
        while (j < boxes.size())
        {
            int size = boxes[j].first.len * boxes[j].first.brd;
            if (i >= size)
            {
                int currentProfit = boxes[j].second + memo[i - size];
                if (currentProfit > maxProfit)
                {
                    maxProfit = currentProfit;
                    lastBox = j;
                }
            }
            j=j+1;
        }

        memo[i] = maxProfit;
        lastBoxIndex[i] = lastBox;
    }
    for (int currentIndex = n; currentIndex > 0 && lastBoxIndex[currentIndex] != -1;)
    {
        path.push_back(lastBoxIndex[currentIndex]);
        currentIndex -= boxes[lastBoxIndex[currentIndex]].first.len * boxes[lastBoxIndex[currentIndex]].first.brd;
    }

    return memo[n];
}
int main()
{
    int n;
    string fileName = "TestCase3.txt";
    vector<pair<Box, int>> boxes;
    readFile(fileName, n, boxes);
    vector<int> path;
    int result = bottomUpDynamicProgramming(boxes, n, path);
    cout << "Maximized Profit: " << result << endl;
    cout << "Path used to maximize profit: ";
    for (int i = path.size() - 1; i >= 0; i=i-1)
    {
        cout << "(" << boxes[path[i]].first.len << "," << boxes[path[i]].first.brd << ") ";
    }
    return 0;
}
