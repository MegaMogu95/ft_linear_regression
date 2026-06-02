#include <iostream>
#include <fstream>
#include <vector>
#include "utils.hpp"

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

int write_theta(double theta0, double theta1)
{
    std::ofstream   file("theta.txt");

    if (!file.is_open())
    {
        std::cerr << "Unable to open file theta.txt\n";
        return (-1);
    }
    file << theta0;
    file << '\n';
    file << theta1;
    file.close();
    return (0);
}

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

void    linear_reg_step(std::vector<double> &mileages, std::vector<double> &prices, double &theta0, double &theta1, double rate)
{
    double  tmp0 = 0;
    double  tmp1 = 0;
    double  m = mileages.size();

    for (long unsigned int i = 0; i < m; i++)
        tmp0 += estimate_price(theta0, theta1, mileages[i]) - prices[i];
    tmp0 *= rate / m;
    for (long unsigned int i = 0; i < m; i++)
        tmp1 += mileages[i] / m * (estimate_price(theta0, theta1, mileages[i]) - prices[i]);
    tmp1 *= rate;
    theta0 -= tmp0;
    theta1 -= tmp1;
}

int main()
{
    double          theta0;
    double          theta1;
    std::vector<double> mileages;
    std::vector<double> prices;

    read_theta(theta0, theta1);
    read_data(mileages, prices);
    for (int i = 0; i < 1e7; i++)
        linear_reg_step(mileages, prices, theta0, theta1, 1e-12);
    write_theta(theta0, theta1);
}