enum type {X,ZIG,ZAG,FALSE};

template <class T>
class splayTree{
    struct node{
    T data;
    node *left, *right;
    node(T d, node *l=NULL, node *r=NULL):data(d),left(l),right(r){}
};
    node *root;

    type insert(const T &x, node *&t);
    type find(const T &x, node *&t);
    void remove(const T &x, node *&t);
    void makeEmpty(node *&t);
    void zigzig(node *&t);
    void zigzag(node *&t);
    void zagzig(node *&t);
    void zagzag(node *&t);
public:
    splayTree() {root = NULL;}
    ~splayTree() {makeEmpty(root);}

    bool find(const T &x);
    void insert(const T &x);
    void remove(const T &x) {remove(x,root);}
};

//-----private-----//
template <class T>
type splayTree<T>::insert(const T &k, node *&t){
    type rn;
    if(t==NULL) {t = new node(k); return X;}    //在空树上插入
    if(k<t->data){      //在左子树插入
        rn = insert(k,t->left);
        switch(rn){
            case X: return ZIG;
            case ZIG: zigzig(t); return X;
            case ZAG: zigzag(t); return X;
        }
    }
    else{               //在右子树插入
        rn = insert(k,t->right);
        switch(rn){
            case X: return ZAG;
            case ZIG: zagzig(t); return X;
            case ZAG: zagzag(t); return X;
        }
    }
}

template <class T>
type splayTree<T>::find(const T &x, node *&t){
    type rn;
    if(t==NULL) return FALSE;   //空树
    if(t->data==x) return X;    //根结点就是要找的结点
    if(x>t->data){              //查找右子树
        rn = find(x,t->right);
        switch(rn){
            case X: return ZAG;
            case ZIG: zagzig(t); return X;
            case ZAG: zagzag(t); return X;
            default: return FALSE;
        }
    }
    else{                       //查找左子树
        rn = find(x,t->left);
        switch(rn){
            case X: return ZIG;
            case ZIG: zigzig(t); return X;
            case ZAG: zigzag(t); return X;
            default: return FALSE;
        }
    }
}

template <class T>
void splayTree<T>::remove(const T &x, node *&t){
    if(t==NULL) return;
    if(x<t->data) remove(x,t->left);
    else if(x>t->data) remove(x,t->right);
    else if(t->left!=NULL&&t->right!=NULL){ //有两个儿子
        node *tmp = t->right;
        while(tmp->left!=NULL) tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data,t->right);
    }
    else{   //被删结点是叶结点或只有一个儿子
        node *oldNode = t;
        t = (t->left!=NULL)?t->left:t->right;
        delete oldNode;
    }
}

template <class T>
void splayTree<T>::makeEmpty(node *&t){
    if(t->left!=NULL) makeEmpty(t->left);
    if(t->right!=NULL) makeEmpty(t->right);
    delete t;
}

template <class T>
void splayTree<T>::zigzig(node *&t){
    node *g = t, *p = g->left, *x = p->left;    //g:祖父,p:父亲,x:伸展结点

    p->left = x->right;
    g->left = p->right;
    p->right = g;
    x->right = p;
    t = x;
}

template <class T>
void splayTree<T>::zigzag(node *&t){
    node *g = t, *p = g->left, *x = p->right;

    g->left = x->right;
    p->right = x->left;
    x->left = p;
    x->right = g;
    t = x;
}

template <class T>
void splayTree<T>::zagzig(node *&t){
    node *g = t, *p = g->right, *x = p->left;

    g->right = x->left;
    p->left = x->right;
    x->left = g;
    x->right = p;
    t = x;
}

template <class T>
void splayTree<T>::zagzag(node *&t){
    node *g = t, *p = g->right, *x = p->right;

    p->right = x->left;
    g->right = p->left;
    p->left = g;
    x->left = p;
    t = x;
}

//-----public-----//

template <class T>
bool splayTree<T>::find(const T &k){
    node *x;
    type rn = find(k,root);
    switch(rn){
        case ZIG:   //伸展结点是根结点的左儿子,LL旋转
            x = root->left;
            root->left = x->right;
            x->right = root;
            root = x;
            return true;
        case ZAG:   //伸展结点是根结点的右儿子,RR旋转
            x = root->right;
            root->right = x->left;
            x->left = root;
            root = x;
            return true;
        case X: return true;    //伸展结点是根结点
        default: return false;  //结点没有找到
    }
}

template <class T>
void splayTree<T>::insert(const T &x){
    type rn = insert(x,root);

    if(rn==ZIG){    //需要LL旋转
        node *x = root->left;
        root->left = x->right;
        x->right = root;
        root = x;
    }
    if(rn==ZAG){    //需要RR旋转
        node *x = root->right;
        root->right = x->left;
        x->left = root;
        root = x;
    }
}
