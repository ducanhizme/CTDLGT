#include <fstream>
#include "iostream"
#include "iomanip"
#include "cstring"



using namespace std;

//================== Utils =============================

const string CARS_DATA_STORAGE = "cars.txt";
const string CUSTOMER_DATA_STORAGE = "customers.txt";
const string CONTRACT_DATA_STORAGE = "rented_car.txt";
const int NOT_FOUND_CODE = 404;

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
    cout << "9.Sap xep xe theo gia thue" << endl;
    cout << "10.Sap xep xe theo so luong cho ngoi" << endl;
    cout << "11.Chinh sua so luong cho ngoi" << endl;
    cout << "0.Exit" << endl;
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

void deleteCustomer(CustomerList &list, CustomerNode *node) {
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

void filterFirstCustomerList(CustomerList &list) {
    CustomerNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == NOT_FOUND_CODE) {
            deleteCustomer(list,current);
        }
        current = current->next;
    }
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
    ofstream file(fileName);
    if (!file) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    int n = customerListSize(list.head);
    CustomerNode *p = list.head;
    file << n << "\n";
    while (p != nullptr) {
        file << p->data.id << " " << p->data.nameCustomer << " " << p->data.age << " " << p->data.phoneNumber << " " << p->data.address << "\n";
        p = p->next;
    }
    cout << "Data saved to text file: " << fileName << endl;
}

CustomerList readCustomersFromTextFile(const char *fileName) {
    ifstream file(fileName);
    CustomerList list{};
    initCustomerList(list);
    if (!file) {
        return list;
    }
    int n;
    if (!(file >> n)) {
        file.close();
        return list;
    }
    string line;
    getline(file, line);
    for (int i = 0; i < n; i++) {
        Customer data;
        std::string nameCustomerStr;
        std::string phoneNumberStr;
        std::string addressStr;
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            if (iss >> data.id >> nameCustomerStr >> data.age >> phoneNumberStr >> addressStr) {
                data.nameCustomer = nameCustomerStr;
                data.phoneNumber = phoneNumberStr;
                data.address = addressStr;
                CustomerNode *p = createCustomerNode(data);
                addCustomer(list, p);
            } else {
                throw std::runtime_error("Error: Cannot read customer file");
            }
        }
    }
    file.close();
    cout << "Successfully read customers from the file." << std::endl;
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
    filterFirstCustomerList(list);
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

    cout << setw(5) << customer.id << " | "
         << left << setw(15) << customer.nameCustomer << " | "
         << setw(5) << customer.age << " | "
         << setw(15) << customer.phoneNumber << " | "
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
    int seatAmount;
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

void deleteCar(CarList &list, CarNode *node) {
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

void filterFirstCarList(CarList &list) {
    CarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == NOT_FOUND_CODE) {
            deleteCar(list,current);
        }
        current = current->next;
    }
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
    ofstream file(fileName);
    if (!file) {
        throw runtime_error("Error: Unable to open file for writing.");
    }
    int n = carListSize(list.head);
    CarNode *p = list.head;
    file << n << std::endl;
    while (p != nullptr) {
        file << p->data.id << " "
             << p->data.nameCar << " "
             << p->data.capacityFuel << " "
             << p->data.mfgDate << " "
             << p->data.price << " "
             << (p->data.status ? "Rented" : "Unrented")<<" "
            << p->data.seatAmount
             << endl;
        p = p->next;
    }

    cout << "Data saved to text file: " << fileName << std::endl;
}

CarList readCarsFromTextFile(const char *fileName) {
    CarList list;
    initCarList(list);
    ifstream file(fileName);
    if (!file) {
        return list;
    }
    int n;
    if (!(file >> n)) {
        return list;
    }
    for (int i = 0; i < n; i++) {
        Car data;
        string nameCarStr;
        string statusStr;
        char nameCarCStr[100];
        char statusCStr[20];
        if (file >> data.id >> nameCarCStr >> data.capacityFuel >> data.mfgDate >> data.price >> statusCStr >> data.seatAmount) {
            nameCarStr = nameCarCStr;
            statusStr = statusCStr;
            data.nameCar = nameCarStr;
            data.status = (statusStr == "Rented");
            CarNode *p = createCarNode(data);
            addCar(list, p);
        } else {
            cout<< "Failed to read car data."<<endl;
        }
    }
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
    cout << "Input amount of seats: ";
    cin >> car.seatAmount;
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
            << setw(10) << "Status" << " | "
         << "Seats" << endl;
}

void showCar(Car car) {
    string status = car.status ? "Rented" : "Unrented";
    cout << setw(10) << car.id << " | "
         << left << setw(15) << car.nameCar << " | "
         << setw(10) << car.mfgDate << " | "
         << setw(10) << car.capacityFuel << " | "
         << setw(10) << car.price << " | "
            << setw(10) << status << " | "
         << car.seatAmount << endl;
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
    filterFirstCarList(list);
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
    filterFirstCarList(list);
    saveCars(list, fileName.c_str());
}


