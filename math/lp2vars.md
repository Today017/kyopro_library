[top](../README.md)

# [Linear Programming (2 valiables](./lp2vars.hpp)

[参考1](https://atcoder.jp/contests/arc139/tasks/arc139_b)
[参考2](https://atcoder.jp/contests/abc374/tasks/abc374_e)

`ll LinearProgramming_2valiables(ll a, ll b, ll c, ll p, ll q)`
- $ax + by \geq c$, $x \geq 0$, $y \geq 0$ を満たすような $x, y$ のうち、 $px + qy$ を最小化するものについて、その最小値を返す。
- $O(\sqrt{c})$

