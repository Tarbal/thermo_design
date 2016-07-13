#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "/home/j_p124/cpp/heatflow/headers/systemheader.hpp"
#include "/home/j_p124/cpp/heatflow/headers/integrateheader.hpp"


using std::cout;
using std::endl;


// Copyright John Petersen 2015 
// johnemilpeterseniii@gmail.com



double old_eta;
double eta_val;
double T2;
//double hc_in3;
//double hc_out3;
double T3;
double power_out;
double new_T_hot;
double minus_q;
double T1;
double T4;
const double boltzmann = 1.38065e-23;
const double pi = 3.1415927;

int main()
{
	int n_TEGs2 = n_TEGs_func();
	double cross_section2 = cross_section_func();
	double circumference = pi * pipe_diameter_func();
	double pipe_length2 = pipe_length_func();
        double pipe_area = pipe_length2 * circumference;

	if (n_TEGs2 * cross_section2 > pipe_area)
	{
		cout << "TOO MANY TEGS!!! CHECK YOUR MATH!!! " << endl;
		exit(0);
	}
	
        double subtract_power = single_TEG();
	cout << "hcout = " << hc_out3 << endl;
        cout << "hcin = " << hc_in3 << endl;
	double total_q_out = subtract_power * eta_val;
	double flow_N_boltz = boltzmann * particle_flow_func();
	double heat_power_start = 5 * flow_N_boltz * T_hot_func() / 2;
	double total_P_out = power_out;
	double difference = heat_power_start - subtract_power;
	cout << "starting heat = " << heat_power_start << endl;
	cout << "heat left = " << difference << endl;
	new_T_hot = 2 * difference /  flow_N_boltz / 5;
	cout << "new T = " << new_T_hot << endl;
	cout << "----------------------" << endl;

	for (int i = 0; i < n_TEGs2 - 1; i++)
	{
		double q_out = single_TEG2();
		total_P_out += power_out -10;
		difference -= q_out;
		cout << "heat left = " << difference << endl;
		new_T_hot = 2 * difference / flow_N_boltz / 5;
		cout << "new T = " << new_T_hot << endl;
		cout << "Total Power out = " << total_P_out << " W" << endl;
		cout << "-----------------------" << endl;
	}
	
	cout << "Total Power out = " << total_P_out << endl;
	double energy_per_year = total_P_out * 24 * 365.25 / 1000;
	cout << "Energy saved per year = " << energy_per_year << " kWh" << endl;
	double dollars_for_3_years = 3 * energy_per_year * price_func();
	cout << "$" << dollars_for_3_years << " saved per 3 years" << endl;
	double raw_mat_cost = finances();
	cout << "raw material cost = " << raw_mat_cost << endl;
	double throughputs = dollars_for_3_years - raw_mat_cost;
	cout << "Throughput = $" << throughputs << endl;
//	cout << "hc out = " << hc_out3 << endl;
//	cout << "hc in = " << hc_in3 << endl;

	FILE * summary;
	summary = fopen ("SUMMARY","w");
	fprintf (summary, "%f	%d	%f	%f	%f	%f\n", total_P_out, n_TEGs2, energy_per_year, dollars_for_3_years, raw_mat_cost, throughputs);

	fclose(summary);
	return 0;

}


