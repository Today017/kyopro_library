[top](../README.md)

# [Linear Equation](./linear_equation.hpp)

[参考](https://mathlandscape.com/solution-sp/)

[実装](https://yukicoder.me/submissions/1011997)

$\mathbb{F}_2$ 上の連立線形方程式を解く。

`int rowReduction(vector<vector<bool>> &a, vector<int> &where)`
- 掃き出し法を行う。
- `a` は連立線形方程式 $Ax = b$ の拡大係数行列。
- `where` はピボットの列番号を格納する。
- `a` のランクを返す。

`bool linearEquation(vector<vector<bool>> a, vector<bool> b, vector<bool> &x0, vector<vector<bool>> &ker)`
- 連立線形方程式 $Ax = b$ を解く。
- `a` は連立線形方程式 $Ax = b$ の係数行列。
- `b` は連立線形方程式 $Ax = b$ の右辺ベクトル。
- `x0` は解の一つを格納する。
- `ker` は $Ax = 0$ の解空間の基底を格納する。
- $A$ のサイズによっては基底のサイズが巨大になることに注意する。

$Ax = b$ の一般解は、特殊解の一つ $x_0$ と、 $Ax = 0$ の解空間の基底 $ker$ の線形結合で表される。
