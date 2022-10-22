#include<bits/stdc++.h>

using namespace std;
typedef int64_t ll;
typedef uint64_t ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define ff first
#define ss second
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<n; i++)
#define dbug(x) cerr<<"debug: "<<x<<"\n"
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define pb emplace_back
#define chk cerr<<"----------------\nCAME HERE\n----------------\n";
seed_seq seq{
(uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
(uint64_t) __builtin_ia32_rdtsc(),
(uint64_t) (uintptr_t) make_unique<char>().get()};
mt19937 rng(seq);
mt19937_64 rng64(seq);
inline int rand(int l, int r){uniform_int_distribution<int> rangeRNG(l,r); return rangeRNG(rng);}
template<typename T>inline bool MAX(T &a, T b){return b>a?a=b,1:0;}
template<typename T>inline bool MIN(T &a, T b){return b<a?a=b,1:0;}
inline bool checkBit(int n, int pos){return bool(n&(1<<pos));}
inline int setBit(int n, int pos){return n|(1<<pos);}
inline int toggleBit(int n, int pos){return n^(1<<pos);}
inline int readline(char *s, char d='\n'){int len=0;while((s[len]=getchar())!=d)len++;s[len]='\0';return len;}
ll modMul(ll a, ll b, ll MOD){ll ret=0;a%=MOD;while(b>0){if(b&1)ret=(ret+a)%MOD;b>>=1;a=(a<<1)%MOD;}return ret%MOD;}
ll bigMod(ll a, ll b, ll MOD){if(a==0)return 0;ll ret=1;a%=MOD;while(b>0){if(b&1)ret=(ret*a)%MOD;b>>=1;a=(a*a)%MOD;}return ret%MOD;}
ll lcm(ll a, ll b){return ((a/__gcd(a,b))*b);}
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int N = 1e5+5;

vector<pii>graph[N];

struct LCA{
    ///LCA with Binary Lifting, O(nlogn) preprocessing, O(logn) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>lvl;
    vector<vector<int > >Table,minTable,maxTable;
    int LOG,n,minn,maxx;

    LCA(int n, int root=1):n(n),lvl(n+1),LOG(ceil(log2(n))+1){
        Table.assign(LOG, vector<int>(n+1,-1));
        minTable.assign(LOG, vector<int>(n+1,INT_MAX));
        maxTable.assign(LOG, vector<int>(n+1,INT_MIN));
        dfs(root,-1);
        for(int i=1; i<LOG; i++)
            for(int j=1; j<=n; j++)
                if(Table[i-1][j]!=-1){
                    Table[i][j] = Table[i-1][Table[i-1][j]];
                    minTable[i][j] = min(minTable[i-1][j], minTable[i-1][Table[i-1][j]]);
                    maxTable[i][j] = max(maxTable[i-1][j], maxTable[i-1][Table[i-1][j]]);
                }
    }

    void dfs(int u, int p){
        Table[0][u]=p;
        for(pii e:graph[u]){
            int v=e.second;
            if(v!=p){
                minTable[0][v]=e.first;
                maxTable[0][v]=e.first;
                lvl[v]=lvl[u]+1;
                dfs(v,u);
            }
        }
    }

    pii get(int u, int v){
        minn=INT_MAX;
        maxx=INT_MIN;
        if(lvl[u]!=lvl[v]){
            if(lvl[u]>lvl[v])swap(u,v);
            for(int i=LOG-1; i>=0; i--)
                if(Table[i][v]!=-1 && lvl[Table[i][v]]>=lvl[u]){
                    minn=min(minn,minTable[i][v]);
                    maxx=max(maxx,maxTable[i][v]);
                    v=Table[i][v];
                }
        }
        if(u==v)return pii(minn,maxx);

        for(int i=LOG-1; i>=0; i--){
            if(Table[i][u]!=Table[i][v]){
                minn=min({minn,minTable[i][v],minTable[i][u]});
                maxx=max({maxx,maxTable[i][v],maxTable[i][u]});
                u=Table[i][u];
                v=Table[i][v];
            }
        }
        minn=min({minn,minTable[0][u],minTable[0][v]});
        maxx=max({maxx,maxTable[0][u],maxTable[0][v]});
        return pii(minn,maxx);
    }
};

inline void Solve(int Case){
    int n;
    si(n);
    for(int i=1,u,v,c; i<n; i++){
        siii(u,v,c);
        graph[u].push_back({c,v});
        graph[v].push_back({c,u});
    }

    LCA lca(n);
    int q,l,r;
    si(q);
    while(q--){
        sii(l,r);
        if(l==r)pf("0 0\n");
        else{
            pii ans=lca.get(l,r);
            pf("%d %d\n",ans.ff,ans.ss);
        }
    }

}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
  //#define fastio
int main(){
    #ifdef fastio
        ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #endif
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        #ifdef fastio
            cin>>T;
        #else
            scanf("%d",&T);
        #endif
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
