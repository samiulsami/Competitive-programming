#include<bits/stdc++.h>
/*
    Problem: https://codeforces.com/gym/102644/ - I. Count Paths Queries
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define FF first
#define SS second
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
#define dbug(x) cerr<<"dbug: "<<x<<"\n"
#define CHK cerr<<"----------------\nCAME HERE\n----------------\n";

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const ll MOD = 1e9+7;
const int MAX = 1e5+5;

template<typename T>
struct Matrix{
    vector<vector<T> >mat;
    int rows,cols;

    Matrix(){}
    Matrix(int rows, int cols):rows(rows),cols(cols),mat(rows, vector<T>(cols,0)){}
    Matrix(vector<vector<T> >val): mat(val), rows((int)val.size()), cols((int)val[0].size()){}

    Matrix operator*(const Matrix &mtrx)const{
        Matrix ret(rows,mtrx.cols);
        for(int i=0; i<rows; i++){
            for(int j=0; j<mtrx.cols; j++){
                    ll tmp=0;
                    for(int k=0; k<cols; k++){
                        tmp+= (1LL * mat[i][k] * mtrx.mat[k][j]);
                        if(tmp>=8LL*MOD*MOD){
                            tmp-=8LL*MOD*MOD;
                        }
                    }
                    ret.mat[i][j]=tmp%MOD;
            }
        }

        return ret;
    }
};

Matrix<int> pre[67];

void precompute(Matrix<int> M, int n){
    pre[0]=M;
    for(int i=1; i<31; i++)pre[i]=pre[i-1]*pre[i-1];
}

template<typename T>
Matrix<T> fast_exponentiation(Matrix<T> m, int p){
    Matrix<T> ret(m.rows,m.rows);
    for(int i=0; i<ret.rows; i++)ret.mat[i][i]=1;
    int cnt=0;
    while(p){
        if(p&1)ret = ret*pre[cnt];
        cnt++;
        p>>=1;
    }
    return ret;
}

inline void Solve(int Case){
    int n,m,q;
    siii(n,m,q);
    Matrix<int> M(n,n);

    for(int i=0,u,v; i<m; i++){
        sii(u,v);
        M.mat[u-1][v-1]=1;
    }

    precompute(M,n);

    int x,y,k;
    while(q--){
        siii(x,y,k);
        Matrix<int> res(1,n);
        res.mat[0][x-1]=1;

        for(int i=0; i<=30; i++){
            if(bool(k&(1<<i)))res=res*pre[i];
        }

        pf("%d\n",res.mat[0][y-1]);
    }
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
