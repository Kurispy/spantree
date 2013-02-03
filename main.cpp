#include <iostream>
#include "graph.h"

using namespace std;

//Time to spread some democracy
int main(void) {
    //Read in the country
    Graph mafghanistan;
    cin >> mafghanistan;
    
    //Determine roads
    mafghanistan.createMST();
    
    //Print out the country
    cout << "<?xml version=\"1.4\"?>\n";
    cout << mafghanistan;
    
    return 0;
}