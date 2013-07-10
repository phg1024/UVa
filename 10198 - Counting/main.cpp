#include <iostream>
#include <string>
using namespace std;

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct BigInt
{
    static const size_t PRECISION = 512; 
    BigInt():
        L(1)
    {
        memset(data, 0, sizeof(char)*PRECISION);
    }

    BigInt(int num)
    {
        sprintf(data, "%d", std::abs(num));
        L = strlen(data);
        std::reverse(data, data+L);
        for(int i=0;i<L;i++)
            data[i] -= '0';
    }

    BigInt(const BigInt& other):
        L(other.L)
    {
		memset(data, 0, sizeof(char)*PRECISION);
        memcpy(data, other.data, sizeof(char)*other.L);
    }

    BigInt& operator=(const BigInt& other)
    {
        if( this != &other )
        {
			memset(data, 0, sizeof(char)*PRECISION);
            L = other.L;
            memcpy(data, other.data, sizeof(char)*other.L);
        }
        return (*this);
    }

    const char& operator()(size_t pos) const
    {
        return data[pos];
    }

    char& operator()(size_t pos)
    {
        return data[pos];
    }

    BigInt operator+(const BigInt& rhs) const;

    friend ostream& operator<<(ostream& os, const BigInt& num);

    size_t L;
    char data[PRECISION];
};

BigInt BigInt::operator+(const BigInt& rhs) const
{
    BigInt v;

    if( rhs.L > L ) v.L = rhs.L;
    else v.L = L;

    for(size_t i=0;i<v.L;i++)
    {
        char val = data[i] + rhs(i) + v(i);
        if( val >= 10 )
        {
            v(i) = val - 10;
            v(i+1)++;
        }
        else
            v(i) = val;
    }

    if( v(v.L) != 0 ) v.L++;
		
    return v;
}

ostream& operator<<(ostream& os, const BigInt& num)
{
    for(int i=num.L-1;i>=0;i--)
        os << (char)(num(i) + '0');

    return os;
}

void init(BigInt values[])
{
    values[1] = BigInt(2);
    values[2] = BigInt(5);
    values[3] = BigInt(13);

    BigInt v(7);            // values[1] + values[2]
    for(int i=4;i<1001;i++)
    {
        const BigInt& vi = values[i-1];
        values[i] = vi + vi + v;    // values[i-1] * 2 + values[i-2] + values[i-3]
        v = vi + values[i-2];
    }
}

int main()
{
    BigInt values[1001];
    init(values);

    int n;
    while( cin >> n )
    {
        cout << values[n] << endl;
    }
    return 0;
}
