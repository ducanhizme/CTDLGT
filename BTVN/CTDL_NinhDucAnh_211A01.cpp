//
// Created by ddanh on 28/08/2023.
//

#include <iostream>
#include <cstring>
#include <iomanip>
#include<stdio.h>

#define READ 1
#define WRITE 0


using namespace std;
struct SinhVien {
    string MaSV;
    string TenSV;
    double DTB = 0;
};

void swap(SinhVien &sv1, SinhVien &sv2) {
    SinhVien temp;
    temp = sv1;
    sv1 = sv2;
    sv2 = temp;
}

void inputStudent(SinhVien &sv) {
    cout << "Nhap ma SV: ";
    cin >> sv.MaSV;
    cout << "Nhap ten SV: ";
    cin.ignore();
    getline(cin, sv.TenSV);
    cout << "Nhap DTB: ";
    cin >> sv.DTB;
}

void inputStudents(SinhVien list[], int length) {
    for (int i = 0; i < length; i++) {
        cout << "\nNhap thong tin cho sinh vien " << i + 1 << ":" << endl;
        inputStudent(list[i]);
    }
}

void printStudents(const SinhVien list[], int length) {
    cout << setw(15) << left << "Ma SV"
         << setw(30) << left << "Ten SV"
         << setw(10) << right << "DTB"
         << endl;

    cout << setfill('-') << setw(60) << "-" << endl;
    cout << setfill(' ');
    for (int i = 0; i < length; i++) {
        cout << setw(15) << left << list[i].MaSV
             << setw(30) << left << list[i].TenSV
             << setw(10) << right << fixed << setprecision(2) << list[i].DTB
             << endl;
    }
}

void printStudent(const SinhVien &sv) {
    cout << "Ma SV: " << sv.MaSV << endl;
    cout << "Ten SV: " << sv.TenSV << endl;
    cout << "DTB: " << sv.DTB << endl;
}


int findStudentByID(const SinhVien list[], int length, const string &id, bool print) {
    bool isExisted = false;
    int position = -1;
    for (int i = 0; i < length; i++) {
        if (list[i].MaSV == id) {
            if (!print) {
                cout << "Thong tin sinh vien co ID " << id << ":" << endl;
                printStudent(list[i]);
                isExisted = true;
                position = i;
            }
        }
    }
    if (!isExisted && !print) {
        cout << "Khong tim thay sinh vien co ten " << id << " trong danh sach." << endl;
    }
    return position;
}

void InsertionSort(SinhVien list[], int n) {
    int position;
    SinhVien x;
    for (int i = 1; i < n; i++) {
        x = list[i];
        position = i - 1;
        while ((position >= 0) && (list[position].DTB > x.DTB)) {
            list[position + 1] = list[position];
            position--;
        }
        list[position + 1] = x;
    }
}

void SelectionSort(SinhVien list[], int n) {
    int min, i, j;
    SinhVien temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j].DTB < list[min].DTB)
                min = j;
        if (min != i)
            swap(list[min], list[i]);
    }
}

void BubbleSort(SinhVien list[], int n) {
    SinhVien temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (list[j].DTB > list[j + 1].DTB) {
                swap(list[i], list[i + 1]);
            }
        }
    }
}


void QuickSort(SinhVien a[], int L, int R) {
    int i, j;
    SinhVien x;
    x = a[(L + R) / 2];
    i = L;
    j = R;
    do {
        while (a[i].DTB < x.DTB) i++;
        while (a[j].DTB > x.DTB) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++, j--;
        }
    } while (i < j);
    if (L < j) QuickSort(a, L, j);
    if (i < R) QuickSort(a, i, R);
}


void deleteStudentByID(SinhVien list[], int &length, const string &id) {
    int position = findStudentByID(list, length, id, false);
    if (position != -1) {
        for (int i = position; i < length - 1; i++) {
            list[i] = list[i + 1];
        }
        length--;
        cout << "Da xoa sinh vien co ma " << id << " ra khoi danh sach." << endl;
    } else {
        cout << "Khong tim thay sinh vien co ma " << id << " trong danh sach." << endl;
    }
}

