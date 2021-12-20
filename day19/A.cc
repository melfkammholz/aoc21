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

using mat = vvi;
using vec = vi;

void printMatrix(const mat& A) {
  FOR(i, SZ(A)) {
    FOR(j, SZ(A[i])) {
      cout << A[i][j] << " ";
    }
    cout << endl;
  }
}

void printVector(const vec& x) {
  int n = SZ(x);
  FOR(i, n) cout << x[i] << " ";
}

vec matvec(const mat& A, const vec& x) {
  vec y(x.size());
  FOR(i, SZ(A)) {
    FOR(j, SZ(A[i])) {
      y[i] += A[i][j] * x[j];
    }
  }
  return y;
}

mat mult(const mat& A, const mat& B) {
  int n = SZ(A), m = SZ(B), p = SZ(B[0]);
  mat C(n, vec(p));
  FOR(i, n) FOR(j, p) FOR(k, m) {
    C[i][j] += A[i][k] * B[k][j];
  }
  return C;
}

vector<mat> rts;
vector<mat> srts = {
  {
    {1, 0, 0},
    {0, 0, -1},
    {0, 1, 0}
  },
  {
    {0, 0, 1},
    {0, 1, 0},
    {-1, 0, 0}
  },
  {
    {0, -1, 0},
    {1, 0, 0},
    {0, 0, 1}
  }
};

vec sub(const vec& x, const vec& y) {
  assert(x.size() == y.size());
  int n = SZ(x);
  vec z(n);
  FOR(i, n) z[i] = x[i] - y[i];
  return z;
}

vec add(const vec& x, const vec& y) {
  assert(x.size() == y.size());
  int n = SZ(x);
  vec z(n);
  FOR(i, n) z[i] = x[i] + y[i];
  return z;
}

optional<vec> findOrigin(const vvi& A, const vvi& B) {
  int most = 0;
  vi t;
  map<vi, int> cnt;
  for (const vi& x : A)
    for (const vi& y : B) {
      auto z = sub(x, y);
      if (chmax(most, ++cnt[z]))
        t = z;
    }

  // check ambiguity
  int p = 0;
  for (auto [x, c] : cnt) {
    p += c >= 12;
  }
  if (most >= 12 && p != 1)
    cout << p << endl;
  assert(!(most >= 12) || p == 1);

  return most < 12 ? optional<vec>() : optional<vec>(t);
}

bool merge(vector<vec>& A, const vector<vec>& B) {
  set<vec> seen(ALL(A));

  for (const mat& T : rts) {
    vvi C;
    for (const vec& x : B) {
      C.pb(matvec(T, x));
    }
    
    auto mo = findOrigin(A, C);
    if (!mo) continue;

    auto& o = mo.value();
    assert(o.size() == 3);
    os.pb(o);

    for (const vec& x : C) {
     auto y = add(o, x);
      if (seen.count(y)) continue;
      A.pb(y);
    }
    return true;
  }
  
  return false;
}

void test_case() {
  rts.push_back({
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  });
  
  REP(4) {
    int n = SZ(rts);
    FOR(i, n) {
      for (mat& T : srts) {
        auto& A = rts[i];
        mat C = mult(T, A);
        rts.pb(C);
      }
    }
    sort(ALL(rts));
    rts.erase(unique(ALL(rts)), rts.end());
  }

  vector<vector<vec>> scs; 
  string s;
  while (getline(cin, s)) {
    if (s.empty()) continue;
    stringstream ss(s);
    if (s.substr(0, 3) == "---") {
      scs.pb(vector<vec>());
    } else {
      int x, y, z;
      char c;
      ss >> x >> c >> y >> c >> z;
      scs.back().pb({ x, y, z }); 
    }
  }

  int n = SZ(scs);
  vector<vec> area(ALL(scs[0]));
  vector<bool> used(n);
  used[0] = true;
  REP(n) FOR(i, n) {
    if (!used[i]) {
      used[i] = merge(area, scs[i]);
    }
  }

  cout << area.size() << endl;
  assert(all_of(ALL(used), [](bool x) { return x; }));
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
