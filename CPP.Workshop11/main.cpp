#include <iostream>
#include <vector>

typedef std::vector< std::vector<int> > Matrix;

void deleteZeroesByFunctions(std::vector<int> &vec)
{
    vec.erase(std::remove(vec.begin(), vec.end(), 0), vec.end());
}

void deleteZeroes(std::vector<int> &vec)
{
    int index = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] != 0)
        {
            vec[index] = vec[i];
            index++;
        }
    }
    vec.resize(index);
}

void deleteColumns(Matrix &matrix) {
    size_t size1 = matrix[0].size();
    for (int i = 0; i < matrix.size(); i++) {
        size_t index = 0;

        for (int k = 0; k < matrix[0].size(); k++) {
            if (matrix[i][k] != 0) {
                for (std::vector<int> &elem : matrix) {
                    elem[index] = elem[k];
                }

                index++;
            }
        }
        for (std::vector<int> &elem : matrix) {
            elem.resize(index);
        }
    }
}


int main()
{
    std::vector<int> vec = {1, 0, 2, 0, 3, 0, 4};
    deleteZeroesByFunctions(vec);
    for (const int &elem : vec)
    {
        std::cout << elem << std::endl;
    }
    deleteZeroes(vec);
    for (const int &elem : vec)
    {
        std::cout << elem << std::endl;
    }
    Matrix matrix = { {1, 0, 2, 0, 3, 0, 4}, {1, 0, 3, 0, 5, 4, 0} };
    deleteColumns(matrix);
    for (const std::vector<int> &vec1 : matrix)
    {
        for (const int &elem : vec1)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}
