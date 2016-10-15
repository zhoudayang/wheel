#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

//length of string equal to p -buf
//key idea:使用对称的数组搞定了负数转换的边界条件
char *itoa(char buf[], int value) {
    const static char *digits = "9876543210123456789";
    const static char *zero = digits + 9;
    int i = value;
    char *p = buf;
    do
    {
        int lsd = i % 10;
        i /= 10;
        *p++ = zero[lsd];
    }
    while (i != 0);
    if (value < 0)
        *p++ = '-';
    *p = '\0';
    std::reverse(buf, p);
    return p;
}

int main() {

    char *buffer = new char[32];
    char *p1 = itoa(buffer, INT_MIN);
    cout << "value: " << INT_MIN << " length: " << (p1 - buffer) << " c_str : " << buffer << endl;
    char *p2 = itoa(buffer, INT_MAX);
    cout << "value: " << INT_MAX << " length: " << (p2 - buffer) << " c_str : " << buffer << endl;
    for (int i = 0; i < 10000; i++)
    {
        int value = rand();
        char *p = itoa(buffer, value);
        cout << "value: " << value << " length: " << (p - buffer) << " c_str : " << buffer << endl;
    }



    return 0;
}