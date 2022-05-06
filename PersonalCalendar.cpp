#include <iostream>
#include "Meeting.cpp"

using namespace std;

int main(){
    MyDate::initializationAndValidationTest();
    MyHour::initializationTestPositive();
    Meeting::initializationTest();
}
