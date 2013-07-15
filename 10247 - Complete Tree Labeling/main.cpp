#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

struct BigInt
{
	typedef int digit_t;
	static const unsigned int base = 10000;
	static const unsigned int w = 4;
	
    static const size_t PRECISION = 4096;
    BigInt():
        L(1)
    {
        memset(data, 0, sizeof(digit_t)*PRECISION);
    }

    BigInt(int num)
    {
        memset(data, 0, sizeof(digit_t)*PRECISION);

		L = 0;
		while( num )
		{
			data[L++] = num % base;
			num /= base;
		}
    }

    BigInt(const BigInt& other):
        L(other.L)
    {
        memset(data, 0, sizeof(digit_t)*PRECISION);
        memcpy(data, other.data, sizeof(digit_t)*other.L);
    }

    BigInt& operator=(const BigInt& other)
    {
        if( this != &other )
        {
            memset(data, 0, sizeof(digit_t)*PRECISION);
            L = other.L;
            memcpy(data, other.data, sizeof(digit_t)*other.L);
        }
        return (*this);
    }

    const digit_t& operator()(size_t pos) const
    {
        return data[pos];
    }

    digit_t& operator()(size_t pos)
    {
        return data[pos];
    }

    void leftShift(size_t n)
    {
        for(int i=L-1;i>=0;i--)
            data[i+n] = data[i];

        for(int i=n-1;i>=0;i--)
            data[i] = 0;

        L += n;
    }

    void rightShift(size_t n)
    {
        for(int i=0;i<L-n;i++)
            data[i] = data[i+n];
        L -= n;
    }

    void zero_justify();

    BigInt operator+(const BigInt& rhs) const;
    BigInt operator+(int rhs) const;
    BigInt operator-(const BigInt& rhs) const;
    BigInt operator-(int rhs) const;
    BigInt operator*(const BigInt& rhs) const;
    BigInt operator*(int rhs) const;
	BigInt operator^(int n) const;
    BigInt operator/(const BigInt& rhs) const;
    BigInt operator/(int rhs) const;

    bool operator<(const BigInt& rhs) const;
    bool operator<=(const BigInt& rhs) const;
    bool operator>(const BigInt& rhs) const;
    bool operator>=(const BigInt& rhs) const;
    bool operator==(const BigInt& rhs) const;

    friend ostream& operator<<(ostream& os, const BigInt& num);
    friend istream& operator>>(istream& is, const BigInt& num);

    size_t L;
    digit_t data[PRECISION];
};

BigInt BigInt::operator+(const BigInt& rhs) const
{
    BigInt v = (*this);

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

BigInt BigInt::operator+(int rhs) const
{
    BigInt r(rhs);
    return (*this) + r;
}

BigInt BigInt::operator-(const BigInt& rhs) const
{
	// assumes (*this) > rhs
    BigInt v = (*this);

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

BigInt BigInt::operator-(int rhs) const
{
    BigInt r(rhs);
    return (*this) - r;
}

BigInt BigInt::operator*(const BigInt& rhs) const
{
    BigInt res(0);
	res.L = rhs.L + L;
    for(size_t i=0;i<rhs.L;i++)
    {
        digit_t digit = rhs(i);
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

BigInt BigInt::operator*(int rhs) const
{
    return (*this) * BigInt(rhs);
}

BigInt BigInt::operator^(int n) const
{
	if( n == 0 ) return BigInt(1);
	
	if( n == 1 )
		return (*this);
	
	int m = n / 2;
	int k = n - m * 2;
	
	BigInt v = (*this)^m;
	BigInt vm = (*this)^k;
	return v * v * vm;	
}

BigInt BigInt::operator/(const BigInt& rhs) const
{
    if( rhs > (*this) )
    {
        return BigInt(0);
    }
    else
    {
        BigInt lhs = (*this);
        BigInt cur = rhs;

        BigInt res(0);
        int offset = lhs.L - rhs.L;
        cur.leftShift(offset);

        while( offset >= 0 )
        {
			int high = base - 1;
			int low = 0;
			int v = (high + low + 1) / 2;
			
            while( high > low )
            {
				BigInt b = cur * v;
				if( b > lhs )
					high = v - 1;
				else
					low = v;
				
				v = (high + low + 1)  / 2;
            }
			
			lhs = lhs - cur * v;
			res(offset) = res(offset) + v;
            res.L++;
            
            offset--;
            cur.rightShift(1);
        }

        // remove leading zeros
        res.zero_justify();

        return res;
    }
}

BigInt BigInt::operator/(int rhs) const
{
    return (*this) / BigInt(rhs);
}

void BigInt::zero_justify()
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

bool BigInt::operator<(const BigInt& rhs) const
{
    return rhs > (*this);
}

bool BigInt::operator<=(const BigInt& rhs) const
{
    return (*this) < rhs || (*this) == rhs;
}

bool BigInt::operator>(const BigInt& rhs) const
{
        if( L > rhs.L )
        {
            return true;
        }
        else if( L < rhs.L )
        {
            return false;
        }
        else
        {
            for(int i=L-1;i>=0;i--)
            {
                if( data[i] != rhs(i) )
                {
                    if( data[i] > rhs(i) )
                        return true;
                    else
						return false;
                }
            }

            return false;
        }
}

bool BigInt::operator>=(const BigInt& rhs) const
{
    return ((*this) > rhs) || ((*this) == rhs);
}

bool BigInt::operator==(const BigInt& rhs) const
{
    if( L != rhs.L ) return false;

    for(size_t i=0;i<L;i++)
        if( data[i] != rhs(i) ) return false;
    return true;
}


ostream& operator<<(ostream& os, const BigInt& num)
{
	os << num(num.L-1);
    for(int i=num.L-2;i>=0;i--)
        os << setw(BigInt::w) << setfill('0') << num(i);

    return os;
}

static const int MAXK = 22;
static const int MAXD = 22;
static const int MAXFACS = 4096;
BigInt values[MAXK][MAXD];
BigInt facs[MAXFACS];

void init()
{	 
	facs[0] = 1;
	for(int i=1;i<MAXFACS;i++)
		facs[i] = facs[i-1]*i;
	
	values[0][1] = BigInt(1);
	for(int k=1;k<MAXK;k++)
	{
		values[k][0] = BigInt(1);
		values[k][1] = facs[k];
	}

    for(int d=1;d<MAXD;d++)
        values[1][d] = BigInt(1);
	
	for(int k=2;k<MAXK;k++)
	{
		for(int d=1;k*d<=21;d++)
		{
			int m = (powf(k, d+1)-1) / (k - 1) - 1;
			int km = m / k;
						
			values[k][d] = facs[m] / ((facs[km])^k) * ((values[k][d-1])^k);			
		}
	}
}

int main()
{
    int k, d;
    init();
    while( cin >> k >> d )
    {
        cout << values[k][d] << endl;
    }
    return 0;
}
