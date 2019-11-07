/// Recreate the multiplication table task, allowing the user to rerun the program again after it prints the multiplication table.

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string ans = "Yes";
    int a, b, i, k;
    do {
        cout << "What us the size of the new table?" << endl;
        cin >> a;
        cout << "What is the divisor?" << endl;
        cin >> b;
        for (i = 0; i <= a; i++) {
            for (k = 0; k <= a; k++) {
                if (i == 0 and k == 0) {
                    cout << "" << "\t";
                } else {
                    if (i == 0) {
                        cout << k << "\t";
                    } else {
                        if (k == 0) {
                            cout << i << "\t";
                        } else {
                            cout << (k * i) % b << "\t";
                        }
                    }
                }
            }
            cout << endl;
        }
        cout << "Do you want to input one more table?" << endl;
        cin >> ans;
    } while (ans == "Yes" or ans == "yes" or ans == "YES");
    return 0;
}
