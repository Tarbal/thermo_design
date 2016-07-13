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

        double T_cold4 = T_cold_func();
	double efficiency_guess4;
        double area_fin_in4 = area_fin_in_func();
        double numfin_in4 = numfin_in_func();
        double ka4 = ka_func();
        double la_in4 = la_in_func();
        double kp4 = kp_func();
        double hc_out4 = hc_out_func();
	double hc_in4 = hc_in_func();
        double l_pt4 = l_pt_func();
        double la_out4 = la_out_func();
        double area_fin_out4 = area_fin_out_func();
        double numfin_out4 = numfin_out_func();



double system_matrix2() 
{

	double T_hot4 = new_T_hot;

//	cout << "CHECK = " << T_hot4 << endl;
        efficiency_guess4 = eta_val;

	Array2D<double> vals(5,5);

	vals[0][0] = hc_out4*area_fin_out4*numfin_out4;
	vals[0][1]=0;
	vals[0][2]=0;
	vals[0][3]=0;
	vals[0][4]=-(1-efficiency_guess4);
	vals[1][0]=ka4/la_in4;
	vals[1][1]=-ka4/la_in4;
	vals[1][2]=0;
	vals[1][3]=0;
	vals[1][4]=(1-efficiency_guess4);
	vals[2][0]=0;
	vals[2][1]=kp4/l_pt4;
	vals[2][2]=-kp4/l_pt4;
	vals[2][3]=0;
	vals[2][4]=(1-efficiency_guess4);
	vals[3][0]=0;
	vals[3][1]=0;
	vals[3][2]=ka4/la_out4;
	vals[3][3]=-ka4/la_out4;
	vals[3][4]=1;
	vals[4][0]=0;
	vals[4][1]=0;
	vals[4][2]=0;
	vals[4][3]=hc_in4*area_fin_in4*numfin_in4;
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
	vector_b[0] = T_cold4*hc_out4*area_fin_out4*numfin_out4;
	vector_b[1] = 0;
	vector_b[2] = 0;
	vector_b[3] = 0;
	vector_b[4] = T_hot4*hc_in4*area_fin_in4*numfin_in4;
	
	LU<double> lu(vals);
	Array1D<double> x(5,1);
	x = lu.solve(vector_b);
	T1 = x[0];
	T2 = x[1];
	T3 = x[2];
	T4 = x[3];
//	cout << "T3 = " << x[2] << endl;
//      cout << "T2 = " << x[1] << endl;
	double dT = T3 - T2;
	cout << "dT = " << dT << endl;
//	cout << "q in = " << x[4] << endl;
	return x[4];
}
