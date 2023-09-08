#include <iostream>

double addition(double a, double b){
    return a + b;
}

double soustraction(double a, double b){
    return a - b;
}

double multiplication(double a, double b){
    return a * b;
}

double division(double a, double b){
    return a / b;
}


int main(){

    char operation;

    std::cout << "Entrez l'opération à effectuer (+, -, *, /): ";
    std::cin >> operation;
    double num1, num2;
    std::cout << "Entrez le premier nombre: ";
    std::cin >> num1;
    std::cout << "Entrez le second nombre: ";
    char test = 1;
    double resultat;

    if(operation == '+') {
        resultat = addition(num1, num2);
    } else if(operation == '-') {
        resultat = soustraction(num1, num2);
    } else if(operation == '*') {
        resultat = multiplication(num1, num2);
    } else if(operation == '/') {
        resultat = division(num1, num2); 
    } else {
        std::cout << "Opération invalide!";
        return 1; 
    }

    std::cout << "Le résultat est: " << resultat;
}
