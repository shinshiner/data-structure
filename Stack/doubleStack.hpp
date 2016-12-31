template <class T>
class doubleStack{
private:
    T *data;
    int top, bottom, size;      //top：0号栈顶 bottom：1号栈顶

    void doubleSize();

public:
    doubleStack(int initSize=10){   //构造函数
        data = new T[initSize];
        size = initSize;
        top = -1;
        bottom = size;
    }

    ~doubleStack() {delete []data;} //析构函数

    bool isEmpty(int pos)           //判断是否为空栈
        {return ((pos==0&&top==-1)||(pos==1&&bottom==size));}

    T getHead(int pos){                 //读pos号的栈顶元素
        if(pos==0) return data[top];
        else return data[bottom];
    }

    void push(int pos, const T &x); //将x加入第pos号栈

    T pop(int pos){                 //第pos号栈出栈
        if(pos==0) return data[top--];
        else return data[bottom++];
    }
};

template <class T>
void doubleStack<T>::doubleSize(){
    int *tmp_data = new T[size*2];
    for(int i=0;i<=top;++i) tmp_data[i] = data[i];              //复制0号栈
    for(int i=size-1;i>=bottom;--i) tmp_data[size+i] = data[i]; //复制1号栈
    bottom += size;     //重新设置1号栈栈顶
    size *= 2;
    delete []data;
    data = tmp_data;
}

template <class T>
void doubleStack<T>::push(int pos, const T &x){
    if(top+1==bottom) doubleSize(); //栈满则扩容
    if(pos==0) data[++top] = x;
    else data[--bottom] = x;
}
