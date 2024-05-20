#include<iostream>
using namespace std;
class HashTable{
    public:
    bool* if_empty;
    int* val;
    int dividor=10;//the default 
    void init(){
        cin>>dividor;
        if_empty=new bool[dividor];
        val=new int[dividor];
        dividor=dividor;
        for(int i=0;i<dividor;i++){
            if_empty[i]=1;
        }
    }
    void insert(int v){
        int pos=v%dividor;
        if(if_empty[pos]){//if the position need to insert is empty,then insert it directly
            if_empty[pos]=false;
            val[pos]=v;
            cout<<(pos%dividor)<<endl;
            return;
        }
        if(val[pos]==v&&!if_empty[pos%dividor]){
            cout<<"Existed"<<endl;
            return;
        }
        do{
            pos++;
            if(val[pos%dividor]==v&&!if_empty[pos%dividor]){
                cout<<"Existed"<<endl;
                return;
            }
            if(if_empty[pos%dividor]){
                if_empty[pos%dividor]=false;
                val[pos%dividor]=v;
                cout<<(pos%dividor)<<endl;
                return;
            }
        }while(1);
    }
    int retrieve(int v,bool if_out=1){
        int pos=v%dividor;
        int start_pos=pos;
        if(if_empty[pos]){
            if(if_out)
            cout<<-1<<endl;
            return -1;
        }
        do{
            if(val[pos%dividor]==v&&!if_empty[pos%dividor]){
                if(if_out)
                cout<<pos%dividor<<endl;
                return pos%dividor;
            }
            pos++;
        }while(pos%dividor!=start_pos&&!if_empty[pos%dividor]);
        if(if_out)
        cout<<-1<<endl;
        return -1;
    }
    void erase(int v){
        int pos=retrieve(v,0);
        if(pos==-1){
            cout<<"Not Found"<<endl;
            return;
        }
        int start_pos=pos;
        if_empty[pos]=true;
        int move_num=0;//the element need to be move
        int empty_pos=pos;
        int key_pos;
        if(val[pos]==v)
        do{
            pos++;
            empty_pos=empty_pos%dividor;
            pos=pos%dividor;
            key_pos=val[pos]%dividor;
            if(if_empty[pos%dividor]){
                break;
            }
            if((empty_pos>=key_pos&&pos>empty_pos)||(key_pos>pos&&(empty_pos>=key_pos||empty_pos<pos))){
                val[empty_pos]=val[pos];
                if_empty[empty_pos]=false;
                if_empty[pos]=true;
                empty_pos=pos;
                move_num++;
            }
        }while(!if_empty[(pos+1)%dividor]&&((pos+1)%dividor)!=start_pos);
        cout<<move_num<<endl;
    }
};
int main(){
    HashTable ht=HashTable();
    ht.init();
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        switch(a){
            case 0:ht.insert(b);break;
            case 1:ht.retrieve(b);break;
            case 2:ht.erase(b);break;
        }
    }
}