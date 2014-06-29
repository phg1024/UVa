#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
using namespace std;

struct Grid {
    Grid(){}
    Grid(int N):m(N),n(N) {
        init();
    }
    Grid(int m, int n):m(m), n(n) {
        init();
    }
    Grid(int m, int n, const vector<vector<char>>& g):
        m(m), n(n), g(g){}
    void init() {
        g.resize(m);
        for(auto &x : g) {
            x.resize(n);
        }        
    }
    char operator()(int r, int c) const {
        return g[r][c];
    }
    char& operator()(int r, int c){
        return g[r][c];
    }
    void read() {
        for(int i=0;i<m;++i) {
            string s;
            cin >> s;
            for(int j=0;j<n;++j) {
                g[i][j] = s[j];
            }
        }        
    }
    
    Grid rotate(int i) {
        switch(i) {
        case 0: {
            return (*this);
        }
        case 1: {
            Grid gr(n, m);
            for(int i=0;i<n;++i) {
                for(int j=0;j<m;++j) {
                    gr(i, j) = (*this)(m-1-j, i);
                }
            }
            return gr;
        }
        case 2: {
            Grid gr(m, n);
            for(int i=0;i<m;++i) {
                for(int j=0;j<n;++j) {
                    gr(i, j) = (*this)(m-1-i, n-1-j);
                }
            }
            return gr;
        }
        case 3: {
            Grid gr(n, m);
            for(int i=0;i<n;++i) {
                for(int j=0;j<m;++j) {
                    gr(i, j) = (*this)(j, n-1-i);
                }
            }
            return gr;
        }
        default:
            return (*this);
        }
    }
    void print() {
        for(auto x:g) {
            for(auto y:x) {
                cout << y;
            }
            cout << endl;
        }
    }
    bool match(const Grid& b, int r, int c) {
        for(int i=0;i<b.m;++i) {
            for(int j=0;j<b.n;++j) {
                if( b(i, j) != g[i+r][j+c] ) return false;
            }
        }
        return true;
    }
    int m, n;
    vector<vector<char>> g;
};

vector<int> solve(Grid A, Grid B) {
    vector<int> res(4, 0);
    Grid b[4];
    for(int i=0;i<4;++i){
        b[i] = B.rotate(i);
        for(int r=0;r<=A.m-B.m;++r) {
            for(int c=0;c<=A.n-B.n;++c) {
                if( A.match(b[i], r, c) ) ++res[i];
            }
        }
    }
    
    return res;
}

int main()
{
    int N, n;
    while( true ) {
        cin >> N >> n;
        if( N==0 && n==0 ) break;
        
        Grid A(N), B(n);
        A.read();
        B.read();
        
        vector<int> count = solve(A, B);
        for(int i=0;i<count.size();++i) {
            cout << count[i] << (i==count.size()-1?"\n":" ");
        }
    }
}
