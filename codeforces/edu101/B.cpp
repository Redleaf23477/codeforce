// by redleaf23477
#include <bits/stdc++.h>

// iostream macros
#define endl '\n'
#define var(x) "[" << #x << "=" << x << "]"
// chrono macros
#define chrono_now std::chrono::high_resolution_clock::now()
#define chrono_duration(t1, t2) std::chrono::duration<double>(t2-t1).count()
#define chrono_rand_seed chrono_now.time_since_epoch().count()
// random
std::mt19937_64 myrand(chrono_rand_seed);

using namespace std;
using LL = long long int;

void init();
void process();

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        init();
        process();
    }
    cout.flush();
    return 0;
}

void init() {
}

void process() {
    LL a = 0, b = 0;
    LL n; cin >> n;
    for (LL i = 0, s = 0; i < n; i++) {
        LL x; cin >> x;
        a = max(a, s+=x);
    }
    cin >> n;
    for (LL i = 0, s = 0; i < n; i++) {
        LL x; cin >> x;
        b = max(b, s+=x);
    }
    cout << a+b << endl;
}

