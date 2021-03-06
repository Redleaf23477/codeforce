//
#include <bits/stdc++.h>

#define endl '\n'
using namespace std;
typedef long long ll;

/////////////////

const double PI = acos(-1.0);
struct Complex
{
    double x,y;
    Complex(){}
    Complex(double a):x(a),y(0){}
    Complex(double a, double b):x(a),y(b){}
    Complex operator+ (const Complex &a){ return Complex(x+a.x,y+a.y); }
    Complex operator- (const Complex &a){ return Complex(x-a.x,y-a.y); }
    Complex operator* (const Complex &a){ return Complex(x*a.x-y*a.y,x*a.y+y*a.x); }
};
inline vector<Complex> fft(vector<Complex> rtn, int Rev = 1)
{
    int fft_n = rtn.size();
    for(int i=0,j=0;i<fft_n;i++)
    {
        if(i>j) swap(rtn[i],rtn[j]);
        for(int k=(fft_n>>1);(j^=k)<k;k>>=1);
    }
    for(int i=2,m;i<=fft_n;i<<=1)
    {
        m = i>>1;
        for(int j=0;j<fft_n;j+=i)
        {
            for(int k=0;k<m;k++)
            {
                Complex y = rtn[j+k+m]*Complex(cos(2*PI/i*k), Rev*sin(2*PI/i*k));
                rtn[j+k+m] = rtn[j+k]-y;
                rtn[j+k] = rtn[j+k]+y;
            }
        }
    }
    for(int i=0;!~Rev&&i<fft_n;i++)
        rtn[i].x = rtn[i].x/fft_n;
    return rtn;
}

class BigInt
{
    public:
        // constructors
        BigInt();
        BigInt(ll);
        BigInt(const char*);
        BigInt(string);
        BigInt(bool, vector<int>);
        // functions
        inline void print();
        // operators
        bool operator== (const BigInt &a) const;
        bool operator!= (const BigInt &a) const;
        bool operator< (const BigInt &a) const;
        bool operator> (const BigInt &a) const;
        bool operator<= (const BigInt &a) const;
        bool operator>= (const BigInt &a) const;
        BigInt operator- () const;
        BigInt operator+ (const BigInt &a) const;
        BigInt operator- (const BigInt &a) const;
        BigInt operator* (const BigInt &a) const;
        BigInt operator/ (const BigInt &a) const;
        BigInt operator% (const BigInt &a) const;
        // variables
        const static int MAX = 1000000;
        bool Neg = false;
        vector<int> seq;
};

