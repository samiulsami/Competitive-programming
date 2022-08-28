#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

typedef double ptType;
typedef double ptType2;
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const double PI = acos(-1.0);
const double eps = 1e-9;

struct pt{
	ptType x,y;
	pt(){}
	pt(ptType a, ptType b){x=a;y=b;}
	pt operator-(const pt p)const{return pt(x-p.x, y-p.y);}
	pt operator+(const pt p)const{return pt(x+p.x, y+p.y);}
	pt operator/(const ptType d)const{return pt(x/d,y/d);}
	pt operator*(const ptType d)const{return pt(x*d,y*d);}
	ptType2 operator*(const pt p)const{return ptType2(1)*x*p.x + ptType2(1)*y*p.y;}///dot
	ptType2 operator^(const pt p)const{return ptType2(1)*x*p.y - ptType2(1)*y*p.x;}///cross
	bool operator==(const pt p)const{return x==p.x && y==p.y;}
	bool operator<(const pt p)const{return p.x==x?y<p.y:x<p.x;}
	void rotateccw(double a){
		///Rotate anti-clockwise about origin
		double s = sin(a);double c = cos(a);
		double newx = x*c - y*s;
		double newy = x*s + y*c;
		x=newx;
		y=newy;
	}
	void rotatecw(double a){rotateccw(PI-a);}
	void rotateccw(double a, pt p){
		///Rotate anti-clockwise about p
		x-=p.x;y-=p.y;
		rotateccw(a);
		x+=p.x;y+=p.y;
	}
	void rotatecw(double a, pt p){rotateccw(PI-a,p);}
	void in(){cin>>x>>y;}	
};

inline double toRad(double deg){return (deg*PI)/180.0;}
inline double toDeg(double rad){return (rad*180.0)/PI;}

struct line{
	double a,b,c;
	pt x,y;
	line(){}
	line(double a, double b, double c):a(a),b(b),c(c){}
	line(pt x, pt y){
		this->x=x;
		this->y=y;
		a=x.y-y.y;
		b=y.x-x.x;
		c=1LL*x.x*y.y-1LL*x.y*y.x;
	}
	
	double distanceToPoint(pt p){
		return abs(a*p.x + b*p.y + c)/sqrt(a*a+b*b);
	}
};

///Assuming line A intersects line B and they're not parallel, returns their point of intersection
pt intersection(line A, line B){
	double D = A.a*B.b - B.a*A.b;
	pt ret;
	ret.x = (A.b*B.c - B.b*A.c)/D;
	ret.y = (B.a*A.c - A.a*B.c)/D;
	return ret;
}

int orientation(pt &a, pt &b, pt &c){
	///Check if segment ac lies anti-clockwise to segment ab
	///-1 = clockwise
	///1 = anti-clockwise
	///0 = collinear
	ptType2 tmp = (b-a)^(c-a);
	if(abs(tmp)<eps)return 0;
	if(tmp>0.0)return 1;
	return -1;
}

int orientation(pt &a, pt &b, pt &c, pt &d){
	///Check if vector ab lies anti-clockwise to vector cd
	///-1 = clockwise
	///1 = anti-clockwise
	///0 = collinear
	ptType2 tmp = (b-a)^(d-c);
	if(abs(tmp)<eps)return 0;
	if(tmp>0.0)return 1;
	return -1;
}

bool onSegment(pt &a, pt &b, pt &c){
	///Check if point c lies on the segment ab
	if(orientation(a,b,c)!=0)return 0;
	if(c.x>=min(a.x, b.x) && c.x<=max(a.x, b.x) && c.y>=min(a.y, b.y) && c.y<=max(a.y, b.y))return 1;
	return 0;
}

bool lineSegmentIntersection(pt &a, pt &b, pt &c, pt &d){
	///Check if segment ab intersects segment cd
	if(onSegment(a,b,c) || onSegment(a,b,d))return 1;
	else if(onSegment(c,d,a) || onSegment(c,d,b))return 1;
	else if(orientation(a,b,c)!=orientation(a,b,d) && orientation(c,d,a)!=orientation(c,d,b))return 1;
	return 0;
}

