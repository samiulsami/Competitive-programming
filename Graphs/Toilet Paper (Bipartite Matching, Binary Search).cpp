#include<bits/stdc++.h>
/*
    Problem: Bubble Cup 13 - Finals [Codeforces Online Mirror, unrated, Div. 2] - B - Valuable Paper
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define xx first
#define yy second
#define pb push_back
#define mp make_pair
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<=n; i++)
#define FORR(i,l,r) for(int i=l; i<=r; i++)
#define dbug(x) cout<<"dbug: "<<x<<endl
#define eikhane cout<<"Eikhane"<<endl

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;

template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
template<typename T> inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v){bool first = true; os << "["; for(unsigned int i = 0; i < v.size(); i++) { if(!first) os << ", "; os << v[i]; first = false; } return os << "]"; }
template<typename T>inline std::ostream &operator << (std::ostream & os,const std::set<T>& v){bool first = true;os << "[";for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii;first = false;}return os << "]";}
template<typename T1, typename T2>inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v){bool first = true;os << "[";for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii ;first = false;}return os << "]";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 2e5+5;

vector<pii>graph[MAX];
int match[MAX];
int dist[MAX];
int n,m,lim=INT_MAX;

bool bfs(){
    queue<int>q;
    for(int i=0; i<n; i++){
        if(match[i]==-1){
            dist[i]=0;
            q.push(i);
        }
        else dist[i]=-1;
    }
    bool flag=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(pii e:graph[u]){
            int v = e.second;
            if(e.first>lim)continue;
            if(match[v]==-1)flag=1;
            else if(dist[match[v]] == -1){
                dist[match[v]] = dist[u]+1;
                q.push(match[v]);
            }
        }
    }
    return flag;
}

bool dfs(int u){
    for(pii e:graph[u]){
        int v=e.second;
        if(e.first>lim)continue;
        if(match[v]==-1 || (dist[match[v]] == dist[u]+1 && dfs(match[v]))){
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    dist[u]=-1;
    return false;
}

int hopcroft_karp(){
    int matching=0;
    memset(match,-1,sizeof(match));
    while(bfs()){
        for(int i=0; i<n; i++){
            if(match[i]==-1 && dfs(i))
                matching++;
        }
    }
    return matching;
}

inline void Solve(int Case){
    sii(n,m);
    int u,v,c,low,high=-1,mid;
    FOR(i,m-1){
        siii(u,v,c);
        u--;
        v--;
        //deg[u]++:
        //deg[v+n]++;
        graph[u].pb({c,v+n});
        high=max(high,c);
    }

    low=1;
    int ans=INT_MAX;
    while(low<=high){
        lim=(low+high)/2;
        if(hopcroft_karp()>=n){
            ans=min(ans,lim);
            high=lim-1;
        }
        else low=lim+1;
    }

    if(ans==INT_MAX)pf("-1");
    else pf("%d",ans);

}

  //#define Multiple_Test_Cases
int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        //cin>>T;
        si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
