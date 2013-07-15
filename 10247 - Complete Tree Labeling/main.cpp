#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct BigInt
{
    static const size_t PRECISION = 65536;
    BigInt():
        sign(Positive),
        L(1)
    {
        memset(data, 0, sizeof(char)*PRECISION);
    }

    BigInt(int num)
    {
        memset(data, 0, sizeof(char)*PRECISION);
        sprintf(data, "%d", std::abs(num));
        L = strlen(data);
        std::reverse(data, data+L);
        for(int i=0;i<L;i++)
            data[i] -= '0';

        if( num < 0 )
            sign = Negative;
        else
            sign = Positive;
    }

    BigInt(const BigInt& other):
        sign(other.sign),
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
            sign = other.sign;
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

    BigInt negate() const
    {
        BigInt v = (*this);
        v.sign = (v.sign == Positive)?Negative:Positive;
        return v;
    }

    BigInt abs() const
    {
        BigInt v = (*this);
        v.sign = Positive;
        return v;
    }

    BigInt leftShift(size_t n) const
    {
        BigInt v;
        memcpy(v.data + n, data, sizeof(char)*L);
        v.L = L + n;
        v.sign = sign;
        return v;
    }

    BigInt rightShift(size_t n) const
    {
        BigInt v;
        memcpy(v.data, data + n, sizeof(char)*(L-n));
        v.L = L - n;
        v.sign = sign;
        return v;
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

    enum Sign
    {
        Negative = 0,
        Positive = 1
    } sign;
    size_t L;
    char data[PRECISION];
};

BigInt BigInt::operator+(const BigInt& rhs) const
{
    if( sign == rhs.sign )
    {
        // + + +
        // - + -
        BigInt v = (*this);

        size_t maxL = max(v.L, rhs.L);

        v.L = maxL;

        for(size_t i=0;i<maxL;i++)
        {
            char val = v(i) + rhs(i);
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
    else
    {
        // + + - 
        // - + +
        return (*this) - rhs.negate();
    }
}

BigInt BigInt::operator+(int rhs) const
{
    BigInt r(rhs);
    return (*this) + r;
}

BigInt BigInt::operator-(const BigInt& rhs) const
{
    if( sign == rhs.sign )
    {
        // - - -
        // + - +
        BigInt v = (*this);

        if( v.abs() >= rhs.abs() )
        {
            // do the normal subtraction
            size_t maxL = max(v.L, rhs.L);
            for(int i=0;i<maxL;i++)
            {
                char val = v(i) - rhs(i);
                if( val < 0 )
                {
                    v(i) = val + 10;
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
        else
        {
            // do rhs - v, and negate the result
            return (rhs - v).negate();
        }
    } 
    else
    {
        // - - +
        // + - -
        return (*this) + rhs.negate();
    }
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
        char digit = rhs(i);
        for(size_t j=0;j<L;j++)
        {
			res(i+j) += digit * data[j];
			res(i+j+1) += res(i+j) / 10;
			res(i+j) %= 10;
        }
    }

    res.sign = ( res.sign == sign )?BigInt::Positive:BigInt::Negative;
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

        BigInt res(0);
        int offset = lhs.L - rhs.L;

        while( offset >= 0 )
        {
            res = res.leftShift(1);
            BigInt cur = rhs.leftShift(offset);

            while( lhs >= cur )
            {
                lhs = lhs - cur;
                res = res + 1;
            }
            
            offset--;
        }

        // remove leading zeros
        res.sign = (sign == rhs.sign)?Positive:Negative;
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
        sign = BigInt::Positive;
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
    if( sign > rhs.sign ) return true;
    else if( sign < rhs.sign ) return false;
    else
    {
        if( L > rhs.L )
        {
            return (sign == Positive)?true:false;
        }
        else if( L < rhs.L )
        {
            return (sign == Positive)?false:true;
        }
        else
        {
            for(int i=L-1;i>=0;i--)
            {
                if( data[i] != rhs(i) )
                {
                    if( data[i] > rhs(i) )
                    {
                        return (sign == Positive)?true:false;
                    }
                    else
                    {
                        return (sign == Positive)?false:true;
                    }
                }
            }

            return false;
        }
    }
}

bool BigInt::operator>=(const BigInt& rhs) const
{
    return ((*this) > rhs) || ((*this) == rhs);
}

bool BigInt::operator==(const BigInt& rhs) const
{
    if( sign != rhs.sign ) return false;
    if( L != rhs.L ) return false;

    for(size_t i=0;i<L;i++)
        if( data[i] != rhs(i) ) return false;
    return true;
}


ostream& operator<<(ostream& os, const BigInt& num)
{
    if( num.sign == BigInt::Negative ) os << '-';
    for(int i=num.L-1;i>=0;i--)
        os << (char)(num(i) + '0');

    return os;
}

istream& operator>>(istream& is, BigInt& num)
{
    char buf[BigInt::PRECISION] = {0};

    is >> buf;

    num.L = strlen(buf);
    strcpy(num.data, buf);

    std::reverse(num.data, num.data+num.L);
    for(int i=0;i<num.L;i++)
        num.data[i] -= '0';
}

BigInt combinationNumber(int n, int k)
{
	BigInt u(1), d(1);
	for(int i=1;i<=k;i++)
	{
		u = u * (n - i + 1);
		d = d * i;
	}	
	return u / d;
}

static const int MAXK = 22;
static const int MAXD = 22;
BigInt values[MAXK][MAXD];

void init()
{	 
	values[0][1] = BigInt(1);
	for(int k=1;k<MAXK;k++)
	{
		values[k][0] = BigInt(1);
		values[k][1] = values[k-1][1] * k;
	}
	
	for(int k=2;k<MAXK;k++)
	{
		for(int d=1;k*d<=21;d++)
		{
			BigInt p(1);
			int m = (powf(k, d+1)-1) / (k - 1) - 1;
			m /= k;
			for(int j=2;j<=k;j++)
			{
				int nn = m*j;
				int kk = m;
				p = p * combinationNumber(nn, kk);
			}
			values[k][d] = p * (values[k][d-1]^k);
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
