#include <bits/stdc++.h>
/* #include <atcoder/all> */

using namespace std;

using _int = int;
#define int long long
#define ll long long
#define ull unsigned long long

#define vi vector<int>
#define vc vector<char>
#define vll vector<ll>
#define vull vector<ull>
#define vvi vector<vector<int>>
#define ii pair<int, int>
#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define FOR3(i, x, n) for (int i = (x); i < (n); i++)
#define FOR2(i, n) FOR3(i, 0, n)
#define FOR(...) GET_MACRO(__VA_ARGS__, FOR3, FOR2)(__VA_ARGS__)
#define CONCAT_INNER(a, b) a ## b
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define REP(n) FOR(CONCAT(_i, __COUNTER__), n)
#define ALL(x) x.begin(), x.end()
#define RALL(x) x.rbegin(), x.rend()
#define SLC(x, l, r) x.begin() + l, x.begin() + r
#define SUM(x) accumulate(ALL(x), 0LL)
#define SORT(x) sort(ALL(x))
#define MOD 1000000007
#define EPS 10e-9
#define DIR4 {{0,1}, {1,0}, {0,-1}, {-1,0}}
#define DIR8 {{0,1}, {0,-1}, {1,0}, {-1,0}, {-1,-1}, {-1,1}, {1,-1}, {1,1}}
#define pb push_back
#define eb emplace_back
#define fst first
#define snd second
#define mp make_pair
#define mt make_tuple
#define SZ(x) ((int) (x).size())
#define MODM(x, m) (((x) % (m) + (m)) % (m))
#ifndef DEBUG
#define DEBUG 0
#endif
  #define dout if (DEBUG) cout
#ifdef DEBUG
  #define debug(...) { \
    __VA_ARGS__;       \
  }                      
#else
  #define debug(...)
#endif
#define VAR(x) #x << "=" << x
#define BIN16(x) bitset<16>(x)
#define BIN32(x) bitset<32>(x)
#define BIN64(x) bitset<64>(x)
#define BIN(x) BIN32(x)
#define OCT(x) oct << x << dec 
#define HEX(x) hex << x << dec

// remember: int = long long
int clz(unsigned int x) {
  return 8 * (int) sizeof(unsigned int) - 1 - __builtin_clzll(x);
}

int popcnt(unsigned int x) { return __builtin_popcountll(x); }

template<typename T>
bool chmin(T& a, const T b) { return a > b ? a = b, true : false; }

template<typename T>
bool chmax(T& a, const T b) { return a < b ? a = b, true : false; }

template<typename T>
T sgn(T a) { return (a > 0) - (a < 0); }

template<typename F>
struct y_combinator_result {
  F f;
  template<typename T>
  explicit y_combinator_result(T&& fun) : f(forward<T>(fun)) {}
  template<typename... Args>
  decltype(auto) operator()(Args&&... args) {
    return f(ref(*this), forward<Args>(args)...);
  }
};

// y combinator
template<typename F>
decltype(auto) $$(F&& f) {
  return y_combinator_result<decay_t<F>>(forward<F>(f));
}

struct skip {
  int n;
  skip(int _n): n(_n) {}
  skip(const char* s) : n(strlen(s)) {}
  friend istream &operator>>(istream &is, const skip &s) {
    is.ignore(s.n);
    return is;
  }
};

/* ------------------------------------------------ */

/* using mint = atcoder::modint998244353; */
/* using mint = atcoder::modint1000000007; */

struct cuboid {
  bool m;
  ii x, y, z;

  cuboid(bool _m, ii _x, ii _y, ii _z) : m(_m), x(_x), y(_y), z(_z) {}
};

bool g[1000][1000][1000];

// heavily inspired by Neal Wu
void test_case() {
  string s;
  vector<cuboid> cs;
  vi X, Y, Z;
  while (getline(cin, s)) {
    stringstream ss(s);
    string m;
    ii x, y, z;
    ss >> m >> skip(" x=") >> x.fst >> skip("..") >> x.snd
      >> skip(",y=") >> y.fst >> skip("..") >> y.snd
      >> skip(",z=") >> z.fst >> skip("..") >> z.snd;
    x.snd++, y.snd++, z.snd++;
    cs.emplace_back(m == "on", x, y, z);
    auto& c = cs.back();
    X.insert(X.end(), {c.x.fst, c.x.snd});
    Y.insert(Y.end(), {c.y.fst, c.y.snd});
    Z.insert(Z.end(), {c.z.fst, c.z.snd});
  }

  SORT(X), SORT(Y), SORT(Z);

  int n = SZ(X);
  // memset(g, 0, sizeof(g));

  auto idx = [](const vi& X, int x) {
    return distance(X.begin(), lower_bound(ALL(X), x));
  };

  auto in = [](cuboid& c) {
    return -50 <= c.x.fst && c.x.snd <= 50
      && -50 <= c.y.fst && c.y.snd <= 50
      && -50 <= c.z.fst && c.z.snd <= 50;
  };

  for (auto& c : cs) {

    if (!in(c)) continue;

    int x0 = idx(X, c.x.fst);
    int x1 = idx(X, c.x.snd);
    int y0 = idx(Y, c.y.fst);
    int y1 = idx(Y, c.y.snd);
    int z0 = idx(Z, c.z.fst);
    int z1 = idx(Z, c.z.snd);
 
    FOR(x, x0, x1) FOR(y, y0, y1) FOR(z, z0, z1)
      g[x][y][z] = c.m;
  }

  int res = 0;
  FOR(x, n - 1) FOR(y, n - 1) FOR(z, n - 1)
    res += g[x][y][z] * (X[x + 1] - X[x]) * (Y[y + 1] - Y[y]) * (Z[z + 1] - Z[z]);
  cout << res << endl;
}

_int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cout << fixed << setprecision(9); 
  
  int t = 1;
  /* cin >> t; */
  FOR(i, t) {
    /* cout << "Case #" << (i + 1) << ": "; */
    test_case();
  }
}
