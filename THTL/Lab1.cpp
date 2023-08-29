//
// Created by ddanh on 29#

#include <bits/stdc++.h>

using namespace std;

void inputArr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Nhap a[" << i << "] = ";
        cin >> arr[i];
    }
}

void printArr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = " << arr[i] << endl;
    }
}

int findElement1(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
}

int findElement2(const int a[], int n, int x) {
    int middle;
    int left = 0;
    int right = n - 1;
    do {
        middle = (left + right) / 2;
        if (x == a[middle]) break;
        else if (x < a[middle]) right = middle - 1;
        else left = middle + 1;
    } while (left <= right);
    if (left <= right) return middle;
    else return -1;
}

void swap(int &a, int &b){
    int temp =0;
    temp = a;
    a = b;
    b= temp;

}

void QuickSort(int a[], int L, int R) {
    int i, j, x;
    x = a[(L + R) / 2];
    i = L;
    j = R;
    do {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++, j--;
        }
    } while (i < j);
    if (L < j) QuickSort(a, L, j);
    if (i < R) QuickSort(a, i, R);
}

void BubbleSort(int a[], int n) {
    printArr(a, n);
    int temp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (a[j] < a[j - 1]) {
                temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }

        }
    }
}

void SelectionSort(int a[], int n) {
    int min, i, j, tg;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (a[j] < a[min]) min = j;
        if (min != i) {
            tg = a[min];
            a[min] = a[i];
            a[i] = tg;
        }
    }
}

int main() {
    int n;
    const int MAX_SIZE = 100;
    int a[MAX_SIZE];
    cout << "Nhap gia so phan tu cua mang: ";
    cin >> n;
    inputArr(a, n);
    printArr(a, n);
    cout << endl;
    QuickSort(a, 0,n-1);
    cout << endl;
    printArr(a, n);
}
