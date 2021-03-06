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

bool bad(LL n) {
    LL tmp = n;
    while (tmp > 0) {
        LL x = tmp % 10;
        tmp /= 10;
        if (x == 0) continue;
        if (n % x != 0) return true;
    }
    return false;
}

void process() {
    LL n; cin >> n;
    while (bad(n)) n++;
    cout << n << endl;
}

