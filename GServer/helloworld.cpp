#include<iostream>
#include<string>

int main() {
    char arr[4] = {'a','b','c','d'};
    std::string h = std::to_string(arr[0]) + std::to_string(arr[1]);
    char* a = (char*) h.c_str();
    return 0;
}