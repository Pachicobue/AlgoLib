---
title: Fenwick Tree
documentation_of: //src/data_structure/fenwick.hpp
---

## Fenwick Tree

### 概要

要素数 $N$ の 数列 $A = \lbrack A _ 0, A _ 1, \dots , A _ {N-1}\rbrack$ について、以下の操作が $\mathrm{O}(\log N)$ でできる。

- 一点加算: $A _ i \leftarrow A _ i + x$
- 範囲総和取得:  $A _ 0 + A _ 1 + \dots + A _ {n-1}$

### I/F

#### コンストラクタ

```
fenwick<T> bit(const std::vector<T>& A)
```

数列 $A$ で初期化する

##### 計算量

- $\mathrm{O}(N)$

#### add

```
void bit.add(int i, const T& x)
```

$A _ i$ に $x$ を加算

##### 計算量

- $\mathrm{O}(\log N)$

#### sum

```
(1) T bit.sum(int i)
(2) T bit.sum(int l, int r)
```

(1) $A _ 0 + A _ 1 + \dots + A _ {i-1}$ を取得
(2) $A _ l + A _ {l+1} + \dots + A _ {r-1}$ を取得

##### 計算量

- $\mathrm{O}(\log N)$

#### max_right

```
int bit.max_right<F>(F f)
```

以下を両方満たす $0 \le r \le N$ を1つ返す
- $f(A _ 0 + A _ 1 + \dots + A _ {r-1}) = true$
- $f(A _ 0 + A _ 1 + \dots + A _ {r}) = false$

##### 制約

- f(0) = True

##### 計算量

- $\mathrm{O}(\log N)$

#### 出力

```
std::cout << bit << std::endl
```

