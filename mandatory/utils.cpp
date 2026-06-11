#include <iostream>
#include <fstream>
#include <vector>

int read_data(std::vector<double> &milages, std::vector<double> &prices)
{
    std::ifstream data("data.csv");
    if (!data.is_open())
    {
        std::cerr << "Unable to open file data.csv\n";
        return (-1);
    }
    std::string line;
    std::getline(data, line);
    while (true)
    {
        double  km;
        if (!(data >> km))
            return (0);
        char c;
        if (!(data >> c) || c != ',')
            return (0);
        double  price;
        if (!(data >> price))
            return (0);
        milages.push_back(km);
        prices.push_back(price);
    }
    return (0);
}

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