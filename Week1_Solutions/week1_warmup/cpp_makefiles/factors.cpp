#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cout<<"Enter number :";
    cin>>n;

    cout<<"Factors :";
    for(int i = 1 ; i <= (n/2); i++)
    {
        if (n%i == 0)
        {
            cout<<i<<" ";
        }
    }
    cout<<n<<endl;

    // //Sieve of Eratosthenes
	// 	vector<bool> arr(n+1, true);
    // for(int i = 2; i*i <= n; i++)
    // {
    //     if (arr[i] == true)
    //     {
    //         for(int j = i*2; j <= n; j += i)
    //         {
    //             arr[j] = false;
    //         }
    //     }
    // }

    // cout<<"1 ";
    //  for (int p = 2; p <= n; p++)
    //  {
    //      if (arr[p] == true){
    //          if (n%p == 0)
    //         //  cout<<"Are we reaching here?";
    //         cout << p <<" ";

    //      }
    //  }
    //  cout<<n;
        
    return 0;
}