// constructors
BigInt::BigInt(){}
BigInt::BigInt(ll in)
{
    if(in<0) Neg=true, in=-in;
    while(in!=0)
    {
        seq.emplace_back(in%MAX);
        in/=MAX;
    }
    if(seq.empty()) seq.emplace_back(0);
}
BigInt::BigInt(const char *s)
{
    int i, j, tmp, end=0;
    if(s[0]=='-') Neg=true, end=1;
    for(i=strlen(s)-1, j=1, tmp=0; i>=end; i--, j*=10)
    {
        if(j==MAX)
        {
            seq.emplace_back(tmp);
            j=1, tmp=0;
        }
        tmp += (s[i]-'0')*j;
    } seq.emplace_back(tmp);
}
BigInt::BigInt(string s):BigInt(s.c_str()){}
BigInt::BigInt(bool b, vector<int> v):Neg(b),seq(v){}
// functions
void BigInt::print()
{
    if(Neg) putchar('-');
    printf("%d",seq.back());
    for(int i=(int)(seq.size())-2; i>=0; i--)
        printf("%06d",seq[i]);
    puts("");
}
// operators
bool BigInt::operator== (const BigInt &a) const
{
    return Neg==a.Neg&&seq==a.seq;
}
bool BigInt::operator!= (const BigInt &a) const
{
    return !((*this)==a);
}
bool BigInt::operator< (const BigInt &a) const
{
    if(Neg^a.Neg) return Neg;
    if(seq.size()!=a.seq.size()) return Neg^(seq.size()<a.seq.size());
    for(int i=seq.size()-1; i>=0; i--)
        if(seq[i]!=a.seq[i]) return Neg^(seq[i]<a.seq[i]);
    return false;
}
bool BigInt::operator> (const BigInt &a) const
{
    if(Neg^a.Neg) return a.Neg;
    if(seq.size()!=a.seq.size()) return a.Neg^(seq.size()>a.seq.size());
    for(int i=seq.size()-1; i>=0; i--)
        if(seq[i]!=a.seq[i]) return a.Neg^(seq[i]>a.seq[i]);
    return false;
}
bool BigInt::operator<= (const BigInt &a) const
{
    return !((*this)>a);
}
bool BigInt::operator>= (const BigInt &a) const
{
    return !((*this)<a);
}
BigInt BigInt::operator- () const
{
    return BigInt(Neg^1, seq);
}
BigInt BigInt::operator+ (const BigInt &a) const
{
    if(Neg^a.Neg)
        return Neg?a-(-(*this)):(*this)-(-a);
    BigInt rtn(Neg, vector<int>(max(seq.size(),a.seq.size())));
    for(int i=0; i<(int)(seq.size()); i++) rtn.seq[i]+=seq[i];
    for(int i=0; i<(int)(a.seq.size()); i++) rtn.seq[i]+=a.seq[i];
    for(int i=0; i<(int)(rtn.seq.size())-1; i++)
        if(rtn.seq[i]>=MAX)
            rtn.seq[i+1]+=rtn.seq[i]/MAX, rtn.seq[i]%=MAX;
    if(rtn.seq.back()>=MAX)
    {
        rtn.seq.emplace_back(rtn.seq.back()/MAX);
        rtn.seq[rtn.seq.size()-2]%=MAX;
    }
    return rtn;
}
BigInt BigInt::operator- (const BigInt &a) const
{
    if(Neg^a.Neg) return (*this)+(-a);
    if(Neg^((*this)<a)) return (-a)-(-(*this));
    BigInt rtn(Neg, vector<int>(max(seq.size(),a.seq.size())));
    for(int i=0; i<(int)(seq.size()); i++) rtn.seq[i]+=seq[i];
    for(int i=0; i<(int)(a.seq.size()); i++) rtn.seq[i]-=a.seq[i];
    for(int i=0; i<(int)(rtn.seq.size())-1; i++)
        if(rtn.seq[i]<0)
            rtn.seq[i+1]--, rtn.seq[i]+=MAX;
    while(!rtn.seq.empty()&&!rtn.seq.back()) rtn.seq.pop_back();
    if(rtn.seq.empty()) rtn = BigInt(0ll);
    return rtn;
}
BigInt BigInt::operator* (const BigInt &a) const
{
    BigInt rtn(Neg^a.Neg, vector<int>(0));
    vector<Complex> x, y;
    for(auto i:seq) x.emplace_back(i);
    for(auto i:a.seq) y.emplace_back(i);
    int N=1;
    while(N<(int)(x.size()+y.size())) N <<= 1;
    while(N!=(int)(x.size())) x.emplace_back(0);
    while(N!=(int)(y.size())) y.emplace_back(0);
    x = fft(x), y = fft(y);
    for(int i=0; i<N; i++) x[i] = x[i]*y[i];
    x = fft(x,-1);
    ll tmp = 0;
    for(int i=0; i<N; i++)
    {
        tmp += (ll)(x[i].x+0.1);
        rtn.seq.emplace_back(tmp%MAX);
        tmp /= MAX;
    } rtn.seq.emplace_back(tmp);
    while(!rtn.seq.empty()&&!rtn.seq.back()) rtn.seq.pop_back();
    if(rtn.seq.empty()) rtn = BigInt(0ll);
    return rtn;
}
BigInt BigInt::operator/ (const BigInt &a) const
{
    if(a==BigInt(0ll)) return a;
    BigInt rtn, check, BItmp, posiA, posiB;
    posiA = (*this), posiA.Neg = false;
    posiB = a, posiB.Neg = false;
    int PRECISION = max(seq.size(),a.seq.size())+6, N = 1;
    ll tmp = 0;
    while(N<PRECISION+6) N <<= 1;
    N <<= 1;
    vector<Complex> B, c1(N,0), c2(N,0), c3(N,0);
    vector<Complex> *x = (&c1), *xp = (&c2), *calc = (&c3);
    for(int i=a.seq.size()-1; i>=0; i--)
        B.emplace_back(a.seq[i]);
    B.resize(N,0);
    B = fft(B);
    (*x)[a.seq.size()] = MAX/a.seq.back();
    bool found = false;
    while(!found)
    {
        (*x) = fft(*x);
        for(int i=0; i<N; i++) (*calc)[i] = (*x)[i]*B[i];
        (*calc) = fft(*calc,-1);
        for(int i=a.seq.size()-1; i<N; i++)
            (*calc)[i-a.seq.size()+1] = (*calc)[i];
        for(int i=N-a.seq.size()+1; i<N; i++)
            (*calc)[i] = 0;
        for(int i=N-1; i>=1; i--)
        {
            tmp = (ll)((*calc)[i].x+0.1);
            (*calc)[i-1] = (ll)((*calc)[i-1].x+0.1)+tmp/MAX;
            (*calc)[i] = tmp %= MAX;
            if(tmp)
            {
                (*calc)[i-1] = (ll)((*calc)[i-1].x+0.1)+1;
                (*calc)[i] = MAX-tmp;
            }
        } (*calc)[0] = 2-(ll)((*calc)[0].x+0.1);
        for(int i=PRECISION+6; i<N; i++) (*calc)[i] = 0;
        (*calc) = fft(*calc);
        for(int i=0; i<N; i++) (*xp)[i] = (*calc)[i]*(*x)[i];
        (*xp) = fft(*xp,-1);
        (*x) = fft(*x,-1);
        for(int i=N-1; i>=1; i--)
        {
            tmp = (ll)((*xp)[i].x+0.1);
            (*xp)[i] = tmp%MAX;
            (*xp)[i-1] = (ll)((*xp)[i-1].x+0.1)+tmp/MAX;
        }
        for(int i=PRECISION+6; i<N; i++) (*xp)[i] = 0;
        found = true;
        for(int i=0; i<=PRECISION&&found; i++)
            if((ll)((*xp)[i].x+0.1)!=(ll)((*x)[i].x+0.1))
                found = false;
        calc = x, x = xp, xp = calc, calc = (&c3);
    }
    for(int i=N-1; i>=(int)(a.seq.size())-1; i--)
        rtn.seq.emplace_back((ll)((*x)[i].x+0.1));
    while(!rtn.seq.back()) rtn.seq.pop_back();
    rtn = rtn*posiA;
    for(int i=N-1; i<(int)(rtn.seq.size()); i++)
        rtn.seq[i-N+1] = rtn.seq[i];
    for(int i=max((int)(rtn.seq.size()-N+1),0); i<(int)(rtn.seq.size()); i++)
        rtn.seq[i] = 0;
    while(!rtn.seq.empty()&&!rtn.seq.back()) rtn.seq.pop_back();
    if(rtn.seq.empty()) rtn = BigInt(0ll);
    check = rtn*posiB;
    BItmp = check+posiB;
    while(posiA>=BItmp)
        rtn = rtn+BigInt(1), check = BItmp, BItmp = check+posiB;
    BItmp = check-posiB;
    while(posiA<=BItmp)
        rtn = rtn-BigInt(1), check = BItmp, BItmp = check-posiB;
    rtn.Neg = Neg^a.Neg;
    return rtn;
}
BigInt BigInt::operator% (const BigInt &a) const
{
    return (*this)-((*this)/a)*a;
}

