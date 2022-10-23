/*
 * @Author: your name
 * @Date: 2020-10-11 23:18:11
 * @LastEditTime: 2020-10-11 23:21:55
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CppLession1\test2.cpp
 */
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
