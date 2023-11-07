#include "iostream"
#include "iomanip"
#include "cstring"

using namespace std;



//================== CUSTOMER =============================
struct Customer {
    string nameCustomer;
    int age;
    string phoneNumber;
    string address;
};

struct CustomerNode {
    Customer data;
    struct CustomerNode *next{};
    struct CustomerNode *prev{};
};

struct CustomerList {
    CustomerNode *head;
    CustomerNode *tail;
};

void initCustomerList(CustomerList &list) {
    list.head = list.tail = nullptr;
}

CustomerNode *createCustomerNode(Customer customer) {
    CustomerNode *p;
    p = new CustomerNode;
    p->data = customer;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void addCustomer(CustomerList &list, CustomerNode *p) {
    if (list.head == nullptr) {
        list.head = p;
        list.tail = list.head;
    } else {
        list.tail->next = p;
        p->prev = list.tail;
        list.tail = p;
    }
}

Customer inputCustomer() {
    Customer customer;
    cout << "Input Customer =======================" << endl;
    cout << "Input name: ";
    getline(cin, customer.nameCustomer);
    cout << "Input age: ";
    cin >> customer.age;
    cout << "Input phone number: ";
    getline(cin, customer.phoneNumber);
    cout << "Input address: ";
    getline(cin, customer.address);
    cout << "======================================" << endl;
}

void showCustomer(Customer customer, bool tittle) {
    if (tittle) {
        cout << left << setw(15) << "Name" << " | "
             << setw(5) << "Age" << " | "
             << setw(15) << "Phone Number" << " | "
             << "Address" << endl;
    }
    cout << left << setw(15) << customer.nameCustomer << " | "
         << std::setw(5) << customer.age << " | "
         << std::setw(15) << customer.phoneNumber << " | "
         << customer.address << endl;
}

//============================================================
//================== CUSTOMER ================================
struct Car {
    string nameCar;
    int capacityFuel;
    int mfgDate;
    float price;
    bool status;
};

struct CarNode {
    Car data;
    struct CarNode *next{};
    struct CarNode *prev{};
};

struct CarList {
    CarNode *head;
    CarNode *tail;
};

void showTitleCarTable();

void initCarList(CarList &list) {
    list.head = list.tail = nullptr;
}

CarNode *createCarNode(Car car) {
    CarNode *p;
    p = new CarNode;
    p->data = car;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void addCar(CarList &list, CarNode *p) {
    if (list.head == nullptr) {
        list.head = p;
        list.tail = list.head;
    } else {
        list.tail->next = p;
        p->prev = list.tail;
        list.tail = p;
    }
}

Car inputCar() {
    Car car;
    cout << "Input Car =======================" << endl;
    cout << "Input name: ";
    getline(cin, car.nameCar);
    cout << "Input manufacturing date: ";
    cin >> car.mfgDate;
    cout << "Input capacity fuel tank: ";
    cin >> car.capacityFuel;
    cout << "Input price: ";
    cin >> car.price;
    car.status = false;
    cin.ignore();
    cout << "======================================" << endl;
    return car;
}

void showTitleCarTable() {
    cout << left << setw(15) << "Name" << " | "
         << setw(10) << "MFG" << " | "
         << setw(10) << "Capacity(l)" << " | "
         << setw(10) << "Price(VND)" << " | "
         << "Status" << endl;
}

void showCar(Car car) {
    string status = car.status ? "Rented" : "Unrented";
    cout << left << setw(15) << car.nameCar << " | "
         << setw(10) << car.mfgDate << " | "
         << setw(10) << car.capacityFuel << " | "
         << setw(10) << car.price<< " | "
         << status << endl;
}

void showCars(CarList list) {
    showTitleCarTable();
    CarNode *p;
    p = list.head;
    while (p != nullptr) {
        showCar(p->data);
        p = p->next;
    }
}

void inputCars(CarList &list) {
    cout << "Input number of car: ";
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        CarNode *p;
        p = createCarNode(inputCar());
        addCar(list, p);
    }
}

void saveCars(CarList list){
    char fileName[20];
    cout<<"Input file name to save product: ";
    cin>>fileName;
    FILE *f;
    f = fopen(fileName,"wb");
    int n =0;
    CarNode *p;
    for(p = list.head; p != NULL; p = p ->next){
        n++;
    }
    fwrite(&n,sizeof(int),1,f);
    for(p = list.head;p!= nullptr; p = p ->next){
        fwrite(&p->data,sizeof (Car), 1 ,f);
    }
    fclose(f);
    cout<<"Complete"<<endl;
}

CarList readStoredCars(){
    CarList list;
    initCarList(list);
    FILE *f;
    Car data;
    int n;
    f = fopen("test1", "rb");
    if (f == nullptr) {
        cerr << "Error: Unable to open file for reading." << endl;
        return list;
    }
    fread(&n,sizeof (int),1,f);
    cout << n;
    for(int i =0 ; i < n ; i++){
        fread(&data, sizeof(Car),1,f);
        CarNode *p;
        p = createCarNode(data);
        addCar(list,p);
    }
    fclose(f);
    cout << "Successfully read " << n << " cars from the file." << endl;
    return list;
}

int main(){
//    CarList carList;
//    initCarList(carList);
//    inputCars(carList);
//    showCars(carList);
//    saveCars(carList);
    CarList carList;
    carList =readStoredCars();
    showCars(carList);
    return 0;

}


