---
title: 区間をmapで管理するやつ
documentation_of: //src/data_structure/monotonic_cht.hpp
---

## 区間をmapで管理するやつ

### 概要

数直線が初め色0で塗られている。  
ここから以下の操作を行う 

- 半開区間 $[l,r)$ を色1 で塗る
- 半開区間 $[l,r)$ を色0 で塗る
- $x$ が 色1で塗られているなら、$x$を含む色1の半開区間を取得

色1で塗った操作の回数 $N$ に対して、これらの操作を ならし$\mathrm{O}(\log N)$ で行える。

### I/F

#### コンストラクタ

```
ranges<T> rs()
```

- `T`: 座標の型(符号付き整数しか対応していない)

#### insert

```
void rs.insert(T l, T r)
```

$[l,r)$ に色1を塗る

##### 計算量

- $\mathrm{O}(\log N)$ amortized

#### erase

```
void rs.erase(T l, T r)
```

$[l,r)$ に色0を塗る

##### 計算量

- $\mathrm{O}(\log N)$ amortized

#### support

```
std::pair<bool, std::pair<T,T>> rs.support(T x)
```

($x$ が色1で塗られているか, $x$ が含まれる色1の半開区間)

##### 計算量

- $\mathrm{O}(\log N)$

#### data

```
std::map<T,T> rs.data()
```

内部で保持しているmapへの参照  
色1 の半開区間$[l,r)$ に対して、`map[l] = r` となっている

##### 計算量

- $\mathrm{O}(1)$

#### 出力

```
std::cout << rs << std::endl
```
