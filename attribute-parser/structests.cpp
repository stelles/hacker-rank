#include <iostream>
#include <map>
using namespace std;

struct Demo
{
  int x;
};

int main()
{
    
    map<string, int> m = {
        {"yes",1}
    };

    int t = m.at("yes");
    int y = m.at("no");
    

    Demo demo;

    demo.x = 5;

    Demo *p_demo = &demo;

    new(p_demo) Demo;

    cout << p_demo->x << endl; //prints 5

    new(p_demo) Demo();

    cout << p_demo->x << endl; //prints 0
}