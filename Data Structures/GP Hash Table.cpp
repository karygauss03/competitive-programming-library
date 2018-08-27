#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// For integer
gp_hash_table<int, int> table;

// Custom hash function approach is better
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<int, int, chash> table;

const ll TIME = chrono::high_resolution_clock::now().time_since_epoch().count();
const ll SEED = (ll)(new ll);
const ll RANDOM = TIME ^ SEED;
const ll MOD = (int)1e9+7;
const ll MUL = (int)1e6+3;
 struct chash{
    ll operator()(ll x) const { return std::hash<ll>{}((x ^ RANDOM) % MOD * MUL); }
};
gp_hash_table<ll, int, chash> table;

unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
// Do we need this hash_combine? Don't know :/
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(int x) const { return hash_f(x); }
};
gp_hash_table<ll, int, chash> table[N][N]; 
// so table[i][j][k] is storing an integer for corresponding k as hash

// For pairs
// The better the hash function, the less collisions
// Note that hash function should not be costly
struct chash {
    int operator()(pii x) const { return x.first* 31 + x.second; }
};
gp_hash_table<pii, int, chash> table;

typedef gp_hash_table<int, int, hash<int>, 
equal_to<int>, direct_mod_range_hashing<int>, linear_probe_fn<>,
hash_standard_resize_policy<hash_prime_size_policy, 
hash_load_check_resize_trigger<true>, true>>
gp;
gp Tree;
// Now Tree can probably be used for fenwick, indices can be long long
// S is an offset to handle negative value
// If values can be >= -1e9, S=1e9+1
// maxfen is the MAXN in fenwick, this case it was 2e9+2;
// Note that it was okay to declare gp in integer as the values were
// still in the range of int.
void add(long long p, int v) {
    for (p += S; p < maxfen; p += p & -p)
        Tree[p] += v;
}
int sum(int p) {
    int ans = 0;
    for (p += S; p; p ^= p & -p)
        ans += Tree[p];
    return ans;
}