#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

int add_bignum(const string& a, const string& b)
{
    string n1 = a;
    string n2 = b;
    std::reverse(n1.begin(), n1.end());
    std::reverse(n2.begin(), n2.end());


    int L = min(n1.size(), n2.size());

    char c[12] = {0};
    int carry = 0;
    for(int i=0;i<L;i++)
    {
        int val = (n1[i] - '0') + (n2[i] - '0') + c[i];
        if( val >= 10 )
        {
            carry++;
            c[i] = val-10;
            c[i+1]++;
        }
        else
            c[i] = val;
    }
    if( n1.size() > n2.size() )
    {
        for(int i=L;i<n1.size();i++)
        {
            int val = (n1[i] - '0') + c[i];
            if( val >= 10 )
            {
                carry++;
                c[i] = val - 10;
                c[i+1]++;
            }
            else
                c[i] = val;
        }
    }
    else
    {
        for(int i=L;i<n2.size();i++)
        {
            int val = (n2[i] - '0') + c[i];
            if( val >= 10 )
            {
                carry++;
                c[i] = val - 10;
                c[i+1]++;
            }
            else
                c[i] = val;
        }
    }


    return carry;
}

int main(){
    while( true )
    {
        string a, b;
        cin >> a >> b;

        if( a == "0" && b == "0" )
            break;
        else if( a == "0" || b == "0" )
            cout << "No carry operation." << endl;
        else
        {
            int carry = add_bignum(a, b);

            switch( carry )
            {
                case 0:
                    {
                    cout << "No carry operation." << endl;
                    break;
                    }
                case 1:
                    {
                    cout << "1 carry operation." << endl;
                    break;
                    }
                default:
                    {
                    cout << carry << " carry operations." << endl;
                    break;
                    }
            }
        }
    }
    return 0;
}