int pointInTriangle(pt &a, pt &b, pt &c, pt &p){
	/// 0 = Boundary
	/// 1 = Inside
	/// -1 0 Outside
	if(onSegment(a,b,p) || onSegment(b,c,p) || onSegment(c,a,p))return 0;
	int x=orientation(a,b,p),y=orientation(b,c,p),z=orientation(c,a,p);
	if(x==y && y==z)return 1;
	return -1;
}

ptType2 dist2(pt &a, pt &b){
	ptType2 x=a.x-b.x, y=a.y-b.y;
	return (x*x)+(y*y);
}

double dist(pt &a, pt &b){
	return sqrt(double(dist2(a,b)));
}

double linePointDistance(pt a, pt b, pt c, bool isSegment=0){///Topcoder
	if(isSegment){
		ptType dot = (a-b)*(c-b);
		if(dot<0)return sqrt(double(dist2(b,c)));
		ptType dot2 = (b-a)*(c-a);
		if(dot2<0)return sqrt(double(dist2(a,c)));
	}
	return abs(double((b-a)^(c-a))/sqrt(double(dist2(a,b))));
}

///return the area of a polygon times 2
ptType2 polygonArea(vector<pt>&pts){
	ptType2 ret=0;
	for(int i=2; i<(int)pts.size(); i++)
		ret+=(pts[i-1]-pts[0])^(pts[i]-pts[0]);
	if(ret<0)ret=-ret;
	return ret;
}

void randPointInTriangle(const pt &A, const pt &B, const pt &C, pt &ret){
	double pr1=double(rand(0,10000000))/10000000.0;
	double pr2=double(rand(0,10000000))/10000000.0;
	double sqr1=sqrt(pr1);
	ret = A*(1.0-sqr1) + B*(sqr1*(1.0-pr2)) + C*(pr2*sqr1);
	
	///https://blogs.sas.com/content/iml/2020/10/19/random-points-in-triangle.html
	// double u1=double(rand(0,range))/100000000.0;
	// double u2=double(rand(0,range))/100000000.0;
	// if(u1+u2>1.0){
		// u1=1-u1;
		// u2=1-u2;
	// }
	// pt va=C-A,vb=B-A;
	// ret = A+(va*u1 + vb*u2);
}

///Winding Number
int pointInsidePolygon(vector<pt> &points, pt &p){
	///1 = p lies inside polygon
	///0 = p lies outside polygon
	///-1 = p lies on the boundary
	int nn=(int)points.size(), cnt=0;
	for(int i=0; i<nn; i++)
		if(onSegment(points[i],points[(i+1)%nn],p))return -1;
	for(int i=0,j; i<nn; i++){
		j=(i+1)%nn;
		bool below = points[i].y<p.y;
		if(below!=(points[j].y<p.y)){
			int orient = orientation(p,points[i],points[j]);
			if(orient==0)return 0;
			if((below && orient==1) || (!below && orient==-1))cnt+=(below?1:-1);
		}
	}
	return (cnt?1:0);
}

///O(logn)
int pointInConvexPolygon(vector<pt> &pts, pt p){///YouKn0wWho
	///Points must be in clockwise order
	///1 = inside
	///0 = boundary
	///-1 = outside
	if((int)pts.size()==2)return onSegment(pts[0],pts[1],p)?0:-1;
	int low=1,high=int(pts.size())-1,mid;
	int a=orientation(pts[0],pts[1],p), b=orientation(pts[0],pts.back(),p);
	if(a==1 || b==-1)return -1;
	while(low+1<high){
		mid=(low+high)>>1;
		if(orientation(pts[0],pts[mid],p)<=0)low=mid;
		else high=mid;
	}
	int orient = orientation(pts[low],pts[high],p);
	if(orient==0)return 0;
	if(orient==1)return -1;
	if(low==1 && a==0)return 0;
	if(high==int(pts.size())-1 && b==0)return 0;
	return 1;
}


