#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class DisjointSet{
private:
    int size;
    int *parent;
public:
    DisjointSet(int s);
    ~DisjointSet() {delete []parent;}
    void Union(int root1, int root2);
    int Find(int x);
};

DisjointSet::DisjointSet(int n){
    size = n;
    parent = new int[size];
    for(int i=0;i<size;++i) parent[i] = -1;
}

int DisjointSet::Find(int x){
    if(parent[x]<0) return x;
    return parent[x] = Find(parent[x]);
}

void DisjointSet::Union(int root1, int root2){
    if(root1==root2) return;  //比较两棵树是否为同一棵树，如果是，则返回
    if(parent[root1]>parent[root2]) {parent[root2]+=parent[root1]; parent[root1]=root2;}
    else {parent[root1]+=parent[root2]; parent[root2]=root1;}
}

//迷宫生成
void createPuzzle(int size){  //size为迷宫的规模
    int num1, num2;
    DisjointSet ds(size*size);  //迷宫中有size*size个单元

    srand(time(0));

    while(ds.Find(0)!=ds.Find(size*size-1)){  //入口和出口不连通，则循环
        while(true){                          //选择两个相邻的不连通单元
            num1 = rand()*size*size / (RAND_MAX+1);  //随机选择一个单元
            num2 = num1 - size;               //检查上方的单元
            if(num2>=0) if(ds.Find(num1)!=ds.Find(num2)) break;
            num2 = num1 - 1;                  //检查左边的单元
            if(num1%size!=0) if(ds.Find(num1)!=ds.Find(num2)) break;
            num2 = num1 + size;               //检查下方的单元
            if(num2<size*size) if(ds.Find(num1)!=ds.Find(num2)) break;
            num2 = num1 + 1;                  //检查右边的单元
            if(num2%size!=0) if(ds.Find(num1)!=ds.Find(num2)) break;
        }
        ds.Union(ds.Find(num1),ds.Find(num2));//连通num1和num2
        cout << '<' << num1 << ',' << num2 << ">,";
    }
}

int main()
{
    createPuzzle(4);
    return 0;
}
