#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/mod/modint.hpp"

namespace NTT998 {
    const int MOD = 998244353;
    const int PRIMITIVE_ROOT = 3;
    const int DIVIDE_MAX = 23;
    using mint = Mod998;
    vector<mint> roots, inv_roots;
    vector<mint> NTT(vector<mint> a, bool inv = false) {
        int n = a.size();
        int h = 0;
        while ((1 << h) < n) {
            h++;
        }
        for (int i = 0; i < n; i++) {
            int j = 0;
            for (int k = 0; k < h; k++) {
                j |= (i >> k & 1) << (h - 1 - k);
            }
            if (i < j) {
                swap(a[i], a[j]);
            }
        }
        for (int b = 1, t = 1; b < n; b <<= 1, t++) {
            mint w = 1, base = inv ? inv_roots[t] : roots[t];
            for (int j = 0; j < b; j++) {
                for (int k = 0; k < n; k += b * 2) {
                    mint s = a[j + k];
                    mint t = a[j + k + b] * w;
                    a[j + k] = s + t;
                    a[j + k + b] = s - t;
                }
                w *= base;
            }
        }
        if (inv) {
            mint inv_n = mint(n).inv();
            for (int i = 0; i < n; i++) {
                a[i] *= inv_n;
            }
        }
        return a;
    }
    vector<mint> Convolution(vector<mint> a, vector<mint> b) {
        int n = 1;
        while (n < (int)a.size() + (int)b.size() - 1) {
            n <<= 1;
        }
        vector<mint> fa(n), fb(n);
        for (int i = 0; i < (int)a.size(); i++) {
            fa[i] = a[i];
        }
        for (int i = 0; i < (int)b.size(); i++) {
            fb[i] = b[i];
        }
        fa = NTT(fa);
        fb = NTT(fb);
        for (int i = 0; i < n; i++) {
            fa[i] *= fb[i];
        }
        fa = NTT(fa, true);
        vector<mint> ret(n);
        for (int i = 0; i < n; i++) {
            ret[i] = fa[i];
        }
        while ((int)ret.size() > (int)a.size() + (int)b.size() - 1) {
            ret.pop_back();
        }
        return ret;
    }
}  // namespace NTT998

struct SetupNTT {
    SetupNTT() {
        using mint = NTT998::mint;
        NTT998::roots = vector<mint>(NTT998::DIVIDE_MAX + 1);
        NTT998::inv_roots = vector<mint>(NTT998::DIVIDE_MAX + 1);
        NTT998::roots[0] = NTT998::inv_roots[0] = mint(1);
        for (ll i = 1; i <= NTT998::DIVIDE_MAX; i++) {
            NTT998::roots[i] = mint(NTT998::PRIMITIVE_ROOT).pow((NTT998::MOD - 1) / (1 << i));
            NTT998::inv_roots[i] = NTT998::roots[i].inv();
        }
    }
} setup_ntt_instance;