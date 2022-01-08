#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e5+5;


#define ptType ll
struct pt{
	ptType x,y;
	int id;
};

inline ptType crossproduct(pt &a, pt &b, pt &c){
	return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

int isleft(pt &a, pt &b, pt &c){
	///Check if segment ac lies anti-clockwise to segment ab
	///-1 = clockwise
	///1 = anti-clockwise
	///0 = collinear
	ptType tmp = crossproduct(a,b,c);
	if(tmp>0)return 1;
	if(tmp<0)return -1;
	return 0;
}

ptType dist(pt &a, pt &b){
	ptType aa=a.x-b.x;
	ptType bb=a.y-b.y;
	return (aa*aa) + (bb*bb);
}

bool onSegment(pt &a, pt &b, pt &c){
	///Check if point c lies on the segment ab
	if(isleft(a,b,c)!=0)return 0;
	if(c.x>=min(a.x, b.x) && c.x<=max(a.x, b.x) && c.y>=min(a.y, b.y) && c.y<=max(a.y, b.y))return 1;
	return 0;
}

bool lineSegmentIntersection(pt &a, pt &b, pt &c, pt &d){
	///Check if segment ab intersects segment cd
	if(onSegment(a,b,c) || onSegment(a,b,d))return 1;
	else if(onSegment(c,d,a) || onSegment(c,d,b))return 1;
	else if(isleft(a,b,c)!=isleft(a,b,d) && isleft(c,d,a)!=isleft(c,d,b))return 1;
	return 0;
}

///Pick's Theorem: S = I + (B/2) - 1
/// S = Area, I = lattice points inside polygon, B = lattice points outside polygon
/// Number of lattice points between point A and B = __gcd(abs(A.x-B.x), abs(A.y-B.y))
#undef ptType

void solve(int casenum){
	int n;
	si(n);
	vector<pt>pts(n);
	int ind=0;
	FOR(i,n){
		sll(pts[i].x,pts[i].y);
		pts[i].id=i;
		if(pts[i].y<pts[ind].y || (pts[i].y==pts[ind].y && pts[i].x<pts[ind].x))ind=i;
	}
	swap(pts[0],pts[ind]);
	//pf("first: %d\n",ind);
	sort(pts.begin()+1,pts.end(), [&](pt &a, pt &b)->bool{
		int orient = isleft(pts[0],a,b);
		if(orient==0)return dist(pts[0],a)<=dist(pts[0],b);
		return orient==1;
	});
	bool b=1;
	for(int i=2; i<n; i++){
		if(isleft(pts[0],pts[1],pts[i])!=0){
			b=0;
			break;
		}
	}
	
	pf("Case %d:\n",casenum);
	if(b)pf("Impossible\n");
	else{
		int tmp=n-2;
		for(;tmp>0; tmp--){
			if(isleft(pts[0],pts[tmp],pts[tmp+1])!=0)break;
		}
		tmp++;
		for(int j=n-1; tmp<j; tmp++,j--)swap(pts[tmp],pts[j]);
		for(int i=0; i<n; i++){
			pf("%d",pts[i].id);
			if(i!=n-1)pf(" ");
		}
		nl;
	}
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}