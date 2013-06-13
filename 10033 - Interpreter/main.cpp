#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main(){
    int regs[10];
    int ram[1000];
    int ic;
    int pc;
    bool halt;


    string buf;
    int tests;
    cin >> tests; 
    cin.ignore();
    getline(cin, buf);

    for(int i=0;i<tests;i++){
        ic=0;
        pc=0;
        halt = false;

        int op, p0, p1;
        
        memset(regs, 0, sizeof(int)*10);
        memset(ram, 0, sizeof(int)*1000);
    
        // read the program
        for(int j=0; 
            getline(std::cin, buf) && (!buf.empty());
            j++){
           ram[j] = atoi(buf.data()); 
        }

        //printf("executing ...\n");
        int code = ram[0];
        while( pc < 1000  ){
            code = ram[pc];

            op = code / 100;
            p0 = (code / 10) % 10;
            p1 = code % 10;
            
            //printf("%d%d%d\n", op, p0, p1);

            switch( op )
            {
                case 0:
                    {
                        // goto
                        //cout << "goto " << regs[p0] << endl;
                        if( regs[p1] != 0 )
                            pc = regs[p0] - 1;
                        break;
                    }
                case 1:
                    {
                        if( (p0 == 0) && (p1 == 0) )
                        {
                            halt = true;
                            ic++;
                        }
                        break;
                    }
                case 2:
                    {
                        regs[p0] = p1;
                        break;
                    }
                case 3:
                    {
                        regs[p0] += p1;
                        break;
                    }
                case 4:
                    {
                        regs[p0] *= p1;
                        break;
                    }
                case 5:
                    {
                        regs[p0] = regs[p1];
                        break;
                    }
                case 6:
                    {
                        regs[p0] += regs[p1];
                        break;
                    }
                case 7:
                    {
                        regs[p0] *= regs[p1];
                        break;
                    }
                case 8:
                    {
                        regs[p0] = ram[regs[p1]];
                        break;
                    }
                case 9:
                    {
                        ram[regs[p1]] = regs[p0];
                        break;
                    }
            }

            if( halt ) break;

            regs[p0] %= 1000;
            pc++;
            ic++;
        }
        cout << ic << endl;
        if( i != tests-1 ) cout << endl;
    }
    return 0;
}
