
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

/*
 *  class to search AP, Bridge, BiCC in an undirected graph
 */
class UndirectedTarjan
{
private:
    int vn;
    int ts; // dfs timestamp
    vector<vector<int>> graph;  // index of v = 0 ~ vn-1
    vector<int> low;
    vector<int> dep;  // depth of node, implemented with timestamp
    stack<int> biccStk;  // stack, used to find BiCC
    stack<int> bccStk;  // stack, used to find BCC
    vector<int> AP;
    vector<vector<int>> BiCC;
    vector<pair<int,int>> Bridge;
    vector<vector<int>> BCC;
    void reportAP(int ap) { AP.emplace_back(ap); }
    void reportBiCC(int v)
    {
        vector<int> block(1, v);
        while(biccStk.top() != v) 
        {
            block.emplace_back(biccStk.top()); biccStk.pop();
        }
        BiCC.emplace_back(block);
    }
    void reportBridge(int u, int v) { Bridge.emplace_back(u, v); }
    void reportBCC(int v)
    {
        vector<int> bcc;
        int x;
        do
        {
            x = bccStk.top(); bccStk.pop();
            bcc.emplace_back(x);
        } while(x != v);
        BCC.emplace_back(bcc);
    }
    void dfs(int v, int p)
    {
        int childNum = 0;
        bool maybeAP = false;
        low[v] = dep[v] = ++ts;
        biccStk.push(v), bccStk.push(v);
        for(auto c : graph[v])
        {
            if(c == p) continue;
            if(dep[c] == 0) // not visited
            {
                childNum++;
                dfs(c, v);
                low[v] = min(low[v], low[c]);
                // AP
                if(dep[v] <= low[c]) maybeAP = true;
                // BiCC
                if(dep[v] <= low[c]) reportBiCC(v);
                // Bridge
                if(dep[v] < low[c]) reportBridge(v, c);
            }
            low[v] = min(low[v], dep[c]);
        }
        // BCC
        if(dep[v] == low[v]) reportBCC(v);
        // AP
        if(v == p && childNum >= 2) reportAP(v);
        if(v != p && maybeAP) reportAP(v);
    }
public:
    void init(int v)
    {
        vn = v, ts = 0;
        graph.resize(v);
        low.resize(v, 0);
        dep.resize(v, 0);
    }
    void addEdge(int u, int v)
    {
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    void run()
    {
        for(int i = 0; i < vn; i++)
            if(dep[i] == 0) dfs(i, i);
    }
    vector<int> getAP() { return AP; }
    vector<vector<int>> getBiCC() { return BiCC; }
    vector<pair<int,int>> getBridge() { return Bridge; }
    vector<vector<int>> getBCC() { return BCC; }
};

int vn;

void init();
void process();

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    while(cin >> vn && vn)
    {
        init();
        process();
    }
    cout.flush();
}

UndirectedTarjan graph;

void init()
{
    graph = UndirectedTarjan();
    graph.init(vn);
    string str;
    cin >> ws;
    while(getline(cin, str))
    {
        stringstream ss(str);
        int a, b;
        ss >> a;
        if(a == 0) break;
        while(ss >> b) graph.addEdge(a-1, b-1);
    }
}

void process()
{
    graph.run();
    auto AP = graph.getAP();
    cout << AP.size() << endl;
}
