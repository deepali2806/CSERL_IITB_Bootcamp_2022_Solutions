#include <iostream>

//Run : g++ -o output functions.h hello.cpp factorial.cpp main.cpp
//$@ : LHS of : in makefile  $^: RHS of : in makefile $< : First item in the dependancy list

using namespace std;

#include "functions.h"

int main(){
   print_hello();
   cout << endl;
   cout << "The factorial of 5 is " << factorial(5) << endl;
   return 0;
}