Car findCarByID(CarList list, int id) {
    CarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == id) {
            return current->data;
        }
        current = current->next;
    }
    return Car{NOT_FOUND_CODE, "x", 0, 0, 0, false};
}

CarList findUnrentedCar(const string &fileName, bool status) {
    CarList listTemp{};
    initCarList(listTemp);
    CarList list = readCarsFromTextFile(fileName.c_str());
    CarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.status == status) {
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

void sortCars(string fileName){
    CarList list = readCarsFromTextFile(fileName.c_str());
    if (list.head == nullptr || list.head->next == nullptr) {
        return;
    }
    bool swapped;
    CarNode *lastNode = nullptr;

    do {
        swapped = false;
        for (CarNode *current = list.head; current->next != lastNode; current = current->next) {
            if (current->data.price > current->next->data.price) {
                swap(current->data, current->next->data);
                swapped = true;
            }
        }
        lastNode = list.tail;
    } while (swapped);
    showCars(list);
}

void sortSeatCar(string fileName){
    CarList list = readCarsFromTextFile(fileName.c_str());
    if (list.head == nullptr || list.head->next == nullptr) {
        return;
    }
    bool swapped;
    CarNode *lastNode = nullptr;
    do {
        swapped = false;
        for (CarNode *current = list.head; current->next != lastNode; current = current->next) {
            if (current->data.seatAmount > current->next->data.seatAmount) {
                swap(current->data, current->next->data);
                swapped = true;
            }
        }
        lastNode = list.tail;
    } while (swapped);
    showCars(list);
}

void editSeatCar(string fileName){
    CarList list = readCarsFromTextFile(fileName.c_str());
    bool check= false;
    cout <<"Input id to edit seatss: "<<endl;
    int id;
    cin >>id;
    CarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == id) {
            cout <<"Input new seat data: "<<endl;
            cin >> current->data.seatAmount;
            check = true;
        }
        current = current->next;
    }
   string logger = check?"Successfully Edit" : "Error:Cannot to edit";
    cout <<logger<<endl;
    saveCars(list,fileName.c_str());
}
//============================================================
//================== RENTED CAR ================================

struct RentedCar {
    int id;
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

void deleteRentedCar(RentedCarList &list, RentedCarNode *node) {
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

void filterFirstRentedCarList(RentedCarList &list) {
    RentedCarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.car.id == NOT_FOUND_CODE) {
            deleteRentedCar(list,current);
        }
        current = current->next;
    }
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
    ofstream file(fileName);
    if (!file) {
       cout<<"Unable to open file for writing."<<endl;
        return;
    }
    int n = rentedCarListSize(list.head);
    RentedCarNode *p = list.head;
    file << n << endl;

    while (p != nullptr) {
        file << p->data.id << " "
             << p->data.car.id << " "
             << p->data.customer.id << " "
             << p->data.startDate << " "
             << p->data.endDate << " "
             << p->data.car.nameCar << " "
             << p->data.customer.nameCustomer << endl;
        p = p->next;
    }

    cout<< "Rented cars data saved to text file: %s"<< fileName<<endl;
}

RentedCarList readRentedCars(const std::string& fileName, CarList carList, CustomerList customerList) {
    RentedCarList list;
    initRentedCarList(list);
    ifstream file(fileName);
    if (!file) {
        return list;
    }

    int n;
    char line[100];
    if (file.getline(line, sizeof(line))) {
        sscanf(line, "%d", &n);
    } else {
        return list;
    }

    for (int i = 0; i < n; i++) {
        RentedCar rentedCar;
        int carID, customerID, id;
        char startDateStr[100], endDateStr[100];
        char nameCarStr[100], nameCustomerStr[100];

        if (file.getline(line, sizeof(line))) {
            sscanf(line, "%d %d %d %s %s %s %s", &id, &carID, &customerID, startDateStr, endDateStr, nameCarStr,
                   nameCustomerStr);
            rentedCar.id = id;
            rentedCar.car = findCarByID(carList, carID);
            rentedCar.customer = findCustomerByID(customerList, customerID);
            rentedCar.startDate = startDateStr;
            rentedCar.endDate = endDateStr;
            addRentedCar(list, createRentedCarNode(rentedCar));
        } else {
            cout << "Error: Failed to read rented car data." << endl;
        }
    }
    cout << "Successfully read rented cars from the file." << endl;
    return list;
}

RentedCar inputRentedCar(CarList carList, CustomerList customerList) {
    RentedCar rentedCar;
    cout << "Input Rented Car =================================";
    cout << "Input id: ";
    cin >> rentedCar.id;
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
        cout << "Cannot find car have id: "<<car.id << endl;
    }
}

