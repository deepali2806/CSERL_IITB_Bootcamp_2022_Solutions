#include <iostream>

using namespace std;

struct complexNo{   
        int real;
        int img;
        };

struct complexNo addComplexNo (struct complexNo c1, struct complexNo c2)
{
    struct complexNo c = { (c1.real+c2.real), (c1.img + c2.img) };
    return c;
}

int main()
{
    int a, b, c, d;
    cout<<"Enter First Complex Number"<<endl;
    cin>>a>>b;
    
    struct complexNo c1 = {a, b};
    
    cout<<"Enter Second Complex Number"<<endl;
    cin>>c>>d;   
    
    struct complexNo c2 = {c, d};

    struct complexNo temp = addComplexNo (c1, c2);
    cout<<"Final answer after addition "<<temp.real<<" "<<temp.img<<endl;

    return 0;
}