/////////////////

int n, l;
map<BigInt, char> mp;
vector<BigInt> msg;
vector<BigInt> arr;

BigInt gcd(BigInt lhs, BigInt rhs)
{
    if(rhs == BigInt(0LL)) return lhs;
    else return gcd(rhs, lhs%rhs);
}

void init();
void process();

int32_t main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T, caseN = 0; cin >> T;
    while(T--)
    {
        cout << "Case #" << ++caseN << ": ";
        init();
        process();
    }
    cout.flush();
    return 0;
}

void init()
{
    cin >> n >> l;
    arr.resize(l);
    msg.resize(l+1);
    mp.clear();
    for(int i = 0; i < l; i++) 
    {
        string str; cin >> str;
        arr[i] = BigInt(str);
    }
}

void process()
{
    // get msg 0
    int ohyeah = -1;
    for(int i = 1; i < l; i++)
    {
        if(arr[i] != arr[i-1])
        {
            BigInt g = gcd(arr[i], arr[i-1]);
            msg[i] = g;
            ohyeah = i;
            break;
        }
    }

//    cout << "ohyeah = " << ohyeah << endl;

    for(int i = ohyeah-1; i >= 0; i--)
    {
        msg[i] = arr[i]/msg[i+1];
    }
    for(int i = ohyeah+1; i <= l; i++)
    {
        msg[i] = arr[i-1]/msg[i-1];
    }

//    for(auto x:msg) x.print();

    // label msg
    set<BigInt> s(msg.begin(), msg.end());

    /*
    for(auto x:s)
    {
        x.print();
    }
    */


    auto it = s.begin();
    for(size_t i = 0; i < 26; i++, it++)
    {
        mp[*it] = 'A'+i;
    }

    // output msg
    for(auto x:msg)
    {
        cout << mp[x];
    }
    cout << endl;

    /*
    for(auto x:mp)
    {
        cout << x.second << " ";
        BigInt tmp = x.first;
        tmp.print();
    }
    */
}

