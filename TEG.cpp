#include <iostream>
#include <cmath>
#include "/home/j_p124/cpp/heatflow/headers/systemheader.hpp"
#include "/home/j_p124/cpp/heatflow/headers/integrateheader.hpp"


using std::cout;
using std::endl;

double single_TEG()
{

	double converge =1;
	minus_q = system_matrix();
	old_eta = eta();
//	cout << "first eta = " << old_eta << endl;
	while (converge > 1e-6)
	{
		minus_q = system_loop();
		eta_val = eta();
//		cout << "next eta = " << eta_val << endl;
		converge = fabs(eta_val - old_eta); 
//		cout << "delta_eta = " << converge << endl;
		old_eta = eta_val;
	}	
//	cout << "converge_final = " << converge << endl;
	cout << "eta_final = "  << eta_val << endl;
	minus_q = system_loop();
	double cross_section = cross_section_func();
	double power_absorbed = minus_q * cross_section;
	power_out = power_absorbed * eta_val;
//	cout << "power absorbed = " << power_absorbed << endl;
	cout << "final q = " << minus_q << endl;
	cout << "power_out = " << power_out << endl;

	return power_absorbed;	
}
