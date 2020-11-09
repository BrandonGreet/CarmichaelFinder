#include <iostream>
#include <math.h>

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int getBinarySize(int a)
{
    if (a == 0) return 0;
    if (a == 1) return 1;
    return getBinarySize(a / 2) + 1;
}

bool * getBinaryArray(int a, int size)
{
    bool * result = new bool[size];
    for (int i = size - 1; i >= 0; i--)
    {
        result[i] = a % 2;
        a /= 2;
    }
    return result;
}

bool isPrime(int a)
{
    for (int i = 2; i < a / 2; i++)
    {
        if (a % i == 0)
        {
            return false;
        }
    }
    return true;
}

long squareMultiply(int base, int power, int modulus)
{
    int powerSize = getBinarySize(power);
    bool * bits = getBinaryArray(power, powerSize);
    unsigned long long result = base;
    unsigned long long lmodulus = unsigned long(modulus);
    for (int bit = 1; bit < powerSize; bit++)
    {
        result = unsigned long long(pow(result, 2)) % lmodulus;
        if (*(bits+bit))
        {
            result = (result * base) % lmodulus;
        }
    }
    return result;
}

bool modifiedFermat(int power, int securityNumber)
{
    for (int i = 0; i < securityNumber; i++)
    {
        int base = rand() % (power - 3) + 2; //random range of 2 to power-1
        if (gcd(base, power) == 1)
        {
            int remainder = squareMultiply(base, power - 1, power);
            if (remainder != 1)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int minimumPower, maximumPower, securityNumber;
    std::cin >> minimumPower;
    std::cin >> maximumPower;
    std::cin >> securityNumber;
    for (int power = minimumPower; power < maximumPower; power++)
    {
        if (!isPrime(power) && modifiedFermat(power, securityNumber))
        {
            std::cout << power << std::endl;
        }
    }
}