#include"../../kyopro_library/template.hpp"

ll ArgSign(const pair<ll,ll>& p) {
    auto& [x,y]=p;
    if(x==0 && y==0) return 0; //原点
    //平面二分割
    if(y>0 || (y==0 && x>0)) return -1;
    return 1;
}

///@brief 偏角ソート用比較関数
///@details 原点から時計回りに並ぶようにソートする
bool ArgComp(const pair<ll,ll>& l, const pair<ll,ll>& r) {
    if(ArgSign(l)!=ArgSign(r)) return ArgSign(l)<ArgSign(r);
    ll cross=l.first*r.second-l.second*r.first; //外積
    //cross = |l| * |r| * sin(theta(r) - theta(l))
    //cross > 0 -> 0 < theta(r) - theta(l) < pi
    //          -> rはlの反時計回り側
    //cross < 0 -> rはlの時計回り側
    return cross>0;
}