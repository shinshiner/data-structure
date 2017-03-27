class bigInt{
    friend istream& operator>>(istream &in, bigInt &obj);
    friend ostream& operator<<(ostream &os, bigInt &obj);
    friend bigInt operator+(const bigInt &r1, const bigInt &r2);
    friend bigInt operator-(const bigInt &r1, const bigInt &r2);
private:
    char data[100];
    int size;
public:
    bigInt() {size = 1; data[0] = '0';}
    bigInt(char str[]);
    ~bigInt() {}
    bigInt& operator=(const bigInt &obj);
};

bigInt::bigInt(char str[]){
    size = strlen(str);
    for(int i=0;i<size;++i) data[i] = str[size-i-1];
}

istream& operator>>(istream &in, bigInt &obj){
    char tmp[100];
    in >> tmp;
    obj.size = strlen(tmp);
    for(int i=0;i<obj.size;++i) obj.data[i] = tmp[obj.size-i-1];
}

ostream& operator<<(ostream &os, bigInt &obj){
    for(int i=obj.size-1;i>=0;--i) os << obj.data[i];
}

bigInt& bigInt::operator=(const bigInt &obj){
    if(this==&obj) return *this;
    size = obj.size;
    for(int i=0;i<size;++i) data[i] = obj.data[i];
    return *this;
}

bigInt operator+(const bigInt &r1, const bigInt &r2){
    int n=min(r1.size,r2.size), k=0, tmp, i;  //k表示进位,tmp暂存逐位相加的结果
    bigInt res;

    for(i=0;i<n;++i){
        tmp = r1.data[i] + r2.data[i] + k - '0';
        if(tmp>'0'+9) {k = 1; tmp -= 10;}
        else k = 0;
        res.data[i] = tmp;
    }

    if(r1.size>r2.size)
        for(i=n;i<r1.size;++i){
            tmp = r1.data[i] + k;
            if(tmp>'0'+9) {k = 1; tmp -= 10;}
            else k = 0;
            res.data[i] = tmp;
        }
    else
        for(i=n;i<r2.size;++i){
            tmp = r2.data[i] + k;
            if(tmp>'0'+9) {k = 1; tmp -= 10;}
            else k = 0;
            res.data[i] = tmp;
        }
    if(k==1) {res.data[i] = '1'; res.size = i + 1;}
    else res.size = i;

    return res;
}

bigInt operator-(const bigInt &r1, const bigInt &r2){  //保证r1>r2
    int n=r2.size, k=0, tmp, i;  //k表示退位,tmp暂存逐位相减的结果
    bigInt res;

    for(i=0;i<n;++i){
        tmp = r1.data[i] - r2.data[i] + '0' - k;
        if(tmp<'0') {k = 1; tmp += 10;}
        else k = 0;
        res.data[i] = tmp;
    }

    if(r1.size>r2.size)
        for(i=n;i<r1.size;++i){
            tmp = r1.data[i] - k;
            if(tmp<'0') {k = 1; tmp += 10;}
            else k = 0;
            res.data[i] = tmp;
        }

    res.size = i;
    for(int j=r1.size-1;j>=0;--j){
        if(res.data[j]=='0') {--res.size;}
        else break;
    }

    return res;
}
