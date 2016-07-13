#ifndef systemheader_HPP_INCLUDED
#define systemheader_HPP_INCLUDED

extern double old_eta;
extern double eta_val;
extern double T2;
extern double T3;
extern double new_T_hot;
extern double power_out;
extern double minus_q;
extern double hc_out3;
extern double hc_in3;
//extern double T1;
//extern double T4;
void split();
double single_TEG();
double single_TEG2();
double system_matrix();
double system_matrix2();
double system_loop();
double system_loop2();
double T_hot_func();
double T_cold_func();
double hc_in_func();
double area_fin_in_func();
double numfin_in_func();
double efficiency_guess_func();
double ka_func();
double la_in_func();
double kp_func();
double l_pt_func();
double la_out_func();
double hc_out_func();
double area_fin_out_func();
double numfin_out_func();
double temp_Al_func();
double cross_section_func();
int n_TEGs_func();
double pipe_diameter_func();
double pipe_length_func();
double particle_flow_func();
double price_func();
double cost_of_Al_func();
double cost_of_thermo_func();
double finances();
double fin_thickness_func();

#endif // systemheader_HPP_INCLUDED

