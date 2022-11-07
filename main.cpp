#include <iostream>
#include <ctime>

using namespace std;
struct DATE {
    int day;
    int month;
    int year;
};

struct product {
    string id;
    string name;
    string category;
    double price;
    int amount;
    double total;
    DATE exp;
    DATE importDate;
};
typedef product PRODUCT;

struct d_node {
    PRODUCT data;
    struct d_node *next;
    struct d_node *prev;
};
typedef d_node DNODE;

struct d_list {
    DNODE *head;
    DNODE *tail;
};
typedef d_list DLIST;

void initList(DLIST &DL) {
    DL.head = DL.tail = NULL;
}

DNODE *initNode(PRODUCT x) {
    DNODE *p = new DNODE;
    p->data = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void insertLast(DLIST &DL, DNODE *p) {
    if (DL.head == NULL) {
        DL.head = p;
        DL.tail = DL.head;
    } else {
        DL.tail->next = p;
        p->prev = DL.tail;
        DL.tail = p;
    }
}

DATE inputDate() {
    DATE date;
    cout << "Input day: ";
    cin >> date.day;
    cout << "Input month: ";
    cin >> date.month;
    cout << "Input year : ";
    cin >> date.year;
    bool validDate = (date.day < 31 && date.month < 12 && date.year > 0);
    if (validDate) return date;
}

void showDate(DATE date) {
    cout << date.day << "/" << date.month << "/" << date.year;
}

PRODUCT inputProduct() {
    cin.ignore();
    PRODUCT product;
    cout << "INPUT PRODUCT=======================" << endl;
    cout << "Input id : ";
    getline(cin, product.id);
    cout << "Input name: ";
    getline(cin, product.name);
    cout << "Input category: ";
    getline(cin, product.category);
    cout << "Input price: ";
    cin >> product.price;
    cout << "Input Amount: ";
    cin >> product.amount;
    product.total = product.price * product.price;
    cout << "Input expiry date: " << endl;
    product.exp = inputDate();
    cout << "Input import date: " << endl;
    product.importDate = inputDate();
    cout << "===================================";
    return product;
}

void inputListProduct(DLIST &dlist) {
    cout << "Input number of products: ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        DNODE *p;
        p = initNode(inputProduct());
        insertLast(dlist, p);
    }
}

void showAProduct(PRODUCT product) {
    cout << product.category << " =================" << endl;
    cout << "ID: " << product.id << endl;
    cout << "Name: " << product.name << endl;
    cout << "Price: " << product.price << endl;
    cout << "Amount: " << product.amount << endl;
    cout << "Total: " << product.total << endl;
    cout << "Exp: " << product.exp.day << "/" << product.exp.month << "/" << product.exp.year << endl;
    cout << "Import Date: " << product.importDate.day << "/" << product.importDate.month << "/"
         << product.importDate.year;
}


void showListProduct(DLIST DL) {
    DNODE *p;
    p = DL.head;
    while (p != NULL) {
        showAProduct(p->data);
        p = p->next;
    }
}


void adminMenu() {
    cout << "===============ADMIN================" << endl;
    cout << "|[1].Input product                 |" << endl;
    cout << "|[2].Show products                 |" << endl;
    cout << "|[3].Edit products by ID           |" << endl;
    cout << "|[4].Find product by ID            |" << endl;
    cout << "|[5].Find product by category      |" << endl;
    cout << "|[6].Total amount of products      |" << endl;
    cout << "|[7].Total money of products       |" << endl;
    cout << "|[8].Sorting products by name      |" << endl;
    cout << "|[9].Sorting products by price     |" << endl;
    cout << "|[10].Show products is out of date |" << endl;
    cout << "|[11].Show cheapest product        |" << endl;
    cout << "|[12].Show most expensive product  |" << endl;
    cout << "|[13].Remove product by ID         |" << endl;
    cout << "|[0].EXIT ADMIN                    |" << endl;
    cout << "====================================\n" << endl;
}

void editProductById(DLIST DL) {
    string idSearch;
    cout << "Input ID product to edit: ";
    getline(cin, idSearch);
    DNODE *p;
    p = DL.head;
    while (p != NULL) {
        if (p->data.id == idSearch)
            p->data = inputProduct();
        p = p->next;
    }
}


void findProductById(DLIST DL) {
    string idSearch;
    cout << "Input ID product to edit: ";
    getline(cin, idSearch);
    DNODE *p;
    p = DL.head;
    while (p != NULL) {
        if (p->data.id == idSearch)
            showAProduct(p->data);
        p = p->next;
    }
}

void findProductByCategory(DLIST DL) {
    string categorySearch;
    cout << "Input category product to edit: ";
    getline(cin, categorySearch);
    DNODE *p;
    p = DL.head;
    while (p != NULL) {
        if (p->data.id == categorySearch)
            showAProduct(p->data);
        p = p->next;
    }
}

