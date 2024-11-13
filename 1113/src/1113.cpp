#include <iostream>
#include <string>
using namespace std;

template<typename T>
int binarySearch(T arr[], int n, const T& target) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    char type;
    int n, q;

    while (cin >> type >> n >> q) {
        if (type == 'i') { 
            int* arr = new int[n];  

            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            for (int i = 0; i < q; i++) {
                int target;
                cin >> target;
                cout << binarySearch(arr, n, target) << endl;
            }

            delete[] arr;  
        }
        else if (type == 's') {  
            string* arr = new string[n];  

            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }

            for (int i = 0; i < q; i++) {
                string target;
                cin >> target;
                cout << binarySearch(arr, n, target) << endl;
            }

            delete[] arr; 
        }
    }

    return 0;
}