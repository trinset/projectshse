/// Create a program that gets the name of the user and then outputs "Hello, <user>" where <user> is the name the user.

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string user;
    cin >> user;
    cout << "Hello, " << user << endl;
    return 0;
}
