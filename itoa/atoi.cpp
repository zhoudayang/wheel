//
// Created by zhouyang on 2016/10/15.
//

#include <iostream>
#include <string>

using namespace std;

//key idea
//使用 unsigned int 存放中间结果，并且注意负数的溢出问题
int atoi(const char *digits) {
    if (!digits)
        return 0;
    while (isspace(*digits))
        digits++;
    int sign = 1;
    if (*digits == '+')
        digits++;
    else if (*digits == '-')
    {
        sign = -1;
        digits++;
    }
    long result = 0;
    while (isdigit(*digits))
    {
        result = 10 * result + *digits++ - '0';
    }
    return sign * result;
}

int main() {
    const char *max_str = to_string(INT_MAX).c_str();
    const char *min_str = to_string(INT_MIN).c_str();
    cout << max_str << " : " << atoi(max_str) << endl;
    cout << min_str << " : " << atoi(min_str) << endl;

    for (int i = 0; i < 1000; ++i)
    {
        int value = rand();
        int negative_value = -value;
        const char *value_str = to_string(value).c_str();
        const char *negative_str = to_string(negative_value).c_str();
        cout << value << " : " << atoi(value_str) << endl;
        cout << negative_value << " : " << atoi(negative_str) << endl;
    }

    return 0;


}