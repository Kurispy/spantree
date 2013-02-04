#include <iostream>
#include "graph.h"

using namespace std;

//Time to spread some democracy
int main(void) {
    //Read in the country
    UnconnectedGraph mafghanistan;
    cin >> mafghanistan;
    
    //Determine regions
    mafghanistan.Partition();
    
    //Determine roads
    mafghanistan.CreateMST();
    
    //Print out the country
    cout << "<?xml version=\"1.4\"?>\n";
    cout << mafghanistan;
    
    return 0;
}