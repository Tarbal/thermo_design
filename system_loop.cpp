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

        double T_hot3 = T_hot_func();
        double T_cold3 = T_cold_func();
	double efficiency_guess3;
        double area_fin_in3 = area_fin_in_func();
        double numfin_in3 = numfin_in_func();
        double ka3 = ka_func();
        double la_in3 = la_in_func();
        double kp3 = kp_func();
        double l_pt3 = l_pt_func();
        double la_out3 = la_out_func();
	double hc_in3 = hc_in_func();
        double hc_out3 = hc_out_func();
        double area_fin_out3 = area_fin_out_func();
        double numfin_out3 = numfin_out_func();



double system_loop() 
{

        efficiency_guess3 = eta_val;

	Array2D<double> vals(5,5);

	vals[0][0] = hc_out3*area_fin_out3*numfin_out3;
	vals[0][1]=0;
	vals[0][2]=0;
	vals[0][3]=0;
	vals[0][4]=-(1-efficiency_guess3);
	vals[1][0]=ka3/la_in3;
	vals[1][1]=-ka3/la_in3;
	vals[1][2]=0;
	vals[1][3]=0;
	vals[1][4]=(1-efficiency_guess3);
	vals[2][0]=0;
	vals[2][1]=kp3/l_pt3;
	vals[2][2]=-kp3/l_pt3;
	vals[2][3]=0;
	vals[2][4]=(1-efficiency_guess3);
	vals[3][0]=0;
	vals[3][1]=0;
	vals[3][2]=ka3/la_out3;
	vals[3][3]=-ka3/la_out3;
	vals[3][4]=1;
	vals[4][0]=0;
	vals[4][1]=0;
	vals[4][2]=0;
	vals[4][3]=hc_in3*area_fin_in3*numfin_in3;
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
	vector_b[0] = T_cold3*hc_out3*area_fin_out3*numfin_out3;
	vector_b[1] = 0;
	vector_b[2] = 0;
	vector_b[3] = 0;
	vector_b[4] = T_hot3*hc_in3*area_fin_in3*numfin_in3;
	
	LU<double> lu(vals);
	Array1D<double> x(5,1);
	x = lu.solve(vector_b);
	T1 = x[0];
	T2 = x[1];
	T3 = x[2];
	T4 = x[3];
//	cout << "T1 = " << T1 << endl;
//	cout << "T4 = " << T4 << endl;
//	cout << "T3 = " << x[2] << endl;
  //    cout << "T2 = " << x[1] << endl;
	double dT = T3 - T2;
//	cout << "dT = " << dT << endl;
//	cout << "q in = " << x[4] << endl;
	return x[4];
}
