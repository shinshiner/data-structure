//代码比较简单，就不写注释了-。=
class seqStack{
private:
    int *elem;
    int top_p, maxSize;
    void doublespace();
public:
    seqStack(int initSize=10){elem = new int[initSize]; maxSize = initSize; top_p = -1;}
    ~seqStack() {delete []elem;}
    bool isEmpty() const {return top_p==-1;}
    void push(const int &x) {if(top_p==maxSize-1) doublespace(); elem[++top_p] = x;}
    void pop() {--top_p;}
    int top() const {return elem[top_p];}
};

void seqStack::doublespace(){
    int *tmp = elem;
    elem = new int[2*maxSize];
    for(int i=0;i<maxSize;++i) elem[i] = tmp[i];
    maxSize *= 2;
    delete []tmp;
}
