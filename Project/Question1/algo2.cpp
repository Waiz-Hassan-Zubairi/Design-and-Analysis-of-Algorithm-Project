#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
using namespace std;
struct Box
{
    int length;
    int breadth;
    Box(int l, int b) : length(l), breadth(b) 
    {
    }
};
void genericFileReading(string& fileName, int& num, vector<pair<Box, int>>& boxes) 
{
    string line;
    int len1, brdth1, len2, brdth2, price;
    ifstream file(fileName);
    if (!file.is_open()) 
    {
        cerr << "Error opening file: " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    file >> num;
    getline(file, line);
    while (getline(file, line))
    {
       
        if (sscanf_s(line.c_str(), "(%d,%d),{%d}", &len1, &brdth1, &price) == 3)
        {
            boxes.emplace_back(Box(len1, brdth1), price);
        }
        else if (sscanf_s(line.c_str(), "(%d,%d),(%d,%d),{%d}", &len1, &brdth1, &len2, &brdth2, &price) == 5)
        {
            boxes.emplace_back(Box(len1, brdth1), price);
            boxes.emplace_back(Box(len2, brdth2), price);
        }
        else
        {
            cerr << "Error"<< endl;
            exit(EXIT_FAILURE);
        }
    }
}
int memorecursion(vector<pair<Box, int>>& boxes, int num, vector<int>& memo) 
{
    if (memo[num] != -1)
    {
        return memo[num];
    }
    if (num <= 0)
    {
        return 0;
    }
    int maxProfit = INT_MIN;
    auto it = boxes.begin();
    while (it != boxes.end())
    {
        int s = it->first.length * it->first.breadth;
        if (num >= s)
        {
            maxProfit = max(maxProfit, it->second + memorecursion(boxes, num - s, memo));
        }
        it=it+1;
    }
    memo[num] = maxProfit;
    return maxProfit;
}

int main()
{
    int num;
    string fileName = "TestCase1.txt";
    vector<pair<Box, int>> boxes;
    genericFileReading(fileName, num, boxes);
    vector<int> memo2(num + 1, -1);
    int ans = memorecursion(boxes, num, memo2);
    cout << "Maximizmum Profit: " << ans<< endl;
    return 0;
}
