#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

static const int MAXBLOCKS = 25;

struct Stack
{	
	Stack():count(0){}
	
	int top() const
	{
		if( count > 0 )
			return slot[count-1];
		else
			return -1;
	}
	
	int pop()
	{
		if( count > 0 )
		{
			count--;
			return slot[count];
		}
		else
			return -1;
	}
	
	int push(int x)
	{
		slot[count++] = x;
	}
	
	void print()
	{
        if( count == 0 ) return;
        putchar(' ');
		for(int i=0;i<count;i++)
        {
            printf("%d", slot[i]);
            if( i!=count-1 ) putchar(' ');
        }
	}
	
	int count;
	int slot[MAXBLOCKS];
};

struct Table
{
	Table(int n):nStacks(n)
	{
		for(int i=0;i<n;i++)
		{
			s[i].slot[0] = i;
			s[i].count = 1;
			pos[i] = i;
		}
	}
	
	bool move(char *op, char *m, int from, int to)
	{
        if( strcmp(op, "quit") == 0 ) return false;

        if( from == to ) return true;
        if( pos[from] == pos[to] ) return true;

        if( strcmp(op, "move") == 0 )
        {
            if( strcmp(m, "onto") == 0 )
            {
				moveOnto(from, to);
            }
            else
            {
                moveOver(from, to);
            }
        }
        else
        {
            if( strcmp(m, "onto") == 0 )
            {
                pileOnto(from, to);
            }
            else
            {
                pileOver(from, to);
            }
        }
		return true;
	}
	
	void moveOnto(int a, int b)
	{
		removeUntil(pos[b], b);
		moveOver(a, b);
	}
	
	void moveOver(int a, int b)
	{
		removeUntil(pos[a], a);
		s[pos[a]].pop();
		s[pos[b]].push(a);
		pos[a] = pos[b];
	}
	
	void pileOnto(int a, int b)
	{
		removeUntil(pos[b], b);
		pileOver(a, b);
	}
	
	void pileOver(int a, int b)
	{
		int v;
		Stack tmp;
		do
		{
			v = s[pos[a]].pop();
			tmp.push(v);
		}while( v != a );
				
		do
		{
			v = tmp.pop();
			s[pos[b]].push(v);
			pos[v] = pos[b];
		}while( tmp.count > 0 );
	}
	
	void removeUntil(int pid, int x)
	{
		while( s[pid].top() != x )
		{
			int t = s[pid].pop();
			s[t].push(t);
			pos[t] = t;
		}
	}
	
	void print()
	{
		for(int i=0;i<nStacks;i++)
		{
            printf("%d:", i);
			s[i].print();
            putchar('\n');
		}
	}
	
	int nStacks;
	Stack s[MAXBLOCKS];
	int pos[MAXBLOCKS];
};

int main()
{
    int n;
    cin >> n;
	cin.ignore();
	
	Table t(n);
	
	string buf;
    while( getline(cin, buf) )
    {
        char op[5], m[5];
		int a, b;
        sscanf(buf.c_str(), "%s %d %s %d", op, &a, m, &b); 
		if( !t.move(op, m, a, b) ) break;
    }
	
	t.print();
    
    return 0;
}
