#include <iostream>
#include <cmath>
#include "/home/j_p124/cpp/heatflow/headers/systemheader.hpp"

using std::cout;
using std::endl;

double finances()
	
{

	double cross_section6 = cross_section_func();	
	double numfin_in6 = numfin_in_func();
	double area_fin_in6 = area_fin_in_func();
	double width_in = sqrt(cross_section6);
	double fin_thickness_in = fin_thickness_func();
	double fin_volume_in = area_fin_in6 * numfin_in6 * fin_thickness_in;

//	cout << "fin volume in = " << fin_volume_in << endl;
	double numfin_out6 = numfin_out_func();
        double area_fin_out6 = area_fin_out_func();
        double width_out = sqrt(area_fin_out6);
        double fin_thickness_out = fin_thickness_func();
	double fin_volume_out = area_fin_out6 * numfin_out6 * fin_thickness_out;
//        cout << "fin volume out = " << fin_volume_out << endl;

	
	double Al_boundary_thickness_total = la_in_func() * cross_section6 + la_out_func() * cross_section6;
//	cout << "boundary volume = " << Al_boundary_thickness_total << endl;

	double Al_total_volume = fin_volume_in + fin_volume_out + Al_boundary_thickness_total;
//	cout << "total AL volume = " << Al_total_volume << endl;

	double Sum_Al_volume = Al_total_volume * n_TEGs_func();
	double Al_expense = Sum_Al_volume * cost_of_Al_func();
//	cout << "Al expense " << Al_expense << endl;

	double thermo_volume = l_pt_func() * cross_section6 * n_TEGs_func();
	double thermo_expense = thermo_volume * cost_of_thermo_func();

	double fans = 10 * n_TEGs_func();

	return Al_expense + thermo_expense +fans;

}
