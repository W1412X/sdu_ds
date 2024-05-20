#include<iostream>
using namespace std;
int n;
template<class T>
class Stack{
    public:
    T*list=new T[100000];
    int size=0;
    void push(T t){
        list[size]=t;
        size++;
    }
    void pop(){
        size--;
    }
    T&top(){
        return list[size-1];
    }
    ~Stack(){
        delete[] list;
    }
};
template<typename T>
class Queue{
public:
    int queuefront;
    int queueback;
    int arraylenth;
    T*queue;
    Queue(int initialCapacity = 10){
        arraylenth=initialCapacity;
        queue=new T[initialCapacity];
        queuefront=0;
        queueback=0;
    }
    ~Queue(){
        delete queue;
    }
    Queue(const Queue&other){
        this->queue=new T[other.arraylenth];
        this->queueback=other.queueback;
        this->queuefront=other.queuefront;
        this->arraylenth=other.arraylenth;
        for(int i=0;i<other.arraylenth;i++){
            this->queue[i]=other.queue[i];
        }
    }
    int size(){
        return (queueback-queuefront<=0?queueback-queuefront+arraylenth:queueback-queuefront)%arraylenth;
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
template<class T>
class Node{
    public:
    bool if_visit=0;
    bool if_push=0;
    T element;
    Node*left;
    Node*right;
    Node(T e){
        element=e;
    };
    Node(){}
};
template<class T>
class BinaryTree{
    public:
    Node<T>* top;
    Stack<Node<T>*>del_set;
    int h_list[100000];
    int node_sum_list[100000];
    void PreOrder(Node<T>*&tmp,bool if_out=1){
        if(if_out)
        cout<<tmp->element<<' ';
        tmp->if_visit=0;
        if(tmp->left!=nullptr){
            PreOrder(tmp->left,if_out);          
        }
        if(tmp->right!=nullptr){
            PreOrder(tmp->right,if_out);
        }
    }
    void InOrder(){
        Stack<Node<T>*>s;
        s.push(top);
        while(s.size!=0){
            Node<T>*tmp=s.top();
            if(tmp->if_visit){
                cout<<tmp->element<<' ';
                s.pop();
                continue;
            }
            tmp->if_visit=1;
            if(tmp->right!=nullptr){
                s.pop();
                s.push(tmp->right);
                s.push(tmp);
            }
            if(tmp->left!=nullptr){
                s.push(tmp->left);
            }
        }
    }
    void PostOrder(){
        Stack<Node<T>*>s;
        s.push(top);
        top->if_push=1;
        while(s.size!=0){
            Node<T>*tmp=s.top();
            if(tmp->if_visit){
                cout<<tmp->element<<' ';
                s.pop();
            }
            if(!tmp->if_visit&&!tmp->if_push)
            s.push(tmp);
            tmp->if_visit=1;
            tmp->if_push=1;
            if(tmp->right!=nullptr){
                if(!tmp->right->if_visit&&!tmp->right->if_push)
                s.push(tmp->right);
                tmp->right->if_push=1;
            }
            if(tmp->left!=nullptr){
                if(!tmp->left->if_visit&&!tmp->left->if_push)
                s.push(tmp->left);
                tmp->left->if_push=1;
            }
        }
    }
    void RowOrder(){
        Queue<Node<int>*>q;
        Node<int>*tmp=top;
        q.push(tmp);
        int last_size=1;
        while(q.size()!=0){
            while(last_size!=0){
                if(q.front()->left!=nullptr){
                    q.push(q.front()->left);
                }
                if(q.front()->right!=nullptr){
                    q.push(q.front()->right);
                }
                cout<<q.front()->element<<' ';
                q.pop();
                last_size--;
            }
            last_size=q.size();
        }
    }
    void height(Node<int>*tmp){
        int lh=0,rh=0;
        if(tmp->left!=nullptr){
            height(tmp->left);
            lh=h_list[tmp->left->element];
        }
        if(tmp->right!=nullptr){
            height(tmp->right);
            rh=h_list[tmp->right->element];
        }
        h_list[tmp->element]=max(lh,rh)+1;
    }
    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    void node_count(Node<T>*tmp){
        int ln=0,rn=0;
        if(tmp->left!=nullptr){
            node_count(tmp->left);
            ln=node_sum_list[tmp->left->element];
        }
        if(tmp->right!=nullptr){
            node_count(tmp->right);
            rn=node_sum_list[tmp->right->element];
        }
        node_sum_list[tmp->element]=ln+rn+1;
    }
    ~BinaryTree(){
        destroyTree(top);
    }
};
int main(){
    BinaryTree<int> bt=BinaryTree<int>();
    Node<int>*list[100001];
    cin>>n;
    bt.top=new Node<int>(1);
    list[1]=bt.top;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        if(l!=-1)
        if(list[l]==nullptr){
            Node<int>*tmp=new Node<int>(l);
            list[l]=tmp;
            list[i]->left=tmp;
        }
        else{
            list[i]=list[l];
        }
        if(r!=-1)
        if(list[r]==nullptr){
            Node<int>*tmp=new Node<int>(r);
            list[r]=tmp;
            list[i]->right=tmp;
        }
        else{
            list[i]=list[r];
        }
    }
    bt.PreOrder(bt.top);
    cout<<endl;
    bt.InOrder();
    cout<<endl;
    bt.PreOrder(bt.top,0);
    bt.PostOrder();
    cout<<endl;
    bt.RowOrder();
    cout<<endl;
    bt.height(bt.top);
    bt.node_count(bt.top);
     for(int i=1;i<=n;i++){
        cout<<bt.node_sum_list[i]<<' ';
    }
    cout<<endl;  
    for(int i=1;i<=n;i++){
        cout<<bt.h_list[i]<<' ';
    }
    cout<<endl; 
}