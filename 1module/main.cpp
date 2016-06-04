#include <iostream>

using namespace std;


int f(int n, int k) {
    int r=0;
    for(int i=k; i<=n/2; ++i) {
	
        r+=f(n-i,i);
    }
    return 1+r;
}
int main() {
    int n;
    cin>>n;
    cout<<f(n, 1);
    return 0;
}
