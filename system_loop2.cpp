#include <iostream>
#include <cmath>
#include "/home/j_p124/cpp/heatflow/headers/systemheader.hpp"
#include </home/j_p124/tnt/tntheaders/tnt_array1d.h>
#include </home/j_p124/tnt/tntheaders/tnt_array2d.h>
#include </home/j_p124/tnt/jamaheaders/jama_lu.h>
#include <vector>


using std::cout;
using namespace TNT;
using namespace JAMA;

        double T_hot5 = new_T_hot;
        double T_cold5 = T_cold_func();
	double efficiency_guess5;
        double area_fin_in5 = area_fin_in_func();
        double numfin_in5 = numfin_in_func();
        double ka5 = ka_func();
        double la_in5 = la_in_func();
        double hc_out5 = hc_out_func();
	double hc_in5 = hc_in_func();
        double kp5 = kp_func();
        double l_pt5 = l_pt_func();
        double la_out5 = la_out_func();
        double area_fin_out5 = area_fin_out_func();
        double numfin_out5 = numfin_out_func();



double system_loop2() 
{


        double T_hot5 = new_T_hot;
//        hc_in3 = minus_q / (T_hot5 - T1);
//	cout << "T4 = " << T4 << endl;
  //      hc_out3 = minus_q * (1 - old_eta) / (T4 - T_cold5);

        efficiency_guess5 = eta_val;

	Array2D<double> vals(5,5);

	vals[0][0] = hc_out5*area_fin_out5*numfin_out5;
	vals[0][1]=0;
	vals[0][2]=0;
	vals[0][3]=0;
	vals[0][4]=-(1-efficiency_guess5);
	vals[1][0]=ka5/la_in5;
	vals[1][1]=-ka5/la_in5;
	vals[1][2]=0;
	vals[1][3]=0;
	vals[1][4]=(1-efficiency_guess5);
	vals[2][0]=0;
	vals[2][1]=kp5/l_pt5;
	vals[2][2]=-kp5/l_pt5;
	vals[2][3]=0;
	vals[2][4]=(1-efficiency_guess5);
	vals[3][0]=0;
	vals[3][1]=0;
	vals[3][2]=ka5/la_out5;
	vals[3][3]=-ka5/la_out5;
	vals[3][4]=1;
	vals[4][0]=0;
	vals[4][1]=0;
	vals[4][2]=0;
	vals[4][3]=hc_in5*area_fin_in5*numfin_in5;
	vals[4][4]=1;

/*	for (int i = 0; i < 5; i++)
	{
		cout << vals[0][i] << "  ";
	}
	cout << endl;
	for (int j = 0; j < 5; j++)
        {
                cout << vals[1][j] << "  ";
        }
	cout << endl;
	for (int i = 0; i < 5; i++)
        {
                cout << vals[2][i] << "  ";
        }
	cout << endl;
	for (int i = 0; i < 5; i++)
        {
                cout << vals[3][i] << "  ";
        }
	cout << endl;
	for (int i = 0; i < 5; i++)
        {
                cout << vals[4][i] << "  ";
        }
	cout << endl;
*/

	Array1D<double> vector_b(5,1);
	vector_b[0] = T_cold5*hc_out5*area_fin_out5*numfin_out5;
	vector_b[1] = 0;
	vector_b[2] = 0;
	vector_b[3] = 0;
	vector_b[4] = T_hot5*hc_in5*area_fin_in5*numfin_in5;
	
	LU<double> lu(vals);
	Array1D<double> x(5,1);
	x = lu.solve(vector_b);
	T1 = x[0];
	T2 = x[1];
	T3 = x[2];
	T4 = x[4];
//	cout << "T3 = " << x[2] << endl;
//	cout << "T2 = " << x[1] << endl;
	double dT = T3 - T2;
//	cout << "dT = " << dT << endl;
//
//	cout << "q in = " << x[4] << endl;
	return x[4];
}