double totalMoneyProduct(DLIST list) {
    double sumMoney = 0;
    DNODE *p;
    p = list.head;
    while (p != NULL) {
        sumMoney += p->data.price;
        p = p->next;
    }
    return sumMoney;
}


int totalAmountProduct(DLIST list) {
    int sumAmount = 0;
    DNODE *p;
    p = list.head;
    while (p != NULL) {
        sumAmount += p->data.amount;
        p = p->next;
    }
    return sumAmount;
}

void swapProduct(PRODUCT product1, PRODUCT product2) {
    PRODUCT temp;
    temp = product1;
    product1 = product2;
    product2 = temp;
}

bool cmpName(string s1, string s2) {
    return s1 > s2;
}

void sortByName(DLIST list) {
    cout << "Sorted ===================================" << endl;
    DNODE *p = list.head;
    DNODE *q = p->next;
    while (p != NULL) {
        q = p->next;
        while (q != NULL) {
            if (cmpName(p->data.name, q->data.name))
                swapProduct(p->data, q->data);
            q = q->next;
        }
        p = p->next;
    }
}


void sortByPrice(DLIST list) {
    cout << "Sorted ===================================" << endl;
    DNODE *p = list.head;
    DNODE *q = p->next;
    while (p != NULL) {
        q = p->next;
        while (q != NULL) {
            if (p->data.price > q->data.price)
                swapProduct(p->data, q->data);
            q = q->next;
        }
        p = p->next;
    }
}

tm *getCurrentTime() {
    time_t currentTime = time(0);
    tm *now = localtime(&currentTime);
    return now;
}

bool isOutDate(DATE date) {
    tm *now = getCurrentTime();
    if (date.year == now->tm_year + 1900)
        if (date.month == now->tm_mon + 1)
            return date.day > now->tm_mday;
        else
            return date.month > now->tm_mon + 1;
    else
        return date.year > now->tm_year + 1900;
}

void outDateProduct(DLIST list) {
    DNODE *p;
    p = list.head;
    while (p != NULL) {
        if (isOutDate(p->data.exp))
            showAProduct(p->data);
        p = p->next;
    }
}

double minPrice(DLIST list) {
    DNODE *p;
    p = list.head;
    double min = p->data.price;
    while (p != NULL) {
        if (min > p->data.price) min = p->data.price;
        p = p->next;
    }
    return min;
}

double maxPrice(DLIST list) {
    DNODE *p;
    p = list.head;
    double max = p->data.price;
    while (p != NULL) {
        if (max < p->data.price) max = p->data.price;
        p = p->next;
    }
    return max;
}

DNODE *searchById(DLIST list) {
    string idSearch;
    cout <<"Input ID for searching: "<<endl;
    getline(cin,idSearch);
    DNODE *p;
    p = list.head;
    while( p!= NULL ){
        if(p->data.id == idSearch)
            break;
        p=p->next;
    }
    return p;
}

void removeByID(DLIST list) {
    DNODE *p;
    p = searchById(list);
    if(p==NULL){
        cout <<"Can't remove by id . Something went wrong!!"<<endl;
        return;
    }else{
        if((p=list.head)&&(p =list.tail)){
            list.head = NULL;
            list.tail = NULL;
        }else if(p == list.tail){
            p->prev->next = NULL;
            list.tail = p->prev;
        }else{
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        delete(p);
    }
}

void admin() {
    DLIST list;
    initList(list);
    int choice;
    adminMenu();
    while (true) {
        cout << endl;
        cout << "Input your selection: ";
        cin >> choice;
        cin.ignore();
        cout << endl;
        switch (choice) {
            case 1:
                inputListProduct(list);
                break;
            case 2:
                showListProduct(list);
                break;
            case 3:
                editProductById(list);
                break;
            case 4:
                findProductById(list);
                break;
            case 5:
                findProductByCategory(list);
                break;
            case 6:
                cout << "Total of products: \n" << totalMoneyProduct(list);
                break;
            case 7:
                cout << "Total of amount: \n" << totalAmountProduct(list);
                break;
            case 8:
                sortByName(list);
                break;
            case 9:
                sortByPrice(list);
                break;
            case 10:
                outDateProduct(list);
                break;
            case 11:
                cout << "Cheapest product : " << minPrice(list);
                break;
            case 12:
                cout << "Expensive product: " << maxPrice(list);
                break;
            case 13:
                removeByID(list);
            default:
                cout << "Something went wrong!!" << endl;
        }
        if (choice == 0) {
            break;
        }
    }
}

int roleMenu() {
    int selectionRole;
    cout << "YOUR ROLE======================================" << endl;
    cout << "| [1].Admin  | [2].Shop Assistants | [x] EXIT |" << endl;
    cout << "===============================================" << endl;
    cout << "Your selection:";
    cin >> selectionRole;
    if (selectionRole == 1) {
        return 1;
    } else if (selectionRole == 2) {
        return 2;
    } else {
        return 0;
    }
}

int main() {
    if (roleMenu() == 1) {
        admin();
    }
    return 0;
}

