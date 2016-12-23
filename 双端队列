//双端队列类,同时支持访问最大元素和最小元素的队列
template <class T>
class MinMaxHeap{
    T *data;    //数组的起始地址
    int length; //有效元素个数
    int size;   //数组规模

    int level(int p);            //检查p在最大层,还是最小层.最大层返回1,最小层返回0
    void VerifyMin(int p, T x);  //沿最小层过滤,维护有序性
    void VerifyMax(int p, T x);  //沿最大层过滤,维护有序性
    int findMinSonOrGrandSon(int n);  //找出结点n的儿子和孙子中的最小结点
    int findMaxSonOrGrandSon(int n);  //找出结点n的儿子和孙子中的最大结点
public:
    MinMaxHeap(int n=100):size(n+1),length(0) {data = new T[size];} //构造函数
    ~MinMaxHeap() {delete []data;}  //析构函数

    void insert(T x);                  //插入元素x
    T getMax();                        //获取最大元素
    T getMin() {return data[1];}       //获取最小元素
    T deleteMax();                     //删除最大元素
    T deleteMin();                     //删除最小元素
    bool isEmpty() {return length==0;} //判断队员是否为空
};

//-----private-----//

template <class T>
int MinMaxHeap<T>::level(int p){
    int lvl = log(p) / 0.693;   //0.693是log2
    return (lvl % 2);
}

template <class T>
void MinMaxHeap<T>::VerifyMin(int i, T x){
    for(int gp=i/4;gp&&(x<data[gp]);gp/=4){  //gp是i的祖父
        data[i] = data[gp];
        i = gp;
    }
    data[i] = x;    //将x插入结点i
}

template <class T>
void MinMaxHeap<T>::VerifyMax(int i, T x){
    for(int gp=i/4;gp&&(x>data[gp]);gp/=4){  //gp是i的祖父
        data[i] = data[gp];
        i = gp;
    }
    data[i] = x;    //将x插入结点i
}

template <class T>
int MinMaxHeap<T>::findMinSonOrGrandSon(int n){
    int min = 2 * n;
    if(min+1<=length&&data[min+1]<data[min]) ++min;
    for(int k=4*n;k<=length&&k<4*(n+1);++k)
        if(data[k]<data[min]) min = k;
    return min;
}

template <class T>
int MinMaxHeap<T>::findMaxSonOrGrandSon(int n){
    int max = 2 * n;
    if(max+1<=length&&data[max+1]<data[max]) ++max;
    for(int k=4*n;k<=length&&k<4*(n+1);++k)
        if(data[k]<data[max]) max = k;
    return max;
}

//-----public-----//

template <class T>
void MinMaxHeap<T>::insert(T x){
    if(length==size-1) {cout << "队列满"; return;}  //可改成doublespace()
    ++length;
    int p = length / 2;   //p是新结点的父亲
    if(p==0) {data[1] = x; return;}
    switch(level(p)){
        case 0:             //p在最小层
            if(x<data[p]){  //沿着最小层检查
                data[length] = data[p];
                VerifyMin(p,x);
            }
            else VerifyMax(length,x);  //沿着最大层检查
            break;
        case 1:             //p在最大层
            if(x>data[p]){  //沿着最大层检查
                data[length] = data[p];
                VerifyMax(p,x);
            }
            else VerifyMin(length,x);  //沿着最小层检查
    }   //switch结束
}

template <class T>
T MinMaxHeap<T>::getMax(){
    if(length==1) return data[1]; //如果堆中只有一个元素,直接操作即可

    //否则在根的两个儿子中找一个大的返回
    int max;
    if(length==2) max = 2;
    else max = (data[2]>data[3]?2:3);
    return data[max];
}

template <class T>
T MinMaxHeap<T>::deleteMax(){
    //如果堆中只有一个元素,则直接删除
    if(length==1) return data[length--];

    int max;
    //将大元素赋给data[0],准备返回.Max为最大的儿子
    if(length==2) max = 2;
    else max = (data[2]>data[3]?2:3);
    data[0] = data[max];

    T x = data[length--];  //删除最后一个元素,暂存于x
    int i, last = length / 2, parent;
    for(i=max;i<=last;){   //插入x
        max = findMaxSonOrGrandSon(i);
        if(x>data[max]) break;
        data[i] = data[max];

        if(max<=2*i+1){    //如果最大元素是i的儿子结点
            i = max;
            break;
        }

        //继续过滤
        parent = max / 2;
        if(x<data[parent]){
            T temp = x;
            x = data[parent];
            data[parent] = temp;
        }
        i = max;
    }
    data[i] = x;
    return data[0];
}

template <class T>
T MinMaxHeap<T>::deleteMin(){
    data[0] = data[1];              //保存根元素
    T x = data[length--];           //删除堆中的最后一个元素
    int i = 1, last = length / 2;   //为重新插入x作初始化
    int min;

    //寻找插入x的位置
    while(i<=last){  //i有儿子
        min = findMinSonOrGrandSon(i);
        if(x<=data[min]) break;     //可将x插入data[i]
        else{       //向下过滤
            data[i] = data[min];
            if(min<=2*i+1){         //min是i的儿子
                i = min;            //可将x插入data[min]
                break;
            }
            else{                   //min是i的孙子
                int p = min / 2;    //p是min的父亲
                if(x>data[p]){
                    T t = data[p];
                    data[p] = x;
                    x = t;
                }
            }
            i = min;
        }
    }   //while结束
    data[i] = x;
    return data[0];
}