ptType2 minEuclideanDistance(vector<pt> &points){///bicsi
	sort(points.begin(), points.end(), [&](auto &a, auto &b)->bool{
		if(a.x==b.x)return a.y<b.y;
		return a.x<b.x;
	});
	set<pair<ptType,ptType> >st;
	ptType2 ans=(ptType2)LLONG_MAX;
	for(int i=0,j=0; i<sz(points); i++){
		ptType2 d = ceil(sqrt(ans));
		while((points[i].x - points[j].x)>=d){
			st.erase({points[j].y, points[j].x});
			j++;
		}
		auto it1 = st.lower_bound({points[i].y-d, points[i].x});
		auto it2 = st.upper_bound({points[i].y+d, points[i].x});
		for(auto it=it1 ;it!=it2; it++){
			ptType2 x = points[i].y - it->first;
			ptType2 y = points[i].x - it->second;
			ans = min(ans, (ptType2)(x*x)+(y*y));
		}
		st.insert({points[i].y, points[i].x});
	}
	return ans;
}


///Rotating Calipers
ptType2 maxEuclideanDistance(vector<pt>&pts){
	///Points must be in clockwise order
	///Computes the maximum distance(squared) between any two points in a convex polygon in O(n);
	int n = (int)pts.size();
	if(n<=1)return 0;
	auto nxt = [&](int i)->int{return i+1>=n?0:i+1;};
	ptType2 ret=0;
	for(int i=0,j=1; i<j; i++){
		for(;;j=nxt(j)){
			ret=max(ret,dist2(pts[i],pts[j]));
			if(orientation(pts[i],pts[nxt(i)],pts[j],pts[nxt(j)])>=0)break;
		}
	}
	return ret;
}

//Sort points in clockwise order
void polarSort(vector<pt> &pts){
	if(pts.empty())return;
	swap(pts[0], pts[min_element(pts.begin(), pts.end()) - pts.begin()]);
	sort(pts.begin()+1, pts.end(), [&](pt &a, pt &b)->bool{
		int orient = orientation(pts[0], a, b);
		if(orient==0)return dist2(pts[0],a)<dist2(pts[0],b);
		return orient==1;
	});
}

///Monotone Chain Algorithm
///Returns the convex hull in clockwise order
vector<pt> convexHull(vector<pt> &pts){
	sort(pts.begin(),pts.end(),[&](pt &a, pt &b)->bool{
		if(a.x==b.x)return a.y<b.y;
		return a.x<b.x;
	});
	vector<pt>ret;
	ret.reserve(sz(pts)+1);
	auto work = [&](int n, int i)->bool{
		if(sz(ret)-n<2)return 0;
		if(orientation(ret[sz(ret)-2],ret.back(),pts[i])>=0)return 1;
		return 0;
	};
	for(int i=0; i<sz(pts); i++){
		while(work(0,i))ret.pop_back();
		ret.push_back(pts[i]);
	}
	ret.pop_back();
	for(int i=sz(pts)-1,x=sz(ret); i>=0; i--){
		while(work(x,i))ret.pop_back();
		ret.push_back(pts[i]);
	}
	ret.pop_back();
	if(sz(ret)==2 && ret[0].x==ret[1].x && ret[0].y==ret[1].y)ret.pop_back();
	return ret;
}

///Pick's Theorem: S = I + (B/2) - 1
/// S = Area, I = lattice points inside polygon, B = lattice points on the boundary of the polygon
/// Number of lattice points between point A and B = __gcd(abs(A.x-B.x), abs(A.y-B.y))
inline void solve(int caseNum){
	double w,h,a;
	cin>>w>>h>>a;

	if(int(a)%180==0){
		cout<<fixed<<setprecision(12)<<w*h;
	}
	else{
		a = toRad(a);
		double ww=w/double(2);
		double hh=h/double(2);
		vector<pt>initial;
		initial.push_back(pt(-ww,hh));
		initial.push_back(pt(ww,hh));
		initial.push_back(pt(ww,-hh));
		initial.push_back(pt(-ww,-hh));

		vector<pt>rotated = initial;
		for(auto &p:rotated)p.rotateccw(a);

		vector<pt>poly;
		for(int i=0; i<4; i++){
			pt A = initial[i];
			pt B = initial[(i+1)%4];
			for(int j=0; j<4; j++){
				pt C = rotated[j];
				pt D = rotated[(j+1)%4];
				if(lineSegmentIntersection(A,B,C,D)){
					poly.push_back(intersection(line(A,B), line(C,D)));
				}
			}
		}

		polarSort(poly);

		cout<<fixed<<setprecision(12)<<polygonArea(poly)/2.0;
	}
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}