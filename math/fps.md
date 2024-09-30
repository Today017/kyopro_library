[top](../README.md)

# [Formal Power Series](./fps.hpp)

[参考・原典](https://potato167.github.io/po167_library)

`vector<mint> f` を、 $f_i$ が $x^i$ の係数となる形式的冪級数とする。

`fpsMul(f, g)`
- $f$ と $g$ の積を返す。 
- $O(n \log n)$

`fpsAdd(f, g)`
- $f$ と $g$ の和を返す。
- $O(n)$

`fpsSub(f, g)`
- $f$ と $g$ の差を返す。
- $O(n)$

`fpsInv(f)`
- $f$ について、 $f\cdot g = 1$ となる $g$ を返す。
- $f_0 \neq 0$ を要求する。
- $O(n \log n)$

`fpsExp(f)`
- $f$ について、 $e^f$ を返す。
- $f_0 = 0$ を要求する。
- $O(n \log n)$

`fpsLog(f)`
- $f$ について、 $\log f$ を返す。
- $f_0 = 1$ を要求する。
- $O(n \log n)$

`fpsPow(f, M)`
- $f$ の $M$ 乗を返す。
- $O(n \log n)$

`bostonMori(ll k, FPS P, FPS Q)`
- $[x^k](P/Q)$ を返す。
- $O(|P| \log |P| \log k)$
