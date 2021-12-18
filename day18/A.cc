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

struct node {
  bool isNum = false;
  int num = 0;
  vector<node*> nodes;
  node* parent = NULL;

  node() {}

  node(int num) {
    this->num = num;
    isNum = true;
  }
};

string nodeAsString(node* a) {
  if (a == NULL)
    return "";
  if (a->isNum) {
    return to_string(a->num);
  }

  stringstream ss;
  ss << '[';
  int n = a->nodes.size();
  for (int i = 0; i < n; i++) {
    ss << nodeAsString(a->nodes[i]);
    if (i + 1 < n) ss << ',';
  }
  ss << ']';
  return ss.str();
}

void printNode(node* a) {
  cout << nodeAsString(a) << endl;
}

node* parse(const string& sfn, int& i) {
  node* n = new node();
  char c;
  do {
    c = sfn[i];
    i++;
    if (c == '[') {
      n->nodes.pb(parse(sfn, i));
    } else if (isdigit(c)) {
      int x = c - '0';
      n->nodes.pb(new node(x));
    }
    c = sfn[i];
    i++;
  } while (c == ',');
  for (node* m : n->nodes)
    m->parent = n;
  if (n->nodes.size() == 1) {
    n->nodes[0]->parent = NULL;
    return n->nodes[0];
  }
  return n;
}

bool split(node* a) {
  if (a->isNum) {
    if (a->num < 10) return false;
    assert(a->nodes.size() == 0);
    a->isNum = false;
    a->nodes.pb(new node(a->num / 2));
    a->nodes.pb(new node((a->num + 1) / 2));
    a->nodes[0]->parent = a->nodes[1]->parent = a;
    return true;
  } else {
    return split(a->nodes[0]) || split(a->nodes[1]);
  }
}

node* left(node* a) {
  node* b = a;
  while (a->parent != NULL) {
    b = a;
    a = a->parent;
    if (a->nodes[0] != b) break;
  }
  if (a->parent == NULL && a->nodes[0] == b)
    return NULL;
  b = a->nodes[0];
  while (!b->isNum) {
    b = b->nodes[1];
  }
  return b;
}

node* right(node* a) {
  node* b = a;
  while (a->parent != NULL) {
    b = a;
    a = a->parent;
    if (a->nodes[1] != b) break;
  }
  if (a->parent == NULL && a->nodes[1] == b)
    return NULL;
  b = a->nodes[1];
  while (!b->isNum)
    b = b->nodes[0];
  return b;
}

bool red(node* a, int l) {
  if (a->isNum) return false;
  if (l < 4) {
    return red(a->nodes[0], l + 1) || red(a->nodes[1], l + 1);
  } else {
    node* l = left(a);
    node* r = right(a);
    assert(l == NULL || l->isNum);
    assert(r == NULL || r->isNum);
    if (l != NULL) l->num += a->nodes[0]->num;
    if (r != NULL) r->num += a->nodes[1]->num;
    a->nodes.clear();
    a->num = 0;
    a->isNum = true;
    return true;
  }
}

bool red(node* a) {
  return red(a, 0);
}

int mag(node* a) {
  if (a->isNum) {
    return a->num;
  }
  int l = mag(a->nodes[0]);
  int r = mag(a->nodes[1]);
  int x = 3 * l + 2 * r;
  return x;
}

node* add(node* a, node* b) {
  node* c = new node();
  c->nodes.pb(a);
  c->nodes.pb(b);
  a->parent = b->parent = c;
  return c;
}

node* norm(node* a) {
  while (red(a) || split(a));
  return a;
}

void test_case() {
  vector<node*> ns;

  string s;
  while (getline(cin, s)) {
    if (s.empty()) continue;
    int i = 0;
    node* a = parse(s, i);
    ns.pb(a);
  }

  node* t = ns[0];
  for (int i = 1; i < SZ(ns); i++) {
    t = add(t, ns[i]);
    t = norm(t);
  }
  cout << mag(t) << endl;
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

