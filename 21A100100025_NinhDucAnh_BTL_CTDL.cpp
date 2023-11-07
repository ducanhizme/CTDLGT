#include "iostream"
#include "iomanip"
#include "cstring"

#define CARS_DATA_STORAGE "cars.txt"
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
    if (validDate){
        formattedDate = to_string(day) + "/" +
                        setw(2) << setfill('0') << to_string(month) << "/" <<
                        setw(4) << setfill('0') << to_string(year);
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
        fprintf(f, "%s %d %s %s\n",
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
    CustomerList list;
    initCustomerList(list);

    FILE *f = fopen(fileName, "r");
    if (f == nullptr) {
        cerr << "Error: Unable to open file for reading." << endl;
        return list; 
    }
    int n;
    if (fscanf(f, "%d", &n) != 1) {
        cerr << "Error: Failed to read the number of customers." << endl;
        fclose(f);
        return list;
    }
    for (int i = 0; i < n; i++) {
        Customer data;
        char nameCustomerStr[100];
        char phoneNumberStr[100];
        char addressStr[100];
        if (fscanf(f, "%s %d %s %s", nameCustomerStr, &data.age, phoneNumberStr, addressStr) == 4) {
            data.nameCustomer = nameCustomerStr;
            data.phoneNumber = phoneNumberStr;
            data.address = addressStr;
            CustomerNode *p = createCustomerNode(data);
            addCustomer(list, p);
        } else {
            cerr << "Error: Failed to read customer data." << endl;
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

Customer findCustomerByID(CustomerList list,int id){
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

int carListSize(CarNode *head) {
    int count = 0;
    CarNode *current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
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
        fprintf(f, "%s %d %d %.2f %s\n",
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
        cerr << "Error: Unable to open file for reading." << endl;
        return list;
    }
    int n;
    if (fscanf(f, "%d", &n) != 1) {
        cerr << "Error: Failed to read the number of cars." << endl;
        fclose(f);
        return list;
    }
    for (int i = 0; i < n; i++) {
        Car data;
        char nameCarStr[100];
        char statusStr[20];
        if (fscanf(f, "%s %d %d %f %s", nameCarStr, &data.capacityFuel, &data.mfgDate, &data.price, statusStr) == 5) {
            data.nameCar = nameCarStr;
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
         << setw(10) << car.capacityFuel << " | "
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

//Input and save into an existing file
void inputCars(string fileName) {
    CarList list = readCarsFromTextFile(fileName.c_str());
    inputCars(list);
}

Car findCarByID(CarList list,int id) {
    CarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == id) {
            return current->data;
        }
        current = current->next;
    }
    return Car{NOT_FOUND_CODE, "", 0, 0, false};
}

void updateStatusCar(CarList list, bool status, int id) {
    CarNode *current = list.head;
    while (current != nullptr) {
        if (current->data.id == id) {
            current->data.status = status;
        }
        current = current->next;
    }
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

int rentedCarListSize(RentedCarNode *head){
    int count = 0;
    RentedCarNode *current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void saveRentedCars(RentedCarList list, const char* fileName) {
    FILE* f = fopen(fileName, "w");
    if (f == nullptr) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    int n = rentedCarListSize(list.head);
    RentedCarNode* p = list.head;
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

RentedCarList readRentedCars(const char* fileName, CarList carList, CustomerList customerList) {
    RentedCarList list;
    initRentedCarList(list);

    FILE* f = fopen(fileName, "r");
    if (f == nullptr) {
        cerr << "Error: Unable to open file for reading." << endl;
        return list;
    }

    int n;
    if (fscanf(f, "%d", &n) != 1) {
        cerr << "Error: Failed to read the number of rented cars." << endl;
        fclose(f);
        return list;
    }

    for (int i = 0; i < n; i++) {
        RentedCar rentedCar;
        int carID, customerID;
        char startDateStr[100], endDateStr[100];
        char nameCarStr[100], nameCustomerStr[100];

        if (fscanf(f, "%d %d %s %s %s %s", &carID, &customerID, startDateStr, endDateStr, nameCarStr, nameCustomerStr) == 6) {
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
    cout << "Input Rented Car =================================";
    cout << "Input id car: ";
    int idCar;
    cin >> idCar;
    Car car = findCarByID(carList,idCar);
    rentedCar.car = car;
    cout << "Input id customer: ";
    int idCustomer;
    cin >> idCustomer;
    Customer customer = findCustomerByID(customerList,idCustomer);
    rentedCar.customer = customer;
    rentedCar.startDate = inputDate();
    rentedCar.endDate = inputDate();
    if (car.id != NOT_FOUND_CODE && customer.id !=NOT_FOUND_CODE) {
        return rentedCar;
    }else{
        cout<<"Something went wrong !!!"<<endl;
    }
}

void inputRentedCars(RentedCarList &list,CarList carList,CustomerList customerList) {
    cout << "Input file name to store cars data: ";
    char fileName[20];
    cin >> fileName;
    cout << "Input number of car: ";
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        RentedCarNode *p;
        p = createRentedCarNode(inputRentedCar(carList,customerList));
        addRentedCar(list, p);
    }
    saveRentedCars(list, fileName);
}

void inputRentedCars(string fileName,CarList carList,CustomerList customerList) {
    RentedCarList list = readRentedCars(fileName.c_str(),carList,customerList);
    inputRentedCars(list,carList,customerList);
}


int main() {

    return 0;

}


