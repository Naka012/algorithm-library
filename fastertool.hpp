/*
pow
*/

ll pw(ll a, ll d){
    ll ret = 1;
    while (d > 0){
        if (d & 1){
            ret *= a;
        }
        a = a * a;
        d >>= 1;
    }
    return ret;
}

/*
floor
*/

ll floor(ll x, ll a){
    if (x >= 0) return x / a;
    return (x - a + 1) / a;
}

/*
grid move
*/

vector<int> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
// vector<int> dx = {1, 0, -1, 0, 1, 1, -1, -1}, dy = {0, 1, 0, -1, 1, -1, 1, -1};

vector<pair<int, int>> d1 = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<pair<int, int>> d2 = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

// std::random_device seed_gen;
// std::mt19937_64 engine(seed_gen());
// std::uniform_int_distribution<> dist(1, 100);

// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
