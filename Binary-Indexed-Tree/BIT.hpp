const int MAX = 100000;
int T[MAX]={0};     //数组初始值必须为0
void Add(int x, int p){   //在x处增加p的值，数组的构造必须用此函数，不能直接赋值
    for(int i=x;i<=MAX;i+=(i&-i)) T[i] += p;
}
int Query(int x){   //查询1~x的区间和
    int res = 0;
    for(int i=x;i;i-=(i&-i)) res += T[i];
    return res;
}
