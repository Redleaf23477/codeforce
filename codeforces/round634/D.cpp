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

void init();
void process();

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while(T--)
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j =0 ; j < 9; j++)
            {
                char ch; cin >> ch;
                if(ch == '7') cout << '1';
                else cout << ch;
            }
            cout << endl;
        }
    }
    cout.flush();
    return 0;
}

void init()
{
}

void process()
{
}

