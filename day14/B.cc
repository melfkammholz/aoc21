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
  string s;
  string T;

  int R[26][26];
  memset(R, 0, sizeof(R));

  int N = 40;

  bool rules = false;
  while (getline(cin, s)) {
    stringstream ss(s);
    if (rules) {
      char a, b, c;
      ss >> a >> b >> skip(" -> ") >> c;
      R[a - 'A'][b - 'A'] = c - 'A' + 1;
    } else {
      T = s;
      getline(cin, s);
      rules = true;
    }
  }

  int dp[N + 1][26][26][26];
  memset(dp, 0, sizeof(dp));
  
  FOR(a, 26) FOR(b, 26)
    dp[0][a][b][a] = 1;

  for (int i = 1; i <= N; i++) FOR(a, 26) FOR(b, 26) {
    if (R[a][b] > 0) {
      int c = R[a][b] - 1;
      FOR(d, 26)
        dp[i][a][b][d] = dp[i - 1][a][c][d] + dp[i - 1][c][b][d];
    }
  }

  int cnt[26];
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < SZ(T) - 1; i++) {
    FOR(j, 26) {
      cnt[j] += dp[N][T[i] - 'A'][T[i + 1] - 'A'][j];
    }
  }
  cnt[T.back() - 'A']++;

  int mi = LONG_MAX, ma = 0;
  for (int i = 0; i < 26; i++) {
    if (cnt[i] == 0) continue;
    chmin(mi, cnt[i]);
    chmax(ma, cnt[i]);
  }
  cout << ma - mi << endl;
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

