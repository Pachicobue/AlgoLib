---
title: Li Chao Tree
documentation_of: //src/data_structure/li_chao_tree.hpp
---

## Li Chao Tree

### 概要

直線 $l_i(x): y = a _ i x + b _ i$ の集合 $\mathcal{L}$ について以下の操作が $\mathrm{O}(\log N)$ で行う。

- 直線追加: $\mathcal{L} \leftarrow \mathcal{L} \cup \lbrace l:y=ax+b \rbrace$
- 最小値取得: $\mathrm{argmin}_{l \in \mathcal{L}}\ l(x)$

### I/F

#### コンストラクタ

```
li_chao_tree<T, V> cht(const T xmin, const T xsup)
```

CHTを初期化する。
以下 $X = x _ {sup}-x _ {min}$

##### テンプレート引数

- `T`: $x$ 座標, 傾き, $y$ 切片の型
- `V`: $l(x)$ の型(デフォルトでは`T`と同じ)

##### 引数

- `xmin`: クエリされる $x$ 座標の最小値
- `xsup`: クエリされる $x$ 座標の最大値 + 1

##### 計算量

- $\mathrm{O}(1)$

#### add_line

```
void cht.add_line(const T a, const T b)
```

$\mathcal{L}$ に直線 $l: y=ax+b$ を追加

##### 計算量

- $\mathrm{O}(\log X)$

#### add_seg

```
void cht.add_line(const T a, const T b, const T xl, const T xr)
```

$\mathcal{L}$ に線分 $l: y=ax+b\quad (x _ l \le x \lt x _ r)$ を追加

##### 計算量

- $\mathrm{O}(\log^2 X)$


#### min_line

```
L cht.min_line(const T x)
```

返り値型 `L`: `std::pair<T, T>` 
$\mathrm{argmin}_{l \in \mathcal{L}}\ l(x)$ を取得

##### 計算量

- $\mathrm{O}(\log X)$

#### exist

```
bool cht.exist(const T x)
```

$x$ 上に線分が存在するかどうか

##### 計算量

- $\mathrm{O}(\log X)$
