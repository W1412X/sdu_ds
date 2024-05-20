#include <iostream>
using namespace std;
template<class T>
struct Node
{
    Node<T> *left;
    Node<T> *right;
    T key;
    int order;
    Node(){};
    Node(T k)
    {
        key = k;
        left = NULL;
        right = NULL;
        order = 0;
    }
    Node(Node<T> *node)
    {
        node->right = this->right;
        node->left = this->left;
        node->key = this->key;
        node->order = this->order;
    }
    Node(const T &k, Node<T>*l, Node<T>*r, int lsize)
    {
        key = k;
        left = l;
        right = r;
        order = lsize;
    }
};
template<class T>
class SearchTree
{
public:
    SearchTree()
    {
        root = NULL;
        node_num = 0;
    };
    int insert(T k)
    {
        Node<T>*tmp = root;
        Node<T>*parent = NULL;
        int ans = 0;
        while (tmp != NULL)
        {
            if (k < tmp->key)
            {
                ans ^= tmp->key;
                parent = tmp;
                tmp = tmp->left;
            }
            else if (k > tmp->key)
            {
                ans ^= tmp->key;
                parent = tmp;
                tmp = tmp->right;
            }
            else if (k == tmp->key)
            {
                return 0;
            }
        }
        Node<T>*newNode = new Node<T>(k);
        if (parent != NULL)
        {
            if (parent->key > k)
                parent->left = newNode;
            else
                parent->right = newNode;
        }
        else
        {
            root = newNode;
        }
        node_num++;
        tmp = root;
        while (tmp->key != k)
        {
            if (tmp->key < k)
            {
                tmp = tmp->right;
            }
            else if (tmp->key > k)
            {
                tmp->order++;
                tmp = tmp->left;
            }
        }
        return ans;
    };

    int erase(T k)
    {
        Node<T>*tmp = root;
        Node<T>*parent = NULL;
        int ans = 0;
        while (tmp != NULL && tmp->key != k)
        {
            ans ^= tmp->key;
            parent = tmp;
            if (tmp->key < k)
            {
                tmp = tmp->right;
            }
            else if (tmp->key > k)
            {
                tmp = tmp->left;
            }
        }
        if (tmp == NULL)
        {
            return 0;
        }
        ans ^= tmp->key;
        tmp = root;
        while (tmp != NULL && tmp->key != k)
        {
            if (tmp->key < k)
            {
                tmp = tmp->right;
            }
            else if (tmp->key > k)
            {
                tmp->order--;
                tmp = tmp->left;
            }
        }
        if (tmp->left != NULL && tmp->right != NULL)
        {
            Node<T>*r_min_node = tmp->right;
            Node<T>*s = tmp;
            while (r_min_node->left != NULL)
            {
                r_min_node->order--;
                s = r_min_node;
                r_min_node = r_min_node->left;
            }
            Node<T>*newNode = new Node<T>(r_min_node->key, tmp->left, tmp->right,
                                               tmp->order);
            if (parent == NULL)
                root = newNode;
            else if (tmp == parent->left)
                parent->left = newNode;
            else
                parent->right = newNode;

            if (s == tmp)
                parent = newNode;
            else
                parent = s;
            delete tmp;
            tmp = r_min_node;
        }
        Node<T>*c=nullptr;
        if (tmp->left != NULL)
            c = tmp->left;
        else
            c = tmp->right;
        if (tmp == root)
            root = c;
        else
        {
            if (tmp == parent->left)
                parent->left = c;
            else
                parent->right = c;
        }
        node_num--;
        return ans;
    };
    int erase_by_order(int order)
    {
        Node<T>*tmp = root;
        Node<T>*parent = NULL;
        int ans = 0;
        while (tmp != NULL && tmp->order != order)
        {
            ans ^= tmp->key;
            parent = tmp;
            if (tmp->order > order)
            {
                tmp = tmp->left;
            }
            else if (tmp->order < order)
            {
                order = order - tmp->order - 1;
                tmp = tmp->right;
            }
        }
        if (tmp == NULL)
            return 0;
        ans ^= tmp->key;
        int k = tmp->key;
        tmp = root;
        while (tmp != NULL && tmp->key != k)
        {
            if (tmp->key < k)
            {
                tmp = tmp->right;
            }
            else if (tmp->key > k)
            {
                tmp->order--;
                tmp = tmp->left;
            }
        }
        if (tmp->left != NULL && tmp->right != NULL)
        {
            Node<T>*r_min_node = tmp->right;
            Node<T>*s = tmp;
            while (r_min_node->left != NULL)
            {
                r_min_node->order--;
                s = r_min_node;
                r_min_node = r_min_node->left;
            }

            Node<T>*newNode = new Node<T>(r_min_node->key, tmp->left, tmp->right, tmp->order);
            if (parent == NULL)
                root = newNode;
            else if (tmp == parent->left)
                parent->left = newNode;
            else
                parent->right = newNode;

            if (s == tmp)
                parent = newNode;
            else
                parent = s;

            delete tmp;
            tmp = r_min_node;
        }
        Node<T>*c;
        if (tmp->left != NULL)
            c = tmp->left;
        else
            c = tmp->right;

        if (tmp == root)
            root = c;
        else
        {
            if (tmp == parent->left)
                parent->left = c;
            else
                parent->right = c;
        }
        node_num--;
        delete tmp;
        return ans;
    };

    int search(T k)
    {
        Node<T>*tmp = root;
        int ans = 0;
        while (tmp != NULL && tmp->key != k)
        {
            ans ^= tmp->key;
            if (tmp->key > k)
            {
                tmp = tmp->left;
            }
            else if (tmp->key < k)

            {
                tmp = tmp->right;
            }
        }
        if (tmp == NULL)
            return 0;
        else
        {
            ans ^= tmp->key;
            return ans;
        }
    };

    int search_by_order(int order)
    {
        Node<T>*tmp = root;
        int ans = 0;
        while (tmp != NULL && tmp->order != order)
        {
            ans ^= tmp->key;
            if (tmp->order > order)
            {
                tmp = tmp->left;
            }
            else if (tmp->order < order)
            {
                order = order - tmp->order - 1;
                tmp = tmp->right;
            }
        }
        if (tmp == NULL)
            return 0;
        else
        {
            ans ^= tmp->key;
            return ans;
        }
    };
    int node_num;
    Node<T>*root;
};
int main()
{
    int n;
    scanf("%d",&n);
    SearchTree<int> st;
    int a, b;
    for(long long int i=0;i<n;i++){
        scanf("%d %d",&a,&b);
        switch (a)
        {
        case 0:
            cout << st.insert(b) << endl;
            break;
        case 1:
            cout << st.search(b) << endl;
            break;
        case 2:
            cout << st.erase(b) << endl;
            break;
        case 3:
            b--;
            cout << st.search_by_order(b) << endl;
            break;
        case 4:
            b--;
            cout << st.erase_by_order(b) << endl;
            break;
        }
    }
    return 0;
}