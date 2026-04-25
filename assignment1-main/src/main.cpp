#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

// 1. Fungsi Tahun
int yearsOld(tm* inputTgl, tm* currentTgl) {
    int age = currentTgl->tm_year - inputTgl->tm_year;
    if (currentTgl->tm_mon < inputTgl->tm_mon || 
       (currentTgl->tm_mon == inputTgl->tm_mon && currentTgl->tm_mday < inputTgl->tm_mday)) {
        age--;
    }
    return age;
}

// 2. Fungsi Bulan
int monthsOld(tm* inputTgl, tm* currentTgl) {
    int totalMonths = (currentTgl->tm_year - inputTgl->tm_year) * 12 + (currentTgl->tm_mon - inputTgl->tm_mon);
    if (currentTgl->tm_mday < inputTgl->tm_mday) {
        totalMonths--;
    }
    return totalMonths;
}

// 3. Fungsi Nama Hari
string dayOfDate(tm* inputTgl) {
    mktime(inputTgl); 
    string days[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    if(inputTgl->tm_wday >= 0 && inputTgl->tm_wday <= 6) {
        return days[inputTgl->tm_wday];
    }
    return "Error";
}

int main() {
    time_t currentTime;
    time(&currentTime);
    tm* currentTgl = localtime(&currentTime);

    int yearinput, monthinput, dayinput;
    string inputstr;
    char ch;

    // Input format: DD/MM/YYYY (Contoh: 17/08/1945)
    if (!(cin >> inputstr)) return 0;
    
    stringstream ss(inputstr);
    ss >> dayinput >> ch >> monthinput >> ch >> yearinput;

    tm* inputTgl = new tm();
    inputTgl->tm_year = yearinput - 1900;
    inputTgl->tm_mon = monthinput - 1;
    inputTgl->tm_mday = dayinput;
    inputTgl->tm_hour = 0;
    inputTgl->tm_min = 0;
    inputTgl->tm_sec = 0;
    inputTgl->tm_isdst = -1;

    int ageOfYear = yearsOld(inputTgl, currentTgl);
    int ageOfMonth = monthsOld(inputTgl, currentTgl);
    string dayName = dayOfDate(inputTgl);

    cout << ageOfYear << " " << ageOfMonth << " " << dayName << endl;

    delete inputTgl;
    return 0;
}