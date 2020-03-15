//
// Created by Олег Васютин on 2020-03-15.
//

#ifndef RREF_MATRIX_H
#define RREF_MATRIX_H

#include<iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include "Fraction.h"



template <typename T>
class Matrix
{
public:
    explicit Matrix(const std::vector<std::vector<T> > &mat) : _mat(mat)
    {}


    std::pair<size_t, size_t> size() const
    {
        std::pair<size_t, size_t> a;

        if (_mat.size() == 0)
            a.second = 0;
        else
            a.second = _mat[0].size();
        a.first = _mat.size();

        return a;
    }

    std::vector<std::vector<T> > get() const
    {
        return _mat;
    }

    Matrix& operator+= (const Matrix& mat)
    {
        for (size_t s = 0; s < _mat.size(); ++s)
        {
            for (size_t i = 0; i < _mat[s].size(); i++)
            {
                _mat[s][i] += mat._mat[s][i];
            }
        }
        return *this;
    }


    Matrix operator+ (const Matrix& mat) const
    {
        Matrix tempMat(_mat);
        for (size_t s = 0; s < _mat.size(); ++s)
        {
            for (size_t i = 0; i < _mat[s].size(); i++)
            {
                tempMat._mat[s][i] = _mat[s][i] + mat._mat[s][i];
            }
        }
        return tempMat;
    }

    template <typename T1>
    Matrix& operator*= (const T1& num)
    {
        for (size_t s = 0; s < _mat.size(); ++s)
        {
            for (size_t i = 0; i < _mat[s].size(); i++)
            {
                _mat[s][i] *= num;
            }
        }
        return *this;
    }

    template <typename T1>
    Matrix operator* (const T1& num) const
    {
        Matrix tempMat(_mat);
        for (size_t s = 0; s < _mat.size(); ++s)
        {
            for (size_t i = 0; i < _mat[s].size(); i++)
            {
                tempMat._mat[s][i] *= num;
            }
        }
        return tempMat;
    }

    std::vector<T>& operator[](size_t a)
    {
        return _mat[a];
    }

    Matrix& transpose()
    {
        std::vector<std::vector<T> > tempMat(_mat[0].size());
        for (size_t ind = 0; ind < _mat[0].size(); ++ind)
        {
            for (size_t ind1 = 0; ind1 < _mat.size(); ind1++)
            {
                tempMat[ind].push_back(_mat[ind1][ind]);
            }
        }
        _mat = tempMat;
        return *this;
    }

    Matrix transposed() const
    {
        std::vector<std::vector<T> > tempMat(_mat[0].size());
        for (size_t ind = 0; ind < _mat[0].size(); ++ind)
        {
            for (size_t ind1 = 0; ind1 < _mat.size(); ind1++)
            {
                tempMat[ind].push_back(_mat[ind1][ind]);
            }
        }
        Matrix mat(tempMat);
        return mat;
    }

    Matrix& operator*=(const Matrix &other)
    {
        std::vector<std::vector<T> > tempMat(_mat.size());
        for (size_t ind = 0; ind < _mat.size(); ++ind)
        {
            for (size_t ind3 = 0; ind3 < other._mat[0].size(); ++ind3)
            {
                T a = 0;
                for (size_t ind1 = 0; ind1 < _mat[0].size(); ind1++)
                {
                    a += (_mat[ind][ind1] * other._mat[ind1][ind3]);
                }
                tempMat[ind].push_back(a);
            }
        }
        _mat = tempMat;
        return *this;
    }

    Matrix operator* (const Matrix &other) const
    {
        Matrix<T> mat1(_mat);
        mat1 *= other;
        return mat1;
    }

    void t_ERO(size_t a, size_t b)
    {
        for (size_t i = 0; i < (_mat[0].size()); ++i)
        {
            std::swap(_mat[a][i], _mat[b][i]);
        }
    }

    void l_ERO(size_t a, size_t b, Rational c)
    {
        for (size_t i = 0; i < (_mat[0].size()); ++i)
        {
            _mat[a][i] += (_mat[b][i] * c);
        }
    }

    void d_ERO(size_t a, Rational d)
    {
        for (size_t i = 0; i < (_mat[0].size()); ++i)
        {
            _mat[a][i] *= d;
        }
    }


private:
    std::vector<std::vector<T> > _mat;
};


template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m)
{
    const std::vector<std::vector<T> > ma = m.get();
    for (size_t s = 0; s < ma.size(); ++s)
    {
        for (size_t i = 0; i < ma[s].size(); i++)
        {
            out << ma[s][i];

            if (i != ma[s].size() - 1)
                out << '\t';
        }
        if (s != ma.size() - 1)
            out << '\n';
    }
    return out;
}

template <typename T>
Matrix<T> transformREF(Matrix<T> A, bool show = true)
{
    size_t cnt = 0;
    for (size_t k = 0; k < std::min(A.size().second, A.size().first); ++k)
    {
        for (size_t i = cnt; i < A.size().first; ++i)
        {
            if (A[i][k] != 0)
            {
                if (i != cnt && show) {
                    std::cout << "t(" << i << ", " << cnt << ")" << '\n';
                    A.t_ERO(i, cnt);
                    std::cout << A << '\n' << '\n';
                }
                else
                {
                    A.t_ERO(i, cnt);
                }
                ++cnt;
                break;
            }
        }
        if (cnt && (A[cnt - 1][k] != 0))
        {
            if (1/(A[cnt-1][k]) != 1 && show) {
                std::cout << "d(" << k << ", " << Rational(1) / A[cnt-1][k] << ")" << '\n';
                A.d_ERO(k, Rational(1) / A[cnt-1][k]);
                std::cout << A << '\n' << '\n';
            }
            else
            {
                A.d_ERO(k, Rational(1) / A[cnt-1][k]);
            }
            for (size_t i = cnt; i < A.size().first; ++i)
            {
                if (A[i][k] != 0 && show)
                {
                    std::cout << "l(" << i << ", " <<  k << ", " << -A[i][k] << ")" << '\n';
                    A.l_ERO(i, k, -A[i][k]);
                    std::cout << A << '\n' << '\n';
                }
                else
                {
                    A.l_ERO(i, k, -A[i][k]);
                }
            }
        }

    }
    return A;
}

template <typename T>
Matrix<T> transformRREF(Matrix<T> A, bool show = true)
{
    A = transformREF(A, show);
    for (size_t i = 0; i < A.size().first; ++i)
    {
        for (size_t k = i; k < A.size().second; ++k)
        {
            if (A[i][k] != 0)
            {
                for (size_t s = 0; s < i; ++s)
                {
                    if (A[s][k] != 0 && show)
                    {
                        std::cout << "l(" << s << ", " <<  i << ", " << -A[s][k] << ")" << '\n';
                        A.l_ERO(s, i, -A[s][k]);
                        std::cout << A << '\n' << '\n';
                    }
                    else
                    {
                        A.l_ERO(s, i, -A[s][k]);
                    }
                }
                break;
            }
        }
    }
    return A;
}

#endif //RREF_MATRIX_H
