#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
using namespace std;
struct Blk
{
    int wth;
    int hgt;

    Blk(int w, int h) : wth(w), hgt(h) 
    {}
};
void rdTstCse(const string& fn, int& n, vector<pair<Blk, int>>& prc)
{
    ifstream file(fn);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << fn << endl;
        exit(EXIT_FAILURE);
    }
    file >> n;
    string line;
    getline(file, line);
    int w1, h1, w2, h2, pr;
    while (getline(file, line))
    {
        if (sscanf_s(line.c_str(), "(%d,%d),{%d}", &w1, &h1, &pr) == 3)
        {
            prc.emplace_back(Blk(w1, h1), pr);
        }
        else if (sscanf_s(line.c_str(), "(%d,%d),(%d,%d),{%d}", &w1, &h1, &w2, &h2, &pr) == 5)
        {
            prc.emplace_back(Blk(w1, h1), pr);
            prc.emplace_back(Blk(w2, h2), pr);
        }
        else
        {
            cerr << "Error reading line: " << line << endl;
            exit(EXIT_FAILURE);
        }
    }
}
pair<int, vector<pair<Blk, int>>> simRcvWthPth(vector<pair<Blk, int>>& prc, int n)
{
    if (n <= 0)
    {
        return { 0, {} };
    }
    int mxPft = INT_MIN;
    vector<pair<Blk, int>> slctdBks;
    int i = 0;
    while (i < prc.size())
    {
        int sz = prc[i].first.wth * prc[i].first.hgt;
        if (n >= sz)
        {
            auto sbprb = simRcvWthPth(prc, n - sz);
            int crtPft = prc[i].second + sbprb.first;

            if (crtPft > mxPft)
            {
                mxPft = crtPft;
                slctdBks = sbprb.second;
                slctdBks.emplace_back(prc[i].first, prc[i].second);
            }
        }
        i++;
    }

    return { mxPft, slctdBks };
}

int main()
{
    string fn = "TestCase2.txt";
    int n;
    vector<pair<Blk, int>> prc;
    rdTstCse(fn, n, prc);
    auto ans = simRcvWthPth(prc, n);
    cout << "Maximized Profit: " << ans.first << endl;
    cout << "Selected Blocks: ";
    int j = 0;
    while (j < ans.second.size())
    {
        cout << "(" <<ans.second[j].first.wth << "," << ans.second[j].first.hgt << ") ";
        j++;
    }

    return 0;
}
