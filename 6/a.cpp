#include<iomanip>
#include<iostream>
using namespace std;
template<class T>
class Stack{
    public:
    T* list=new T[4001];
    int size=0;
    void push(T t){
        list[size]=t;
        size++;
    }
    T&top(){
        return list[size-1];
    }
    void pop(){
        size--;
    }
};
class Solution{
    public:
    Stack<double>number_set;
    Stack<char>mode_set;
    char s[2001];
    int size=0;
    int index=0;
    void in(){
        number_set.size=0;
        mode_set.size=0;
        index=0;
        size=0;
        scanf("%s",s);
        while(s[size]!='\0'){
            size++;
        }
    }
    int to_val(char a){
        int ia;
        switch(a){
            case '+':return 1;
            case '-':return 1;
            case '*':return 2;
            case '/':return 2;
            case '(':return 3;
            case ')':return 3;
            case '\0':return 0;
        }
        return 1412;
    }
    bool compare(char a,char b){
        int ia,ib;
        ia=to_val(a);
        ib=to_val(b);
        return ia>ib;
    }
    double compute_by_mode(char mode,double a,double b){
        switch (mode)
        {
            case '+':
            return a+b;
            case '-':
            return a-b;
            case '*':
            return a*b;
            case '/':
            return a/b;
        }
        return 1412;
    }
    void compute(){
        while(index<size+1){
            if(s[index]==')'){
                while(mode_set.top()!='('){
                    char mode=mode_set.top();
                    double a=number_set.top();
                    number_set.pop();
                    double b=number_set.top();
                    number_set.pop();
                    double c=compute_by_mode(mode,b,a);
                    number_set.push(c); 
                    mode_set.pop();
                }
                mode_set.pop();
            }
            else if(s[index]>='0'&&s[index]<='9'){
                number_set.push(double(s[index]-48));
            }
            else{
                if(mode_set.size==0)
                mode_set.push(s[index]);
                else if(compare(s[index],mode_set.top())||mode_set.top()=='('){//dayu
                    mode_set.push(s[index]);
                }
                else{
                    char mode=mode_set.top();
                    mode_set.pop();
                    double a=number_set.top();
                    number_set.pop();
                    double b=number_set.top();
                    number_set.pop();
                    double c=compute_by_mode(mode,b,a);
                    number_set.push(c);
                    index--;
                }
            }
            index++;
        }
    }
};
int main(){
    int n;
    cin>>n;
    Solution s=Solution();
    for(int i=0;i<n;i++){
        s.in();
        s.compute();
        cout<<fixed<<setprecision(2)<<s.number_set.top()<<endl;;
    }
}