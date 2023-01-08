#include <stdio.h>
#include <math.h>

double cND(double X) {
    double L, K, w ;
    double const a1 = 0.31938153, a2 = -0.356563782, a3 = 1.781477937;
    double const a4 = -1.821255978, a5 = 1.330274429;

    L = fabs(X);
    K = 1.0 / (1.0 + 0.2316419 * L);
    w = 1.0 - 1.0 / sqrt(2 * 3.14159265358979323846) * exp(-L *L / 2) * (a1 * K + a2 * K *K + a3 * pow(K,3) + a4 * pow(K,4) + a5 * pow(K,5));

    if (X < 0 ){
        w= 1.0 - w;
    }
    return w;
}

double d_j(int j, double S, double K, double r, double v, double T) {
    return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));
}

double call_price(double S, double K, double r, double v, double T) {
    return S * cND(d_j(1, S, K, r, v, T)) - K*exp(-r*T) * cND(d_j(2, S, K, r, v, T));
}

double put_price(double S, double K, double r, double v, double T) {
    return -S * cND(-d_j(1, S, K, r, v, T)) + K*exp(-r*T) * cND(-d_j(2, S, K, r, v, T));
}

int main(int argc, char** argv) {
    double S = 50.0;  // spot price
    double K = 52.0;  // strike price
    double r = 0.05;  // risk-free rate
    double v = 0.2;   // volatility
    double T = 0.5;   // time to expiration

    // calculate call and put prices
    double call = call_price(S, K, r, v, T);
    double put = put_price(S, K, r, v, T);

    printf("Call price: %.2f\n", call);
    printf("Put price: %.2f\n", put);

    return 0;
}


//Call price = S * cND(d1) - K * e^(-rT) * cND(d2)
