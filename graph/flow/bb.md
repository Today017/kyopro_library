[top](../../README.md)

# [燃やす埋める](./bb.hpp)

`BurningBurying<T>(n)`
- コストの型が `T` 、頂点数　$n$ の燃やす埋める問題を解く。

`void add_single(int i, Cost zero, Cost one)`
- $x_{i}=0$ のときコスト $zero$ 、$x_{i}=1$ のときコスト $one$ がかかるという条件を課す。

`void add_double(int i, int j, Cost a, Cost b, Cost c, Cost d)`
- $x_{i}$ と $x_{j}$ の組み合わせに対して、以下のコストがかかるという条件を課す。
|  | $x_{j}=0$ | $x_{j}=1$ |
| --- | --- | --- |
| $x_{i}=0$ | $a$ | $b$ |
| $x_{i}=1$ | $c$ | $d |
- $b+c \leq a+d$ を要求する。(劣モジュラ性)


---
