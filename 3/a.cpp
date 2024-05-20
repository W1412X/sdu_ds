#include<iostream>
using namespace std;
int ans[20000];
int ans_size=0;
bool compare(char*n1,char*n2){
    int i=0;
    while(1){
        if(n1[i]==n2[i]&&n1[i]!='\0'){
            i++;
            continue;
        }
        else if(n1[i]==n2[i]&&n1[i]=='\0'){
            return 1;
        }
        else{
            return 0;
        }
    }
}
void convey_char(char*a,char*b){
    int i=0;
    while(b[i]!='\0'){
        a[i]=b[i];
        i++;
    }
    a[i]='\0';
}
int char_to_int(const char*a){
    int i=0;
    int re=0;
    while(a[i]!='\0'){
        re=re*10+a[i]-48;
        i++;
    }
    return re;
}
struct man{
    char name[20];
    char telephone[12];
    char clas[10];
    int apartment;
    man(){};
    man(char*n,char*t,char*c,int a) {
        convey_char(name,n);
        convey_char(telephone,t);
        convey_char(clas,c);
        apartment=a;
    }
};
class myvector{
    private:
    man*list;//save the list
    int size;
    int volum;//the real capcity
    public:
    myvector(){
        list=nullptr;
        size=0;
        volum=0;
    }
    myvector(int n,man t){
        list=new man[n];
        size=n;
        volum=n;
        for(int i=0;i<n;i++){
            list[i]=t;
        }
    }
    man& operator[](int index)const{
        if(index>=size){
            throw "index out range";
        }
        return list[index];
    }
    myvector(const myvector&other){
        size=other.size;
        volum=other.volum;
        list=new man[volum];
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
            man* list1=new man[volum];
            for(int i=0;i<size;i++){
                list1[i]=other[i];
            }
            delete[] list;
            list=nullptr;
            list=list1;
            return *this;
        }
    }
    void expand(const int new_volum){
        if(new_volum==0){
            volum=1;//update the volum
            list=new man[1];
            return;
        }
        man* list1=new man[new_volum];
        for(int i=0;i<size;i++){
            list1[i]=list[i];
        }
        delete[] list;
        list=list1;
        volum=new_volum;
    }
    void push_back(const man&t){
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
    int find(char*n){
        for(int i=0;i<size;i++){
            if(compare(list[i].name,n)){
                return 1;
            }
            else continue;
        }
        return 0;
    }
    void erase(char*n){
        int p=-1;//record the position
        for(int i=0;i<size;i++){
            if(compare(list[i].name,n)){
                p=i;
                break;
            }
        }
        volum--;
        size--;
        man* list1=new man[volum];
        for(int i=0,u=0;i<size+1;i++,u++){
            if(i==p){
                u--;
                continue;
            }
            list1[u]=list[i];
        }
        delete[] list;
        list=list1;
    }
    void edit(char*name,int mode,char*content){
        int p=-1;
        for(int i=0;i<size;i++){
            if(compare(name,list[i].name)){
                p=i;
                break;
            }
        }
        if(mode==1){
            convey_char(list[p].telephone,content);
        }
        else if(mode==2){
            convey_char(list[p].clas,content);
        }
        else{
            list[p].apartment=char_to_int(content);
        }
    }
    void output(int clas){
        int re=0;
        for(int i=0;i<size;i++){
            if(char_to_int(list[i].clas)==clas)
            re=re^list[i].apartment;
        }
        ans[ans_size]=re;
        ans_size++;
    }
};
void get_command(myvector&a){
    char name[20];
    char telephone[12];
    char clas[10];
    int apartment;
    int mode;
    scanf("%d",&mode);
    if(mode==0){
        scanf("%s",name);
        scanf("%s",telephone);
        scanf("%s",clas);
        scanf("%d",&apartment);
        a.push_back(man(name,telephone,clas,apartment));
    }
    else if(mode==1){
        scanf("%s",name);
        a.erase(name);
    }
    else if(mode==2){
        int mode;
        char content[20];
        scanf("%s",name);
        scanf("%d",&mode);
        scanf("%s",content);
        a.edit(name,mode,content);
    }
    else if(mode==3){
        scanf("%s",name);
        ans[ans_size]=a.find(name);
        ans_size++;
    }
    else if(mode==4){
        int clas;
        scanf("%d",&clas);
        a.output(clas);
    }
}
int main(){
    myvector a;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        get_command(a);
        getchar();
    }
    for(int i=0;i<ans_size;i++){
        cout<<ans[i]<<endl;
    }
}
