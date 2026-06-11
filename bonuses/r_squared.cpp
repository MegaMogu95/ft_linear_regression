#include <fstream>
#include <iostream>
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

double  mean(std::vector<double> v)
{
    if (v.size() == 0)
        return (0);
    double  sum = 0;
    for (size_t i = 0; i < v.size(); i++)
        sum += v[i];
    sum /= v.size();
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
        std::cerr << "Unable to open file error.txt\n";
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