#include <iostream>
#include <fstream>

int read_theta(double &theta0, double &theta1)
{
    std::ifstream   file("theta.txt");

    if (!file.is_open())
    {
        std::cerr << "Unable to open file theta.txt\n";
        return (-1);
    }
    file >> theta0;
    file >> theta1;
    file.close();
    return (0);
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

void    linear_reg_step(double &theta0, double &theta1, double rate)
{
    theta0++;
    theta1++;
    (void)rate;
}

int main()
{
    double  theta0;
    double  theta1;

    read_theta(theta0, theta1);
    linear_reg_step(theta0, theta1, 0);
    write_theta(theta0, theta1);
}