RentedCar inputRentedCar(CarList &carList, CustomerList &customerList, bool save) {
    RentedCar rentedCar;
    cout << "Input Rented Car =================================" << endl;
    cout << "Input id: ";
    cin >> rentedCar.id;
    cout << "Input id car: ";
    int idCar;
    cin >> idCar;
    rentedCar.car = findCarByID(carList, idCar);
    updateStatusCar(carList, true, idCar, CARS_DATA_STORAGE.c_str());
    rentedCar.customer = inputCustomer();
    rentedCar.startDate = inputDate();
    rentedCar.endDate = inputDate();
    if (rentedCar.car.id != NOT_FOUND_CODE && !rentedCar.car.status) {
        if (save) {
            addCustomer(customerList, createCustomerNode(rentedCar.customer));
            saveCustomersToTextFile(customerList, CUSTOMER_DATA_STORAGE.c_str());
        }
    } else {
        cout << "Cannot create constract with car id: "<<rentedCar.car.id <<"Status: "<<rentedCar.car.status  << endl;
        rentedCar.car = Car{NOT_FOUND_CODE, "x", 0, 0, 0, false};
    }
    return rentedCar;
}

void inputRentedCars(RentedCarList &list, CarList carList, CustomerList customerList, string fileName) {
    cout << "Input number of rented car: ";
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        RentedCarNode *p;
        p = createRentedCarNode(inputRentedCar(carList, customerList, true));
        addRentedCar(list, p);
    }
    filterFirstRentedCarList(list);
    saveRentedCars(list, fileName.c_str());
}

void inputRentedCars(const string &fileNameRentedCar, const string &fileNameCar, const string &fileNameCustomer) {
    CarList carList = readCarsFromTextFile(fileNameCar.c_str());
    CustomerList customerList = readCustomersFromTextFile(fileNameCustomer.c_str());
    RentedCarList list = readRentedCars(fileNameRentedCar.c_str(), carList, customerList);
    inputRentedCars(list, carList, customerList, fileNameRentedCar);
}

void showTitleRentedCarTable() {
    cout << setw(10) << "ID" << " | "
         << setw(10) << "ID CAR" << " | "
         << left << setw(10) << "ID CUSTOMER" << " | "
         << setw(15) << "Start date" << " | "
         << setw(15) << "End date" << " | "
         << setw(10) << "Car name" << " | "
         << setw(10) << "Customer name" << endl;
}

void showRentedCar(RentedCar rentedCar) {
    cout << setw(10) << rentedCar.id << " | "
         << setw(10) << rentedCar.car.id << " | "
         << left << setw(11) << rentedCar.customer.id << " | "
         << setw(15) << rentedCar.startDate << " | "
         << setw(15) << rentedCar.endDate << " | "
         << setw(10) << rentedCar.car.nameCar << " | "
         << setw(10) << rentedCar.customer.nameCustomer << endl;
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

void showRentedCars(const string &fileRentedName, const string &fileCarName, const string &fileCustomerName) {
    CarList carList = readCarsFromTextFile(fileCarName.c_str());
    CustomerList customerList = readCustomersFromTextFile(fileCustomerName.c_str());
    RentedCarList list = readRentedCars(fileRentedName.c_str(), carList, customerList);
    showRentedCars(list);
}

RentedCarNode *findRentedCarByID(RentedCarList list,int id){
    RentedCarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void deleteRentedCarByID(const string &fileRentedName, const string &fileCarName, const string &fileCustomerName){
    CarList carList = readCarsFromTextFile(fileCarName.c_str());
    CustomerList customerList = readCustomersFromTextFile(fileCustomerName.c_str());
    RentedCarList list = readRentedCars(fileRentedName.c_str(), carList, customerList);
    cout<<"Input id to delete contract: ";
    int id;
    cin >> id;
    RentedCarNode *deleteRentedCarNode = findRentedCarByID(list,id);
    cout<<deleteRentedCarNode->data.id<<"Hereee"<<endl;
    updateStatusCar(carList, false,deleteRentedCarNode->data.id,fileCarName.c_str());
    deleteRentedCar(list, deleteRentedCarNode);
    saveRentedCars(list,fileRentedName.c_str());
}


//===============================================================================================================
int main() {
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
                showRentedCars(CONTRACT_DATA_STORAGE, CARS_DATA_STORAGE, CUSTOMER_DATA_STORAGE);
                break;
            case 6:
                inputCars(CARS_DATA_STORAGE);
                break;
            case 7:
                inputRentedCars(CONTRACT_DATA_STORAGE, CARS_DATA_STORAGE, CUSTOMER_DATA_STORAGE);
                break;
            case 8:
                deleteRentedCarByID(CONTRACT_DATA_STORAGE, CARS_DATA_STORAGE, CUSTOMER_DATA_STORAGE);
                break;
            case 9:
                sortCars(CARS_DATA_STORAGE);
                break;
            case 10:
                sortSeatCar(CARS_DATA_STORAGE);
                break;
            case 11:
                editSeatCar(CARS_DATA_STORAGE);
            case 0:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    return 0;
}


