//
// Created by ninhd on 13/10/2022.
//
#include <iostream>
#include <string>
#define CURRENT_YEAR 2022
using namespace std;

struct sanPham {
    string maSp;
    string tenSp;
    int namSX;
    int hanSuDung;
};
typedef struct sanPham SAN_PHAM;

struct node {
    SAN_PHAM data;
    node *pNext;
};
typedef struct node NODE;

struct list{
    NODE *pHead;
    NODE *pTail;
};

typedef struct list LIST;

void initList(LIST &list){
    list.pHead = NULL;
    list.pTail = NULL;
}

NODE* initNode(SAN_PHAM sp){
    NODE *p;
    p = new NODE ;
    if(p == NULL) exit(1);
    p->data = sp;
    p->pNext = NULL;
    return p;
}

void insertLast(LIST &list,NODE *p ){
    if (list.pHead==NULL) {
        list.pHead=p;
        list.pTail=p;
    }else {
        list.pTail->pNext= p;
        list.pTail=p;
    }
}

SAN_PHAM inputProduct(){
    SAN_PHAM sp;
    cout<<"===========Nhap thong tin san pham==============="<<endl;
    cout<<"Nhap vao ten san pham: ";
    getline(cin,sp.tenSp);
    cout <<"Nhap vao ma san pham (2 chu cai + 2 chu so)";
    getline(cin,sp.maSp);
    cout<<"Nhap vao nam san xuat: ";
    cin >> sp.namSX;
    cout<<"Nhap vao han su dung: ";
    cin >>sp.hanSuDung;
    cin.ignore();
    return sp;
}

void inputListProduct(LIST &list){
    cout <<"Nhap vao so san pham: ";
    int n;
    cin >> n;
    cin.ignore();
    for (int i =0 ; i< n; i++ ){
        NODE *p;
        p = initNode(inputProduct());
        insertLast(list,p);
    }
}
void showAProduct(SAN_PHAM sp){
    cout <<"Thong tin san pham "<< sp.tenSp<<endl;
    cout <<"Ma san pham : " << sp.maSp << endl;
    cout <<"Nam san xuat : " << sp.namSX << endl;
    cout <<"Han su dung : " << sp.hanSuDung <<endl;
}

void showListProduct(LIST list){
    NODE *p;
    p = list.pHead;
    while (p != NULL) {
        showAProduct(p->data);
        p = p->pNext;
    }
}

void  countProduct(LIST list){
    cout <<"Nhap nam san xuat muon dem: ";
    int k;
    cin >> k;
    int count=0;
    NODE *p;
    p = list.pHead;
    while(p!=NULL){
        if(p->data.namSX == k) count++;
        p = p->pNext;
    }
    cout <<"so luong la: " << count<<endl;
}

int subID(string id){
    string subID = id.substr(2,3);
    int id_ = stoi(subID);
    return id_;
}

void sort(LIST list) {
    for (NODE *p = list.pHead; p != NULL; p = p->pNext) {
        for (NODE *q = p->pNext; q != NULL; q = q->pNext) {
            if (subID(p->data.maSp) > subID(q->data.maSp)) {
                SAN_PHAM temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
}
bool outDatedProduct(int yearMFT, int yearOutDate){
    if((CURRENT_YEAR - yearMFT) > yearOutDate) return true;
    else return false;
}

void showOutDateProduct(LIST list){
    NODE *p;
    p = list.pHead;
    while (p != NULL) {
        if(outDatedProduct(p->data.namSX, p->data.hanSuDung)){
            showAProduct(p->data);
        }
        p = p -> pNext;
    }
}
int main() {
    LIST list;
    initList(list);
    cout <<"================================Nhap thong tin san pham ========================================"<<endl;
    inputListProduct(list);
    showListProduct(list);
    cout<<"===========================Dem so luong san pham co nam san xuat k =============================="<<endl;
    countProduct(list);
    cout <<"===============================Danh sach sau khi sap xep========================================"<<endl;
    sort(list);
    showListProduct(list);
    cout <<"==============================Nhung san pham da het han========================================="<< endl;
    showOutDateProduct(list);
    return 0;
}
