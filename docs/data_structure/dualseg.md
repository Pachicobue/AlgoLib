---
title: Dual Segment Tree
documentation_of: //src/data_structure/dualseg.hpp
---

## Dual Segment Tree

### 概要

作用素モノイド $(F, \circ, \mathrm{id})$ が決まっている。  
要素数 $N$ の 作用素列 $G = \lbrack G _ 0, G _ 1, \dots , G _ {N-1}\rbrack$ について、以下の操作が $\mathrm{O}(\log N)$ でできる。

- 範囲作用: $G _ i \leftarrow f \circ G _ i \quad (i \in \lbrack l, r) )$
- 範囲一点取得: $G _ i$

### I/F

#### コンストラクタ

```
dualseg<OpMonoid> seg(const std::vector<F>& G)
```

作用素列 $G$ で初期化する

テンプレート引数`OpMonoid`は以下のようなフィールドを持つクラス

```
struct OpMonoid
{
    using F = int;
    F operator()(const F& f1, const F& f2) const { return f1 + f2; }
    static constexpr F id() { return F{0}; }
};
```

- `F`: 作用素型
- `operator()(F f1, F f2)`: $f _ 1 \circ f _ 2$ 
- `id()`: 単位元

##### 計算量

- $\mathrm{O}(N)$

#### get

```
F seg.get(int i)
```

$G _ i$ の取得

##### 計算量

- $\mathrm{O}(\log N)$

#### set

```
void seg.set(int i, const F& f)
```

$G _ i \leftarrow f$ 

##### 計算量

- $\mathrm{O}(\log N)$

#### act

```
void seg.act(int l, int r, const F& f)
```

$G _ i \leftarrow f \circ G _ i \quad (i \in \lbrack l, r) )$

##### 計算量

- $\mathrm{O}(\log N)$

#### 出力

```
std::cout << seg << std::endl
```
