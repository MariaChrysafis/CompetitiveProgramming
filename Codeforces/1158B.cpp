#include <iostream>
int main(){int n,k;std::cin>>n>>k;for(int i=0;i<n;i++)std::cout<<!(i%((n-k)/2+1)-(n-k)/2);}
