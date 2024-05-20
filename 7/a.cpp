#include<iostream>
using namespace std;
template<typename T>
class extendedarrayqueue{
public:
    int queuefront;
    int queueback;
    int arraylenth;
    T*queue;
    extendedarrayqueue(int initialCapacity = 10){
        arraylenth=initialCapacity;
        queue=new T[initialCapacity];
        queuefront=0;
        queueback=0;
    }
    ~extendedarrayqueue(){
        delete queue;
    }
    extendedarrayqueue(const extendedarrayqueue&other){
        this->queue=new T[other.arraylenth];
        this->queueback=other.queueback;
        this->queuefront=other.queuefront;
        this->arraylenth=other.arraylenth;
        for(int i=0;i<other.arraylenth;i++){
            this->queue[i]=other.queue[i];
        }
    }
    int size(){
        return queueback-queuefront<=0?queueback-queuefront+arraylenth:queueback-queuefront;
    }
    void input(){
        string s;
        getline(std::cin,s);
        for(int i=0;i<s.size();i++){
            if(s[i]!=' ')
            this->push(T(s[i])-48);
        }
    }
    void output(){
        int tmp=queueback;
        if(queuefront>queueback){
            tmp+=arraylenth;
        }
        for(int i=queuefront+1;i<=tmp;i++){
            cout<<queue[i%arraylenth]<<' ';
        }
        cout<<endl;
    }
    void split(extendedarrayqueue &a,extendedarrayqueue &b){
        extendedarrayqueue tmp=*this;
        while(!tmp.empty()){
            a.push(tmp.front());
            tmp.pop();
            if(!tmp.empty()){
                b.push(tmp.front());
                tmp.pop();
            }
        }
    }
    extendedarrayqueue combine(extendedarrayqueue &a1,extendedarrayqueue &b1){
        extendedarrayqueue re;
        extendedarrayqueue a=a1,b=b1;
        while(!a.empty()&&!b.empty()){
            re.push(a.front());
            a.pop();
            re.push(b.front());
            b.pop();
        }
        while(!a.empty()){
            re.push(a.front());
            a.pop();     
        }
        while(!b.empty()){
            re.push(b.front());
            b.pop();
        }
        return re;
    }
    bool empty() const{
        return queuefront==queueback;      
    }
    void expand(){
        T*newQueue=new T[2*arraylenth];
        int thefront=queuefront;
        int theback=queueback;
        int i=0;
        while((thefront%arraylenth)!=theback){
            newQueue[i]=queue[(thefront+1)%arraylenth];
            thefront++;
            i++;
        }
        queuefront=2*arraylenth-1;
        queueback=arraylenth-2;
        delete[] queue;
        queue=newQueue;
        arraylenth=2*arraylenth;
    }
    T& front(){
        return queue[(queuefront+1)%arraylenth];
    }
    T& back(){
        return queue[queueback];
    }
    void pop(){
        if(queuefront==queueback){
            throw "the queue is empty";
        }
        queuefront=(queuefront+1)%arraylenth;
        queue[queuefront].~T();
    }

    void push(const T& theElement){
        if((queueback+1)%arraylenth==queuefront){
            expand();
        }
        queueback=(queueback+1)%arraylenth;
        T tmp=theElement;
        queue[queueback]=theElement;
    }
};
int main(){
    extendedarrayqueue<int>a=extendedarrayqueue<int>();
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        a.push(i);
    }
    while(a.size()>1){
        a.pop();
        a.push(a.front());
        a.pop();
    }
    cout<<a.front();
}