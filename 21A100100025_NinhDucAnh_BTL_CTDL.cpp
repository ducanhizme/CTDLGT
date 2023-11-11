#include "iostream"
#include "iomanip"
#include "cstring"

#define CARS_DATA_STORAGE "cars.txt"
#define CUSTOMER_DATA_STORAGE "customers.txt"
#define CONTRACT_DATA_STORAGE "rented_car.txt"
#define NOT_FOUND_CODE 404

using namespace std;

//================== Utils =============================
string inputDate() {
    string formattedDate;
    int day;
    int month;
    int year;
    cout << "Input day: ";
    cin >> day;
    cout << "Input month: ";
    cin >> month;
    cout << "Input year : ";
    cin >> year;
    bool validDate = (day < 31 && month < 12 && year > 0);
    if (validDate) {
        formattedDate = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
        return formattedDate;
    }
}

//================== CUSTOMER =============================
struct Customer {
    int id;
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

bool isCustomerListEmpty(CustomerList list) {
    if (list.head == nullptr)
        return true;
    return false;
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

void deleteCustomer(CustomerList &list, CustomerNode* node) {
    if (node == list.head) {
        list.head = node->next;
        if (list.head != nullptr) {
            list.head->prev = nullptr;
        }
        delete node;
        return;
    }

    if (node->next == nullptr) {
        node->prev->next = nullptr;
        delete node;
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

int customerListSize(CustomerNode *head) {
    int count = 0;
    CustomerNode *current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void saveCustomersToTextFile(CustomerList list, const char *fileName) {
    FILE *f = fopen(fileName, "w");
    if (f == nullptr) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    int n = customerListSize(list.head);
    CustomerNode *p = list.head;
    fprintf(f, "%d\n", n);
    while (p != nullptr) {
        fprintf(f, "%d %s %d %s %s\n",
                p->data.id,
                p->data.nameCustomer.c_str(),
                p->data.age,
                p->data.phoneNumber.c_str(),
                p->data.address.c_str()
        );
        p = p->next;
    }
    fclose(f);
    cout << "Data saved to text file: " << fileName << endl;
}

CustomerList readCustomersFromTextFile(const char *fileName) {
    FILE *f;
    CustomerList list{};
    initCustomerList(list);
        f = fopen(fileName, "r");
        if (f == nullptr) {
            return list;
        }
    int n;
    if (fscanf(f, "%d", &n) != 1) {
        fclose(f);
        return list;
    }
    for (int i = 0; i < n; i++) {
        Customer data;
        char nameCustomerStr[100];
        char phoneNumberStr[100];
        char addressStr[100];
        if (fscanf(f, "%d %s %d %s %s", &data.id, nameCustomerStr, &data.age, phoneNumberStr, addressStr) == 5) {
            data.nameCustomer = nameCustomerStr;
            data.phoneNumber = phoneNumberStr;
            data.address = addressStr;
            CustomerNode *p = createCustomerNode(data);
            addCustomer(list, p);
        } else {

        }
    }
    fclose(f);
    cout << "Successfully read " << n << " customers from the file." << endl;
    return list;
}

Customer inputCustomer() {
    Customer customer;
    cout << "Input Customer =======================" << endl;
    cout << "Input id: ";
    cin >> customer.id;
    cin.ignore();
    cout << "Input name: ";
    getline(cin, customer.nameCustomer);
    cout << "Input age: ";
    cin >> customer.age;
    cin.ignore();
    cout << "Input phone number: ";
    getline(cin, customer.phoneNumber);
    cout << "Input address: ";
    getline(cin, customer.address);
    cout << "======================================" << endl;
    return customer;
}

void inputCustomers(CustomerList &list) {
    cout << "Input file name to store customers' data: ";
    char fileName[20];
    cin >> fileName;
    cout << "Input the number of customers: ";
    int n;
    cin >> n;
    cin.ignore(); // Consume the newline character
    for (int i = 0; i < n; i++) {
        CustomerNode *p;
        p = createCustomerNode(inputCustomer());
        addCustomer(list, p);
    }
    saveCustomersToTextFile(list, fileName);
}

void inputCustomers(string fileName) {
    CustomerList list = readCustomersFromTextFile(fileName.c_str());
    inputCustomers(list);
}

void showCustomerTittleTable() {
    cout << setw(5) << "ID" << " | "
         << left << setw(15) << "Name" << " | "
         << setw(5) << "Age" << " | "
         << setw(15) << "Phone Number" << " | "
         << "Address" << endl;
}

void showCustomer(Customer customer) {

    cout << std::setw(5) << customer.id << " | "
         << left << setw(15) << customer.nameCustomer << " | "
         << std::setw(5) << customer.age << " | "
         << std::setw(15) << customer.phoneNumber << " | "
         << customer.address << endl;
}

void showCustomers(CustomerList list) {
    showCustomerTittleTable();
    CustomerNode *p;
    p = list.head;
    while (p != nullptr) {
        showCustomer(p->data);
        p = p->next;
    }
}

void showCustomers(string fileName) {
    CustomerList list = readCustomersFromTextFile(fileName.c_str());
    showCustomers(list);
}

Customer findCustomerByID(CustomerList list, int id) {
    CustomerNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == id) {
            return current->data;
        }
        current = current->next;
    }
    return Customer{NOT_FOUND_CODE, "", 0, "", ""};
}

//============================================================
//================== CAR ================================
struct Car {
    int id;
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

void notifyDataCarChanged(CarList list, char *name);

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

void deleteCar(CarList &list, CarNode* node) {
    if (node == list.head) {
        list.head = node->next;
        if (list.head != nullptr) {
            list.head->prev = nullptr;
        }
        delete node;
        return;
    }

    if (node->next == nullptr) {
        node->prev->next = nullptr;
        delete node;
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

int carListSize(CarNode *head) {
    int count = 0;
    CarNode *current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

bool isCarListEmpty(CarList list) {
    if (list.head == nullptr)
        return true;
    return false;
}

void saveCars(CarList list, const char *fileName) {
    FILE *f = fopen(fileName, "w");
    if (f == nullptr) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    int n = carListSize(list.head);
    CarNode *p = list.head;
    fprintf(f, "%d\n", n);
    while (p != nullptr) {
        fprintf(f, "%d %s %d %d %.2f %s\n",
                p->data.id,
                p->data.nameCar.c_str(),
                p->data.capacityFuel,
                p->data.mfgDate,
                p->data.price,
                p->data.status ? "Rented" : "Unrented"
        );
        p = p->next;
    }

    fclose(f);
    cout << "Data saved to text file: " << fileName << endl;
}

CarList readCarsFromTextFile(const char *fileName) {
    CarList list;
    initCarList(list);
    FILE *f = fopen(fileName, "r");
    if (f == nullptr) {
        return list;
    }
    int n;
    if (fscanf(f, "%d", &n) != 1) {
        fclose(f);
        return list;
    }
    for (int i = 0; i < n; i++) {
        Car data;
        char nameCarStr[100];
        char statusStr[20]; // Assuming the status string won't exceed 20 characters
        if (fscanf(f, "%d %s %d %d %f %s", &data.id, nameCarStr, &data.capacityFuel, &data.mfgDate, &data.price,
                   statusStr) == 6) {
            data.nameCar = nameCarStr; // Convert the C-style string to a std::string
            data.status = (strcmp(statusStr, "Rented") == 0);
            CarNode *p = createCarNode(data);
            addCar(list, p);
        } else {
            cerr << "Error: Failed to read car data." << endl;
        }
    }

    fclose(f);

    cout << "Successfully read " << n << " cars from the file." << endl;
    return list;
}

Car inputCar() {
    Car car;
    cout << "Input Car =======================" << endl;
    cout << "Input id: ";
    cin >> car.id;
    cin.ignore();
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
    cout << setw(10) << "ID" << " | "
         << left << setw(15) << "Name" << " | "
         << setw(10) << "MFG" << " | "
         << setw(10) << "Capacity(l)" << " | "
         << setw(10) << "Price(VND)" << " | "
         << "Status" << endl;
}

void showCar(Car car) {
    string status = car.status ? "Rented" : "Unrented";
    cout << setw(10) << car.id << " | "
         << left << setw(15) << car.nameCar << " | "
         << setw(10) << car.mfgDate << " | "
         << setw(11) << car.capacityFuel << " | "
         << setw(10) << car.price << " | "
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

void showCars(string fileName) {
    CarList list = readCarsFromTextFile(fileName.c_str());
    showCars(list);
}

//Input and save into new file
void inputCars(CarList &list) {
    cout << "Input file name to store cars data: ";
    char fileName[20];
    cin >> fileName;
    cout << "Input number of car: ";
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        CarNode *p;
        p = createCarNode(inputCar());
        addCar(list, p);
    }
    saveCars(list, fileName);
}

void inputCars(string fileName) {
    CarList list = readCarsFromTextFile(fileName.c_str());
    cout << "Input number of car: ";
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        CarNode *p;
        p = createCarNode(inputCar());
        addCar(list, p);
    }
    saveCars(list, fileName.c_str());
}

//Input and save into an existing file
//void inputCars(string fileName) {
//    CarList list = readCarsFromTextFile(fileName.c_str());
//    inputCars(list);
//}

Car findCarByID(CarList list, int id) {
    CarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == id) {
            return current->data;
        }
        current = current->next;
    }
    return Car{NOT_FOUND_CODE, "", 0, 0, false};
}

CarList findUnrentedCar( const string& fileName,bool status){
    CarList listTemp{};
    initCarList(listTemp);
    CarList list = readCarsFromTextFile(fileName.c_str());
    CarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.status==status) {
            addCar(listTemp, createCarNode(current->data));
        }
        current = current->next;
    }
    return listTemp;
}

void updateStatusCar(CarList list, bool status, int id, const char *fileName) {
    CarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == id) {
            current->data.status = status;
        }
        current = current->next;
    }
    saveCars(list, fileName);
}

