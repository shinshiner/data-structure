/*
    在一段长度为L的道路下面，埋有水管、煤气管、光纤等线路。维修水管、煤气管、
光纤时都要开挖路面，设计一个程序统计没有被开挖的长度
*/

//用线段树解决
class road{
private:
    struct node{
        int start, end, state;  //state-0:空闲,1:开挖,2:部分开挖
        node *left, *right;
        node(int s, int e):start(s),end(e),state(0),left(NULL),right(NULL) {}
    };
    node *root;

    void create(node *&t, int start, int end);  //建路
    void destory(node *t, int start, int end);  //开挖
    int count(node *t) const;  //统计
    void clear(node *t);  //清除树
public:
    road(int len) {create(root,0,len);}  //单位长度编号从0开始
    ~road() {clear(root);}
    void destory(int start, int end) {destory(root,start,end);}
    int count() const {return count(root);}
};

void road::create(node *&t, int start, int len){
    t = new node(start,start+len-1);
    if(len==1) return;
    create(t->left,start,len/2);
    create(t->right,start+len/2,len-len/2);
}

void road::destory(node *t, int start, int end){
    if(t==NULL||start>t->end||end<t->start) return;
    else if(start<=t->start&&end>=t->end) {t->state = 1; return;}
    destory(t->left,start,end);
    destory(t->right,start,end);
    if(t->state==0) t->state = 2;
}

int road::count(node *t) const{
    if(t->state==0) return t->end-t->start+1;
    else if(t->state==1) return 0;
    return count(t->left)+count(t->right);
}

void road::clear(node *t){
    if(t==NULL) return;
    clear(t->left);
    clear(t->right);
    delete t;
}
