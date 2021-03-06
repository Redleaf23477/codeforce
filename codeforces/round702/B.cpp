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
// stl
#define range(seq) seq.begin(), seq.end()


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
    int n; cin >> n;
    vector<int> cnt(3, 0); {
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            cnt[x%3]++;
        }
    }
    int ans = 0; {
        int i = max_element(range(cnt))-cnt.begin();
        for (int j = 0; j < 6; j++, i=(i+1)%3) {
            int d = cnt[i] - n/3;
            if (d > 0) {
                ans += d, cnt[(i+1)%3] += d, cnt[i] -= d;
            }
        }
    }
    cout << ans << endl;
}

