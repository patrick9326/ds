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
    // ��l�ư}�C�e�q
    DynamicArray(int init_capacity = 2) : size(0), capacity(init_capacity) {
        arr = new int[capacity];
    }

    //����O����
    ~DynamicArray() {
        delete[] arr;
    }

    // �K�[�������
    void add(int value) {
        if (size == capacity) {
            resize(capacity * 2); // �e�q�[��
        }
        arr[size++] = value;
    }

    // ��X��e�}�C���e�θ�T
    void print() const {
        cout << "��e�}�C�j�p: " << size << '\n';
        cout << "�}�C�e�q: " << capacity << '\n';
        cout << "�}�C����: ";
        for (int i = 0; i < size; i++) cout << arr[i] << " ";
        cout << '\n' << "-----------------------" << '\n';
    }
};

int main() {
    DynamicArray dynamicArr;
    int input;

    cout << "�п�J�Ʀr�[�J�}�C (��J -1 ����): " << endl;
    while (true) {
        cout << "��J�Ʀr: ";
        cin >> input;

        if (input == -1) break; // ��������
        dynamicArr.add(input);
        dynamicArr.print();
    }

    cout << "�����{���C" << endl;
    return 0;
}