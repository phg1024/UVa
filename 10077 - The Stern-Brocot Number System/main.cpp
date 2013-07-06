#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

struct Fraction
{
    Fraction(unsigned int uVal, unsigned int dVal):u(uVal),d(dVal){}

    Fraction operator+(const Fraction& f)
    {
        Fraction res = (*this);
        res.u += f.u;
        res.d += f.d;
        return res;
    }

    bool operator<(const Fraction& f) const
    {
        if( u == 0 ) return true;
        else
        {
            return u * f.d < f.u * d;
        }
    }

    bool operator==(const Fraction& f) const
    {
        return (u == f.u && d == f.d);
    }

    bool operator!=(const Fraction& f) const
    {
        return !((*this) == f);
    }


    unsigned int u, d;
};

int main()
{
    int m, n;
    while( true )
    {
        scanf("%d %d", &m, &n);
        if( m == 1 && n == 1 ) break;
        Fraction left(0, 1), right(1, 0);
        Fraction mid = left + right;
        Fraction target(m, n);

        int pos = 0;
        char rep[16384] = {0};

        while( mid != target  )
        {
            if( target < mid )
            {
                rep[pos++] = 'L';
                right = mid;
            }
            else
            {
                rep[pos++] = 'R';
                left = mid;
            }
            mid = left + right;
        }

        printf("%s\n", rep);
    }
    return 0;
}
