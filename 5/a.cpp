
#include<iostream>
using namespace std;
long int re[300000][4];
long int col_set[700][700];
long int row1[700][4];
long int row_set2[700][700];
long int row_set1[700][700];
long int col_set_size[700];
long int row_set1_size[700];
long int row_set2_size[700];
class SparseMatrix{
    public:
    int col,row;
    int matrix[300000][3];
    int size=0;
    void in();
    void out();
    void add();
    int help_multiply(int i,int u);
    void multiply();
    void transpose();
};
SparseMatrix other;
    void SparseMatrix::in(){
        size=0;
        cin>>row>>col;
        for(int i=1;i<=row;i++){
            for(int u=1;u<=col;u++){
                int t;
                cin>>t;
                if(t!=0){
                    matrix[size][0]=i;
                    matrix[size][1]=u;
                    matrix[size][2]=t;
                    size++;
                }
            }
        }
    }
    void SparseMatrix::transpose(){
        int re_size=0;
        for(int i=0;i<700;i++){
            col_set_size[i]=0;
        }
        for(int i=0;i<size;i++){
            col_set[matrix[i][1]-1][col_set_size[matrix[i][1]-1]]=i;
            col_set_size[matrix[i][1]-1]++;
        }
        for(int i=0;i<col;i++){
            for(int u=0;u<col_set_size[i];u++){
                re[re_size][0]=matrix[col_set[i][u]][0];
                re[re_size][1]=matrix[col_set[i][u]][1];
                re[re_size][2]=matrix[col_set[i][u]][2];
                re_size++;
            }
        }
        for(int i=0;i<re_size;i++){
            int t=re[i][0];
            re[i][0]=re[i][1];
            re[i][1]=t;
        }
        for(int i=0;i<re_size;i++){
            matrix[i][0]=re[i][0];
            matrix[i][1]=re[i][1];
            matrix[i][2]=re[i][2];
        }
        size=re_size;
        int t=col;
        col=row;
        row=t;
    }
    void SparseMatrix::out(){
        cout<<row<<' '<<col<<endl;
        int p=0;
        for(int i=1;i<=row;i++){
            int row1_size=0;
            while(p<size&&matrix[p][0]==i){
                row1[row1_size][0]=matrix[p][0];
                row1[row1_size][1]=matrix[p][1];
                row1[row1_size][2]=matrix[p][2];
                row1_size++;
                p++;
            }
            int p1=0;
            for(int u=1;u<=col;u++){
                if(p1<row1_size&&u==row1[p1][1]){
                    cout<<row1[p1][2]<<' ';
                    p1++;
                }
                else{
                    cout<<0<<' ';
                }
            }
            cout<<endl;
        }
    }
    void SparseMatrix::add(){
        other.size=0;
        cin>>other.row>>other.col;
        int num;
        cin>>num;
        int e,r,t;
        for(int i=0;i<num;i++){
            cin>>e>>r>>t;
            other.matrix[other.size][0]=e;
            other.matrix[other.size][1]=r;
            other.matrix[other.size][2]=t;
            other.size++;
        }
        if(other.row!=row||other.col!=col){
            for(int i=0;i<other.size;i++){
                matrix[i][0]=other.matrix[i][0];
                matrix[i][1]=other.matrix[i][1];
                matrix[i][2]=other.matrix[i][2];
            }
            this->size=other.size;
            this->col=other.col;
            this->row=other.row;
            cout<<-1<<endl;
            return;
        }
        /*add row by row*/
        int re_size=0;
        int p1=0;
        int p2=0;
        while(p1<size&&p2<other.size){
            if(col*matrix[p1][0]+matrix[p1][1]<col*other.matrix[p2][0]+other.matrix[p2][1]){
                re[re_size][0]=matrix[p1][0];
                re[re_size][1]=matrix[p1][1];
                re[re_size][2]=matrix[p1][2];
                re_size++;
                p1++;
            }
            else if(col*matrix[p1][0]+matrix[p1][1]>col*other.matrix[p2][0]+other.matrix[p2][1]){
                re[re_size][0]=other.matrix[p2][0];
                re[re_size][1]=other.matrix[p2][1];
                re[re_size][2]=other.matrix[p2][2];
                re_size++;
                p2++;
            }
            else{
                matrix[p1][2]+=other.matrix[p2][2];
                re[re_size][0]=matrix[p1][0];
                re[re_size][1]=matrix[p1][1];
                re[re_size][2]=matrix[p1][2];
                re_size++;
                p1++;
                p2++;
            }
        }
        while(p1<size){
            re[re_size][0]=matrix[p1][0];
            re[re_size][1]=matrix[p1][1];
            re[re_size][2]=matrix[p1][2];
            re_size++;
            p1++;
        }
        while(p2<other.size){
            re[re_size][0]=other.matrix[p2][0];
            re[re_size][1]=other.matrix[p2][1];
            re[re_size][2]=other.matrix[p2][2];
            re_size++;
            p2++;
        }
        for(int i=0;i<re_size;i++){
            matrix[i][0]=re[i][0];
            matrix[i][1]=re[i][1];
            matrix[i][2]=re[i][2];
        }
        size=re_size;
    }
    int SparseMatrix::help_multiply(int i,int u){
        int u1=0,u2=0;
        int ans=0; 
        while(u1<row_set1_size[i]&&u2<row_set2_size[u]){
            if(matrix[row_set1[i][u1]][1]==other.matrix[row_set2[u][u2]][1]){
                ans+=matrix[row_set1[i][u1]][2]*other.matrix[row_set2[u][u2]][2];
                u1++;
                u2++;
            }
            else{
                if(matrix[row_set1[i][u1]][1]<other.matrix[row_set2[u][u2]][1]){
                    u1++;
                }
                else{
                    u2++;
                }
            }
        }
        return ans;
    }
    void SparseMatrix::multiply(){
        other.size=0;
        int re_size=0;
        cin>>other.row>>other.col;
        int num;
        cin>>num;
        int e,r,t;
        for(int i=0;i<num;i++){
            cin>>e>>r>>t;
            other.matrix[other.size][0]=e;
            other.matrix[other.size][1]=r;
            other.matrix[other.size][2]=t;
            other.size++;
        }
        if(other.row!=col){
            for(int i=0;i<other.size;i++){
                matrix[i][0]=other.matrix[i][0];
                matrix[i][1]=other.matrix[i][1];
                matrix[i][2]=other.matrix[i][2];
            }
            this->size=other.size;
            this->col=other.col;
            this->row=other.row;
            cout<<-1<<endl;
            return;
        }
        other.transpose();
        for(int i=0;i<700;i++){
            row_set1_size[i]=0;
            row_set2_size[i]=0;
        }
        for(int i=0;i<size;i++){
            row_set1[matrix[i][0]-1][row_set1_size[matrix[i][0]-1]]=i;
            row_set1_size[matrix[i][0]-1]++;
        }
        for(int i=0;i<other.size;i++){
            row_set2[other.matrix[i][0]-1][row_set2_size[other.matrix[i][0]-1]]=i;
            row_set2_size[other.matrix[i][0]-1]++;
        }
        for(int i=0;i<row;i++){
            for(int u=0;u<other.row;u++){
                int g=help_multiply(i,u);
                if(g!=0){
                    re[re_size][0]=i+1;
                    re[re_size][1]=u+1;
                    re[re_size][2]=g;
                    re_size++;
                }
            }
        }
        for(int i=0;i<re_size;i++){
            matrix[i][0]=re[i][0];
            matrix[i][1]=re[i][1];
            matrix[i][2]=re[i][2];
        }
        size=re_size;
        col=other.row;
    }
int main(){
    SparseMatrix s;
    int w;
    cin>>w;
    int i=0;
    int c;
    while(i<w){
        i++;
        cin>>c;
        switch(c){
            case 1:
            s.in();
            break;
            case 2:
            s.multiply();
            break;
            case 3:
            s.add();
            break;
            case 4:
            s.out();
            break;
            case 5:
            s.transpose();
        }
    }
}