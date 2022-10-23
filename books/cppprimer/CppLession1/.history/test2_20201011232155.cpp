#include <iostream>
using namespace std;
int face(int a)
{
    if(a>1)
        return face(a-1)*a;
    return 1;
}

int main()
{
    int n = 5;
    int m = face(n);
    cout<<"Hello Greenman The face value is"<<" "<<m<<endl;
    system("pause");
    return 0;
}
