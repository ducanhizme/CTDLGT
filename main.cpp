#include <bits/stdc++.h>

float Sum(float a[],int n);

using namespace std;
float SUM(float a[] , int n){
    if(n ==0 ) return 0;
    return a[n-1] + Sum(a,n);
}

int Partition(SinhVien list[], int low, int high) {
    double pivot = list[high].DTB;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (list[j].DTB < pivot) {
            i++;
            swap(list[i], list[j]);
        }
    }
    swap(list[i + 1], list[high]);
    return i + 1;
}

void QuickSort(SinhVien list[], int low, int high) {
    if (low < high) {
        int pi = Partition(list, low, high);
        QuickSort(list, low, pi - 1);
        QuickSort(list, pi + 1, high);
    }
}

void InterchangeSort(SinhVien list[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (list[i].DTB > list[j].DTB) {
                swap(list[i], list[j]);
            }
        }
    }
}
int main() {
    float a []= {1,2,3,4,5,6,7,8};
    cout << SUM(a,8);
}

//nhập mảng nguyên n phần tử
 // hiện mảng đã nhâp ra màn hình
 // tìm kiếm tuyến tính tìm kiếm nhị phân
 // sắp xếp quick sort buble sort selection sort
 // hiện danh sách sau khi sắp

