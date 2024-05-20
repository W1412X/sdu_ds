#include<iostream>
#include <cstring>
using namespace std;
int s,t;

class Node{
    public:
    int id;
    Node*next;
    bool if_visit=0;
    Node(int i):id(i){next=nullptr;}
    Node(){next=nullptr;}
    void insert(int i){
        Node*tmp=this;
        while(tmp->next!=nullptr){
            if(i<tmp->next->id){
                Node*t=tmp->next;
                tmp->next=new Node(i);
                tmp->next->next=t;
                return;
            }
            tmp=tmp->next;
        }
        tmp->next=new Node(i);
    }
    bool find(int i){
        Node*tmp=this;
        while(tmp->id!=i){
            tmp=tmp->next;
            if(tmp==nullptr){
                return 0;
            }
        }
        return 1;
    }
    void erase(int i){
        Node*tmp=this;
        Node*last=tmp;
        while(tmp!=nullptr){
            if(tmp->id==i){
                last->next=tmp->next;
                break;
            }
            last=tmp;
            tmp=tmp->next;
        }
    }
    void out(){
        Node*tmp=this;
        while(tmp!=nullptr){
            cout<<tmp->id<<' ';
            tmp=tmp->next;
        }
        cout<<endl;
    }
};
class Array{    
    public:
    int list[100001];
    int size=0;
    void push(int i){
        list[size]=i;
        size++;
    }
    void out(){
        for(int i=0;i<size;i++){
            cout<<list[i]<<' ';
        }
        cout<<endl;
    }
    int&operator [](int i){
        return list[i];
    }
};
class Qeuery{
    public:
    Node*top=nullptr;
    int size=0;
    Node*last=nullptr;
    void push(int t){
        if(size==0){
            top=new Node(t);
            last=top;
            size++;
            return;
        }
        last->next=new Node(t);
        last=last->next;
        size++;
    }
    int pop(){
        if(size<=0){
            throw "size<=0";
        }
        size--;
        int rt=top->id;
        Node*tmp=top;
        top=top->next;
        delete tmp;
        return rt;
    }
};
class Map{
    public:
    int node_num;
    int min_node_num=0;
    Array min_node_array;
    Array dfs_way;
    Array bfs_way;
    Array min_way;
    int bfs_count=0;
    int pre_node[100001]={-1};
    int distFromStart[100001]={INT32_MAX};
    int if_min_dist[100001]={0};
    int min_node=INT32_MAX;
    bool *if_visit;
    int dfs_count=0;
    Node*chain;
    Map(int n){
        node_num=n;
        if_visit=new bool[100001];
        for(int i=0;i<100001;i++){
            pre_node[i]=-1;
            distFromStart[i]=INT32_MAX;
        }
        chain=new Node[node_num+1];
        for(int i=0;i<=node_num;i++){
            chain[i].id=i;
            chain[i].next=nullptr;
        }
    }

