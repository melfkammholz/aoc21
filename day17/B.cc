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
#define FOR(i, n) for (int i = 0; i < n; i++)
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

void test_case() {
  ii tx, ty;
  cin >> skip("target area: x=")
    >> tx.fst
    >> skip("..")
    >> tx.snd
    >> skip(", y=")
    >> ty.fst
    >> skip("..")
    >> ty.snd;

  int cnt = 0;
  for (int vx = 0; vx <= tx.snd; vx++) {
    for (int vy = ty.fst; vy <= 1000; vy++) {
      int x = 0, y = 0;
      int s = 0;
      bool good = false;
      while (!good && x <= tx.snd && y >= ty.fst) {
        x += max(vx - s, 0LL);
        y += vy - s;
        good = tx.fst <= x && x <= tx.snd && ty.fst <= y && y <= ty.snd;
        s++;
      }
      cnt += good;
    }
  }

  cout << cnt << endl;
}

_int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  /* cout << fixed << setprecision(9); */ 
  
  int t = 1;
  /* cin >> t; */
  FOR(i, t) {
    /* cout << "Case #" << (i + 1) << ": "; */
    test_case();
  }
}

