#include <iostream>
#include <vector>
using namespace std;

class Image{
public:
    Image():mRows(0), mCols(0){}
    Image(int cols, int rows):mCols(cols), mRows(rows){
        init();
    }

    void init(){
        mImg.resize(mRows);
        for(int i=0;i<mImg.size();i++) 
            mImg[i].resize(mCols); 
        clear();
    }

    void clear(){
        fill(0, 0, mCols-1, mRows-1, 'O');
    }

    void fill(int x1, int y1, int x2, int y2, char c){
        for(int i=y1;i<=y2;i++)
            for(int j=x1;j<=x2;j++)
                mImg[i][j] = c;
    }

    void flood(int x, int y, char c){
        flood_impl(x, y, mImg[y][x], c);
    }

    void flood_impl(int x, int y, char c0, char c){
        if( mImg[y][x] == c ) return;
        mImg[y][x] = c;

        if( x>0 && mImg[y][x-1] == c0 ) flood_impl(x-1, y, c0, c);
        if( x<mCols-1 && mImg[y][x+1] == c0 ) flood_impl(x+1, y, c0, c);
        if( y>0 && mImg[y-1][x] == c0 ) flood_impl(x, y-1, c0, c);
        if( y<mRows-1 && mImg[y+1][x] == c0 ) flood_impl(x, y+1, c0, c);
    }

    void save(const string& file){
        cout << file << endl;
        print();
    }

    void print() const{
        for(int i=0;i<mRows;i++)
        {
            for(int j=0;j<mCols;j++)
                cout << mImg[i][j];
            cout << endl;
        }
    }

    int mRows, mCols;
    vector<vector<char> > mImg;
};

int main(){
    char op;
    Image img;
    while( cin>>op ){
        if( op == 'X' ) break;

        switch( op ){
            case 'I':
                {
                    int m, n;
                    cin >> m >> n;
                    img = Image(m, n);
                    break;
                }
            case 'L':
                {
                    int x, y;
                    char c;
                    cin >> x >> y >> c;
                    img.fill(x-1, y-1, x-1, y-1, c);
                    break;
                }
            case 'C':
                {
                    img.clear();
                    break;
                }
            case 'V':
                {
                    int x, y1, y2;
                    char c;
                    cin >> x >> y1 >> y2 >> c;
                    if( y1 > y2 ) std::swap(y1, y2);
                    img.fill(x-1, y1-1, x-1, y2-1, c);
                    break;
                }
            case 'H':
                {
                    int x1, x2, y;
                    char c;
                    cin >> x1 >> x2 >> y >> c;
                    if( x1 > x2 ) std::swap(x1, x2);
                    img.fill(x1-1, y-1, x2-1, y-1, c);
                    break;
                }
            case 'K':
                {
                    int x1, y1, x2, y2;
                    char c;
                    cin >> x1 >> y1 >> x2 >> y2 >> c;
                    if( x1 > x2 ) std::swap(x1, x2);
                    if( y1 > y2 ) std::swap(y1, y2);
                    img.fill(x1-1, y1-1, x2-1, y2-1, c);
                    break;
                }
            case 'F':
                {
                    int x, y;
                    char c;
                    cin >> x >> y >> c;
                    img.flood(x-1, y-1, c);
                    break;
                }
            case 'S':
                {
                    string filename;
                    cin >> filename;
                    img.save(filename);
                }
            default:
                {
                    string buf;
                    getline(cin, buf);
                    break;
                }
        }
    }
    return 0;
}
