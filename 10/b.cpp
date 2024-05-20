#include<iostream>
using namespace std;
struct Node{
    int val;
    char c;
    Node*left;
    Node*right;
};
class BigRootPile{
    public:
    Node* list[100000];
    int size=0;
    Node* top(){
        return list[1];
    }
    void push(Node* a){
        list[size+1]=a;
        int pos=(size+1);
        size++;
        while(pos!=1&&a->val<list[pos/2]->val){
            Node* tmp=list[pos];
            list[pos]=list[pos/2];
            list[pos/2]=tmp;
            pos/=2;
        }
    }
    Node* pop(){
        Node* re=list[1];
        Node* val=list[size];
        size--;
        list[1]=val;
        int pos=2;
        while(pos<=size){
            if(pos<size&&list[pos]->val >list[pos+1]->val){
                pos++;
            }
            if(list[pos]->val<val->val){
                list[pos/2]=list[pos];
                list[pos]=val;
                pos*=2;
            }
            else{
                break;
            }
        }
        return re;
    }
};
struct Str{
    char s[100];
    int len=0;
    void push(char c){
        s[len]=c;
        len++;
    }
    void pop(){len--;}
    void out(){cout<<s<<endl;}
};
struct StrLong{
    char s[1000000];
    int len=0;
    void push(char c){
        s[len]=c;
        len++;
    }
    void push(char*s1){
        char t=s1[0];
        int i=1;
        while(t!='\0'){
            s[len]=t;
            len++;
            t=s1[i];
            i++;
        }
    }
    void pop(){len--;}
    void out(){cout<<s<<endl;}
};
Str letter_dict[26];
void dfs(Node*node,Str s){
    if(node->left==nullptr&&node->right==nullptr){
        letter_dict[node->c-97]=s;
        return;
    }
    if(node->left!=nullptr){
        s.push('0');
        dfs(node->left,s);
    }
    s.pop();
    if(node->right!=nullptr){
        s.push('1');
        dfs(node->right,s);
    }
}
int main(){
    BigRootPile brp=BigRootPile();
    char s[1000000];
    cin>>s;
    int letter_prev[26];
    char c=s[0];
    int i=1;
    while(c!='\0'){
        letter_prev[c-97]++;
        c=s[i];
        i++;
    }
    for(int i=0;i<26;i++){
        if(letter_prev[i]==0)continue;
        Node*tmp=new Node();
        tmp->c=97+i;
        tmp->val=letter_prev[i];
        brp.push(tmp);
    }
    while(brp.size!=1){
        Node*a;Node*b;
        Node*new_node=new Node();
        new_node->c=' ';
        a=brp.pop();
        b=brp.pop();
        new_node->left=a;
        new_node->right=b;
        new_node->val=a->val+b->val;
        brp.push(new_node);
    }
    Node* hoffmann_root=brp.pop();
    Str s1;
    dfs(hoffmann_root,s1);
    StrLong re;
    i=1;
    c=s[0];
    while(c!='\0'){
        re.push(letter_dict[c-97].s);
        c=s[i];
        i++;
    }
    cout<<re.len;
}