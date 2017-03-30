//跳表类，插入时用了随机数，运气不好可能会崩
template <class T>
class skipList{
private:
    struct node{  //跳表中的结点类型
        T data;
        int type;
        node **next;
        node() {}
        node(int t){
            type = t;
            next = new node*[t+1];
            for(int i=0;i<=t;++i) next[i] = NULL;
        }
        node(T x, int t){
            data = x;
            type = t;
            next = new node*[t+1];
            for(int i=0;i<=t;++i) next[i] = NULL;
        }
    };
    node *head;  //指向头结点的指针
    int size;    //表长
public:
    skipList() {head = new node(0); size = 0; srand(time(NULL));}
    ~skipList();
    void insert(T x);
    void remove(T x);
    bool find(T x);
};

template <class T>
skipList<T>::~skipList(){
    node *p = head, *q;

    while(p!=NULL){  //释放每个结点
        q = p;
        p = p->next[0];
        delete [] q->next;  //释放结点中的指针数组
        delete q;
    }
}

template <class T>
bool skipList<T>::find(T x){
    node *p;
    int count = 0;

    p = head;
    for(int i=head->type;i>=0;--i){           //从最高层链开始查找
        while(p->next[i]&&p->next[i]->data<x) //查找第i条链
            p = p->next[i];
        if(p->next[i]&&p->next[i]->data==x) return true; //找到
    }
    return false;
}

template <class T>
void skipList<T>::insert(T x){
    int level, randNum;
    node *p, *newp, **last;  //last:插入结点各层的前一结点

    last = new node*[head->type];
    p = head;
    for(int i=head->type;i>=0;--i){  //查找插入结点的前一结点
        while(p->next[i]&&p->next[i]->data<x) p = p->next[i];
        if(p->next[i]&&p->next[i]->data==x) return;
        last[i] = p;
    }

    //生成插入结点的类型，为插入结点申请空间
    ++size;
    level = 0;
    randNum = rand() * size / (RAND_MAX + 1);
    while(randNum>1) {++level; randNum /= 2;}
    newp = new node(x,level);

    if(level>head->type){  //跳表的层次增加了，需要修改头结点
        node *oldHead = head;
        head = new node(level);
        while(level>oldHead->type) head->next[level--] = newp;
        level = oldHead->type;
        for(int i=0;i<=level;++i) head->next[i] = oldHead->next[i];
        for(int i=0;i<=level;++i) if(last[i]==oldHead) last[i] = head;
        delete oldHead;
    }

    for(int i=level;i>=0;--i){  //插入结点链入跳表
        newp->next[i] = last[i]->next[i];
        last[i]->next[i] = newp;
    }
}

template <class T>
void skipList<T>::remove(T x){
    node *p, **last = new node *[head->type];

    p = head;
    for(int i=head->type;i>=0;--i){  //找到被删结点的所有前驱
        while(p->next[i]&&p->next[i]->data<x) p = p->next[i];
        last[i] = p;
    }
    if(p->next[0]==NULL||p->next[0]->data>x) return;
    p = p->next[0];

    --size;
    for(int i=p->type;i>=0;--i)  //将被删结点从所有链上除去
        if(last[i]->next[i]==p) last[i]->next[i] = p->next[i];
    delete []p->next;
    delete p;
}
