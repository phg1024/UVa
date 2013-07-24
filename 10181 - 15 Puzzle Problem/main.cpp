#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <bitset>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int64_t TARGET = 0x123456789abcdef0;
static const int MAXSTEPS = 50;

enum Direction
{
    L = 0,
    R = 1,
    D = 2,
    U = 3
};

char dir[] = {'L', 'R', 'D', 'U'};
int m[][2] = {
    {-1,  0},
    { 1,  0},
    { 0,  1},
    { 0, -1}
};

struct Board
{
    Board():depth(0){
        memset(steps, 0, sizeof(char)*MAXSTEPS);
    }
    Board(const Board& b):
        px(b.px), py(b.py),
        score(b.score),
        data(b.data),
        depth(b.depth)
    {
        memcpy(steps, b.steps, sizeof(char)*MAXSTEPS);
        memcpy(state, b.state, sizeof(char)*16);
    }

    Board& operator=(const Board& b)
    {
        if( this != &b )
        {
            px = b.px;
            py = b.py;
            score = b.score;
            data = b.data;
            depth = b.depth;
            memcpy(steps, b.steps, sizeof(char)*MAXSTEPS);
            memcpy(state, b.state, sizeof(char)*16);
        }
        return (*this);
    }

    void nextBoards(Board v[], int& nBoards) const
    {
        nBoards = 0;
        for(int i=0;i<4;i++)
        {
            int nx = px + m[i][0];
            int ny = py + m[i][1];

            if( nx >= 0 && nx < 4 
             && ny >= 0 && ny < 4 )
            {
                v[nBoards] = (*this);
                // make the move
                v[nBoards].move((Direction)i);
                nBoards++;
            }
        }
    }

    void move(Direction d)
    {
        steps[depth++] = dir[d];

        int nx = px + m[d][0];
        int ny = py + m[d][1];

        int p = py * 4 + px;
        int np = ny * 4 + nx;

        std::swap(state[p], state[np]);

        px = nx, py = ny;
    }

    void evaluate()
    {
        // compute the key
        data = 0x0;
        for(int i=0;i<16;i++)
        {
            data = data * 16 + state[i];
        }

        score = 0;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                int v = state[i*4+j];
                // current position: (j, i)
                int rx = (v-1)%4;
                int ry = (v-1)/4;

                if( v == 0 )
                    rx = 3, ry = 3;

                score += abs(rx-j) + abs(ry-i);
				//score += ((rx==j)&&(ry==i))?0:1;
            }
        }
        //cout << score << endl;
		score = score * 2 + depth;
    }

    bool isSolvable() const
    {
        int inv = 0;
        for(int i=0;i<16;i++)
        {
            char vi = state[i];
            for(int j=i+1;j<16;j++)
            {
                char vj = state[j];
                if( vj == 0 ) continue;
                if( vi > vj )
                    inv ++;
            }
        }

        return ( ((inv + py + 1) & 0x1) == 0 );
    }

    bool isSolved() const
    {
        return (data == TARGET);
    }

    bool operator<(const Board& b) const
    {
        return data < b.data; 
    }

    bool operator>(const Board& b) const
    {
        return score >= b.score;
    }

    bool operator==(const Board& b) const
    {
        return data == b.data;
    }

    friend istream& operator>>(istream& is, Board& b);
    friend ostream& operator<<(ostream& os, const Board& b);

    int px, py;
    float score;
    int64_t data;
    int depth;
    char steps[MAXSTEPS];
    char state[16];
};

istream& operator>>(istream& is, Board& b)
{
    int v;
    for(int i=0;i<16;i++)
    {
        is >> v;
        b.state[i] = v;
        if( v == 0 )
        {
            b.py = i / 4;
            b.px = i % 4;
        }
    }
    b.evaluate();
    return is;
}

ostream& operator<<(ostream& os, const Board& b)
{
    cout << "piece 0 is @ " << b.px << ", " << b.py << endl;
    cout << "score = " << b.score << endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            os << b.state[i*4+j];
        }
        os << endl;
    }

    return os;
}

Board solve_astar(const Board& b)
{
    map<int64_t, float, std::less<int64_t> > visited;

    priority_queue<Board, vector<Board>, std::greater<Board> > Q;

    Q.push(b);

    // complete tree search
    while( !Q.empty() )
    {
        Board cur = Q.top();
        Q.pop();
       
        //cout << "queue size = " << Q.size() << endl;
        //cout << cur << endl;
        //cout << cur.data << endl;

        //getchar();

        visited.insert(make_pair(cur.data, cur.score));

        if( cur.isSolved() ) return cur;

        Board candidates[4];
        int nCandidates;

        cur.nextBoards(candidates, nCandidates);

        for(int i=0;i<nCandidates;i++)
        {
            Board& cb = candidates[i];
            cb.evaluate();
			//cout << cb << endl;
			/*
            cout << "current node = " << cb.data << endl;
			cout << "map = " << endl;
			for(map<int64_t, float>::iterator mit=visited.begin();
				mit!=visited.end();
				mit++)
				{
					cout << (*mit).first << '\t';
				}
				cout << endl;
				*/
				//getchar();
				
            map<int64_t, float>::iterator it = visited.find(cb.data);
            if( it == visited.end() )
            {
                //cout << "new state." << endl;
                //cout << cb.data << endl;
                //cout << cb << endl;
                Q.push(cb);
            }
            else
            {
                //cout << "visited." << endl;
                //cout << cb << endl;
                // visited state
                if( cb.score < (*it).second )
                {
                    //cout << "lower cost" << endl;
                    visited.erase(it);
                    Q.push(cb);
                }
            }

            //cout << "current queue size = " << Q.size() << endl;
        }
    }
}


/*
 // BFS  method
Board solve(const Board& b)
{
    set<int64_t> visited;

    queue<Board> Q;

    Q.push(b);
    visited.insert(b.data);

    // complete tree search
    while( !Q.empty() )
    {
        Board cur = Q.front();
        Q.pop();
        if( cur.depth > 45 ) continue;

        Board candidates[4];
        int nCandidates;

        cur.nextBoards(candidates, nCandidates);

        for(int i=0;i<nCandidates;i++)
        {
            Board& cb = candidates[i];
            
            if( cb.isSolved() ) return cb;
            else if( visited.find(cb.data) == visited.end() )
            {
                Q.push(cb);
                visited.insert(cb.data);
            }
        }
    }
}
*/

int main()
{	
    int ncases;
    cin >> ncases;
    while( ncases-- > 0 )
    {
        Board b;
        cin >> b;

        if( b.isSolved() ){
            putchar('\n');
            continue;
        }

        if( b.isSolvable() )
        {
            b.evaluate();
            Board solution = solve_astar(b);
            printf("%s\n", solution.steps);
        }
        else
        {
            cout << "This puzzle is not solvable." << endl;
        }
    }
    return 0;
}
