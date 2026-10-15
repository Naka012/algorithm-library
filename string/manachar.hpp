// https://github.com/Naka012/algorithm-library/blob/main/string/manachar.hpp
// 参考: https://snuke.hatenablog.com/entry/2014/12/02/235837

vector<int> manachar(string s){
    int n = (int)s.size();
    vector<int> rad(n);
    int c = 0, r = 0;
    while (c < n) {
        while (0 <= c - r && c + r < n && s[c - r] == s[c + r]) r++;
        rad[c] = r;

        int k = 1;
        while (0 <= c - k && k + rad[c - k] < r) {
        rad[c + k] = rad[c - k];
        k++;
        }
        c += k;
        r -= k;
    }
    return rad;  
}
