#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;


struct Node
{
    static int nodeCount;
    friend ostream& operator<<(ostream& os, const Node& n);
    Node():erdosNumber(-1){ id = nodeCount; nodeCount++;}
    Node(const string& str):name(str),erdosNumber(-1){ id = nodeCount; nodeCount++; }
    Node(const Node& n):id(n.id),name(n.name),neighbors(n.neighbors),erdosNumber(n.erdosNumber){}

    int id;
    string name;
    set<int> neighbors;
    int erdosNumber;
};

int Node::nodeCount = 0;

ostream& operator<<(ostream& os, const Node& n)
{
    os << n.id << ": " << n.name << ", erdosNumber = " << n.erdosNumber << endl;
    for(set<int>::iterator sit=n.neighbors.begin();
        sit!=n.neighbors.end();
        sit++)
        os << (*sit) << " ";
    return os;
}


vector<string> getAuthors(const string& line)
{
    size_t pos = line.find(":");
    string authors = line.substr(0, pos);

    stringstream ss;
    ss.str(authors);

    vector<string> v;

    while( true )
    {
        string firstname, lastname;
        ss >> firstname >> lastname;
        if( firstname.empty() ) break;
        string name = firstname + " " + lastname;
        if( name[name.size()-1] == ',' ) name = name.substr(0, name.size()-1);
        v.push_back( name );
    }
    
    return v;
}

inline void connectNodes(Node& n1, Node& n2)
{
    n1.neighbors.insert(n2.id);
    n2.neighbors.insert(n1.id);
}

void computeErdosNumber(vector<Node>& nodes, map<string, int>& nodeMap)
{
    const string erdosName = "Erdos, P.";

    int rootIdx = nodeMap[erdosName];
    nodes[rootIdx].erdosNumber = 0;

    // bfs starting from root

    queue<int> Q;

    Q.push(rootIdx);

    while( !Q.empty() )
    {
        int nid = Q.front();
        Q.pop();
        Node& n = nodes[nid];

        for(set<int>::iterator sit=n.neighbors.begin();
            sit!=n.neighbors.end();
            sit++)
        {
            Node& neighbor = nodes[(*sit)];
            if( neighbor.erdosNumber == -1 )
            {
                neighbor.erdosNumber = n.erdosNumber + 1;
                Q.push( neighbor.id );
            }
        }
    }
}

int main(){
    int nscenarios;
    scanf("%d", &nscenarios);
    for(int i=0;i<nscenarios;i++)
    {
        map<string, int> nodeMap;
        vector<Node> nodes;
        Node::nodeCount = 0;

        int npapers, nnames;
        scanf("%d %d", &npapers, &nnames);
        cin.ignore();

        for(int j=0;j<npapers;j++)
        {
            string line;
            getline(cin, line);
            vector<string> authors = getAuthors(line);

            for(int k=0;k<authors.size();k++)
            {
                map<string, int>::iterator nit = nodeMap.find(authors[k]);
                if( nit == nodeMap.end() )
                {
                    // create a new node for this author
                    Node n( authors[k] ); 
                    nodeMap[ authors[k] ] = n.id;
                    nodes.push_back(n);
                }
            }

            for(int k=0;k<authors.size();k++)
            {
                int nid1 = nodeMap[authors[k]];
                Node& n1 = nodes[nid1];
                for(int m=k+1;m<authors.size();m++)
                {
                    int nid2 = nodeMap[authors[m]];
                    Node& n2 = nodes[nid2];

                    connectNodes(n1, n2);
                }
            }
        }

        computeErdosNumber(nodes, nodeMap);

        printf("Scenario %d\n", i + 1);
        for(int j=0;j<nnames;j++)
        {
            string name;
            getline(cin, name);
            if( nodeMap.find( name ) != nodeMap.end() )
            {
                int eNumber = nodes[nodeMap[name]].erdosNumber ;
                if( eNumber == -1 )
                    printf("%s infinity\n", name.c_str());
                else
                    printf("%s %d\n", name.c_str(), eNumber);
            }
            else
                printf("%s infinity\n", name.c_str());
        }
    }

    return 0;
}
