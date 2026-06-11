#include <fstream>
#include <iostream>
#include <vector>
#include "utils.hpp"

double  mean(std::vector<double> &v)
{
    if (v.size() == 0)
        return (0);
    double  sum = 0;
    for (size_t i = 0; i < v.size(); i++)
        sum += v[i];
    return (sum / v.size());
}

double  ss_tot(std::vector<double> &prices)
{
    double  ret = 0;
    double  m = mean(prices);

    for (size_t i = 0; i < prices.size(); i++)
        ret += (prices[i] - m) * (prices[i] - m);
    return (ret);
}

double  ss_res(std::vector<double> &mileages, std::vector<double> &prices, double theta0, double theta1)
{
    double  ret = 0;

    for (size_t i = 0; i < mileages.size(); i++)
        ret += (prices[i] - estimate_price(theta0, theta1, mileages[i])) * (prices[i] - estimate_price(theta0, theta1, mileages[i]));
    return (ret);
}

double  r_squared(std::vector<double> &mileages, std::vector<double> &prices, double theta0, double theta1)
{
    return (1 - ss_res(mileages, prices, theta0, theta1) / ss_tot(prices));
}

int main()
{
    std::ofstream out("r_squared.txt");
    std::vector<double> mileages;
    std::vector<double> prices;
    double  theta0;
    double  theta1;
    double  rs;

    if (!out.is_open())
    {
        std::cerr << "Unable to open file r_squared.txt\n";
        return (-1);
    }
    if (read_data(mileages, prices))
        return (1);
    if (read_theta(theta0, theta1))
        return (1);
    rs = r_squared(mileages, prices, theta0, theta1);
    out << rs << "\n";
    std::cout << "The coefficient of determination (R^2) for the current value of theta0 and theta1 is ";
    std::cout << rs << "\n";
    if (rs < 0)
        std::cout << "The prediction is worse that guessing the average of the sample\n";
    else
        std::cout << "The remaining unexplained variance is " << 1 - rs << "\n";
    out.close();
}