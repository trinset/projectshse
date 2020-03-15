//
// Created by Олег Васютин on 2020-03-15.
//

#ifndef RREF_SHOWRREF_H
#define RREF_SHOWRREF_H

void showRREF()
{
    std::cout << "Enter the dimensions!" << '\n';
    size_t n, m;
    std::cin >> n >> m;
    std::cout << "Enter the elements:" << '\n';
    std::vector<std::vector<Rational>> b(n, std::vector<Rational>(m));
    Rational c;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t k = 0; k < m; ++k)
        {
            std::cin >> c;
            b[i][k] = c;
        }
    }
    Matrix<Rational> a(b);
    std::string ans;
    std::string ans2;
    bool show = false;
    std::cout << "Which form do you want? (RREF/REF)" << '\n';
    std::cin >> ans;
    while (ans != "REF" and ans != "RREF")
    {
        std::cout << "Wrong input! Which form do you want? (RREF/REF)" << '\n';
        std::cin >> ans;
    }
    std::cout << "Do you want details? (yes/no)" << '\n';
    std::cin >> ans2;
    while (ans2 != "yes" and ans2 != "no")
    {
        std::cout << "Wrong input! Do you want details? (yes/no)" << '\n';
        std::cin >> ans2;
    }
    if (ans2 == "yes")
    {
        show = true;
    }
    if (ans == "REF")
    {
        a = transformREF(a, show);
    }
    else
    {
        a = transformRREF(a, show);
    }
    std::cout << a;
}

#endif //RREF_SHOWRREF_H
