// https://github.com/Naka012/algorithm-library/blob/main/data_structure/ballance_multiset.hpp

// 小さいほうの個数がt
struct BallanceSet{
    public :
        BallanceSet(int _t) : t(_t){}
        
        void ballance(){
            while ((int)x.size() < t && (int)y.size()){
                auto it = y.begin();
                x.insert(*it);
                sx += *it;
                sy -= *it;
                y.erase(it);
            }
            if ((int)x.size() == 0 || (int)y.size() == 0) return;

            while (true){
                auto xit = x.end(); xit--;
                auto yit = y.begin();
                ll ex = *xit, ey = *yit;
                if (ex <= ey) break;
                sx += ey - ex;
                sy += ex - ey;
                x.erase(xit);
                y.erase(yit);
                x.insert(ey);
                y.insert(ex);
            }
        }

        void add(ll p){
            y.insert(p);
            sy += p;
            ballance();
        }

        void erase(ll p){
            auto xit = x.find(p);
            if (xit != x.end()){
                x.erase(xit);
                sx -= p;
            }else{
                y.erase(y.find(p));
                sy -= p;
                auto it = x.end(); it--;
                sy += *it;
                sx -= *it;
                y.insert(*it);
                x.erase(it);
            }
            ballance();
        }

        ll lower_sum(){return sx;}
        ll upper_sum(){return sy;}
    private : 
        multiset<ll> x, y;
        ll sx = 0, sy = 0;
        int t;
};
