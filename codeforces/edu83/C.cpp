// by redleaf23477
#include <bits/stdc++.h>

#define endl '\n'
#define var(x) "[" << #x << "=" << x << "]"
#define chrono_now std::chrono::high_resolution_clock::now()
#define chrono_duration(t1, t2) std::chrono::duration<double>(t2-t1).count()

using namespace std;
using ll = long long int;

int n;
ll k;
vector<ll> cnt;

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
    cnt.resize(64, 0);
    fill(cnt.begin(), cnt.end(), 0);
    for(int i = 0; i < n; i++)
    {
        ll tmp; cin >> tmp;
        for(int j = 0; tmp > 0; j++)
        {
            ll r = tmp % k;
            cnt[j] += r;
            tmp /= k;
        }
    }
//    for(int i = 0; i < 10; i++) cout << var(i) << var(cnt[i]) << endl;
}

void process()
{
    if(*max_element(cnt.begin(), cnt.end()) <= 1) cout << "YES" << endl;
    else cout << "NO" << endl;
}

