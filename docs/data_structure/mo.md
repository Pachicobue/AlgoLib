---
title: Mo's Algorithm
documentation_of: //src/data_structure/mo.hpp
---

## Mo's Algorithm

### 概要

$N$ 個の 二次元格子点 $P _ i = (x _ i, y _ i)$ が与えられる。以下これをターミナルという。  
また $0 \le x _ i, y _ i \lt L$ であるとする。

$(0,0)$ からスタートして隣り合う格子点に移動することを繰り返して、ターミナル集合 $\lbrace P _ 0, \dots, P _ {N-1} \rbrace$ をすべてたどることを考える(たどる順番は何でも良い)。  
ブロックサイズ $B$ ごとにブロック分けして $\lbrace P _ 0, \dots, P _ {N-1} \rbrace$ をたどる順番をいい感じにすると、移動回数を $\mathrm{O}(BN+\frac{L^2}{B})$ にできる。  
$B = \sqrt{\frac{L^2}{N}}$ に設定することで、移動回数は $\mathrm{O}(L\sqrt{N})$ になる。

![Mo's algorithm](/algolib/data_structure/mo.png)

この話を応用すると、連続部分列に対する オフラインクエリ みたいなものに適用できる。  
<u>(例) 静的数列の区間種類数クエリ</u>  
数列 $A = \lbrace A _ 0, \dots, A _ {N-1} \rbrace$ に対して、以下のようなクエリが $Q$ 個飛んでくる。  

- $(l,r)$ : $\lbrace A _ l, \dots, A _ {r-1} \rbrace$ の値の種類数を出力

このクエリはオフラインで与えられる。  

座標 $(x,y)$ のことを $\lbrace A _ x, \dots, A _ {y-1}\rbrace$ と捉えると、隣の格子点に移動することは区間を1だけ伸縮させることに対応する。  
以下の4種類の移動を実装すればいい。

- $(x,y) \rightarrow (x+1, y)$: $A _ {x}$ を削除
- $(x,y) \rightarrow (x-1, y)$: $A _ {x-1}$ を挿入
- $(x,y) \rightarrow (x, y+1)$: $A _ {y}$ を挿入 
- $(x,y) \rightarrow (x, y-1)$: $A _ {y-1}$ を削除

(値，個数)の集合,値の種類数 を管理しつつ、要素の 挿入/削除 を捌けばいい。  
これは $\mathrm{O}(1)$ でできるので、この問題は $\mathrm{O}(N\sqrt{N})$ で解ける。

### I/F

#### コンストラクタ

```
mo_iterator<B> mo(const std::vector<int>& xs, const std::vector<int>& ys)
```

ターミナル $(x _ i, y _ i)$ を配置。  
内部でたどるべき順番に並べ替えて保持する。

- `B`: ブロックサイズ


##### 計算量

- $\mathrm{O}(N \log N)$

#### next

```
int mo.next<R,L,D,U>(R right, L left, D down, U up)
```

次のターミナルまで移動する。  
返り値は到達したターミナル番号

##### 入力

- `right`: $(x,y)\rightarrow (x+1,y)$ の移動処理 
- `left`: $(x,y)\rightarrow (x-1,y)$ の移動処理 
- `down`: $(x,y)\rightarrow (x,y+1)$ の移動処理 
- `up`: $(x,y)\rightarrow (x,y-1)$ の移動処理 

##### 計算量

- $\mathrm{O}(L)$

但し $N$ 回の移動で合計 $\mathrm{O}(BL+\frac{L^2}{B})$ になる。
