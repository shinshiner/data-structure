//操作比较简单，就不注释了，如果队空，getHead函数不会返回正常值
class seqQueue{
private:
    int *elem;
    int maxSize, front, rear;
    void doublespace();
public:
    seqQueue(int size=10) {elem = new int[size]; maxSize = size; front = rear = 0;}
    ~seqQueue() {delete []elem;}
    bool isEmpty() {return front==rear;}
    void enQueue(const int &x);
    void deQueue();
    int getHead() {return elem[(front+1)%maxSize];}
};

void seqQueue::doublespace(){
    int *tmp = elem;
    elem = new int[2*maxSize];

    for(int i=1;i<maxSize;++i) elem[i] = tmp[(front+i)%maxSize];
    front = 0; rear = maxSize - 1; maxSize *= 2;

    delete tmp;
}

void seqQueue::enQueue(const int &x){
    if((rear+1)%maxSize==front) doublespace();
    rear = (rear+1) % maxSize;
    elem[rear] = x;
}

void seqQueue::deQueue(){
    if(isEmpty()) return;
    front = (front+1) % maxSize;
}
