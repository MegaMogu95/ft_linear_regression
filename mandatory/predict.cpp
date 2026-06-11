#include <iostream>
#include <fstream>
#include <vector>
#include "utils.hpp"

int main()
{
    double  mileage;
    double  theta0;
    double  theta1;

    if (read_theta(theta0, theta1))
        return (1);
    std::cout << "Please enter a mileage:\n";
    if (!(std::cin >> mileage))
    {
        std::cerr << "Error reading mileage\n";
        return (1);
    }
    std::cout << estimate_price(theta0, theta1, mileage) << std::endl;
}