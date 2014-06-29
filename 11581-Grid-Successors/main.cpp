#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
using namespace std;

string tostring(const vector<vector<int>>& g) {
  string s;
  for(auto y:g){
    for(auto x:y) {
      s.push_back('0' + x);
    }
  }
  return s;
}

int main()
{
  int n;
  cin >> n;
  cin.ignore();
  while( n ) {
    vector<vector<int>> g;
    g.resize(5);
    cin.ignore();
    for(auto& x:g) x.resize(5, 0);
    for(int i=0;i<3;++i) {
      string s;
      getline(cin, s);
      for(int j=0;j<3;++j) {
        g[i+1][j+1] = s[j] - '0';
      }
    }
  int idx = 0;
  auto pfunc = [](vector<vector<int>>& g){
    for(auto y:g) {for(auto x:y) cout << x; cout << endl;}
  };
  map<string, int> visited;
  string pattern0 = tostring(g);
  visited[pattern0] = 0;
  //cout << idx <<": " << pattern0 << endl;

  while( true ) {
    string pattern = pattern0;
    int neighbors[] = {-5, -1, 1, 5};
    for(int i=1;i<4;++i) {
      for(int j=1;j<4;++j) {
        int pos = i*5+j;
        int sum = 0;
        for(int k=0;k<4;++k) {
          sum += pattern0[pos+neighbors[k]] - '0';
        }
        pattern[pos] = (sum & 0x1) + '0';
      }
    }
    ++idx;
    //cout << idx <<": " << pattern << endl;
    auto it = visited.find(pattern);
    if( it != visited.end() ){
      cout << it->second-1 << endl;
      break;
    }
    else visited[pattern] = idx;
    pattern0 = pattern;
  }
  --n;
  }
  return 0;
}
