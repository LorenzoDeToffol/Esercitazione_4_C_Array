#include "Utils.hpp"

#include "iostream"
#include "fstream"
#include "sstream"
#include <vector>
#include <iomanip>

using namespace std;

bool ImportVectors(const string& inputFilePath,
                   double& S,
                   size_t& n,
                   double*& w,
                   double*& r)
{
    // Open File
    ifstream file;
    file.open(inputFilePath);

    if (file.fail())
    {
        cerr<< "file open failed"<< endl;
        return false;
    }
    string line;

    getline(file, line); // 1 riga

    istringstream ss1(line);
    char temp1;
    ss1 >> temp1 >>  temp1 >> S;

    getline(file, line); // 2 riga
    istringstream ss2(line);
    char temp2;
    ss2 >> temp2 >>  temp2 >> n;

    getline(file, line); //3 riga da saltare

    w = new double[n];
    r = new double[n];

    unsigned int i = 0;

    while (getline(file, line))//altre righe
    {
        istringstream ss3(line);
        char temp3;
        ss3 >> w[i] >> temp3 >> r[i];

        i++;
    }

    file.close();




    return true;
}


double DotProduct(const size_t& n,
                        const double* const& w,
                        const double* const& r)
{
    double dotProduct = 0;
    for (unsigned int i = 0; i < n; i++)
        dotProduct += w[i] * r[i];

    return dotProduct;
}

string ArrayToString(const size_t& n,
                     const double* const& w)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString << w[i] << " ";
    toString << "]";

    return toString.str();
}

bool ExportResult(const string& outputFilePath,
                const double& S,
                const size_t& n,
                const double* const& w,
                const double* const& r,
                const double& dotProduct)
{
    ofstream file;
    file.open(outputFilePath);

    if (file.fail())
    {
        cerr << "File open failed" << endl;
        return false;
    }

    file << "S = " << fixed<< setprecision(2)<< S<<", n = " << n << endl;


    file << "w = [ ";
    for (unsigned int i = 0; i < n; ++i)
    {
        file << w[i];
        if (i < n - 1)
        {
            file << " ";
        }
    }
    file << " ]" << endl;

    file << "r = [ ";
    for (unsigned int i = 0; i < n; ++i)
    {
        file << r[i];
        if (i < n - 1)
        {
            file << " ";
        }
    }
    file << " ]" << endl;
    file << setprecision(4)<< "Rate of return of the portfolio: " << dotProduct << endl;
    file  << "V: " << setprecision(2)<< (1+dotProduct)*S << endl;

    file.close();

    return true;

}
