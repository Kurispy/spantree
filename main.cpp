#include <iostream>
#include "graph.h"

using namespace std;

//Time to spread some democracy
int main(void) {
    //Read in the country
    Graph mafghanistan;
    cin >> mafghanistan;
    
    //Sort roads
    mafghanistan.SortEdges();
    
    //Determine roads
    cout << "<?xml version=\"1.4\"?>\n";
    mafghanistan.CreateMST();


    
    return 0;
}