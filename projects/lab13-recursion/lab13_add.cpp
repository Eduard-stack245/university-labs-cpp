#include <iostream>
#include <string>
#include "lab_compat.h"

using namespace std;

void decTo2(const int num, string& snum) {
    if (num % 2 == 0)
        snum += "0";
    else snum += "1";
    if ((num / 2) != 0) decTo2(num / 2, snum);
    else return;
}
void decTo8(const int num, string& snum) {
    snum += to_string(num % 8);
    if ((num / 8) != 0) decTo8(num / 8, snum);
    else return;
}
void decTo16(const int num, string& snum) {
    if (num % 16 < 10)
        snum += to_string(num % 16);
    else {
        switch (num % 16)
        {
        case 10:snum += "A";
            break;
        case 11:snum += "B";
            break;
        case 12:snum += "C";
            break;
        case 13:snum += "D";
            break;
        case 14:snum += "E";
            break;
        case 15:snum += "F";
            break;
        default:
            break;
        }

    }
    if ((num / 16) != 0) decTo16(num / 16, snum);
    else return;
}
void reverse_String(string& greet, int n, int i) {

    if (n <= i) { return; }

    swap(greet[i], greet[n]);
    reverse_String(greet, n - 1, i + 1);

}
int main()
{
    lab::init_console();
    cout << "Введите число N :\n";
    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "Enter a non-negative integer.\n";
        return 1;
    }
    string snum2, snum8, snum16;
    decTo2(n, snum2);
    reverse_String(snum2, snum2.length() - 1, 0);
    cout << "Число " << n << " в 2-оичной системе: " << snum2 << endl;
    decTo8(n, snum8);
    reverse_String(snum8, snum8.length() - 1, 0);
    cout << "Число " << n << " в 8-ричной системе: " << snum8 << endl;
    decTo16(n, snum16);
    reverse_String(snum16, snum16.length() - 1, 0);
    cout << "Число " << n << " в 16-ричной системе: " << snum16 << endl;
}