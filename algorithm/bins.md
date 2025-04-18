[top](../README.md)

# [Binary Search](./bins.hpp)

`T binarySearch(T ok, T ng, function<bool(T)> judge)`
- $ok$ を条件を満たす極限値、 $ng$ を条件を満たさない極限値として、 $judge(x)$ が真となる境界値を二分探索する。
- $O(\log(|ok-ng|))$

`T binarySearchIteration(T ok, T ng, function<bool(T)> judge, int count = 100)`
- $ok$ を条件を満たす極限値、 $ng$ を条件を満たさない極限値として、 $judge(x)$ が真となる境界値を二分探索する。
- $count$ 回で打ち切る。
- $O(count)$