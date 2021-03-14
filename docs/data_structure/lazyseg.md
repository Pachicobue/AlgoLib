---
title: Lazy Segment Tree
documentation_of: //src/data_structure/lazyseg.hpp
---

## Lazy Segment Tree

### 概要

値モノイド $(T, \ast, e)$ と モノイド作用 $(F, \circ, \mathrm{id})$ が決まっている。  
更に $f(x _ 1 \ast x _ 2) = f(x _ 1) \ast f(x _ 2)\quad (\forall f \in F, x _ 1 x _ 2 \in T)$ が成立しているとする。  
要素数 $N$ の 数列 $A = \lbrack A _ 0, A _ 1, \dots , A _ {N-1}\rbrack$ について、以下の操作が $\mathrm{O}(\log N)$ でできる。

- 範囲総積取得: $A _ l \ast \dots \ast A _ {r-1}$
- 範囲作用: $A _ i \leftarrow f(A _ i) \quad (i \in \lbrack l, r) )$

### I/F

#### コンストラクタ

```
lazyseg<MergeMonoid, OpMonoid, Act> seg(const std::vector<T>& A)
```

数列 $A$ で初期化する

テンプレート引数`MergeMonoid`は以下のようなフィールドを持つクラス

```
struct MergeMonoid
{
    using T = int;
    T operator()(const T& x1, const T& x2) const { return std::min(x1, x2); }
    static constexpr T e() { return inf_v<T>; }
};
```

- `T`: 作用素型
- `operator()(T x1, T x2)`: $x _ 1 \ast x _ 2$ 
- `T e()`: 単位元

テンプレート引数`OpMonoid`は以下のようなフィールドを持つクラス

```
struct OpMonoid
{
    using F = int;
    F operator()(const F& f1, const F& f2) const { return f1 + f2; }
    static constexpr F id() { return 0; }
};
```

- `F`: 作用素型
- `operator()(F f1, F f2)`: $f _ 1 \circ f _ 2$ 
- `F id()`: 単位元

テンプレート引数`Act`は以下のようなフィールドを持つクラス

- `operator()(F f, T x)`: $f(x)$ 

```
struct Act
{
    T operator()(const F& f, const T& x) const { return f + x; }
};
```


##### 計算量

- $\mathrm{O}(N)$

#### get

```
T seg.get(int i)
```

$A _ i$ の取得

##### 計算量

- $\mathrm{O}(\log N)$

#### set

```
void seg.set(int i, const T& x)
```

$A _ i \leftarrow x$ 

##### 計算量

- $\mathrm{O}(\log N)$

#### fold

```
void seg.fold(int l, int r)
```

$A _ l \ast \dots \ast A _ {r-1}$ の取得

##### 計算量

- $\mathrm{O}(\log N)$

#### act

```
void seg.act(int l, int r, const F& f)
```

$A _ i \leftarrow f(A _ i) \quad (i \in \lbrack l, r) )$

##### 計算量

- $\mathrm{O}(\log N)$

#### 出力

```
std::cout << seg << std::endl
```
