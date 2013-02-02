#include <cstdio>

using namespace std;

//Time to spread some democracy
int main(void) {
    //Read in the country
    Country country;
    cin >> country;
    
    //Determine roads
    country.rebuild();
    
    //Print out the country
    cout << "<?xml version=\"1.4\"?>\n";
    cout << country;
    
    return 0;
}