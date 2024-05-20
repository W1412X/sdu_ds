#include<iostream>
using namespace std;
class BigRootPile{
    public:
    int list[10000];
    int size=0;
    void in(bool if_in=1,int si=0){
        if(if_in)
        cin>>size;
        else{
            size=si;
        }
        for(int i=0;i<size;i++){
            cin>>list[i+1];
        }
    }
    int top(){
        return list[1];
    }
    void push(int a){
        list[size+1]=a;
        int pos=(size+1);
        size++;
        while(pos!=1&&a<list[pos/2]){
            int tmp=list[pos];
            list[pos]=list[pos/2];
            list[pos/2]=tmp;
            pos/=2;
        }
    }
    void pop(){
        int val=list[size];
        size--;
        list[1]=val;
        int pos=2;
        while(pos<=size){
            if(pos<size&&list[pos]>list[pos+1]){
                pos++;
            }
            if(list[pos]<val){
                list[pos/2]=list[pos];
                list[pos]=val;
                pos*=2;
            }
            else{
                break;
            }
        }
    }
    void init(){//init from the last node that have a son
        int current_root=size/2;
        for(;current_root>=1;current_root--){
            int pos=2*current_root;
            while(pos<=size){//same logic as the pop
                if(pos<size&&list[pos]>list[pos+1]){
                    pos++;
                }
                if(list[pos]<list[pos/2]){
                    int tmp=list[pos];
                    list[pos]=list[pos/2];
                    list[pos/2]=tmp;
                }
                pos*=2;
            }
        }
    }
    void out(){
        for(int i=1;i<=size;i++){
            cout<<list[i]<<' ';
        }
        cout<<endl;
    }
    void sort(int size){
        BigRootPile b=BigRootPile();
        b.in(0,size);
        b.init();
        int r[b.size];
        int r_size=b.size;
        while(b.size>0){
        r[b.size-1]=b.top();
        b.pop();
    }
    for(int i=r_size-1;i>=0;i--){
        cout<<r[i]<<' ';
    }
    cout<<endl;
    }
};
int main(){
    BigRootPile brp=BigRootPile();
    brp.in();
    brp.init();
    cout<<brp.top()<<endl;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a;
        if(a==2){
            brp.pop();
            cout<<brp.top()<<endl;
        }
        else{
            cin>>b;
            switch(a)
            {
            case 1:
                brp.push(b);
                cout<<brp.top()<<endl;
                break;
            case 3:
                brp.sort(b);
            default:
                break;
            }
        }
    }
}