#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Utils.hpp"

using namespace std;


int main()
{
    string inputFileName = "data.csv";
    double S = 0;
    size_t n = 0;
    double* w = nullptr;
    double* r = nullptr;

    if (!ImportVectors(inputFileName, S, n, w, r))
    {
        cerr<< "Something goes wrong with import"<< endl;
        return -1;
    }
    else
        cout<< "Import successful" << endl;
    cout << "S = " << fixed<< setprecision(2)<< S<<", n = " << n << endl;
    cout<< "w= "<< ArrayToString(n, w)<<endl;
    cout<< "r= "<< ArrayToString(n, r)<< endl;

    double dotProduct = DotProduct(n, w, r);
    cout<< setprecision(4) <<"Rate of return of the portfolio: "<< dotProduct << endl;
    cout<<setprecision(2) << "V: " << (1+dotProduct)*S << endl;

    string outputFileName = "result.txt";
    if (!ExportResult(outputFileName, S, n, w, r, dotProduct))
    {
        cerr<< "Something goes wrong with export"<< endl;
        return -1;
    }
    else
        cout<< "Export successful"<< endl;

    delete[] w;
    delete[] r;

    return 0;
}
