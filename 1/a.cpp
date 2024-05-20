#include<iostream>
using namespace std;
template<typename T>
class myvector{
    private:
    T*list;//save the list
    T*last;//it's the last of this list
    int size;
    int volum;//the real capcity
    public:
    myvector(){
        list=nullptr;
        size=0;
        volum=0;
    }
    myvector(int n){
        list=new T[n];
        size=n;
        volum=n;
        for(int i=0;i<n;i++){
            list[i]=0;
        }
    }
    myvector(int n,T t){
        list=new T[n];
        size=n;
        volum=n;
        for(int i=0;i<n;i++){
            list[i]=t;
        }
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
            list[i]=other[i];
        }
    }
    ~myvector(){
        delete[] list;
    }
    myvector& operator=(const myvector&other){
        if(this==&other){
            return *this;
        }
        else{
            size=other.size;
            volum=other.volum;
            T* list1=new T[volum];
            for(int i=0;i<size;i++){
                list1[i]=other[i];
            }
            delete[] list;
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
    void expand(const int new_volum){
        if(new_volum==0){
            volum=1;//update the volum
            list=new T[1];
            return;
        }
        T* list1=new T[new_volum];
        for(int i=0;i<size;i++){
            list1[i]=list[i];
        }
        delete[] list;
        list=list1;
        volum=new_volum;
    }
    void push_back(T&t){
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
    void pop_back(){
        size--;
        if(size<volum/2){
            this->expand(volum/2);
        }
    }
    int mysize()const{
        return size;
    }
    void clear(){
        size=0;
        volum=0;
        delete[] list;
    }
    T* begin(){return list;}
};
class Solution{
private:
myvector<int>a;
int n;
myvector<myvector<int>>son;
myvector<int>subset;
public:
Solution(){

}
void in(){
    cin>>n;
    int g;
    for(int i=0;i<n;i++){
        cin>>g;
        a.push_back(g);
    }
}
void recursion(int i,bool status){
    if(i==n){
        if(status)
        son.push_back(subset);
        return;
    }
        if(status){
            subset.push_back(a[i]);
            recursion(i+1,1);
            subset.pop_back();
            subset.push_back(a[i]);
            recursion(i+1,0);
            subset.pop_back();
        }
        else{
            recursion(i+1,1);
            recursion(i+1,0);
        }

}
void caculate(){
    int sum=0;
    for(int i=0;i<son.mysize();i++){
        int sum1=0;
        for(int u=0;u<son[i].mysize();u++){
            sum1+=son[i][u]*(u+1);
        }
        sum=sum^sum1;
    }
    cout<<sum;
}
};
int main(){
    Solution s=Solution();
    s.in();
    s.recursion(0,1);
    s.recursion(0,0);
    s.caculate();
}