#include <iostream>
#include <algorithm>

using namespace std;

class DynamicArray {
private:
    int* arr;
    int size;
    int capacity;

    void resize(int new_capacity) {
        int* new_arr = new int[new_capacity];
        copy(arr, arr + size, new_arr);
        delete[] arr;
        arr = new_arr;
        capacity = new_capacity;
    }

public:
    // 初始化陣列容量
    DynamicArray(int init_capacity = 2) : size(0), capacity(init_capacity) {
        arr = new int[capacity];
    }

    //釋放記憶體
    ~DynamicArray() {
        delete[] arr;
    }

    // 添加元素函數
    void add(int value) {
        if (size == capacity) {
            resize(capacity * 2); // 容量加倍
        }
        arr[size++] = value;
    }

    // 輸出當前陣列內容及資訊
    void print() const {
        cout << "當前陣列大小: " << size << '\n';
        cout << "陣列容量: " << capacity << '\n';
        cout << "陣列元素: ";
        for (int i = 0; i < size; i++) cout << arr[i] << " ";
        cout << '\n' << "-----------------------" << '\n';
    }
};

int main() {
    DynamicArray dynamicArr;
    int input;

    cout << "請輸入數字加入陣列 (輸入 -1 結束): " << endl;
    while (true) {
        cout << "輸入數字: ";
        cin >> input;

        if (input == -1) break; // 結束條件
        dynamicArr.add(input);
        dynamicArr.print();
    }

    cout << "結束程式。" << endl;
    return 0;
}