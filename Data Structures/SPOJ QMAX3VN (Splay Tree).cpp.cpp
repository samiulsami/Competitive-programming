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



template<typename T>
struct ImplicitSplayTree{
	
	struct node{
		node *l, *r, *p;///left, right, parent
		T val;
		int cnt,mx;///subtree size

		node(){
			l=r=p=NULL;
			cnt=1;
		}
		
		node(T x){
			l=r=p=NULL;
			cnt=1;
			val=x;
			mx=x;
		}
		
		void rotate(){
			if(!p)return;
			if(p->l == this)rightRotate();
			else if(p->r == this)leftRotate();
			
			node *g = p->p;
			if(g!=NULL){
				if(g->l==p)g->l=this;
				else g->r=this;
			}
			p->p = this;
			p = g;
			updatecnt();
		}
		
		inline void leftRotate(){
			p->r = l;
			if(l)l->p = p;
			l = p;
			l->updatecnt();
		}
		
		inline void rightRotate(){
			p->l = r;
			if(r)r->p = p;
			r = p;
			r->updatecnt();
		}
		
		inline void splay(){
			while(p!=NULL){
				if(p->p!=NULL){
					if(bool(p->p->l == p) == bool(p->l == this))p->rotate();
					else rotate();
				}
				rotate();
			}
		}
		
		inline void push(){///push down lazy values
			
		}
		
		inline void updatecnt(){///Merge subtrees
			 cnt = 1 + (l?l->cnt:0) + (r?r->cnt:0);
			 mx = val;
			 if(r)mx = max(mx, r->mx);
			 if(l)mx = max(mx, l->mx);
		}
		
	}*root=NULL;
	node *arr=NULL;
	//int maxNodes;
	int nodeCnt=0;
	
	ImplicitSplayTree(int n=0){
		//maxNodes=n;
		root=NULL;
		arr = (node*)malloc(n*(sizeof(node)));
	}
	~ImplicitSplayTree(){
		// stack<node*>st;
		// if(root)st.push(root);
		// while(!st.empty()){
			// node *top = st.top();
			// st.pop();
			// if(top->r)st.push(top->r);
			// if(top->l)st.push(top->l);
			// delete top;
		// }
		free(arr);
	}
	
	inline node *newNode(T val){
		//assert(nodeCnt<maxNodes);
		node *tmp = (node*)(arr + nodeCnt);
		nodeCnt++;
		*tmp = node(val);
		return tmp;
	}
	
	inline int getcnt(node *cur){return cur?cur->cnt:0;}
	inline bool empty(){return getcnt(root)==0;}
	inline int size(){return getcnt(root);}
	
	
	node *rightmost(node *cur){
		node *ret=NULL;
		node *tmp=cur;
		while(tmp){
			tmp->push();
			ret=tmp;
			tmp = tmp->r;
		}
		ret->splay();
		return ret;
	}
	
	node *kth(int k, node *cur){/// returns the k'th smallest node (0 indexed)
		node *ret=NULL;
		int add=0;
		while(cur){
			cur->push();
			int curCnt = add+getcnt(cur->l);
			if(curCnt==k){
				ret=cur;
				break;
			}
			else if(curCnt<k){
				add = curCnt+1;
				cur = cur->r;
			}
			else cur = cur->l;
		}
		ret->splay();
		
		return ret;
	}
	
	T operator[](int k){///returns the value at the k'th index
		assert(root!=NULL && k<getcnt(root));
		node *tmp = kth(k,root);
		root = tmp;
		return tmp->val;
	}
	
	void append(T val){///Appends 'val' to the right of the array
		node *tmp = newNode(val);
		merge(root, root, tmp);
	}
	
	void insert(int i, T val){///Inserts 'val' into the i'th index
		node *l,*r;
		split(root, l, r, i);
		node *tmp = newNode(val);
		merge(l,l,tmp);
		merge(root,l,r);
	}
	
	void erase(int i){/// Erases the i'th index
		node *tmp = kth(i, root);
		tmp->splay();
		if(tmp->l)tmp->l->p=NULL;
		if(tmp->r)tmp->r->p=NULL;
		merge(root, tmp->l, tmp->r);
		delete tmp;
	}
	
	int range_max(int L, int R){
		node *l,*r,*m;
		split(root,l,m,L);
		split(m,m,r,R-L+1);
		int ret=m->mx;
		merge(root,l,m);
		merge(root,root,r);
		return ret;
	}
	
	///Split 'whole' into two subtrees: 'l' and 'r'
	///'l' contains elements strictly less than 'key'
	void split(node *whole, node* &l, node* &r, int key){
		if(!whole){
			l=r=NULL;
			return;
		}
		if(getcnt(whole)<=key){
			r=NULL;
			l = rightmost(whole);
			l->splay();
			return;
		}

		whole->push();
		node *x = kth(key, whole);
		l = x->l;
		x->l=NULL;
		if(l){
			l->p=NULL;
			l->updatecnt();
		}
		r = x;
		if(r){
			r->updatecnt();
			r->p=NULL;
		}
	}
	
	///Merges the trees 'l' and 'r' into 'whole'
	void merge(node* &whole, node *l, node *r){
		if(l)l->push();
		if(r)r->push();
		if(!l || !r){
			whole = l?l:r;
			return;
		}
		node *tmp = rightmost(l);
		tmp->r = r;
		r->p = tmp;
		whole = tmp;
		whole->updatecnt();
	}
	
};

void solve(int casenum){
	int n,l,r;
	char c;
	si(n);
	ImplicitSplayTree<int> T(n);
	
	while(n--){
		sf(" %c %d%d",&c, &l, &r);
		if(c=='A')T.insert(r-1,l);
		else pf("%d\n",T.range_max(l-1,r-1));
	}
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}