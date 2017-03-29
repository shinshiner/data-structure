//代码比较简单，就不写注释了-。=
class linkStack{
private:
    struct node{
        int data;
        node *next;
        node(const int &x, node *N=NULL) {data = x; next = N;}
        node():next(NULL) {}
        ~node() {}
    };
    node *elem;
public:
    linkStack() {elem = NULL;}
    ~linkStack();
    bool isEmpty() const {return elem==NULL;}
    void push(const int &x) {node *tmp = new node(x,elem); elem = tmp;}
    void pop() {node *tmp = elem; elem = elem->next; delete tmp;}
    int top() const {return elem->data;}
};

linkStack::~linkStack(){
    node *tmp;
    while(elem!=NULL){
        tmp = elem;
        elem = elem->next;
        delete tmp;
    }
}
