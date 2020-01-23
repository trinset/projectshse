#include <iostream>


int cnt_1(int a)
{
    int res = 0;
    int b = 1;

    while (b <= a)
    {
        if (((a + 1) % (b * 2)) == 0)
            res += (a + 1) / 2;
        else {

            if (((a + 1) % (b * 2)) <= b)
                res += ((a + 1) / (b * 2)) * b;
            else
                res += ((a + 1) / (b * 2)) * b + ((a + 1) % (b * 2)) - b;

        }

        b *= 2;
    }
    return res;
}


int count_1_bit(int min, int max)
{
    if (min != 0)
        min -= 1;

    return cnt_1(max) - cnt_1(min);
}

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << count_1_bit(a, b);
}
