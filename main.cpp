#include <iostream>
#include <ctime>
#include <cstring>

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
    cout << "|[15].Read from file               |" << endl;
    cout << "|[0].EXIT ADMIN                    |" << endl;
    cout << "====================================\n" << endl;
}

void editProductById(DLIST_PRODUCT DL) {
    string idSearch;
    cout << "Input ID product to edit: ";
    cin.ignore();
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
    cin.ignore();
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
    cin.ignore();
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

void writeProductToFile(DLIST_PRODUCT list) {
    char fileName[20];
    cout<<"Input file name to save product: ";
    gets(fileName);
    FILE *f;
    f = fopen(fileName,"wb");
    int n =0;
    DNODE_PRODUCT *p;
    for(p = list.head; p != NULL; p = p ->next){
        n++;
    }
    fwrite(&n,sizeof(int),1,f);
    for(p = list.head;p!=NULL; p = p ->next){
        fwrite(&p->data,sizeof (PRODUCT), 1 ,f);
    }
    fclose(f);
    cout<<"Complete"<<endl;
}

DLIST_PRODUCT readProductFromFile(DLIST_PRODUCT &list) {
    DLIST_PRODUCT newList;
    initListProduct(newList);
    FILE *f;
    PRODUCT dt;
    DNODE_PRODUCT *p;
    int n;
    char fileName[20];
    cout<<"Input file name to read file: "<<endl;
    gets(fileName);
    f = fopen(fileName, "rb");
    fread(&n,sizeof (int),1,f);
    cout << n;
    if(list.head == NULL){
        for(int i =0 ; i < n ; i++){
            fread(&dt, sizeof(PRODUCT),1,f);
            p = initNodeProduct(dt);
            insertLastProduct(newList,p);
        }
    }
    fclose(f);
    return newList;
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
                showListProduct(readProductFromFile(list));
                break;
            default:
                cout << "Something went wrong!!" << endl;
        }
        if (choice == 0) {
            break;
        }
    }
}

void roleMenu() {
    cout << "YOUR ROLE======================================" << endl;
    cout << "| [1].Admin  | [2].Shop Assistants | [0] EXIT |" << endl;
    cout << "===============================================" << endl;
}

void salePersonMenu() {
    cout << "=============== SHOP ASSISTANTS ================" << endl;
    cout << "| [1].Input bill                               |" << endl;
    cout << "| [2].Show bill                                |" << endl;
    cout << "| [3].Edit bill                                |" << endl;
    cout << "| [4].Find bill by id                          |" << endl;
    cout << "| [5].Total of bill money                      |" << endl;
    cout << "| [6].Total quantity of products sold          |" << endl;
    cout << "| [7].Sort bill by price                       |" << endl;
    cout << "| [8].Show most expensive bill                 |" << endl;
    cout << "| [9].Count bill have price                    |" << endl;
    cout << "| [10].Delete bill                             |" << endl;
    cout << "| [11].Save to file                            |" << endl;
    cout << "| [12].Read file                               |" << endl;
    cout << "| [0].EXIT                                     |" << endl;
    cout << "================================================" << endl;
}

void insertLastBill(DLIST_BILL &list, DNODE_BILL *p) {
    if (list.head == NULL) {
        list.head = p;
        list.tail = list.head;
    } else {
        list.tail->next = p;
        p->prev = list.tail;
        list.tail = p;
    }
}

BILL inputBill() {
    BILL bill;
    cin.ignore();
    cout << "INPUT BILL ========================" << endl;
    cout << "Input id: ";
    getline(cin, bill.id);
    cin.ignore();
    cout << "Input date: \n";
    bill.date = inputDate();
    cout << "Input name of product: ";
    getline(cin, bill.productName);
    cin.ignore();
    cout << "Input price: ";
    cin >> bill.price;
    cout << "Input amount of products: ";
    cin >> bill.amount;
    cout << "===========================" << endl;
    bill.totalMoney = bill.price * bill.amount;
    return bill;
}

void inputListBill(DLIST_BILL &list) {
    int n;
    cout << "Input number of bill: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        DNODE_BILL *p;
        p = initNodeBill(inputBill());
        insertLastBill(list, p);
    }
}

void showABill(BILL bill) {
    showDate(bill.date);
    cout << " ==========================" << endl;
    cout << "ID bill: " << bill.id << endl;
    cout << "Name of product: " << bill.productName << endl;
    cout << "Price of product: " << bill.price << endl;
    cout << "Amount of product: " << bill.amount << endl;
    cout << "Total money: " << bill.totalMoney << endl;
    cout << "===================================" << endl;
}

