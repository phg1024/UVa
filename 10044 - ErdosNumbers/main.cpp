#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Node
{
    friend ostream& operator<<(ostream& os, const Node& n);
    static int nodeCount;
    Node():erdosNumber(-1){ id = nodeCount; nodeCount++;}
    Node(const Node& n):id(n.id),name(n.name),neighbors(n.neighbors),erdosNumber(n.erdosNumber){}
    int id;
    string name;
    vector<int> neighbors;
    int erdosNumber;
};

ostream& operator<<(ostream& os, const Node& n)
{
    os << n.id << ": " << n.name << " - ";
    for(int i=0;i<n.neighbors.size();i++)
        os << n.neighbors[i] << " ";
    return os;
}

int Node::nodeCount = 0;

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

void connectNodes(Node& n1, Node& n2)
{
    if( find(n1.neighbors.begin(), n1.neighbors.end(), n2.id) == n1.neighbors.end() )
        n1.neighbors.push_back(n2.id);

    if( find(n2.neighbors.begin(), n2.neighbors.end(), n1.id) == n2.neighbors.end() )
        n2.neighbors.push_back(n1.id);
}

void computeErdosNumber(const vector<Node>& nodes, const map<string, int>& nodeMap)
{

}

int main(){
    int authorCount = 0;
    map<string, int> nodeMap;
    vector<Node> nodes;

    int nscenarios;
    cin >> nscenarios;
    for(int i=0;i<nscenarios;i++)
    {
        int npapers, nnames;
        cin >> npapers >> nnames;
        cin.ignore();

        for(int j=0;j<npapers;j++)
        {
            string line;
            getline(cin, line);
            cout << line << endl;
            vector<string> authors = getAuthors(line);

            for(int k=0;k<authors.size();k++)
            {
                map<string, int>::iterator nit = nodeMap.find(authors[k]);
                if( nit == nodeMap.end() )
                {
                    // create a new node for this author
                    Node n; 
                    n.name = authors[k];
                    nodeMap[n.name] = n.id;
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

        cout << nodes.size() << endl;
        for(map<string, int>::iterator nit = nodeMap.begin();
            nit != nodeMap.end();
            nit++)
        {
            cout << (*nit).first << " @ " << (*nit).second << endl;
            cout << "\t" << nodes[(*nit).second] << endl;
        }

        computeErdosNumber(nodes, nodeMap);

        for(int j=0;j<nnames;j++)
        {
        }
    }

    return 0;
}
