#include <iostream>
#include "graph.h"

using namespace std;

//Time to spread some democracy
int main(void) {
    //Read in the country
    Graph mafghanistan;
    cin >> mafghanistan;
    
    //Sort roads
    mafghanistan.SortEdges(mafghanistan.edges_, 0, mafghanistan.num_edges_ - 1);
    
    //Determine roads
    mafghanistan.CreateMST();
    
    //Sort components
    mafghanistan.SortComponents(mafghanistan.components_, 0, mafghanistan.num_components_ - 1);
    
    //Print out country
    cout << mafghanistan;
 
    return 0;
}