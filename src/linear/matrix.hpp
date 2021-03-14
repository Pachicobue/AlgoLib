#pragma once
#include <cassert>
#include <iostream>
#include <vector>
template<typename T>
class matrix
{
public:
    matrix(const int row_, const int column_) : row{row_}, column{column_}, table(row, std::vector<T>(column, 0)) {}
    matrix(const matrix& m) : row{m.row}, column{m.column}, table{m.table} {}
    matrix& operator=(const matrix& m)
    {
        assert(row == m.row), assert(column == m.column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) { table[i][j] = m[i][j]; }
        }
        return *this;
    }
    const std::vector<T>& operator[](const int r) const { return assert(0 <= r and r < row), table[r]; }
    std::vector<T>& operator[](const int r) { return assert(0 <= r and r < row), table[r]; }
    friend matrix operator+(const matrix& m) { return m; }
    friend matrix operator-(const matrix& m)
    {
        matrix ans(m.row, m.column);
        for (int r = 0; r < m.row; r++) {
            for (int c = 0; c < m.column; c++) { ans.table[r][c] = -m.table[r][c]; }
        }
        return ans;
    }
    friend matrix operator+(const matrix& m1, const matrix& m2)
    {
        assert(m1.row == m2.row), assert(m1.column == m2.column);
        matrix ans(m1.row, m1.column);
        for (int i = 0; i < m1.row; i++) {
            for (int j = 0; j < m1.column; j++) { ans[i][j] = m1.table[i][j] + m2.table[i][j]; }
        }
        return ans;
    }
    friend matrix operator-(const matrix& m1, const matrix& m2)
    {
        assert(m1.row == m2.row), assert(m1.column == m2.column);
        matrix ans(m1.row, m1.column);
        for (int i = 0; i < m1.row; i++) {
            for (int j = 0; j < m1.column; j++) { ans[i][j] = m1.table[i][j] - m2.table[i][j]; }
        }
        return ans;
    }
    friend matrix operator*(const matrix& m1, const matrix& m2)
    {
        assert(m1.column == m2.row);
        matrix ans(m1.row, m2.column);
        for (int i = 0; i < m1.row; i++) {
            for (int j = 0; j < m2.column; j++) {
                for (int k = 0; k < m1.column; k++) { ans[i][j] += m1.table[i][k] * m2.table[k][j]; }
            }
        }
        return ans;
    }
    friend matrix operator*(const matrix& m, const T& t)
    {
        matrix ans(m.row, m.column);
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.column; j++) { ans[i][j] = m.table[i][j] * t; }
        }
        return ans;
    }
    friend matrix operator/(const matrix& m, const T& t)
    {
        assert(t != static_cast<T>(0));
        matrix ans(m.row, m.column);
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.column; j++) { ans[i][j] = m.table[i][j] / t; }
        }
        return ans;
    }
    friend matrix operator*(const T& t, const matrix& m) { return m * t; }
    friend matrix operator^(const matrix& m, const unsigned long long n) { return assert(m.row == m.column), n == 0 ? matrix::I(m.row) : n % 2 == 1 ? m*(m ^ (n - 1))
                                                                                                                                                    : ((m * m) ^ (n / 2)); }
    friend matrix& operator+=(matrix& m1, const matrix& m2)
    {
        assert(m1.row == m2.row), assert(m1.column == m2.column);
        for (int i = 0; i < m1.row; i++) {
            for (int j = 0; j < m1.column; j++) { m1.table[i][j] += m2.table[i][j]; }
        }
        return m1;
    }
    friend matrix& operator-=(matrix& m1, const matrix& m2)
    {
        assert(m1.row == m2.row), assert(m1.column == m2.column);
        for (int i = 0; i < m1.row; i++) {
            for (int j = 0; j < m1.column; j++) { m1.table[i][j] -= m2.table[i][j]; }
        }
        return m1;
    }
    friend matrix& operator*=(matrix& m1, const matrix& m2) { return m1 = m1 * m2; }
    friend matrix& operator*=(matrix& m, const T& t)
    {
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.column; j++) { m.table[i][j] *= t; }
        }
        return m;
    }
    friend matrix& operator/=(matrix& m, const T& t)
    {
        assert(t != 0);
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.column; j++) { m.table[i][j] /= t; }
        }
        return m;
    }
    friend matrix& operator^=(matrix& m, const unsigned long long n) { return m = m ^ n; }
    friend std::ostream& operator<<(std::ostream& os, const matrix& m)
    {
        os << "[\n";
        for (int i = 0; i < m.row; i++) {
            os << "[";
            for (int j = 0; j < m.column; j++) { os << m[i][j] << ","; }
            os << "]\n";
        }
        return (os << "]\n");
    }
    static matrix I(const int N)
    {
        matrix ans(N, N);
        for (int i = 0; i < N; i++) { ans[i][i] = 1; }
        return ans;
    }
    const int row, column;

private:
    std::vector<std::vector<T>> table;
};
