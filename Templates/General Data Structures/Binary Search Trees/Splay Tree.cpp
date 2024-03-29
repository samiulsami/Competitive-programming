template<typename T>///statically allocated. 0 indexed
struct SplayTree{
	
	struct node{
		node *l, *r, *p;///left, right, parent
		T val;
		int cnt;///subtree size

		node(){
			l=r=p=NULL;
			cnt=1;
		}
		
		node(T x){
			l=r=p=NULL;
			cnt=1;
			val=x;
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
			 
		}
		
	}*root=NULL;
	node *arr=NULL;
	int totalSize;
	int nodeCounter=0;
	
	SplayTree(int n){
		root=NULL;
		totalSize=n;
		arr = (node*)malloc(sizeof(node)*n);
	}
	~SplayTree(){
		free(arr);
	}
	
	inline node *newnode(T val){
		assert(nodeCounter<totalSize);
		node *tmp = (node*)(arr + nodeCounter);
		*tmp = node(val);
		nodeCounter++;
		return tmp;
	}
	
	inline int getcnt(node *cur){return cur?cur->cnt:0;}
	inline bool empty(){return getcnt(root)==0;}
	inline int size(){return getcnt(root);}
	
	node *findNode(T val, node *curnode){
		node *prevNode=NULL;
		
		while(curnode!=NULL){
			curnode->push();
			prevNode=curnode;
			if(val < curnode->val)curnode = curnode->l;
			else if(val > curnode->val)curnode = curnode->r;
			else return curnode;
		}
		
		return prevNode;
	}	
	
	node *findMax(node *cur){
		node *ret=NULL;
		node *tmp=cur;
		while(tmp){
			tmp->push();
			ret=tmp;
			tmp = tmp->r;
		}
		return ret;
	}
	
	bool exists(T val){ /// Returns true if 'val' exists in the tree
		if(root==NULL)return 0;
		node *cur = findNode(val,root);
		cur->splay();
		root=cur;
		
		return cur->val == val;
	}
	
	void insert(T val){/// Inserts 'val' if it doesn't already exist
		if(root==NULL){
			root = newnode(val);
			return;
		}
		
		node *cur = findNode(val,root);
		if(cur->val == val){
			cur->splay();
			root=cur;
			return;
		}
		
		node *newNode = newnode(val);
		if(cur->val < val)cur->r = newNode;
		else cur->l = newNode;
		cur->updatecnt();
		newNode->p = cur;
		newNode->splay();
		root=newNode;
	}
	
	
	void erase(T val){/// Erases 'val' from the tree if it exists
		if(root==NULL)return;
		node *cur = findNode(val,root);
		cur->splay();
		root = cur;
		if(cur->val != val)return;
		
		node *l = cur->l;
		node *r = cur->r;
		
		cur->l=NULL;
		cur->r=NULL;
		
		if(l)l->p=NULL;
		if(r)r->p=NULL;
		
		if(l){
			node *mxNode = findMax(l);
			mxNode->r = r;
			mxNode->updatecnt();
			if(r)r->p = mxNode;
			mxNode->splay();
			root = mxNode;
		}
		else root = r;
	}
	
	T kth(int k){/// returns the kth element (0 indexed)
		assert(k<size());
		node *cur = root;
		T ret;
		int add=0;
		while(cur){
			cur->push();
			int curCnt = add+getcnt(cur->l);
			if(curCnt==k){
				ret=cur->val;
				break;
			}
			else if(curCnt<k){
				add = curCnt+1;
				cur = cur->r;
			}
			else cur = cur->l;
		}
		cur->splay();
		root=cur;
		
		return ret;
	}
	
	T operator[](int i){return kth(i);}
	
	int LTE(T val){/// returns the number of elements less/equal to than 'val'
		if(root==NULL)return 0;
		int cnt=0;
		node *cur = root;
		while(cur){
			cur->push();
			if(cur->val <= val){
				cnt += getcnt(cur->l)+1;
				if(cur->r)cur = cur->r;
				else break;
			}
			else if(cur->l)cur = cur->l;
			else break;
		}
		cur->splay();
		root=cur;
		
		return cnt;
	}
	
	///Split 'whole' into two subtrees: 'l' and 'r'
	///'l' contains elements strictly less than 'key'
	void split(node *whole, node* &l, node* &r, T key){
		if(!whole){
			l=r=NULL;
			return;
		}
		
		whole->push();
		node *tmp = findNode(key,whole);
		tmp->splay();
		
		if(tmp->val < key){
			l=tmp;
			r=tmp->r;
			tmp->r=NULL;
			if(r)r->p=NULL;
			l->p=NULL;
		}
		else{
			l=tmp->l;
			r=tmp;
			tmp->l=NULL;
			if(l)l->p=NULL;
			r->p=NULL;
		}
		
		if(l)l->updatecnt();
		if(r)r->updatecnt();
	}
	
	///Merges the trees 'l' and 'r' into 'whole'
	void merge(node* &whole, node *l, node *r){
		if(l){
			l->push();
			l->p=NULL;
		}
		if(r){
			r->push();
			r->p=NULL;
		}
		if(!l || !r){
			whole = l?l:r;
			return;
		}
		node *tmp = findMax(l);
		tmp->splay();
		tmp->r = r;
		r->p = tmp;
		whole = tmp;
		whole->updatecnt();
	}
	
};