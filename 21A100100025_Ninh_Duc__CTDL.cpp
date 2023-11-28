//
// Created by ddanh on 19/09/2023.
//
#include <utility>

#include "bits/stdc++.h"

using namespace std;

string inputString(){
    string str;
    cin>>str;
    return str;
}

int inputInteger(){
    int number;
    cin >> number;
    return number;
}

struct MOVIE {
    string ID;
    string name;
    string manufacturer;
    int productYear;
};

struct NODE {
    MOVIE data;
    struct NODE *next;
};


struct LIST {
    NODE *head;
    NODE *tail;
};

NODE *initNode(MOVIE data) {
    NODE *p = new NODE;
    p->data = data;
    p->next = nullptr;
    return p;
}
void writeProductToFile(LIST &list);
void readProductFromFile(LIST &list);

void initListProduct(LIST &x) {
    x.head = x.tail = nullptr;
}

void insertLastList(LIST &list, NODE *p) {
    if (list.head == nullptr) {
        list.head = p;
        list.tail = list.head;
    } else {
        list.tail->next = p;
        list.tail = p;
    }
}



MOVIE inputObject() {
    MOVIE x;
    cout << "ID: ";
     x.ID = inputString();
    cout << "Name: ";
    x.name = inputString();
    cout << "Manufacturer: ";
    x.manufacturer =inputString();
    cout<<"Year of product";
    x.productYear = inputInteger();
    return x;
}

void inputObjects (LIST &list , bool isHaveCondition){
    while(isHaveCondition){
        MOVIE x;
        cout << "ID: ";
        x.ID = inputString();
        cout << "Name: ";
        x.name = inputString();
        cout << "Manufacturer: ";
        x.manufacturer =inputString();
        cout<<"Year of product";
        x.productYear = inputInteger();
        if(x.productYear==0){
            break;
        }
        NODE *p = initNode(x);
        insertLastList(list,p);
    }
    writeProductToFile(list);

}

void inputObjects(LIST &list) {
        int n;
        cout << "Input n object: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            NODE *p ;
            p = initNode(inputObject());
            insertLastList(list, p);
        }
}



void showObject(MOVIE x) {
    cout << "ID: " << x.ID << endl;
    cout << "Name: " << x.name << endl;
    cout << "Manufacturer: "<<x.manufacturer<< endl;
    cout << "Year of product: " << x.productYear << endl;
}

void showObjects(LIST &list) {
    NODE *p;
    for(p=list.head ; p!= nullptr;p=p->next){
        showObject(p->data);
    }
}


NODE *searchByID(LIST &list){
    cout<<"Input ID to find: ";
    NODE*p ;
    for (p= list.head; p!= nullptr; p=p->next) {
        if(p->data.ID == inputString()){
            return p;
        }
    }
}



NODE *searchByProductYear(LIST &list){
    cout<<"Input Year Of Movie to find: ";
    NODE*p ;
    for (p= list.head; p!= nullptr; p=p->next) {
        if(p->data.productYear == inputInteger()){
            return p;
        }else{
            cout<<"Can't not find Movie ";
        }
    }
    return nullptr;
}

void searchByManufacturer(LIST &list){
    readProductFromFile(list);
    LIST anonymousList;
    initListProduct(anonymousList);
    cout<<"Input Manufacturer to find: ";
    NODE*p ;
    for (p= list.head; p!= nullptr; p=p->next) {
        if(p->data.manufacturer == inputString()){
            insertLastList(anonymousList,p);
        }
    }
    writeProductToFile(anonymousList);
}


NODE* MIN_ (LIST &list){
    NODE*p = list.head;
    NODE* min = p;
    for (p=p->next; p!= nullptr; p=p->next) {
        if(min->data.productYear > p->data.productYear){
            min = p;
        }
    }
    return min;
}

NODE *SORT(LIST &list){
    NODE *p;
    NODE *q;
    for(p=list.head; p!= nullptr;p=p->next){
        for(q=p->next;q!= nullptr;q=q->next){
            if(p->data.manufacturer > q->data.manufacturer){
                swap(p->data,q->data);
            }
        }
    }
}

void inputObjectsAfterProductID(NODE *node,LIST &list){
    if(node == nullptr) return;
    LIST anonymousList;
    initListProduct(anonymousList);
    inputObjects(anonymousList);
    NODE * p = anonymousList.head;
    while (p!= nullptr){
        NODE *temp = p;
        p=p->next;
        temp->next = node->next;
        node->next = temp;
        if(node == list.tail){
            list.tail=temp;
        }
    }
}

void writeProductToFile(LIST &list) {
    char fileName[20];
    cout<<"Input file name to save product: ";
    cin >>fileName;
    FILE *f;
    f = fopen(fileName,"wb");
    int n =0;
    NODE *p;
    for(p = list.head; p != nullptr; p = p ->next){
        n++;
    }
    fwrite(&n,sizeof(int),1,f);
    for(p = list.head;p!=NULL; p = p ->next){
        fwrite(&p->data,sizeof (MOVIE), 1 ,f);
    }
    fclose(f);
    cout<<"Complete"<<endl;
}

void readProductFromFile(LIST &list) {
    FILE *f;
    MOVIE movie;
    NODE *p;
    int n;
    char fileName[20];
    cout<<"Input file name to read file: "<<endl;
    cin>>fileName;
    f = fopen(fileName, "rb");
    fread(&n,sizeof (int),1,f);
    cout << n;
    if(list.head == NULL){
        for(int i =0 ; i < n ; i++){
            fread(&movie, sizeof(MOVIE),1,f);
            p = initNode(movie);
            insertLastList(list,p);
        }
    }
    fclose(f);
}

void removeProductBy(LIST& list, int year) {
    NODE* current = list.head;
    NODE* prev = nullptr;

    while (current != nullptr) {
        if (current->data.productYear == year) {
            if (prev == nullptr) {
                list.head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            current = (prev == nullptr) ? list.head : prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}


int main() {
    LIST list;
    initListProduct(list);
    inputObjects(list,true);
    showObjects(list);
    inputObjectsAfterProductID(searchByID(list),list);
    searchByManufacturer(list);
    SORT(list);
    removeProductBy(list,inputInteger());

}
