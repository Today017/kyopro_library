/// @attention 未verify
struct RollingHash2D {
    RollingHash2D()=default;
    vector<vector<Hash>> hash;

    RollingHash2D(const vector<string>& s) {
        int h=s.size(), w=s[0].size();
        hash=vector<vector<Hash>>(h,vector<Hash>(w+1));
        for(int i=1; i<=h; i++) for(int j=1; j<=w; j++) {
            hash[i][j]=Hash(s[i-1][j-1]).shift(i-1).shift(j-1)+hash[i][j-1]+hash[i-1][j]-hash[i-1][j-1];
        }
    }

    Hash get(int l, int r, int u, int d) {
        Hash ret=hash[r][d]-hash[l][d]-hash[r][u]+hash[l][u];
        ret=ret.shift(-l).shift(-u);
        return ret;
    }
};
