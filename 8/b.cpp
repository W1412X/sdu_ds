#include<iostream>
using namespace std;
struct Node{
	public:
	int val;
	Node*next;
	Node(int v,Node* n=nullptr){
		val=v;
		next=n;
	}
};
class HashMap{
	public:
	Node** list;
	int*length_set;
	int divisor;
	void init(const int&d){
		divisor=d;
		list=new Node* [divisor];
		length_set=new int[divisor];
		for(int i=0;i<divisor;i++){
			list[i]=nullptr;
			length_set[i]=0;
		}
	}
	~HashMap(){
		delete[] list;
		delete[] length_set;
	}
	void insert(const int&v){
		int pos=v%divisor;
		Node*head=list[pos];
		length_set[pos]++;
		Node*last_node=nullptr;
		if(head==nullptr){
			list[pos]=new Node(v);
			return;
		}
		while(head!=nullptr){
			if(head->val==v){
				cout<<"Existed"<<endl;
				length_set[pos]--;
				return;
			}
			else{
				last_node=head;
				head=head->next;
			}
		}
		last_node->next=new Node(v);
	};
    void retrieve(const int&v){
		int pos=v%divisor;
		Node*tmp=list[pos];
		while(tmp!=nullptr){
			if(tmp->val==v){
				cout<<length_set[pos]<<endl;
				return;
			}
			else{
				tmp=tmp->next;
			}
		}
		cout<<"Not Found"<<endl;
	}
	void erase(const int&v){
		int pos=v%divisor;
		Node*tmp=list[pos];
		Node*last_node=nullptr;
		bool if_find=0;
		while(tmp!=nullptr){
			if(tmp->val==v){
				if_find=1;
				break;
			}
			else{
				last_node=tmp;
				tmp=tmp->next;
			}
		}
		if(if_find){
			length_set[pos]--;
			if(last_node==nullptr){//the first node
				list[pos]=tmp->next;
				delete tmp;
			}
			else{
				last_node->next=tmp->next;
				delete tmp;
			}
			cout<<length_set[pos]<<endl;
		}
		else{
			cout<<"Delete Failed"<<endl;
		}
	}
	void deal(){
		int n,d;
		cin>>d>>n;
		this->init(d);
		int a,b;
		for(int i=0;i<n;i++){
			cin>>a>>b;
			switch(a){
				case 0:this->insert(b);break;
				case 1:this->retrieve(b);break;
				case 2:this->erase(b);break;
			}
		}
	}
};
int main(){
	HashMap().deal();
}