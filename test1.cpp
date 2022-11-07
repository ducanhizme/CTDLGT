//
// Created by ninhd on 11/7/2022.
//
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    time_t currentTime = time(0);
    tm *now = localtime(&currentTime);

    cout << (now->tm_year + 1900) << '-'
              << (now->tm_mon + 1) << '-'
              << now->tm_mday
              << "\n";

}