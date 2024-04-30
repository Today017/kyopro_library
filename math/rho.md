[top](../README.md)

# [Prime Factorization based on Pollard's rho](./rho.hpp)

`vector<ll> factors(ll n)`
- Miller-Rabin の素数判定法に基づき、 $n$ の素因数分解を行う。
- $O(n^{1/4})$

---

```cpp
vector<ll> factors(ll x){
    vector<ll> fs;
    FILE* fp = popen(("factor " + to_string(x)).c_str(), "r");
    char buf[1024];
    fgets(buf, 1024, fp);
    pclose(fp);
    string s = buf;
    s = s.substr(s.find(":") + 1);
    stringstream ss(s);
    ll f;
    while(ss >> f){
        fs.push_back(f);
    }
    return fs;
}
```
