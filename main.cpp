#include <iostream>
#include <ctime>
#include <fstream>
#include <string.h>

#define TXT_TYPE_FILE ".txt"
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
typedef d_node DNODE_PRODUCT;

struct d_list {
    DNODE_PRODUCT *head;
    DNODE_PRODUCT *tail;
};
typedef d_list DLIST_PRODUCT;


typedef d_list DLIST_PRODUCT;
struct bill {
    string id;
    DATE date;
    string productName;
    double price;
    int amount;
    double totalMoney;
};
typedef bill BILL;

struct d_node_bill {
    BILL data;
    struct d_node_bill *next;
    struct d_node_bill *prev;
};
typedef d_node_bill DNODE_BILL;

struct d_list_bill {
    DNODE_BILL *head;
    DNODE_BILL *tail;
};
typedef d_list_bill DLIST_BILL;


void initListProduct(DLIST_PRODUCT &DL) {
    DL.head = DL.tail = NULL;
}

void initListBill(DLIST_BILL &DL) {
    DL.head = DL.tail = NULL;
}

DNODE_PRODUCT *initNodeProduct(PRODUCT x) {
    DNODE_PRODUCT *p = new DNODE_PRODUCT;
    p->data = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

DNODE_BILL *initNodeBill(BILL x) {
    DNODE_BILL *p = new DNODE_BILL;
    p->data = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void insertLastProduct(DLIST_PRODUCT &DL, DNODE_PRODUCT *p) {
    if (DL.head == NULL) {
        DL.head = p;
        DL.tail = DL.head;
    } else {
        DL.tail->next = p;
        p->prev = DL.tail;
        DL.tail = p;
    }
}

void writeProductToFile(DLIST_PRODUCT list) {
    DNODE_PRODUCT *x;
    PRODUCT dt;
    FILE *f;
    f = fopen("test5.dat", "ab");
    x = list.head;
    if (x == NULL) {
        cout << "\nDanh sach chua co gia tri, nhap truoc khi luu file!";
    }
    if (f == NULL) {
        cout << "\nLoi khi mo tep";
        exit(1);
    } else {
        while (x != NULL) {
            dt = x->data;
            fwrite(&dt, sizeof(dt), 1, f);
            x = x->next;
        }

        fclose(f);
//        cout<<"\nDa luu vao file!"<<fileName;
    }
}

void readProductFromFile(DLIST_PRODUCT list) {
    FILE *f;
    DNODE_PRODUCT *p;
    PRODUCT dt;
    f = fopen("test5.dat", "rb");
    int n = 0;
    if (f == NULL) {
        cout << "\nMo file bi loi!";
    } else {
        p = list.head;
        while (fread(&dt, sizeof(dt), 1, f) == 1) {
            p = new DNODE_PRODUCT;
            p->data = dt;
            if (list.head == NULL) {
                list.head = p;
                list.tail = list.head;
                p->next = NULL;
            } else {
                p->next = list.head;
                list.head = p;
            }
        }
        fclose(f);
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
    cout << date.day << "/" << date.month << "/" << date.year << endl;
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
    cout << "===================================" << endl;
    return product;
}

void inputListProduct(DLIST_PRODUCT &dlist) {
    cout << "Input number of products: ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        DNODE_PRODUCT *p;
        p = initNodeProduct(inputProduct());
        insertLastProduct(dlist, p);
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


void showListProduct(DLIST_PRODUCT DL) {
    DNODE_PRODUCT *p;
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
    cout << "|[14].Save to file                 |" << endl;
    cout << "|[14].Read from file               |" << endl;
    cout << "|[0].EXIT ADMIN                    |" << endl;
    cout << "====================================\n" << endl;
}

void editProductById(DLIST_PRODUCT DL) {
    string idSearch;
    cout << "Input ID product to edit: ";
    getline(cin, idSearch);
    DNODE_PRODUCT *p;
    p = DL.head;
    while (p != NULL) {
        if (p->data.id == idSearch)
            p->data = inputProduct();
        p = p->next;
    }
}


void findProductById(DLIST_PRODUCT DL) {
    string idSearch;
    cout << "Input ID product to edit: ";
    getline(cin, idSearch);
    DNODE_PRODUCT *p;
    p = DL.head;
    while (p != NULL) {
        if (p->data.id == idSearch)
            showAProduct(p->data);
        p = p->next;
    }
}

void findProductByCategory(DLIST_PRODUCT DL) {
    string categorySearch;
    cout << "Input category product to edit: ";
    getline(cin, categorySearch);
    DNODE_PRODUCT *p;
    p = DL.head;
    while (p != NULL) {
        if (p->data.id == categorySearch)
            showAProduct(p->data);
        p = p->next;
    }
}

double totalMoneyProduct(DLIST_PRODUCT list) {
    double sumMoney = 0;
    DNODE_PRODUCT *p;
    p = list.head;
    while (p != NULL) {
        sumMoney += p->data.price;
        p = p->next;
    }
    return sumMoney;
}


int totalAmountProduct(DLIST_PRODUCT list) {
    int sumAmount = 0;
    DNODE_PRODUCT *p;
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

void sortByName(DLIST_PRODUCT list) {
    cout << "Sorted ===================================" << endl;
    DNODE_PRODUCT *p = list.head;
    DNODE_PRODUCT *q = p->next;
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


void sortByPrice(DLIST_PRODUCT list) {
    cout << "Sorted ===================================" << endl;
    DNODE_PRODUCT *p = list.head;
    DNODE_PRODUCT *q = p->next;
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

void outDateProduct(DLIST_PRODUCT list) {
    DNODE_PRODUCT *p;
    p = list.head;
    while (p != NULL) {
        if (isOutDate(p->data.exp))
            showAProduct(p->data);
        p = p->next;
    }
}

double minPrice(DLIST_PRODUCT list) {
    DNODE_PRODUCT *p;
    p = list.head;
    double min = p->data.price;
    while (p != NULL) {
        if (min > p->data.price) min = p->data.price;
        p = p->next;
    }
    return min;
}

double maxPrice(DLIST_PRODUCT list) {
    DNODE_PRODUCT *p;
    p = list.head;
    double max = p->data.price;
    while (p != NULL) {
        if (max < p->data.price) max = p->data.price;
        p = p->next;
    }
    return max;
}

DNODE_PRODUCT *searchById(DLIST_PRODUCT list) {
    string idSearch;
    cout << "Input ID for searching: " << endl;
    getline(cin, idSearch);
    DNODE_PRODUCT *p;
    p = list.head;
    while (p != NULL) {
        if (p->data.id == idSearch)
            break;
        p = p->next;
    }
    return p;
}

void removeByID(DLIST_PRODUCT list) {
    DNODE_PRODUCT *p;
    p = searchById(list);
    if (p == NULL) {
        cout << "Can't remove by id . Something went wrong!!" << endl;
        return;
    } else {
        if ((p = list.head) && (p = list.tail)) {
            list.head = NULL;
            list.tail = NULL;
        } else if (p == list.tail) {
            p->prev->next = NULL;
            list.tail = p->prev;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        delete (p);
    }
}


void admin() {
    DLIST_PRODUCT list;
    initListProduct(list);
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
            case 14:
                writeProductToFile(list);
                break;
            case 15:
                readProductFromFile(list);
                break;
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