void showListBill(DLIST_BILL listBill) {
    DNODE_BILL *p;
    p = listBill.head;
    while (p != NULL) {
        showABill(p->data);
        p = p->next;
    }
}


void editBillById(DLIST_BILL listBill) {
    string id;
    cin.ignore();
    cout << " Input ID to edit: ";
    getline(cin, id);
    DNODE_BILL *p;
    p = listBill.head;
    while (p != NULL) {
        if (p->data.id == id)
            p->data = inputBill();
        p = p->next;
    }
}


void findBillById(DLIST_BILL listBILL) {
    string id;
    cin.ignore();
    cout << " Input ID to edit: ";
    getline(cin, id);
    DNODE_BILL *p;
    p = listBILL.head;
    while (p != NULL) {
        if (p->data.id == id)
            showABill(p->data);
        p = p->next;
    }
}

void totalMoneyBill(DLIST_BILL listBill) {
    double sum = 0;
    DNODE_BILL *p;
    p = listBill.head;
    while (p != NULL) {
        sum += p->data.totalMoney;
        p = p->next;
    }
    cout <<"Total Money Bill : "<<sum;
}

void totalAmountProductSold(DLIST_BILL listBill) {
    double sum = 0;
    DNODE_BILL *p;
    p = listBill.head;
    while (p != NULL) {
        sum += p->data.amount;
        p = p->next;
    }
    cout <<"Amount of products sold : "<<sum;
}


void swapBill(BILL bill1, BILL bill2) {
    BILL temp;
    temp = bill1;
    bill1 = bill2;
    bill2 = temp;
}

void sortBillByTotalMoney(DLIST_BILL listBill) {
    cout << "Sorted ===================================" << endl;
    DNODE_BILL *p = listBill.head;
    DNODE_BILL *q = p->next;
    while (p != NULL) {
        q = p->next;
        while (q != NULL) {
            if (p->data.totalMoney > q->data.totalMoney)
                swapBill(p->data, q->data);
            q = q->next;
        }
        p = p->next;
    }
}

double showMostExpensiveBill(DLIST_BILL listBill) {
    DNODE_BILL *p;
    p = listBill.head;
    double max = p->data.totalMoney;
    while (p != NULL) {
        if (max < p->data.totalMoney) max = p->data.totalMoney;
        p = p->next;
    }
    return max;
}

void countBillByID(DLIST_BILL listBill) {
    cout << "Input id to count: ";
    string id;
    getline(cin, id);
    DNODE_BILL *p;
    p = listBill.head;
    int count = 0;
    while (p != NULL) {
        if (p->data.id == id) count++;
    }
    cout << "BILL ID " << id << ": " << count;
}

DNODE_BILL *searchByIdProduct(DLIST_BILL listBill) {
    string idSearch;
    cout << "Input ID for searching: " << endl;
    getline(cin, idSearch);
    DNODE_BILL *p;
    p = listBill.head;
    while (p != NULL) {
        if (p->data.id == idSearch)
            break;
        p = p->next;
    }
    return p;
}

void removeBillById(DLIST_BILL listBill) {
    DNODE_BILL *p;
    p = searchByIdProduct(listBill);
    if (p == NULL) {
        cout << "Can't remove by id . Something went wrong!!" << endl;
        return;
    } else {
        if ((p = listBill.head) && (p = listBill.tail)) {
            listBill.head = NULL;
            listBill.tail = NULL;
        } else if (p == listBill.tail) {
            p->prev->next = NULL;
            listBill.tail = p->prev;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        delete (p);
    }
}
void salePerson() {
    DLIST_BILL listBILL;
    initListBill(listBILL);
    salePersonMenu();
    int choice;
    while (true) {
        cout << "Input your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                inputListBill(listBILL);
                break;
            case 2:
                showListBill(listBILL);
                break;
            case 3:
                editBillById(listBILL);
                break;
            case 4:
                findBillById(listBILL);
                break;
            case 5:
                totalMoneyBill(listBILL);
                break;
            case 6:
                totalAmountProductSold(listBILL);
                break;
            case 7:
                sortBillByTotalMoney(listBILL);
                break;
            case 8:
                cout << "Most expensive bill value: " << showMostExpensiveBill(listBILL);
                break;
            case 9:
                countBillByID(listBILL);
                break;
            case 10:
                removeBillById(listBILL);
                break;
        }
        if (choice == 0) break;
    }
}

int main() {
    int selection;
    while (true) {
        roleMenu();
        cout << "Input your role: ";
        cin >> selection;
        switch (selection) {
            case 1:
                admin();
                break;
            case 2:
                salePerson();
                break;
            default:
                cout << "Something went wrong !!! " << endl;
        }
        if (selection == 0) break;
    }
}