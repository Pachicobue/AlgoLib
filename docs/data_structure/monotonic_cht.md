---
title: 単調性のある Convex Hull Trick
documentation_of: //src/data_structure/monotonic_cht.hpp
---

## 単調性のある Convex Hull Trick

### 概要

直線 $l_i(x): y = a _ i x + b _ i$ の集合 $\mathcal{L}$ について以下の操作を ならし$\mathrm{O}(1)$ で行う。

- 直線追加: $\mathcal{L} \leftarrow \mathcal{L} \cup \lbrace l:y=ax+b \rbrace$
- 最小値取得: $\mathrm{argmin}_{l \in \mathcal{L}}\ l(x)$

但し、クエリについて以下の制約が満たされているとする。  
- 1つめのクエリで与えられる直線の傾き $a_i$ は広義単調増加 or 広義単調減少
- 2つめのクエリで与えられる座標 $x$ は広義単調増加 or 広義単調減少

### I/F

#### コンストラクタ

```
monotonic_cht<T,V> cht(bool query_inc)
```

##### テンプレート引数

- `T`: $x$ 座標, 傾き, $y$ 切片の型
- `V`: $l(x)$ の型(デフォルトでは`T`と同じ)

##### 引数

- `query_inc`: クエリされる $x$ 座標が広義単調増加かどうか(デフォルト:true)

##### 計算量

- $\mathrm{O}(1)$

#### add_line

```
void cht.add_line(const T a, const T b)
```

$\mathcal{L}$ に直線 $l: y=ax+b$ を追加

##### 計算量

- $\mathrm{O}(1)$

#### min_line

```
L cht.min_line(const T x)
```

返り値型 `L`: `std::pair<T, T>` 
$\mathrm{argmin}_{l \in \mathcal{L}}\ l(x)$ を取得

##### 計算量

- $\mathrm{O}(1)$ amortized

