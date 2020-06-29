#include <iostream>
#include <stdio.h>
using namespace std;
double raznost(double, double);
double summa(double, double);
double delenie(double, double);
double umnojenie(double, double);
double operation (double(*)(double, double), double, double);
int main() {
double a, b;
double answer;
int nomer;
cin >> a >> b;
cout<< "vvedite nomer"<<endl;
cin>>nomer;
if (nomer>4 || nomer<1){
cout<< "operation not found"<<endl;
}
else {
switch (nomer){
case 1:
answer=operation(raznost, a, b);
cout << "raznost: " << answer << endl;
break;
case 2:
answer=operation(summa, a, b);
cout << "summa: " << answer << endl;
break;
case 3:
if (b!=0){
answer=operation(delenie, a, b);
cout << "delenie: " << answer << endl;}
else {cout << "delenie nevozmojno";}
break;
case 4:
answer=operation(umnojenie, a, b);
cout<< "umnojenie: " << answer << endl;
break;
}
return 0;
};}

