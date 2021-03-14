#pragma once
#include <array>
#include <iostream>
template<typename T, int row, int column>
class array_matrix
{
public:
    array_matrix()
    {
        for (auto& v : table) {
            for (auto& e : v) { e = T{0}; }
        }
    }
    array_matrix(const array_matrix& m) : table{m.table} {}
    array_matrix& operator=(const array_matrix& m)
    {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) { table[i][j] = m[i][j]; }
        }
        return *this;
    }
    const std::array<T, column>& operator[](const int r) const { return table[r]; }
    std::array<T, column>& operator[](const int r) { return table[r]; }
    friend array_matrix operator+(const array_matrix& m) { return m; }
    friend array_matrix operator-(const array_matrix& m)
    {
        array_matrix ans;
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < column; c++) { ans.table[r][c] = -m.table[r][c]; }
        }
        return ans;
    }
    friend array_matrix operator+(const array_matrix& m1, const array_matrix& m2)
    {
        array_matrix ans;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) { ans[i][j] = m1.table[i][j] + m2.table[i][j]; }
        }
        return ans;
    }
    friend array_matrix operator-(const array_matrix& m1, const array_matrix& m2)
    {
        array_matrix ans;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) { ans[i][j] = m1.table[i][j] - m2.table[i][j]; }
        }
        return ans;
    }
    template<int c>
    friend array_matrix operator*(const array_matrix<T, row, column>& m1, const array_matrix<T, column, c>& m2)
    {
        array_matrix<T, row, c> ans;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < c; j++) {
                for (int k = 0; k < column; k++) { ans[i][j] += m1.table[i][k] * m2.table[k][j]; }
            }
        }
        return ans;
    }
    friend array_matrix operator*(const array_matrix& m, const T& t)
    {
        array_matrix ans;
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.column; j++) { ans[i][j] = m.table[i][j] * t; }
        }
        return ans;
    }
    friend array_matrix operator/(const array_matrix& m, const T& t)
    {
        array_matrix ans;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) { ans[i][j] = m.table[i][j] / t; }
        }
        return ans;
    }
    friend array_matrix operator*(const T& t, const array_matrix& m) { return m * t; }
    friend array_matrix operator^(const array_matrix& m, const unsigned long long n) { return n == 0 ? array_matrix::I() : n % 2 == 1 ? m * (m ^ (n - 1))
                                                                                                                                      : ((m * m) ^ (n / 2)); }
    friend array_matrix& operator+=(array_matrix& m1, const array_matrix& m2)
    {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) { m1.table[i][j] += m2.table[i][j]; }
        }
        return m1;
    }
    friend array_matrix& operator-=(array_matrix& m1, const array_matrix& m2)
    {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) { m1.table[i][j] -= m2.table[i][j]; }
        }
        return m1;
    }
    friend array_matrix& operator*=(array_matrix& m1, const array_matrix& m2) { return m1 = m1 * m2; }
    friend array_matrix& operator*=(array_matrix& m, const T& t)
    {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) { m.table[i][j] *= t; }
        }
        return m;
    }
    friend array_matrix& operator/=(array_matrix& m, const T& t)
    {
        assert(t != 0);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) { m.table[i][j] /= t; }
        }
        return m;
    }
    friend array_matrix& operator^=(array_matrix& m, const unsigned long long n) { return m = m ^ n; }
    friend std::ostream& operator<<(std::ostream& os, const array_matrix& m)
    {
        os << "[\n";
        for (int i = 0; i < row; i++) {
            os << "[";
            for (int j = 0; j < column; j++) { os << m[i][j] << ","; }
            os << "]\n";
        }
        return (os << "]");
    }
    static array_matrix I()
    {
        static_assert(row == column, "Must be rectangular!");
        array_matrix ans;
        for (int i = 0; i < row; i++) { ans[i][i] = 1; }
        return ans;
    }

private:
    std::array<std::array<T, column>, row> table;
};
