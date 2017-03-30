template <class T>
class bernoulliQueue{
    struct node{
        T data;
        node *son, *brother;
        node(T d, node *s = NULL, node *b = NULL) {data = d; son = s; brother = b;}
        node() {}
    };
    node **forest; //存放贝努里森林中的每棵树的树根的数组
    int treenum;   //数组规模

    int findmin();  //找出根节点值最小的树
    node* merge(node *t1, node *t2){ //归并贝努里树
        node *min, *max;
        if(t1->data<t2->data) {min = t1; max = t2;} //确定树根
        else {min = t2; max = t1;}
        if(min->son==NULL) min->son = max;
        else{
            node *t=min->son;
            while(t->brother!=NULL) t = t->brother;
            t->brother = max;
        }
        return min;
    }
    void delTree(node *rt){  //释放以rt为根的树的空间
        node *son = rt->son, *t;
        while(son!=NULL) {t = son; son = son->brother; delTree(t);}
        delete rt;
    }
public:
    bernoulliQueue(int n=100){  //n是队列中预计的元素个数
        treenum = int(log(n)/log(2)) + 1;  //计算所需的贝努里树的阶数
        forest = new node *[treenum];
        for(int i=0;i<treenum;++i) forest[i] = NULL;
    }
    ~bernoulliQueue(){
        for(int i=0;i<treenum;++i)  //删除每一棵树
            if(forest[i]!=NULL) delTree(forest[i]);
        delete []forest;  //删除存储树根的数组
    }
    void enQueue(T x);
    void deQueue();
    void merge(bernoulliQueue &other);
    T getHead() {int pos=findmin(); return forest[pos]->data;}
};

template <class T>
void bernoulliQueue<T>::merge(bernoulliQueue &other){
    node **tmp=forest, *carry;  //当前对象暂存在tmp中
    int tmpsize=treenum, min=treenum<other.treenum?treenum:other.treenum, i;  //当前对象规模暂存在tmpsize中

    if(treenum<other.treenum){ //确定归并后的森林规模
        treenum = other.treenum;
        if(other.forest[treenum]!=NULL) ++treenum;
    }
    else if(forest[treenum]!=NULL) ++treenum;

    forest = new node*[treenum]; //为归并后的队列申请空间
    for(i=0;i<treenum;++i) forest[i] = NULL;

    carry = NULL;  //初始时进位为空
    for(i=0;i<min;++i){  //归并两个队列中阶数相同的树
        if(carry==NULL){ //没有进位
            if(tmp[i]==NULL) forest[i] = other.forest[i];
            else{
                if(other.forest[i]==NULL) forest[i] = tmp[i];
                else carry = merge(other.forest[i],tmp[i]);
            }
        }
        else{ //有进位
            if(tmp[i]!=NULL&&other.forest[i]!=NULL){
                forest[i] = carry;
                carry = merge(other.forest[i],tmp[i]);
            }
            else{
                if(tmp[i]==NULL&&other.forest[i]==NULL) {forest[i] = carry; carry = NULL;}
                else if(tmp[i]==NULL) carry = merge(other.forest[i],carry);
                else carry = merge(tmp[i],carry);
            }
        }
    }

    //一个队列已结束
    if(other.treenum==min){ //other已结束
        for(;i<tmpsize;++i)
            if(carry==NULL) forest[i] = tmp[i];
            else if(tmp[i]==NULL){forest[i] = carry; carry = NULL;}
            else carry = merge(tmp[i],carry);
    }
    else{  //当前队列已结束
        for(;i<other.treenum;++i)
            if(carry==NULL) forest[i] = other.forest[i];
            else if(other.forest[i]==NULL) {forest[i] = carry; carry = NULL;}
            else carry = merge(other.forest[i],carry);
    }
    if(carry!=NULL) forest[i] = carry;

    for(i=0;i<other.treenum;++i) other.forest[i] = NULL;
    delete []tmp;
}

template <class T>
void bernoulliQueue<T>::enQueue(T x)
{
    bernoulliQueue tmp(1);
    tmp.forest[0] = new node(x);
    merge(tmp);
}

template <class T>
void bernoulliQueue<T>::deQueue()
{
    int min = findmin(); //找到根节点最小的这棵树

    if(min==0) {delete forest[0]; forest[0] = NULL; return;}//删除0阶树

    node *t=forest[min], *son, *brother;  //t:包含最小结点的树根
    int sizeq=int(pow(2,min)-1);
    bernoulliQueue tmp(sizeq);  //存储产生的子树
    forest[min] = NULL;  //从当前树中删除根节点值最小的树t

    son = t->son;  //找到第一棵子树
    delete t;  //释放结点t
    int i=0;
    do {tmp.forest[i++] = son;  //将所有子树存入tmp
        brother = son->brother;
        son->brother = NULL;
    }while((son=brother)!=NULL);

    merge(tmp); //归并tmp
}

template <class T>
int bernoulliQueue<T>::findmin()
{
    int min, i;
    for(i=0;i<treenum&&forest[i]==NULL;++i); //找到第一棵非空树min
    min = i;
    for(;i<treenum;++i)  //扫描后续的树，找出根结点最小的树
        if(forest[i]!=NULL&&forest[i]->data<forest[min]->data) min = i;
    return min;
}
