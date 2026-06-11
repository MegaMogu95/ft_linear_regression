#include <iostream>
#include <fstream>
#include <vector>

int read_theta(double &theta0, double &theta1)
{
    std::ifstream   file("theta.txt");

    if (!file.is_open())
    {
        std::cerr << "Unable to open file theta.txt\n";
        return (-1);
    }
    if (!(file >> theta0) || !(file >> theta1))
    {
        std::cerr << "Wrong theta.txt file format\n";
        return (-1);
    }
    file.close();
    return (0);
}

double  estimate_price(double theta0, double theta1, double mileage)
{
    return (theta0 + theta1 * mileage);
}

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