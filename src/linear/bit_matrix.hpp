#pragma once
#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>
template<int column>
class bit_matrix
{
public:
    bit_matrix(const int row_) : row{row_}, table(row) {}
    bit_matrix(const bit_matrix& m) : row{m.row}, table{m.table} {}
    bit_matrix& operator=(const bit_matrix& m)
    {
        assert(row == m.row), assert(column == m.column);
        for (int i = 0; i < row; i++) { table[i] = m[i]; }
        return *this;
    }
    const std::bitset<column>& operator[](const int r) const { return assert(0 <= r and r < row), table[r]; }
    std::bitset<column>& operator[](const int r) { return assert(0 <= r and r < row), table[r]; }
    friend bit_matrix operator+(const bit_matrix& m) { return m; }
    friend bit_matrix operator^(const bit_matrix& m1, const bit_matrix& m2)
    {
        assert(m1.row == m2.row);
        bit_matrix ans(m1.row);
        for (int i = 0; i < m1.row; i++) { ans[i] = m1.table[i] ^ m2.table[i]; }
        return ans;
    }
    template<int col2>
    friend bit_matrix operator*(const bit_matrix& m1, const bit_matrix<col2>& m2)
    {
        assert(column == m2.row);
        bit_matrix<col2> ans(m1.row);
        for (int i = 0; i < m1.row; i++) {
            for (int j = 0; j < column; j++) {
                if (not m1.table[i][j]) { continue; }
                ans[i] ^= m2.table[j];
            }
        }
        return ans;
    }
    friend bit_matrix operator^(const bit_matrix& m, const unsigned long long n) { return assert(m.row == m.column), n == 0 ? bit_matrix::id(m.row) : n % 2 == 1 ? m*(m ^ (n - 1))
                                                                                                                                                                 : ((m * m) ^ (n / 2)); }
    friend bit_matrix& operator^=(bit_matrix& m1, const bit_matrix& m2)
    {
        assert(m1.row == m2.row), assert(m1.column == m2.column);
        for (int i = 0; i < m1.row; i++) { m1.table[i] ^= m2.table[i]; }
        return m1;
    }
    friend bit_matrix& operator*=(bit_matrix& m1, const bit_matrix& m2) { return m1 = m1 * m2; }
    friend bit_matrix& operator^=(bit_matrix& m, const unsigned long long n) { return m = m ^ n; }
    friend std::ostream& operator<<(std::ostream& os, const bit_matrix& m)
    {
        os << "[\n";
        for (int i = 0; i < m.row; i++) { os << "[" << m[i] << "]\n"; }
        return (os << "]");
    }
    static bit_matrix id(const int n)
    {
        bit_matrix ans(n);
        for (int i = 0; i < n; i++) { ans[i].set(i); }
        return ans;
    }
    int row;

private:
    std::vector<std::bitset<column>> table;
};
