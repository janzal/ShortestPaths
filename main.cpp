#include <iostream>
#include <queue>
#include <list>
#include <set>
#include <algorithm>
#include <stdio.h>

using namespace std;

struct Node
{
    long id;
    long dst;
    set<Node*> children;
    set<Node*> parents;
    char state;
    
    void print()
    {
        cout << "Node id: " << id << ", " << "dst: " << dst << ", state: " << (int)state << endl;
        cout << "Children: ";
        for(set<Node *>::const_iterator iterator = children.begin(); iterator != children.end(); iterator++)
        {
            cout << (*iterator)->id << " ";
        }
        
        cout << endl;
        
        cout << "Parents: ";
        for(set<Node *>::const_iterator iterator = parents.begin(); iterator != parents.end(); iterator++)
        {
            cout << (*iterator)->id << " ";
        }
        
        cout << endl;
    }
};

Node *nodes, *reconstruct;
set<Node *> closed;
long nodesCount, edgesCount, startPoint, endPoint;


// TODO Spocitat pocet cest... Neni to tak easy
long countPaths(Node * start, Node * end)
{
//    cout << "CountPaths called" << endl;
//    cout << start->id << " - " << end->id << endl;

    if(start == end)
    {
//        cout << "Start == end" << endl;
        return 1;
    }

    long sum = 0;
    for(set<Node *>::const_iterator iterator = end->parents.begin(); iterator != end->parents.end(); iterator++)
    {
//        cout << "Iterating..." << endl;
//        cout << (*iterator)->id << ", ";
        sum = (sum + countPaths(start, *iterator)) % 536870909;
    }
//    cout << "Sum: " << sum << endl;

//    cout << endl;

    return sum;
}

void printNodes()
{
    for(long i = 0; i < nodesCount; i++)
    {        
        nodes[i].print();
        cout << endl;
    }
}



/*
     4 4 0 3
> 0: 2 1 2
  1: 1 3
  2: 1 3
< 3: 0

10 0 0 9
3 1 2 3
1 4
2 5 6
2 6 7
2 8 7
1 9
1 9
1 9
1 9
0
*/

int main()
{
//    cout << "Initializing..." << endl;
    //cin >> nodesCount >> edgesCount >> startPoint >> endPoint;
    scanf("%d %d %d %d", &nodesCount, &edgesCount, &startPoint, &endPoint);

    nodes = new Node[nodesCount];
    
    //cout << "Loading nodes" << endl;
    for(long i = 0; i < nodesCount; i++)
    {
        nodes[i] . id = i;
        nodes[i] . dst = 2147483000;
        nodes[i] . state = 0;

        long childrenCount;
        scanf("%d", &childrenCount);

        long nodeNumber;
        for(int k = 0; k < childrenCount; k++)
        {
            scanf("%d", &nodeNumber);
            //cin >> nodeNumber;
            //cout << k << nodeNumber << endl;
            nodes[i] . children . insert(&nodes[nodeNumber]);
        }
    }

    list<Node*> nodesQueue;
    
    nodes[startPoint].dst = 0;
    nodesQueue.push_back(&nodes[startPoint]);    

    //long maxLen = 2147483000;
    
    //cout << "Processing nodes" << endl;
    
    long processed = 0;
    long shortestPath = 2147483000;
    while(true)
    {        
        if(processed > nodesCount) { 
                printf("Pocet zpracovanych byl vetsi nez pocet uzlu.\n"); 
                printNodes();   
                
                printf("Dump fronty:\n");
                
                int iter = 0;
                while(!nodesQueue.empty())
                {
                    printf("%d\n", iter);
                    printf("%d ", nodesQueue.front()->id);
                    nodesQueue.pop_front();
                    iter++;
                }
                
                break;
                
                exit(1);
        }
        
        processed ++;
        Node* actual = nodesQueue.front();
        nodesQueue.pop_front();

        //if(processed % 100 == 0)
                //printf("\r%d/%d", processed, nodesCount);
        //cout << (actual -> id) << ", ";

        if(actual->id == endPoint)
        {
            shortestPath = actual->dst;
            break;
            cout << "Quitted!";
        }

        for(set<Node *>::const_iterator iterator = actual->children.begin(); iterator != actual->children.end(); iterator++)
        {
            //const bool isClo
            //list<Node *>::iterator findIter = find(nodesQueue.begin(), nodesQueue.end(), (*iterator));
            //const bool isOpened = findIter != nodesQueue.end();
            
//            if(isOpened)
//            {
//                if((*findIter).)
//            }

            if (((*iterator)->state == 0 || (*iterator)->dst == (actual->dst+1)) && (((*iterator)->dst <= shortestPath) && (*iterator)->state < 2)) // && !isOpened
            {
                
                //cout << (*iterator)->id << ": ";
                 
                (*iterator)->state = 1;
                
                (*iterator) -> dst = actual->dst+1;
                (*iterator) -> parents.insert(actual);
                
                nodesQueue.push_back(*iterator);
                
            }
            
            actual->state = 2;

            
            //cout << endl;
        }

        if(nodesQueue.empty()) {
            break;
        }
    }
    
    //cout << "Counting paths" << endl;
    
    printf("%d\n", countPaths(&nodes[startPoint], &nodes[endPoint]));
    
    printf("Projito uzlu: %ld, nacteno uzlu: %ld\n", processed, nodesCount);
    
    return 0;
}
















// TODO Udelat to http://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Pseudocode a pri relaxaci kontrolovat i rovnost



