#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200010, M = 500010;
int p[N];
// 快速排序算法
struct Edge {
    int a, b, w;
    bool operator<(const Edge &W) const {
        return w < W.w;
    }
};
// 快速排序算法
void quickSort(Edge* arr, int start, int end) {
    if (start >= end) {
        return;
    }
    
    int pivot = arr[start].w; // 以第一个元素为基准
    int i = start + 1;      // 左指针
    int j = end;            // 右指针
    
    while (i <= j) {
        if (arr[i].w > pivot && arr[j].w < pivot) {
            // 如果左指针指向的元素大于基准，右指针指向的元素小于基准
            // 则交换这两个元素的位置
            swap(arr[i], arr[j]);
        }
        
        if (arr[i].w <= pivot) {
            i++; // 左指针右移
        }
        
        if (arr[j].w >= pivot) {
            j--; // 右指针左移
        }
    }
    
    swap(arr[start], arr[j]); // 将基准元素放到正确的位置上
    
    // 递归调用，对基准元素左右两侧的子序列进行排序
    quickSort(arr, start, j - 1);
    quickSort(arr, j + 1, end);
}

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}//找到并查集的祖宗，并且进行路径压缩优化
class Graph {
public:
    Graph(int num, int point) {
        edges = new Edge[num];
        this->num = num;
        this->point = point;
    }

    long long kruskal();

    void set(int a, int b, int w, int i) {
        edges[i] = {a, b, w};
    }

private:
    int n;
    int num;
    int point;
    struct Edge *edges;
};
long long Graph::kruskal() {
    quickSort(edges,0,num-1);

    for (int i = 1; i <= point; i++) p[i] = i;    // 初始化并查集

    long long res = 0;
    for (int i = 0; i < num; i++) {
        int a = edges[i].a,
                b = edges[i].b,
                w = edges[i].w;
        a = find(a), b = find(b);
        if (a != b) {
            p[a] = b;
            res += w;
        }
    }
    return res;
}
int main() {
    int n, m;
    cin >> n >> m;
    Graph g(m, n);

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        g.set(a, b, w, i);
    }

    cout << g.kruskal() << endl;


    return 0;
}