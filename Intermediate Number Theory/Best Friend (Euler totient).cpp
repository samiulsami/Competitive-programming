#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;

/*
    problem: Best Friend
    verdict:
*/

///----------------------------------TEMPLATE START------------------------------------------------------------------------------------------

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;

///using namespace __gnu_pbds;
///typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
///typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;
///typedef trie<string, null_type, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update> Trie;

///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'


#define xx first
#define yy second
#define sf scanf
#define pf printf
#define pb push_back
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(s) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define nl printf("\n")
#define FOR(n) for(int i=0; i<n; i++)
int dbugtimes=0;
#define dbug printf("GOT HERE %d time(s)\n",++dbugtimes)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define READ  freopen("input.txt","r",stdin)
#define WRITE freopen("output.txt","w",stdout)

inline bool Check(int n, int pos){return bool(n&(1<<pos));}
inline int Set(int n, int pos){return n|(1<<pos);}
inline int unSet(int n, int pos){return n&(~(1<<pos));}

ll modMul(ll a, ll b, ll mod){///(a*b)%mod
    ll ret=0;
    a%=mod;
    while(b>0){
        if(b&1)ret=(ret+a)%mod;
        b>>=1;
        a=(a<<1)%mod;
    }
    return ret%mod;
}

ll bigMod(ll a, ll b, ll mod){///(a^b)%mod
    if(a==0)return 0;
    ll ret=1;
    a%=mod;
    while(b>0){
        if(b&1)ret=(ret*a)%mod;
        b>>=1;
        a=(a*a)%mod;
    }
    return ret%mod;
}

ll lcm(ll a, ll b ){return ((a/__gcd(a,b))*b);}

///--------------------Define to enable sieve---------------------------------
    #define Enable_Sieve

#ifdef Enable_Sieve
const int primesN=1000000;
bitset<primesN>status;
vector<int>primes;
void sieve(){
    int sq=sqrt(primesN);
    status[0]=1;
    for(int i=3; i<=sq; i+=2)
        if(!status[i])
            for(int j=i*i; j<=primesN; j+=i+i)
                status[j]=1;
    primes.push_back(2);
    for(int i=3; i<=primesN; i+=2)if(!status[i])primes.push_back(i);
}
#endif


bool isPrime(int n){
    if(n==2)return 1;
    if(n%2==0 || n==1)return 0;

    #ifdef Enable_Sieve
        if(n<=primesN)return !status[n>>1];
        for(int i:primes) if(n%i==0)return 0;
        return 1;
    #else
        for(int i=3; i*i<=n; i+=2)if(n%i==0)return 0;
    #endif

    return 1;
}

///----------------------------------TEMPLATE END/CODE START----------------------------------------------------------------------------------------

const int MAX   = 1e5 + 5;
const int MOD   = 1e9 + 7;
const double EPS   = 1e-10;
const double PI = acos(-1.0);

#define Multiple_test_cases

ll phi(ll n){
    ll ret=n;
    for(ll i:primes){
        if(i*i>n)break;
        if(n%i==0){
            while(n%i==0)n/=i;
            ret-=ret/i;
        }
    }
    if(n>1)ret-=ret/n;
    return ret;
}

void factorize(ll n,vector<pll> &res){
    ll sq=sqrt(n)+5;
    ll div;
    //set<ll>divisors;
    for(ll i=1; i<=sq; i++){
        if(n%i==0){
            div=n/i;
            res.push_back({i,phi(div)});// n/i
            if(div>sq)res.push_back({div,phi(i)});// n/div
        }
    }

    sort(res.begin(),res.end(),less<pll>());

    for(int i=1,len=(int)res.size()-1; i<len; i++){
        res[i].yy+=res[i-1].yy;
    }

}


void solve(int cases){

    ll n,q,x;
    sll(n,q);

    pf("Case %d\n",cases);

    //vector<ll>divisors;
    vector<pll>res;

    int low,high,mid;
    ll ans;

    while(q--){

        sl(x);

        if(x>=n){
                pf("%lld\n",n);
        }
        else{

            if(res.empty()){
                factorize(n,res);
                //preCalc(n,factors,res);
                //for(int i:factors)cout<<i<<endl;
                //for(auto v: res)cout<<v.xx<<" "<<v.yy<<endl;
            }

            low=0;
            high=(int)res.size()-1;
            ans=0;


            while(low<=high){
                mid=(low+high)/2;
                if(res[mid].xx<=x){
                    ans=max(ans,res[mid].yy);
                    low=mid+1;
                }
                else high=mid-1;
            }

            pf("%lld\n",ans);

        }

    }

}


int main(){
    #ifndef ONLINE_JUDGE
        double start = clock();
        //READ;
        //WRITE;
    #endif

    #ifdef Enable_Sieve
        sieve();
    #endif
    ///fastio;
    //for(int i=0; i<20; i++)cout<<primes[i]<<" ";


    #ifdef Multiple_test_cases
        int T;
        scanf("%d", &T);
        for (int cases = 1; cases <= T; cases++) {
            solve(cases);
        }
	#else
		solve(0);
	#endif

    #ifndef ONLINE_JUDGE
        double tim = (clock() - start)/CLOCKS_PER_SEC;
        cerr<<"\n\nRunning Time : "<<tim<<" \n";
    #endif
return 0;
}
