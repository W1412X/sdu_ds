#include<bits/stdc++.h>
using namespace std;
const int mxn=200001;
template <class T>
class myvector{
    public:
    T*list;//save the list
    T*last;//it's the last of this list
    int size;
    int volum;//the real capcity
    myvector(){
        list=new T[50];
        size=0;
        volum=50;
    }
    T& operator[](int index)const{
        if(index>=size){
            throw "index out range";
        }
        return list[index];
    }
    myvector(const myvector&other){
        size=other.size;
        volum=other.volum;
        list=new T[volum];
        for(int i=0;i<size;i++){
            list[i]=other.list[i];
        }
    }
    ~myvector(){
        delete[] list;
    }
    void expand(const int&new_volum){
        T* new_list=new T[new_volum];
        for(int i=0;i<size;i++){
            new_list[i]=list[i];
        }
        delete[] list;
        list=new_list;
        volum=new_volum;
    }
    myvector& operator=(const myvector&other){
        if(this==&other){
            return *this;
        }
        else{
            size=other.size;
            volum=other.volum;
            T* list1=new T[volum];
            delete[] list;
            for(int i=0;i<size;i++){
                list1[i]=other.list[i];
            }
            list=nullptr;
            list=list1;
            return *this;
        }
    }
    bool operator==(const myvector&other)const{
        if(size!=other.size){
            return 0;
        }
        for(int i=0;i<size;i++){
            if(list[i]!=other[i]){
                return 0;
            }
        }
        return 1;
    }
    void push_back(const T&t){
        if(size<volum){
            list[size]=t;
            size++;
        }
        else{
            this->expand(2*volum);
            list[size]=t;
            size++;
        }
    }
    int mysize()const{
        return size;
    }
    void clear(){
        delete[] list;
        size=0;
        volum=0;
    }
};
struct Node
{
    int t;int d;
    bool operator < (const Node &a) const
    {
        return d<a.d;
    }
};
template <class T>
class Queue
{
public:
    T list[500001];
    int size = 0;
    T &top()
    {
        return list[1];
    }
    bool empty(){
        return size==0;
    }
    void push(T a)
    {
        list[size + 1] = a;
        int pos = (size + 1);
        size++;
        while (pos != 1 && a < list[pos / 2])
        {
            T tmp = list[pos];
            list[pos] = list[pos / 2];
            list[pos / 2] = tmp;
            pos /= 2;
        }
    }
    void pop()
    {
        T val = list[size];
        size--;
        list[1] = val;
        int pos = 2;
        while (pos <= size)
        {
            if (pos < size && list[pos + 1]<list[pos])
            {
                pos++;
            }
            if (list[pos] < val)
            {
                list[pos/2] = list[pos];
                list[pos]=val;
                pos *= 2;
            }
            else
            {
                break;
            }
        }
    }
};
int n,m;
int if_link[mxn];
myvector<Node>Edge[500001];
Queue<Node> q;
long long prim()
{
    long long ans=0;
    int cnt=0;
    q.push((Node){1,0});
    while (!q.empty()&&cnt<=n)
    {
        Node k=q.top();q.pop();
        if (if_link[k.t]) continue;
        if_link[k.t]=1;
        ans+=k.d;
        cnt++;
        for (int i=0;i<Edge[k.t].size;i++)
        if (!if_link[Edge[k.t][i].t]){
            q.push((Node){Edge[k.t][i].t,Edge[k.t][i].d});
        }
    }
    return ans;
}
int main()
{
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        int x,y,z;
        cin>>x>>y>>z;
        Edge[x].push_back((Node){y,z});Edge[y].push_back((Node){x,z});
    }
    printf("%lld",prim());
    return 0;
}