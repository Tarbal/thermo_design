#include <iostream>
#include <cmath>
#include "/home/j_p124/cpp/heatflow/headers/systemheader.hpp"

using std::cout;
using std::endl;


double trapezoid(double a, double b, int nsub, double (*f)(double) )
{
        // initialize the partial sum to be f(a)+f(b) and
        // deltaX to be the step size using nsub subdivisions
        double psum = f(a)+f(b);
        double deltaX = (b-a)/nsub;

        // increment the partial sum
        for(int index=1;index<nsub;index++)
        {
                psum = psum + 2.0*f(a+index*deltaX);
        }

        // multiply the sum by the constant deltaX/2.0
        psum = (deltaX/2.0)*psum;


        // return approximation
        return psum;

}



double kappa_func_T(double T)
{
	return 0.91729 - 0.01301 * T + 7.6966e-05 * pow(T,2) - 9.1441e-08 * pow(T,3) + 5.9423e-11 * pow(T,4);
}

double Seebeck_func_T(double T)
{
        return -9.5702e-05 + 1.8609e-06 * T - 3.4475e-09 * pow(T,2) + 2.6944e-12 * pow(T,3) - 7.9181e-16 * pow(T,4);
}

double rho_func_T(double T)
{
        return 1.6248e-05 - 5.9262e-08 * T + 8.8471e-11 * pow(T,2) - 6.0138e-14 * pow(T,3) + 1.5342e-17 * pow(T,4);
}

double ZTeng_func()
{
	double kappaT = trapezoid(T2,T3,10000,&kappa_func_T);
	double SeebeckT = trapezoid(T2,T3,10000,&Seebeck_func_T);
	double rhoT = trapezoid(T2,T3,10000,&rho_func_T);
	double dT = T3 - T2;
	double ZTeng = dT * (pow(SeebeckT,2)) / (kappaT * rhoT);
//	cout << ZTeng << endl;
	return ZTeng;   // 1.1839
}


double Wj()
{
	double integ_integ_rho = 5.114e-19 * pow(T2,6) - 3.0069e-15 * pow(T2,5) + 7.372583333e-12 * pow(T2,4) - 0.000000009877 * pow(T2,3) + 0.000008124 * pow(T2,2) - 3.0684e-18 * T2 * pow(T3,5) + 1.50345e-14 * T2 * pow(T3,4) - 2.949033333e-11 * T2 * pow(T3,3) + 0.000000029631 * T2 * pow(T3,2) - 0.000016248 * T2 * T3 + 2.557e-18 * pow(T3,6) - 1.20276e-14 * pow(T3,5) + 2.211775e-11 * pow(T3,4) - 0.000000019754 * pow(T3,3) + 0.000008124 * pow(T3,2);   //trapezoid(T2,T3,10000,&rho_func_T_integrated);
//	cout << "integ_integ_rho = " << integ_integ_rho << endl;
	double integ_rho_times_delT = (T3 - T2) * trapezoid(T2,T3,10000,&rho_func_T);
	double Wj_var = integ_integ_rho / integ_rho_times_delT;
//	cout << "Wj_var = " << Wj_var << endl;
	return Wj_var; // 0.425267

}

double Tau(double T) // no value
{
	return (-3.1672400000000002e-15 * pow(T,4) + 8.0832000000000001e-12 * pow(T,3) - 6.8949999999999999e-9 * pow(T,2) + 1.8609e-6 * T);
}


double Wt()
{
	double Tau_integ_integ = - 1.055746667e-16 * pow(T2,6) + 4.0416e-13 * pow(T2,5) - 0.0000000005745833333 * pow(T2,4) + 0.00000031015 * pow(T2,3) + 6.33448e-16 * T2 * pow(T3,5) - 2.0208e-12 * T2 * pow(T3,4) + 0.000000002298333333 * T2 * pow(T3,3) - 0.00000093045 * T2 * pow(T3,2) - 5.278733333e-16 * pow(T3,6) + 1.61664e-12 * pow(T3,5) - 0.00000000172375 * pow(T3,4) + 0.0000006203 * pow(T3,3); //trapezoid(T2,T3,10000,&Tau_func_T_integrated);
//	cout << "integ_integ_Tau = " << Tau_integ_integ << endl;
	double T_times_Tau_integ = (T3 - T2) * trapezoid(T2,T3,10000,&Tau);
	double Wt_var = Tau_integ_integ / T_times_Tau_integ;
	return Wt_var; // -0.7544
}

double S_integrate() 
{
	double S_int_val = trapezoid(T2,T3,10000,&Seebeck_func_T);
//	cout << "S integrated = " << S_int_val << endl; // 0.064519
	return S_int_val;

}

double alpha0()
{
	double SeebeckT2 = trapezoid(T2,T3,10000,&Seebeck_func_T);
	double carnot = (T3 - T2) / T3;
	double S_of_T3 = Seebeck_func_T(T3);
	double wt = Wt();
	double integrated_Tau = trapezoid(T2,T3,10000,&Tau);
	double alpha0_var = (T3 * carnot * S_of_T3 / SeebeckT2) - (wt * carnot * integrated_Tau / SeebeckT2);
//	cout << "alpha0_var = " << alpha0_var << endl;
	return alpha0_var; // 1.00126
}


double alpha1()
{
	double carnot2 = (T3 - T2) / T3;
	double wj = Wj();
	double alpha0_var2 = alpha0();
	double alpha1_var = alpha0_var2 - wj * carnot2;
//	cout << "alpha1_var = " << alpha1_var << endl;  // 0.8377
	return alpha1_var;
}

double alpha2()
{
        double carnot3 = (T3 - T2) / T3;
        double wj = Wj();
        double alpha0_var3 = alpha0();
        double alpha2_val = alpha0_var3 - 2 * wj * carnot3;
//	cout << "alpha2 = " << alpha2_val << endl; // 0.674133
	return alpha2_val;
}

double eta()
{
	double carnot3 = (T3 - T2) / T3;
	double ZTeng2 = ZTeng_func();
	double alpha1_var = alpha1();
	double alpha0_var = alpha0();
	double alpha2_var = alpha2();
	double zteng_times_alpha1 = ZTeng2 * alpha1_var;
	double eta_var = carnot3 * (sqrt(1 + zteng_times_alpha1 / carnot3) -1) / (alpha0_var * sqrt(1 + zteng_times_alpha1 / carnot3) + alpha2_var);
	return eta_var;
	
}

/*
int main()
{
	eta();
}
*/
