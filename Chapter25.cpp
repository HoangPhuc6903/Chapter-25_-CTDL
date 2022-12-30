
#include<iostream>
using namespace std;

//in ra số E và T

void ZigZag(int n)
{
    //Tạo ra hai mảng gồm các giá trị 0 ;
    long long fact[1000] = { 0 };// tính mảng giai thừa
    long long zig[1000] = { 0 };//dùng để lưu giá trị của số 



    // gồm các giai thừa từ 0 dến n
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i;

    // n=0 và n=1
    zig[0] = 1;
    zig[1] = 1;



    // in ra số E và T
    for (int i = 2; i < n; i++)
    {
        long long sum = 0;

        for (int k = 0; k <= i - 1; k++)
        {
            // tính theo công thức:(n, k)*a(k)*a(n-k)
            sum += (fact[i - 1] / (fact[i - 1 - k] * fact[k]))
                * zig[k] * zig[i - 1 - k];
        }

        //Lưu giá trị  n chẵn là E n lẻ là T
        zig[i] = sum / 2;



    }
    int z = 1;
    cout << " Day so Euler: " << endl;
    for (int i = 0; i < n; i += 2)
    {
        cout << i << ":         ";

        cout << zig[i] << " " << endl;

    }
    cout << endl;
    cout << " Day so Tangent: " << endl;
    for (int i = 1; i < n; i += 2)
    {

        cout << i << ":         ";

        cout << zig[i] << " " << endl;;
    }



}
long long factorial(int n) // tính gia thừa
{
    if (n < 1)
        return 1;
    else
        return n * factorial(n - 1);
}
long long combination(int m, int  k)
{
    if (k <= m)
        return factorial(m) / (factorial(k) * factorial(m - k));
    else
        return 0;
}
double Bernoulli(int m) {
    if (m == 0)
        return 1;
    else {
        double t = 0;
        for (int k = 0; k < m; k++)
        {
            t += combination(m, k) * Bernoulli(k) / (m - k + 1);

        }
        return 1 - t;
    }
}
// Driver code
int main()
{
    int n = 20;

    // Function call
    ZigZag(n);
    cout << "Day so bernouli: " << endl;
    for (int i = 2; i < n; i += 2)
    {
        cout << i << ":           ";
        cout << Bernoulli(i) << endl;
    }
    return 0;
}