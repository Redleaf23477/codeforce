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
using ll = long long int;

int n, k;
vector<int> arr;

void init();
void process();

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while(T--)
    {
        init();
        process();
    }
    cout.flush();
    return 0;
}

void init()
{
    cin >> n >> k;
    arr.resize(n);
    for(auto &x : arr) cin >> x;
}

void process()
{
    set<int> s(arr.begin(), arr.end());
    if((int)s.size() > k) 
    {
        cout << -1 << endl;
        return;
    }
    vector<int> f(s.begin(), s.end());
    while((int)f.size() != k) f.push_back(1);
    cout << n*k << endl;
    for(int i = 0; i < n; i++)
        for(auto x : f) cout << x << " ";
    cout << endl;
}
