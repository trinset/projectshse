/// Implement strlen function: count the length of a C-style string variable initialized with a string literal

#include <iostream>
#include <string>

int custom_strlen (const std::string str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}
int main()
{
    std::string str;
    std::cin >> str;
    std::cout << custom_strlen (str) << std::endl;
    return 0;
}