    void dfs(Node*tmp,int &min_node,bool if_out=0){
        if(tmp==nullptr||if_visit[tmp->id]){
            return;
        }
        if_visit[tmp->id]=1;
        if(min_node>tmp->id){
            min_node=tmp->id;
        }
        dfs_count++;
        if(if_out){
            cout<<tmp->id<<' ';
        }
        tmp=tmp->next;
        while(tmp!=nullptr){
            dfs(&chain[tmp->id],min_node,if_out);
            tmp=tmp->next;
        }
    }
    Qeuery& get_qeuery(int pre,Qeuery&q1,Qeuery&q2){
        if(pre%2==0){
            return q1;
        }
        else{
            return q2;
        }
    }
    Qeuery& get_qeuery_to_update(int pre,Qeuery&q1,Qeuery&q2){
        if(pre%2==1){
            return q1;
        }
        else{
            return q2;
        }
    }
    void bfs(int tmp,bool if_out=0){
        Qeuery q1;
        Qeuery q2;
        int pre=0;
        q1.push(tmp);
        while(get_qeuery(pre,q1,q2).size>0){
            while(get_qeuery(pre,q1,q2).size>0){
                Node*t=&chain[get_qeuery(pre,q1,q2).pop()];
                bfs_count++;
                if(if_out)
                cout<<t->id<<' ';
                if_visit[t->id]=1;
                t=t->next;
                while(t!=nullptr){
                    if(!if_visit[t->id]){
                        if_visit[t->id]=1;
                        get_qeuery_to_update(pre,q1,q2).push(t->id);
                    }
                    t=t->next;
                }
            }
            pre++;
        }
    }
    void find_all_min_node(){
        for(int i=1;i<=node_num;i++){
            min_node=INT32_MAX;
            int last_min_node=min_node;
            dfs(&chain[i],min_node);
            if(min_node==INT32_MAX){//在前后没有任何的变化
                continue;
            }
            else{//min_node的值被更新
                min_node_array.push(min_node);
            }
        }
        cout<<min_node_array.size<<endl;
        min_node_array.out();
    }
    //DIJKRA
    int get_min_id(){
        int min_d=INT32_MAX;
        int rt_id=s;
        for(int i=1;i<=node_num;i++){
            if(distFromStart[i]<min_d&&!if_min_dist[i]){
                min_d=distFromStart[i];
                rt_id=i;
            }
        }
        return rt_id;
    }
    void get_min_way(int start,int final){
        for(int i=0;i<node_num;i++){
            if(i==0){
                distFromStart[s]=0;
                if_min_dist[s]=1;
                continue;
            }
            int min_id=get_min_id();
            if_min_dist[min_id]=1;
            if(if_min_dist[t]){
                break;
            }

            Node*tmp=chain[min_id].next;
            while(tmp!=nullptr){
                int g=tmp->id;
                if(!if_min_dist[g]&&distFromStart[min_id]+1<distFromStart[g]){
                    distFromStart[g]=distFromStart[min_id]+1;
                    pre_node[g]=min_id;
                }
                tmp=tmp->next;
            }
        }
        int g=t;
        while(1){
            min_way.push(g);
            g=pre_node[g];
            if(g==-1){
                break;
            }
        }
        if(min_way.size>=2)
        cout<<min_way.size-1<<endl;
        else{
            cout<<-1<<endl;
        }
    }
    int get_min_way_by_bfs(int final){
        Qeuery q1;
        Qeuery q2;
        int pre=0;
        q1.push(s);
        int step=0;
        while(get_qeuery(pre,q1,q2).size>0){
            while(get_qeuery(pre,q1,q2).size>0){
                Node*t=&chain[get_qeuery(pre,q1,q2).pop()];
                if(final==t->id){
                    return step;
                }
                if_visit[t->id]=1;
                t=t->next;
                while(t!=nullptr){
                    if(!if_visit[t->id]){
                        if_visit[t->id]=1;
                        get_qeuery_to_update(pre,q1,q2).push(t->id);
                    }
                    t=t->next;
                }
            }
            pre++;
            step++;
        }
        return -1;
    }
};
int main(){
    int n;
    scanf("%d",&n);
    Map map=Map(n);
    scanf("%d",&n);
    scanf("%d %d",&s,&t);
    int op;
    int a,b;
    int g=0;
    for(int i=0;i<n;i++){
        scanf("%d %d %d",&op,&a,&b);
        if(op==0){
            map.chain[a].insert(b);
            map.chain[b].insert(a);
        }
        else{
            map.chain[a].erase(b);
            map.chain[b].erase(a);
        }
    }
    map.find_all_min_node();
    for(int i=0;i<100001;i++){
        map.if_visit[i]=false;
    }
    map.dfs_count=0;
    map.dfs(&map.chain[s],g);
    cout<<map.dfs_count<<endl;
    for(int i=0;i<100001;i++){
        map.if_visit[i]=false;
    }
    map.dfs(&map.chain[s],g,1);
    cout<<endl;
    for(int i=0;i<100001;i++){
        map.if_visit[i]=false;
    }
    map.bfs(map.chain[t].id);
    cout<<map.bfs_count<<endl;
    for(int i=0;i<100001;i++){
        map.if_visit[i]=false;
    }
    map.bfs(map.chain[t].id,1);
    cout<<endl;
    for(int i=0;i<100001;i++){
        map.if_visit[i]=false;
    }
    cout<<map.get_min_way_by_bfs(t)<<endl;
}