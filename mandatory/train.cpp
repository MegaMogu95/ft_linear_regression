#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "utils.hpp"

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

void    linear_reg_step(std::vector<double> &mileages, std::vector<double> &prices, double &theta0, double &theta1, double rate)
{
    double  tmp0 = 0;
    double  tmp1 = 0;
    double  m = mileages.size();

    for (long unsigned int i = 0; i < m; i++)
    {
        tmp0 += estimate_price(theta0, theta1, mileages[i]) - prices[i];
        tmp1 += mileages[i] * (estimate_price(theta0, theta1, mileages[i]) - prices[i]);
    }
    tmp0 *= rate / m;
    tmp1 *= rate / m;
    theta0 -= tmp0;
    theta1 -= tmp1;
}

void    normalize(std::vector<double> &v, double min, double max)
{
    if (max == min)
        return;
    for (size_t i = 0; i < v.size(); i++)
    {
        if (max == min)
            v[i] = 0;
        else
            v[i] = (v[i] - min) / (max - min);
    }
}

void    get_normalized_theta(double &theta0, double &theta1, double mileages_min, double mileages_max, double prices_min, double prices_max)
{
    if (prices_max == prices_min)
    {
        theta0 = 0;
        theta1 = 0;
        return;
    }
    theta0 += theta1 * mileages_min - prices_min;
    theta0 /= prices_max - prices_min;
    theta1 *= (mileages_max - mileages_min) / (prices_max - prices_min);
}

void    get_unnormalized_theta(double &theta0, double &theta1, double mileages_min, double mileages_max, double prices_min, double prices_max)
{
    theta1 *=(prices_max - prices_min) / (mileages_max - mileages_min);
    theta0 = prices_min + theta0 * (prices_max - prices_min) - theta1 * mileages_min;
}

int main(int argc, char **argv)
{
    double              theta0;
    double              theta1;
    std::vector<double> mileages;
    std::vector<double> prices;
    int                 num_iter = 20000;

    if (argc > 1)
    {
        try
        {
            num_iter = std::stoi(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return (1);
        }
        if (num_iter < 0)
        {
            std::cerr << "Negative number of iterations\n";
            return (1);
        }
    }
    if (read_data(mileages, prices) || read_theta(theta0, theta1))
        return (1);
    if (mileages.size() == 0)
        return (1);
    double mileages_min = *min_element(mileages.begin(), mileages.end());
    double mileages_max = *max_element(mileages.begin(), mileages.end());
    double prices_min = *min_element(prices.begin(), prices.end());
    double prices_max = *max_element(prices.begin(), prices.end());
    if (mileages_min == mileages_max)
    {
        std::cerr << "error: mileages_max = mileages_min\n";
        return (1);
    }
    get_normalized_theta(theta0, theta1, mileages_min, mileages_max, prices_min, prices_max);
    normalize(mileages, mileages_min, mileages_max);
    normalize(prices, prices_min, prices_max);
    for (int i = 0; i < num_iter; i++)
        linear_reg_step(mileages, prices, theta0, theta1, 0.1);
    get_unnormalized_theta(theta0, theta1, mileages_min, mileages_max, prices_min, prices_max);
    write_theta(theta0, theta1);
}