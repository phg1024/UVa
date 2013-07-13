#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

template <typename T>
struct BigInt
{
    static const size_t PRECISION = 24;
    BigInt():
        L(1)
    {
        memset(data, 0, sizeof(T)*PRECISION);
    }

    BigInt(unsigned int num)
    {
        memset(data, 0, sizeof(T)*PRECISION);

		int i = 0;
		while ( num )
		{
			data[i++] = (num % base);
			num /= base;
		}
		L = i;
    }

    BigInt(const BigInt& other):
        L(other.L)
    {
        memset(data, 0, sizeof(T)*PRECISION);
        memcpy(data, other.data, sizeof(T)*other.L);
    }

    BigInt& operator=(const BigInt& other)
    {
        if( this != &other )
        {
            memset(data, 0, sizeof(T)*PRECISION);
            L = other.L;
            memcpy(data, other.data, sizeof(T)*other.L);
        }
        return (*this);
    }

    const T& operator()(size_t pos) const
    {
        return data[pos];
    }

    T& operator()(size_t pos)
    {
        return data[pos];
    }

    void zero_justify();

    BigInt operator+(const BigInt& rhs) const;
	BigInt& operator+=(const BigInt& rhs);
    BigInt operator-(const BigInt& rhs) const;
    BigInt operator*(const BigInt& rhs) const;

	template <typename BT>
    friend ostream& operator<<(ostream& os, const BigInt<BT>& num);

    size_t L;
    unsigned int data[PRECISION];
	static const int base = 10000;
	static const int w = 4;
};

template <typename T>
BigInt<T> BigInt<T>::operator+(const BigInt<T>& rhs) const
{
    BigInt<T> v = (*this);

    size_t maxL = max(v.L, rhs.L);

    v.L = maxL;

    for(size_t i=0;i<maxL;i++)
    {
		v(i) += rhs(i);
		
        if( v(i) >= base )
        {
            v(i) -= base;
            v(i+1)++;
        }
    }

    if( v(v.L) != 0 ) v.L++;

    return v;
}

template <typename T>
BigInt<T>& BigInt<T>::operator+=(const BigInt<T>& rhs)
{
    size_t maxL = max(L, rhs.L);

    L = maxL;

    for(size_t i=0;i<maxL;i++)
    {
		data[i] += rhs(i);
		
        if( data[i] >= base )
        {
            data[i] -= base;
            data[i+1]++;
        }
    }

    if( data[L] != 0 ) L++;

    return (*this);
}

template <typename T>
BigInt<T> BigInt<T>::operator-(const BigInt<T>& rhs) const
{
    BigInt v = (*this);

	// assume (*this) > rhs
    // do the normal subtraction
    size_t maxL = max(v.L, rhs.L);
    for(int i=0;i<maxL;i++)
    {
        int val = v(i) - rhs(i);
        if( val < 0 )
        {
            v(i) = val + base;
            v(i+1)--;
        }
        else
            v(i) = val;
    }

    v.L = maxL;

    // remove leading zeros
    v.zero_justify();
            
    return v;
}

template <typename T>
BigInt<T> BigInt<T>::operator*(const BigInt<T>& rhs) const
{
    BigInt<T> res(0);
	res.L = rhs.L + L;
    for(size_t i=0;i<rhs.L;i++)
    {
        T digit = rhs(i);
        for(size_t j=0;j<L;j++)
        {
            res(i+j) += digit * data[j];
            res(i+j+1) += res(i+j) / base;
            res(i+j) %= base;
        }
    }
	
    res.zero_justify();

    return res;
}

template <typename T>
void BigInt<T>::zero_justify()
{
    for(int i=L-1;i>=0;i--)
    {
        if( data[i] != 0 ) break;
        L--;
    }

    if( L == 0 )
    {
        L = 1;
    } 
}

template <typename BT>
ostream& operator<<(ostream& os, const BigInt<BT>& num)
{
	os << num(num.L-1);
    for(int i=num.L-2;i>=0;i--)
        os << setw(num.w) << setfill('0') << num(i);

    return os;
}

static const int MAXN = 151;
static const int MAXD = 151;
BigInt<unsigned int> values[MAXN][MAXD];
BigInt<unsigned int> result[MAXN][MAXD];

void init()
{	
	for(unsigned int d=0;d<MAXD;d++)
		values[0][d] = BigInt<unsigned int>(1);
	
	for(unsigned int n=1;n<MAXN;n++)
	{
		for(unsigned int d=1;d<MAXD;d++)
		{
			for(unsigned int k=0;k<=n-1;k++)
				values[n][d] += values[k][d-1] * values[n-k-1][d];
			result[n][d] = values[n][d] - values[n][d-1];
		}
	}
}

int main()
{	
	init();
    unsigned int n, d;
    while( scanf("%u %u", &n, &d) != EOF )
    {
		n = n/2;
        cout << result[n][d] << endl;
    }
    return 0;
}
