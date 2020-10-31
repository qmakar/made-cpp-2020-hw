#pragma once
#include <vector>
#include <iostream>

namespace task {

double operator*(const std::vector<double>& v1, const std::vector<double>& v2) {
    if (v1.size() != v2.size()) {
        return 0;
    }
    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

std::vector<double> operator%(const std::vector<double>& v1, const std::vector<double>& v2) {
    if (v1.size() != v2.size() || v1.size() != 3) {
        return std::vector<double>(1, 0);
    }
    std::vector<double> tmp(3, 0);
    tmp[0] = v1[1] * v2[2] - v1[2] * v2[1];
    tmp[1] = v1[2] * v2[0] - v1[0] * v2[2];
    tmp[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return tmp;
}

std::vector<double> operator+(const std::vector<double>& v1, const std::vector<double>& v2) {
    if (v1.size() != v2.size()) {
        return std::vector<double>(1, 0);
    }
    std::vector<double> tmp(v1.size(), 0);
    for (int i = 0; i < v1.size(); i++) {
        tmp[i] = v1[i] + v2[i];
    }
    return tmp;
}

std::vector<double> operator-(const std::vector<double>& v1, const std::vector<double>& v2) {
    if (v1.size() != v2.size()) {
        return std::vector<double>(1, 0);
    }
    std::vector<double> tmp(v1.size(), 0);
    for (int i = 0; i < v1.size(); i++) {
        tmp[i] = v1[i] - v2[i];
    }
    return tmp;
}

std::vector<double> operator-(const std::vector<double>& v) {
    std::vector<double> tmp(v.size(), 0);
    for (int i = 0; i < v.size(); i++) {
        tmp[i] = -v[i];
    }
    return tmp;
}

std::vector<double> operator+(const std::vector<double>& v) {
    std::vector<double> tmp(v.size(), 0);
    for (int i = 0; i < v.size(); i++) {
        tmp[i] = v[i];
    }
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const std::vector<double>& v) {
    if (v.size() == 0)
        return os;
    
    os << v[0];
    for (int i = 1; i < v.size(); i++) {
        os << " " << v[i];
    }
    os << '\n';
    return os;
}

std::istream & operator>>(std::istream &is, std::vector<double>& v) {
    int n;
    is >> n;
    
    v.clear();
    double value;
    for (int i = 0; i < n; i++) {
        is >> value;
        v.push_back(value);
    }
    
    return is;
}

void reverse(std::vector<double>& v) {
    double tmp;
    int n = v.size();
    for (int i = 0; i < n / 2; i++) {
        tmp = v[i];
        v[i] = v[n - i - 1];
        v[n - i - 1] = tmp;
    }
}

double length(const std::vector<double>& v) {
    double len = 0;
    for (int i = 0; i < v.size(); i++) {
        len += v[i] * v[i];
    }
    len = sqrt(len);
    return len;
}

bool operator||(const std::vector<double>& v1, const std::vector<double>& v2) {
    if (v1.size() != v2.size()) {
        return false;
    }
    double len1 = length(v1);
    double len2 = length(v2);
    double dot_product = v1 * v2;
    double cosinus = abs(dot_product / (len1 * len2));
    if (0.9999 < cosinus && cosinus < 1.0001) {
        return true;
    }
    return false;
}

bool operator&&(const std::vector<double>& v1, const std::vector<double>& v2) {
    if (v1.size() != v2.size()) {
        return false;
    }
    double len1 = length(v1);
    double len2 = length(v2);
    double dot_product = v1 * v2;
    double cosinus = dot_product / (len1 * len2);
    if (0.9999 < cosinus && cosinus < 1.0001) {
        return true;
    }
    return false;
}

std::vector<int> operator|(const std::vector<int>& v1, const std::vector<int>& v2) {
    if (v1.size() != v2.size()) {
        return std::vector<int>(1, 0);
    }
    std::vector<int> tmp(v1.size(), 0);
    for (int i = 0; i < v1.size(); i++) {
        tmp[i] = v1[i] | v2[i];
    }
    return tmp;
}

std::vector<int> operator&(const std::vector<int>& v1, const std::vector<int>& v2) {
    if (v1.size() != v2.size()) {
        return std::vector<int>(1, 0);
    }
    std::vector<int> tmp(v1.size(), 0);
    for (int i = 0; i < v1.size(); i++) {
        tmp[i] = v1[i] & v2[i];
    }
    return tmp;
}

}
