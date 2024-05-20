#include<iostream>
using namespace std;
template<typename T>
class Sorter {
private:
    T* data;
    int size;
public:
    Sorter(int n) : size(n) {
        data = new T[n];
    }
    ~Sorter() {
        delete[] data;
    }
    void read_data() {
        for (int i = 0; i < size; ++i) {
            std::cin >> data[i];
        }
    }
    void print_data() {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    void rank_sort() {
        T* sorted_data = new T[size];
        for(int i=0;i<size;i++){
            sorted_data[i]=-1412;
        }
        int* ranks = new int[size];
        for (int i = 0; i < size; ++i) {
            ranks[i] = 0;
            for (int j = 0; j < size; ++j) {

                if (data[j]<data[i]) {
                    ranks[i]++;
                }
            }
        }
        for (int i = 0; i < size; ++i) {
            sorted_data[ranks[i]] = data[i];
        }
        for(int i=0;i<size;i++){
            if(sorted_data[i]==-1412){
                sorted_data[i]=sorted_data[i-1];
            }
        }
        delete[] ranks;
        for(int i=0;i<size;i++){
            data[i]=sorted_data[i];
        }
        delete[] sorted_data;
    }
    void selection_sort() {
        for (int i = 0; i < size - 1; ++i) {
            int min_index = i;
            for (int j = i + 1; j < size; ++j) {
                if (data[j] < data[min_index]) {
                    min_index = j;
                }
            }
            if (min_index != i) {
                T temp = data[i];
                data[i] = data[min_index];
                data[min_index] = temp;
            }
        }
    }
    void bubble_sort() {
        bool swapped;
        for (int i = 0; i < size - 1; ++i) {
            swapped = false;
            for (int j = 0; j < size - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
    }
    void insertion_sort() {
        for (int i = 1; i < size; ++i) {
            T key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
           data[j + 1] = key;
        }
    }
};
int main() {
    int n;
    cin>>n;
    Sorter<int> sorter(n);
    sorter.read_data();
    sorter.rank_sort();
    sorter.print_data();
    return 0;
}