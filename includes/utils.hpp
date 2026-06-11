#ifndef UTILS_HPP
# define UTILS_HPP

int read_data(std::vector<double> &milages, std::vector<double> &prices);

int read_theta(double &theta0, double &theta1);

double  estimate_price(double theta0, double theta1, double mileage);

#endif