class linkQueue{
private:
    struct node{
        int data;
        node *next;
        node(const int &x, node *N=NULL) {data = x; next = N;}
        node():next(NULL) {}
        ~node() {}
    };
    node *front, *rear;
public:
    linkQueue() {front = rear = NULL;}
    ~linkQueue();
    bool isEmpty() {return front==NULL;}
    void enQueue(const int &x);
    void deQueue();
    int getHead() {return front->data;}
};

linkQueue::~linkQueue(){
    node *tmp;
    while(front!=NULL){
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

void linkQueue::enQueue(const int &x){
    if(rear==NULL) front = rear = new node(x);
    else {rear->next = new node(x); rear = rear->next;}
}

void linkQueue::deQueue(){
    if(front==NULL) return; //队列为空，不做任何操作
    node *tmp = front;
    front = front->next;
    if(front==NULL) rear = NULL;
    delete tmp;
}

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph{
private:
    struct edgeNode{ //保存边的结点类
        int end;
        TypeOfEdge weight;
        edgeNode *next;
        edgeNode(int e, TypeOfEdge w, edgeNode *n=NULL)
            {end = e; weight = w; next = n;}
    };
    struct verNode{ //保存顶点的结点类
        TypeOfVer ver;
        edgeNode *head;
        verNode(edgeNode *h=NULL) {head = h;}
    };
    struct EulerNode{ //保存欧拉回路的结点类
        int NodeNum;
        EulerNode *next;
        EulerNode(int ver) {NodeNum = ver; next = NULL;}
    };

    int Vers, Edges;
    verNode *verList;

    void dfs(int start, bool p[]) const;

    EulerNode *EulerCircuit(int start, EulerNode *&end){
        EulerNode *beg;
        int nextNode;

        beg = end = new EulerNode(start);  //将起始结点放入欧拉回路
        while(verList[start].head!=NULL){  //起始结点尚有边未被访问
            nextNode = verList[start].head->end;
            remove(start,nextNode);
            remove(nextNode,start);
            start = nextNode;
            end->next = new EulerNode(start);
            end = end->next;
        }
        return beg;
    }

    verNode *clone() const{
        verNode *tmp = new verNode[Vers];
        edgeNode *p;

        for(int i=0;i<Vers;++i){  //复制每个结点在邻接表中的信息
            tmp[i].ver = verList[i].ver;  //复制结点i的信息
            p = verList[i].head;
            while(p!=NULL){  //复制结点i对应的边的信息
                tmp[i].head = new edgeNode(p->end,p->weight,tmp[i].head);
                p = p->next;
            }
        }
        return tmp;
    }
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    bool insert(int u, int v, TypeOfEdge w);
    bool remove(int u, int v);
    bool exist(int u, int v) const;
    void dfs() const;
    void bfs() const;
    void EulerCircuit(TypeOfVer start);
    void topSort() const;
};

//
//-------------------public--------------------
//
template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[]){
    Vers = vSize; Edges = 0;
    verList = new verNode[vSize];
    for(int i=0;i<Vers;++i) verList[i].ver = d[i];
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph(){
    edgeNode *p;
    for(int i=0;i<Vers;++i)
        while((p=verList[i].head)!=NULL) {verList[i].head = p->next; delete p;}
    delete []verList;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w){
    verList[u].head = new edgeNode(v,w,verList[u].head);
    ++Edges;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v){
    edgeNode *p = verList[u].head, *q;
    if(p==NULL) return false; //结点u没有相邻的边
    if(p->end==v){  //单链表中的第一个结点就是待删除的边
        verList[u].head = p->next;
        delete p;
        --Edges;
        return true;
    }
    while(p->next!=NULL&&p->next->end!=v) p = p->next; //查找待删除的边
    if(p->next==NULL) return false; //没有找到待删除的边
    q = p->next;
    p->next = q->next;
    delete q;
    --Edges;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const{
    edgeNode *p = verList[u].head;
    while(p!=NULL&&p->end!=v) p = p->next;
    if(p==NULL) return false;
    else return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const{
    bool *visited = new bool[Vers];
    for(int i=0;i<Vers;++i) visited[i] = false;

    cout << "当前图的深度优先遍历序列为：\n";
    for(int i=0;i<Vers;++i){
        if(visited[i]==true) continue;
        dfs(i,visited);
        cout << '\n';
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const{
    bool *visited = new bool[Vers];
    int currentNode;
    linkQueue q;
    edgeNode *p;

    for(int i=0;i<Vers;++i) visited[i] = false; //初始化所有元素为未访问
    cout << "当前图的广度优先遍历序列为：\n";

    for(int i=0;i<Vers;++i){
        if(visited[i]==true) continue;
        q.enQueue(i);
        while(!q.isEmpty()){
            currentNode = q.deQueue();
            if(visited[currentNode]==true) continue;
            cout << verList[currentNode].ver << ' ';
            visited[currentNode] = true;
            p = verList[currentNode].head;
            while(p!=NULL){ //currentNode的后继结点放入队列
                if(visited[p->end]==false) q.enQueue(p->end);
                p = p->next;
            }
        }
        cout << '\n';
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start){
    EulerNode *beg, *end, *p, *q, *tb, *te; //beg,end为欧拉回路的起点和终点
    int numOfDegree, i;
    edgeNode *r;
    verNode *tmp;

    //检查是否存在欧拉回路
    if(Edges==0) {cout << "不存在欧拉回路\n"; return;}
    for(i=0;i<Vers;++i){
        numOfDegree = 0;
        r = verList[i].head;
        while(r!=0) {++numOfDegree; r = r->next;}
        if(numOfDegree==0||numOfDegree%2) {cout << "不存在欧拉回路\n"; return;}
    }

    //寻找起始结点的编号
    for(i=0;i<Vers;++i)
        if(verList[i].ver==start) break;
    if(i==Vers) {cout << "起始结点不存在\n"; return;}
    tmp = clone();  //创建一份邻接表的复制

    //寻找从i出发的路径,路径的起点和终点地址分别是beg和end
    beg = EulerCircuit(i,end);

    while(true){
        p = beg;
        while(p->next!=NULL)  //检查是否有边尚未被访问
            if(verList[p->next->NodeNum].head!=NULL) break;
            else p = p->next;
        if(p->next!=NULL) break;  //所有的边都已被访问
        q = p->next;  //尚有未被访问过的结点
        tb = EulerCircuit(q->NodeNum,te);  //从此结点开始深度优先搜索
        te->next = q->next;  //将搜索到的路径拼接到原来的路径上
        p->next = tb;
        delete q;
    }

    //恢复原图
    delete []verList;
    verList = tmp;

    //显示得到的欧拉回路
    cout << "欧拉回路是：\n";
    while(beg!=NULL){
        cout << verList[beg->NodeNum].ver << ' ';
        p = beg;
        beg = beg->next;
        delete p;
    }
    cout << '\n';
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const{
    linkQueue q;
    edgeNode *p;
    int current, i;
    int *inDegree = new int[Vers];

    //计算每个结点的入度
    for(i=0;i<Vers;++i) inDegree[i] = 0;
    for(i=0;i<Vers;++i)
        for(p=verList[i].head;p!=NULL;p=p->next) ++inDegree[p->end];

    //入度为0的结点入队
    for(i=0;i<Vers;++i)
        if(inDegree[i]==0) q.enQueue(i);

    cout << "拓扑排序为：\n";
    while(!q.isEmpty()){
        current = q.deQueue();
        cout << verList[current].ver << ' ';
        for(p=verList[current].head;p!=NULL;p=p->next)
            if(--inDegree[p->end]==0) q.enQueue(p->end);
    }
    cout << '\n';
}

//
//-------------------private--------------------
//

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const{
    edgeNode *p = verList[start].head;

    cout << verList[start].ver << ' '; //访问结点,可根据实际应用添加相应操作
    visited[start] = true;
    while(p!=NULL){ //对start的后继结点执行dfs
        if(visited[p->end]==false) dfs(p->end,visited);
        p = p->next;
    }
}
