#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

static const int MAXM = 2048;
static const int MAXSIZE = 5000;

struct Node
{
	int left, right, value;
};

int flag;

void printTree(Node tree[], int idx)
{
	if(tree[idx].left <0 && tree[idx].right <0) 
	{
        if(flag)    putchar(' ');
        flag = 1;
        printf("%d", tree[idx].value);
        return;
    }
    printTree(tree, tree[idx].left);
    printTree(tree, tree[idx].right);
}

int main()
{
	Node tree[MAXSIZE];

	int n;
	while( true )
	{
		scanf("%d", &n);
		if( n == 0 ) break;
		int m = n*2-1;

		int size = 1;
		while(size <= n) size <<= 1;
        for(int i = 0; i < m; i++) {
            scanf("%d", &tree[size+i].value);
            tree[size+i].left = -1, tree[size+i].right = -1;
        }

		int odd[MAXM], even[MAXM];
		while( size > 1 )
		{
			int nodd = 0, neven = 0;
			for(int i=0;i<size-1;i++)
			{
				if( tree[size+i].value & 0x1 )
					odd[nodd++] = size+i;
				else
					even[neven++] = size+i;
			}

			int nodepos = size >> 1;

			// fill the tree
			if(nodd&1) nodd--;
            if(neven&1) neven--;

            for(int i = 0; i < nodd; i += 2) 
			{
				tree[nodepos].value = (tree[odd[i]].value+tree[odd[i+1]].value)/2;
                tree[nodepos].left = odd[i];
                tree[nodepos].right = odd[i+1];
                nodepos++;
            }

			for(int i = 0; i < neven; i += 2) 
			{
				tree[nodepos].value = (tree[even[i]].value+tree[even[i+1]].value)/2;
                tree[nodepos].left = even[i];
                tree[nodepos].right = even[i+1];
                nodepos++;
            }

			size >>= 1;
		}

		printf("Yes\n");

		flag = 0;
		printTree( tree, 2 );

		putchar('\n');
	}
	return 0;
}