//============================================================
//================== RENTED CAR ================================

struct RentedCar {
    Car car;
    Customer customer;
    string startDate;
    string endDate;
};

struct RentedCarNode {
    RentedCar data;
    struct RentedCarNode *next{};
    struct RentedCarNode *prev{};
};

struct RentedCarList {
    RentedCarNode *head;
    RentedCarNode *tail;
};

void initRentedCarList(RentedCarList &list) {
    list.head = list.tail = nullptr;
}

RentedCarNode *createRentedCarNode(RentedCar rentedCar) {
    RentedCarNode *p;
    p = new RentedCarNode;
    p->data = rentedCar;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void addRentedCar(RentedCarList &list, RentedCarNode *p) {
    if (list.head == nullptr) {
        list.head = p;
        list.tail = list.head;
    } else {
        list.tail->next = p;
        p->prev = list.tail;
        list.tail = p;
    }
}

void deleteRentedCar(RentedCarList &list, RentedCarNode* node) {
    if (node == list.head) {
        list.head = node->next;
        if (list.head != nullptr) {
            list.head->prev = nullptr;
        }
        delete node;
        return;
    }

    if (node->next == nullptr) {
        node->prev->next = nullptr;
        delete node;
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

int rentedCarListSize(RentedCarNode *head) {
    int count = 0;
    RentedCarNode *current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void saveRentedCars(RentedCarList list, const char *fileName) {
    FILE *f = fopen(fileName, "w");
    if (f == nullptr) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    int n = rentedCarListSize(list.head);
    RentedCarNode *p = list.head;
    fprintf(f, "%d\n", n);

    while (p != nullptr) {
        fprintf(f, "%d %d %s %s %s %s\n",
                p->data.car.id,
                p->data.customer.id,
                p->data.startDate.c_str(),
                p->data.endDate.c_str(),
                p->data.car.nameCar.c_str(),
                p->data.customer.nameCustomer.c_str()
        );
        p = p->next;
    }

    fclose(f);
    cout << "Rented cars data saved to text file: " << fileName << endl;
}

RentedCarList readRentedCars(const char *fileName, CarList carList, CustomerList customerList) {
    RentedCarList list;
    initRentedCarList(list);
    FILE *f = fopen(fileName, "r");
    if (f == nullptr) {
        return list;
    }
    int n;
    if (fscanf(f, "%d", &n) != 1) {
        fclose(f);
        return list;
    }

    for (int i = 0; i < n; i++) {
        RentedCar rentedCar;
        int carID, customerID;
        char startDateStr[100], endDateStr[100];
        char nameCarStr[100], nameCustomerStr[100];

        if (fscanf(f, "%d %d %s %s %s %s", &carID, &customerID, startDateStr, endDateStr, nameCarStr,
                   nameCustomerStr) == 6) {
            rentedCar.car = findCarByID(carList, carID);
            rentedCar.customer = findCustomerByID(customerList, customerID);
            rentedCar.startDate = startDateStr;
            rentedCar.endDate = endDateStr;
            addRentedCar(list, createRentedCarNode(rentedCar));
        } else {
            cerr << "Error: Failed to read rented car data." << endl;
        }
    }
    fclose(f);
    cout << "Successfully read " << n << " rented cars from the file." << endl;
    return list;
}

RentedCar inputRentedCar(CarList carList, CustomerList customerList) {
    RentedCar rentedCar;
    cout << "Input Rented Car =================================" << endl;
    cout << "Input id car: ";
    int idCar;
    cin >> idCar;
    Car car = findCarByID(carList, idCar);
    rentedCar.car = car;
    cout << "Input id customer: ";
    int idCustomer;
    cin >> idCustomer;
    Customer customer = findCustomerByID(customerList, idCustomer);
    rentedCar.customer = customer;
    rentedCar.startDate = inputDate();
    rentedCar.endDate = inputDate();
    if (car.id != NOT_FOUND_CODE && customer.id != NOT_FOUND_CODE) {
        return rentedCar;
    } else {
        cout << "Something went wrong !!!" << endl;
    }
}

RentedCar inputRentedCar(CarList &carList, CustomerList &customerList, bool save) {
    RentedCar rentedCar;
    cout << "Input Rented Car =================================" << endl;
    cout << "Input id car: ";
    int idCar;
    cin >> idCar;
    rentedCar.car = findCarByID(carList, idCar);
    updateStatusCar(carList, true, idCar, CARS_DATA_STORAGE);
    rentedCar.customer = inputCustomer();
    rentedCar.startDate = inputDate();
    rentedCar.endDate = inputDate();
    if (save) {
        addCustomer(customerList, createCustomerNode(rentedCar.customer));
        saveCustomersToTextFile(customerList, CUSTOMER_DATA_STORAGE);
    }
    return rentedCar;
}

void inputRentedCars(RentedCarList &list, CarList carList, CustomerList customerList,string fileName) {
    cout<<"Input number of rented car: ";
    int n;
    cin>>n;
    for (int i = 0; i < n; i++) {
        RentedCarNode *p;
        p = createRentedCarNode(inputRentedCar(carList, customerList, true));
        addRentedCar(list, p);
    }
    saveRentedCars(list, fileName.c_str());
}

void inputRentedCars(const string& fileNameRentedCar, const string& fileNameCar, const string& fileNameCustomer) {
    CarList carList = readCarsFromTextFile(fileNameCar.c_str());
    CustomerList customerList = readCustomersFromTextFile(fileNameCustomer.c_str());
    RentedCarList list = readRentedCars(fileNameRentedCar.c_str(), carList, customerList);
    inputRentedCars(list, carList, customerList,fileNameRentedCar);
}
void showTitleRentedCarTable() {
    cout << setw(10) << "ID CAR" << " | "
         << left << setw(10) << "ID CUSTOMER" << " | "
         << setw(15) << "Start date" << " | "
         << setw(15) << "End date" << " | "
         << setw(10) << "Car name" << " | "
            << setw(10) << "Customer name" << endl;
}

void showRentedCar(RentedCar rentedCar) {
    cout << setw(10) << rentedCar.car.id << " | "
         << left << setw(11) << rentedCar.customer.id << " | "
         << setw(15) << rentedCar.startDate << " | "
         << setw(15) << rentedCar.endDate << " | "
         << setw(10) << rentedCar.car.nameCar << " | "
            << setw(10) << rentedCar.customer.nameCustomer<< endl;
}

void showRentedCars(RentedCarList list) {
    showTitleRentedCarTable();
    RentedCarNode *p;
    p = list.head;
    while (p != nullptr) {
        showRentedCar(p->data);
        p = p->next;
    }
}

void showRentedCars(const string& fileRentedName, const string& fileCarName, const string& fileCustomerName) {
    CarList carList = readCarsFromTextFile(fileCarName.c_str());
    CustomerList customerList = readCustomersFromTextFile(fileCustomerName.c_str());
    RentedCarList list = readRentedCars(fileRentedName.c_str(),carList,customerList);
    showRentedCars(list);
}

void menu() {
    cout << "Menu" << endl;
    cout << "1.Hien thong tin tat ca cac khach hang" << endl;
    cout << "2.Hien thong tin tat ca cac xe" << endl;
    cout << "3.Hien thong tin cac xe da duoc thue" << endl;
    cout << "4.Hien thong tin cac xe chua duoc thue" << endl;
    cout << "5.Hien hop dong cho thue" << endl;
    cout << "6.Them xe cho thue" << endl;
    cout << "7.Them hop dong cho thue" << endl;
    cout << "8.Xoa hop dong" << endl;
    cout << "0.Exit" << endl;
}

string handleFileInput() {
    char choice1;
    cout << "Khong co danh sach nao ban co muon import du lieu khong (Y/N): "<<endl;
    cin >> choice1;
    cin.ignore();
    do {
        if (choice1 == 'Y' || choice1 == 'y') {
            cout << "Nhap file de import danh sach oto: (0.EXIT)";
            string fileName;
            getline(cin, fileName);
            if (fileName == "0") {
                break;
            }
            return fileName;
        }else{
            cin.ignore();
            break;
        }
    } while (choice1 != 'N');
    return "0";
}

int main() {
    CustomerList customerList{};
    initCustomerList(customerList);
    CarList carList{};
    initCarList(carList);
    RentedCarList rentedCarList{};
    initRentedCarList(rentedCarList);
    int choice;
    do {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                showCustomers(CUSTOMER_DATA_STORAGE);
                break;
            case 2:
                showCars(CARS_DATA_STORAGE);
                break;
            case 3:
                showCars(findUnrentedCar(CARS_DATA_STORAGE, true));
                break;
            case 4:
                showCars(findUnrentedCar(CARS_DATA_STORAGE, false));
                break;
            case 5:
                showRentedCars(CONTRACT_DATA_STORAGE,CARS_DATA_STORAGE,CUSTOMER_DATA_STORAGE);
                break;
            case 6:
                inputCars(CARS_DATA_STORAGE);
                break;
            case 7:
                inputRentedCars(CONTRACT_DATA_STORAGE,CARS_DATA_STORAGE,CUSTOMER_DATA_STORAGE);
                break;
            case 0:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    return 0;
}