void writeStudentsToFile(SinhVien list[], int n) {
//    char fileName[20];
//    cout<<"Input file name to save product: ";
//    cin>>fileName;
//    FILE *f;
//    f = fopen(fileName,"wb");
//    for (int i = 0; i < n; i++) {
//        fwrite(&list[i], sizeof(SinhVien), 1, f);
//    }
//    fclose(f);
//    cout << "Complete" << endl;
}

void writeStudentsExcellent(SinhVien list[], int n) {

    fwrite(&n, sizeof(int), 1, f);
    for (int i = 0; i < n; i++) {
        if (list[i].DTB >= 8) {

        }
    }
}

FILE *openFile(int action) {
    // action = 1 -> READ
    // action = 0  -> WRITE
    char fileName[20];
    cout << "Input file name to save product: ";
    cin >> fileName;
    FILE *f;
    f = action == 1 ? fopen(fileName, "wb") : fopen(fileName, "rb");
    return f;
}

void saveExcellentStudentsToFile(SinhVien list[] ,int n){
    FILE *f = openFile(WRITE);
    fwrite(&n, sizeof(int),1,f);
    for (int i = 0; i < n; i++) {
        if (list[i].DTB >= 8) {
            fwrite(&list[i], sizeof(SinhVien),1,f);
        }
    }
    fclose(f);
    cout <<"Saved";
}

void saveStudentsToFile(SinhVien list[] ,int n){
    FILE *f = openFile(WRITE);
    fwrite(&n, sizeof(int),1,f);
    for (int i = 0; i < n; i++)
        fwrite(&list[i], sizeof(SinhVien),1,f);
    fclose(f);
    cout <<"Saved";
}

void getStudentsFromFile(SinhVien list[] , int n){
    FILE *f = openFile(READ);
    fread(&n,sizeof (int),1,f);
    for(int i =0 ; i < n ; i++){
        fread(&list[i], sizeof(SinhVien),1,f);
    }
}


void printMenu() {
    cout << "============================" << endl;
    cout << "MENU" << endl;
    cout << "1. Nhap danh sach sinh vien" << endl;
    cout << "2. Hien thi danh sach sinh vien" << endl;
    cout << "3. Sap xep danh sach theo DTB (InsertionSort)" << endl;
    cout << "4. Sap xep danh sach theo DTB (SelectionSort)" << endl;
    cout << "5. Sap xep danh sach theo DTB (BubbleSort)" << endl;
    cout << "6. Sap xep danh sach theo DTB (QuickSort)" << endl;
    cout << "7. Tim kiem sinh vien bang ma" << endl;
    cout << "8. Xoa sinh vien bang ma" << endl;
    cout << "9. Luu sinh vien vao file" << endl;
    cout << "10. Luu sinh vien gioi vao file" << endl;
    cout << "11. Luu tat ca sinh vien  vao file" << endl;
    cout << "12. Exit" << endl;
    cout << "Nhap lua chon cua ban: ";
}

int main() {
    int choice;
    int n;
    const int MAX_LIST = 100;
    SinhVien list[MAX_LIST];
    do {
        printMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Nhap so luong sinh vien: ";
                cin >> n;
                inputStudents(list, n);
                break;
            case 2:
                cout << "\nBang danh sach sinh vien:" << endl;
                printStudents(list, n);
                break;
            case 3:
                cout << "Da sap xep danh sach theo DTB (InsertionSort)" << endl;
                InsertionSort(list, n);
                break;
            case 4:
                cout << "Da sap xep danh sach theo DTB (SelectionSort)" << endl;
                SelectionSort(list, n);
                break;
            case 5:
                cout << "Da sap xep danh sach theo DTB (BubbleSort)" << endl;
                BubbleSort(list, n);
                break;
            case 6:
                cout << "Da sap xep danh sach theo DTB (QuickSort)" << endl;
                QuickSort(list,0,n-1);
                break;
            case 7:{
                cout << "Nhap ma sinh vien can tim: ";
                string id;
                cin >> id;
                findStudentByID(list, n, id, false);
                break;
            }
            case 8: {
                string id_del;
                cout << "Nhap ma sinh vien can xoa: ";
                cin >> id_del;
                deleteStudentByID(list, n, id_del);
                break;
            }
            case 9:
                saveStudentsToFile(list,n);
                break;
            case 10:
                writeStudentsExcellent(list,n);
                break;
            case 11:
                writeStudentsToFile(list,n);
                break;
            case 12:
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    } while (choice != 12);
    return 0;
}

