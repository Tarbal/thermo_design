#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include <fstream>
#include "/home/j_p124/cpp/heatflow/headers/systemheader.hpp"


using namespace std;

double 
	l_pt,
	position_PbTe,
	t,
	alpha_PbTe,
	kp,
	ka,
	position_Al,
	la_in,
	temp_Al,
	velocity,
	hc_in,
	n_tegs,
	numfin_in,
	temp_fin_guess,
	area_fin_in,
	efficiency_guess,
	n_flux,
	nkt,
	area_fin_out,
	numfin_out,
	hc_out,
	la_out,
	T_hot,
	T_cold,
	cross_section,
	pipe_diameter,
	pipe_length,
	particle_flow,
	price,
	cost_of_Al,
	cost_of_thermo,
	fin_thickness;

int n_TEGs;


void split(  std::string &line, char read_c, vector<string> &read_v)
{
        string::size_type k = 0;
        string::size_type j = line.find(read_c);

        while (j != string::npos)
        {
                read_v.push_back(line.substr(k, j - 1));
                k = ++j;
                j = line.find(read_c, j);

                if (j == string::npos)
                        read_v.push_back(line.substr(k, line.length()));
        }
}

double l_pt_func()
{
        std::string l_pt_pattern("l_pt");
        std::ifstream l_pt_in("options");

        if (!l_pt_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string l_pt_line;
        bool l_pt_found = false;
        while (getline(l_pt_in, l_pt_line))
        {
                if (std::string::npos != l_pt_line.find(l_pt_pattern))
                {
                        l_pt_found = true;
                        vector<string> l_pt_v;
                        split(l_pt_line, '=', l_pt_v);
                        istringstream ss(l_pt_v[1]);
                        ss >> l_pt;
                }
        }

        if (!l_pt_found)
                std::cout << '"' << l_pt_pattern << "\" not found.\n";
	return l_pt;
}




double position_PbTe_func()
{
        std::string position_PbTe_pattern("position_PbTe");
        std::ifstream position_PbTe_in("options");

        if (!position_PbTe_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string position_PbTe_line;
        bool position_PbTe_found = false;
        while (getline(position_PbTe_in, position_PbTe_line))
        {
                if (std::string::npos != position_PbTe_line.find(position_PbTe_pattern))
                {
                        position_PbTe_found = true;
                        vector<string> position_PbTe_v;
                        split(position_PbTe_line, '=', position_PbTe_v);
                        istringstream ss(position_PbTe_v[1]);
                        ss >> position_PbTe;
                }
        }

        if (!position_PbTe_found)
                std::cout << '"' << position_PbTe_pattern << "\" not found.\n";
	return position_PbTe;
}



double t_func()
{
        std::string t_pattern("t");
        std::ifstream t_in("options");

        if (!t_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string t_line;
        bool t_found = false;
        while (getline(t_in, t_line))
        {
                if (std::string::npos != t_line.find(t_pattern))
                {
                        t_found = true;
                        vector<string> t_v;
                        split(t_line, '=', t_v);
                        istringstream ss(t_v[1]);
                        ss >> t;
                }
        }

        if (!t_found)
                std::cout << '"' << t_pattern << "\" not found.\n";
	return t;
}



double alpha_PbTe_func()
{
        std::string alpha_PbTe_pattern("alpha_PbTe");
        std::ifstream alpha_PbTe_in("options");

        if (!alpha_PbTe_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string alpha_PbTe_line;
        bool alpha_PbTe_found = false;
        while (getline(alpha_PbTe_in, alpha_PbTe_line))
        {
                if (std::string::npos != alpha_PbTe_line.find(alpha_PbTe_pattern))
                {
                        alpha_PbTe_found = true;
                        vector<string> alpha_PbTe_v;
                        split(alpha_PbTe_line, '=', alpha_PbTe_v);
                        istringstream ss(alpha_PbTe_v[1]);
                        ss >> alpha_PbTe;
                }
        }

        if (!alpha_PbTe_found)
                std::cout << '"' << alpha_PbTe_pattern << "\" not found.\n";
        return alpha_PbTe;
}

double kp_func()
{
        std::string kp_pattern("kp");
        std::ifstream kp_in("options");

        if (!kp_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string kp_line;
        bool kp_found = false;
        while (getline(kp_in, kp_line))
        {
                if (std::string::npos != kp_line.find(kp_pattern))
                {
                        kp_found = true;
                        vector<string> kp_v;
                        split(kp_line, '=', kp_v);
                        istringstream ss(kp_v[1]);
                        ss >> kp;
                }
        }

        if (!kp_found)
                std::cout << '"' << kp_pattern << "\" not found.\n";
        return kp;
}

double ka_func()
{
        std::string ka_pattern("ka");
        std::ifstream ka_in("options");

        if (!ka_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string ka_line;
        bool ka_found = false;
        while (getline(ka_in, ka_line))
        {
                if (std::string::npos != ka_line.find(ka_pattern))
                {
                        ka_found = true;
                        vector<string> ka_v;
                        split(ka_line, '=', ka_v);
                        istringstream ss(ka_v[1]);
                        ss >> ka;
                }
        }

        if (!ka_found)
                std::cout << '"' << ka_pattern << "\" not found.\n";
        return ka;
}

double position_Al_func()
{
        std::string position_Al_pattern("position_Al");
        std::ifstream position_Al_in("options");

        if (!position_Al_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string position_Al_line;
        bool position_Al_found = false;
        while (getline(position_Al_in, position_Al_line))
        {
                if (std::string::npos != position_Al_line.find(position_Al_pattern))
                {
                        position_Al_found = true;
                        vector<string> position_Al_v;
                        split(position_Al_line, '=', position_Al_v);
                        istringstream ss(position_Al_v[1]);
                        ss >> position_Al;
                }
        }

        if (!position_Al_found)
                std::cout << '"' << position_Al_pattern << "\" not found.\n";
        return position_Al;
}

double la_in_func()
{
        std::string la_in_pattern("la_in");
        std::ifstream la_in_in("options");

        if (!la_in_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string la_in_line;
        bool la_in_found = false;
        while (getline(la_in_in, la_in_line))
        {
                if (std::string::npos != la_in_line.find(la_in_pattern))
                {
                        la_in_found = true;
                        vector<string> la_in_v;
                        split(la_in_line, '=', la_in_v);
                        istringstream ss(la_in_v[1]);
                        ss >> la_in;
                }
        }

        if (!la_in_found)
                std::cout << '"' << la_in_pattern << "\" not found.\n";
        return la_in;
}

double temp_Al_func()
{
        std::string temp_Al_pattern("temp_Al");
        std::ifstream temp_Al_in("options");

        if (!temp_Al_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string temp_Al_line;
        bool temp_Al_found = false;
        while (getline(temp_Al_in, temp_Al_line))
        {
                if (std::string::npos != temp_Al_line.find(temp_Al_pattern))
                {
                        temp_Al_found = true;
                        vector<string> temp_Al_v;
                        split(temp_Al_line, '=', temp_Al_v);
                        istringstream ss(temp_Al_v[1]);
                        ss >> temp_Al;
                }
        }

        if (!temp_Al_found)
                std::cout << '"' << temp_Al_pattern << "\" not found.\n";
        return temp_Al;
}

double velocity_func()
{
        std::string velocity_pattern("velocity");
        std::ifstream velocity_in("options");

        if (!velocity_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string velocity_line;
        bool velocity_found = false;
        while (getline(velocity_in, velocity_line))
        {
                if (std::string::npos != velocity_line.find(velocity_pattern))
                {
                        velocity_found = true;
                        vector<string> velocity_v;
                        split(velocity_line, '=', velocity_v);
                        istringstream ss(velocity_v[1]);
                        ss >> velocity;
                }
        }

        if (!velocity_found)
                std::cout << '"' << velocity_pattern << "\" not found.\n";
        return velocity;
}

double hc_in_func()
{
        std::string hc_in_pattern("hc_in");
        std::ifstream hc_in_in("options");

        if (!hc_in_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string hc_in_line;
        bool hc_in_found = false;
        while (getline(hc_in_in, hc_in_line))
        {
                if (std::string::npos != hc_in_line.find(hc_in_pattern))
                {
                        hc_in_found = true;
                        vector<string> hc_in_v;
                        split(hc_in_line, '=', hc_in_v);
                        istringstream ss(hc_in_v[1]);
                        ss >> hc_in;
                }
        }

        if (!hc_in_found)
                std::cout << '"' << hc_in_pattern << "\" not found.\n";
        return hc_in;
}

double n_tegs_func()
{
        std::string n_tegs_pattern("n_tegs");
        std::ifstream n_tegs_in("options");

        if (!n_tegs_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string n_tegs_line;
        bool n_tegs_found = false;
        while (getline(n_tegs_in, n_tegs_line))
        {
                if (std::string::npos != n_tegs_line.find(n_tegs_pattern))
                {
                        n_tegs_found = true;
                        vector<string> n_tegs_v;
                        split(n_tegs_line, '=', n_tegs_v);
                        istringstream ss(n_tegs_v[1]);
                        ss >> n_tegs;
                }
        }

        if (!n_tegs_found)
                std::cout << '"' << n_tegs_pattern << "\" not found.\n";
        return n_tegs;
}


double numfin_in_func()
{
        std::string numfin_in_pattern("numfin_in");
        std::ifstream numfin_in_in("options");

        if (!numfin_in_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string numfin_in_line;
        bool numfin_in_found = false;
        while (getline(numfin_in_in, numfin_in_line))
        {
                if (std::string::npos != numfin_in_line.find(numfin_in_pattern))
                {
                        numfin_in_found = true;
                        vector<string> numfin_in_v;
                        split(numfin_in_line, '=', numfin_in_v);
                        istringstream ss(numfin_in_v[1]);
                        ss >> numfin_in;
                }
        }

        if (!numfin_in_found)
                std::cout << '"' << numfin_in_pattern << "\" not found.\n";
        return numfin_in;
}

double temp_fin_guess_func()
{
        std::string temp_fin_guess_pattern("temp_fin_guess");
        std::ifstream temp_fin_guess_in("options");

        if (!temp_fin_guess_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string temp_fin_guess_line;
        bool temp_fin_guess_found = false;
        while (getline(temp_fin_guess_in, temp_fin_guess_line))
        {
                if (std::string::npos != temp_fin_guess_line.find(temp_fin_guess_pattern))
                {
                        temp_fin_guess_found = true;
                        vector<string> temp_fin_guess_v;
                        split(temp_fin_guess_line, '=', temp_fin_guess_v);
                        istringstream ss(temp_fin_guess_v[1]);
                        ss >> temp_fin_guess;
                }
        }

        if (!temp_fin_guess_found)
                std::cout << '"' << temp_fin_guess_pattern << "\" not found.\n";
        return temp_fin_guess;
}

double area_fin_in_func()
{
        std::string area_fin_in_pattern("area_fin_in");
        std::ifstream area_fin_in_in("options");

        if (!area_fin_in_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string area_fin_in_line;
        bool area_fin_in_found = false;
        while (getline(area_fin_in_in, area_fin_in_line))
        {
                if (std::string::npos != area_fin_in_line.find(area_fin_in_pattern))
                {
                        area_fin_in_found = true;
                        vector<string> area_fin_in_v;
                        split(area_fin_in_line, '=', area_fin_in_v);
                        istringstream ss(area_fin_in_v[1]);
                        ss >> area_fin_in;
                }
        }

        if (!area_fin_in_found)
                std::cout << '"' << area_fin_in_pattern << "\" not found.\n";
        return area_fin_in;
}

double efficiency_guess_func()
{
        std::string efficiency_guess_pattern("efficiency_guess");
        std::ifstream efficiency_guess_in("options");

        if (!efficiency_guess_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string efficiency_guess_line;
        bool efficiency_guess_found = false;
        while (getline(efficiency_guess_in, efficiency_guess_line))
        {
                if (std::string::npos != efficiency_guess_line.find(efficiency_guess_pattern))
                {
                        efficiency_guess_found = true;
                        vector<string> efficiency_guess_v;
                        split(efficiency_guess_line, '=', efficiency_guess_v);
                        istringstream ss(efficiency_guess_v[1]);
                        ss >> efficiency_guess;
                }
        }

        if (!efficiency_guess_found)
                std::cout << '"' << efficiency_guess_pattern << "\" not found.\n";
        return efficiency_guess;
}

double n_flux_func()
{
        std::string n_flux_pattern("n_flux");
        std::ifstream n_flux_in("options");

        if (!n_flux_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string n_flux_line;
        bool n_flux_found = false;
        while (getline(n_flux_in, n_flux_line))
        {
                if (std::string::npos != n_flux_line.find(n_flux_pattern))
                {
                        n_flux_found = true;
                        vector<string> n_flux_v;
                        split(n_flux_line, '=', n_flux_v);
                        istringstream ss(n_flux_v[1]);
                        ss >> n_flux;
                }
        }

        if (!n_flux_found)
                std::cout << '"' << n_flux_pattern << "\" not found.\n";
        return n_flux;
}

double nkt_func()
{
        std::string nkt_pattern("nkt");
        std::ifstream nkt_in("options");

        if (!nkt_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string nkt_line;
        bool nkt_found = false;
        while (getline(nkt_in, nkt_line))
        {
                if (std::string::npos != nkt_line.find(nkt_pattern))
                {
                        nkt_found = true;
                        vector<string> nkt_v;
                        split(nkt_line, '=', nkt_v);
                        istringstream ss(nkt_v[1]);
                        ss >> nkt;
                }
        }

        if (!nkt_found)
                std::cout << '"' << nkt_pattern << "\" not found.\n";
        return nkt;
}

double area_fin_out_func()
{
        std::string area_fin_out_pattern("area_fin_out");
        std::ifstream area_fin_out_in("options");

        if (!area_fin_out_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string area_fin_out_line;
        bool area_fin_out_found = false;
        while (getline(area_fin_out_in, area_fin_out_line))
        {
                if (std::string::npos != area_fin_out_line.find(area_fin_out_pattern))
                {
                        area_fin_out_found = true;
                        vector<string> area_fin_out_v;
                        split(area_fin_out_line, '=', area_fin_out_v);
                        istringstream ss(area_fin_out_v[1]);
                        ss >> area_fin_out;
                }
        }

        if (!area_fin_out_found)
                std::cout << '"' << area_fin_out_pattern << "\" not found.\n";
        return area_fin_out;
}

double numfin_out_func()
{
        std::string numfin_out_pattern("numfin_out");
        std::ifstream numfin_out_in("options");

        if (!numfin_out_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string numfin_out_line;
        bool numfin_out_found = false;
        while (getline(numfin_out_in, numfin_out_line))
        {
                if (std::string::npos != numfin_out_line.find(numfin_out_pattern))
                {
                        numfin_out_found = true;
                        vector<string> numfin_out_v;
                        split(numfin_out_line, '=', numfin_out_v);
                        istringstream ss(numfin_out_v[1]);
                        ss >> numfin_out;
                }
        }

        if (!numfin_out_found)
                std::cout << '"' << numfin_out_pattern << "\" not found.\n";
        return numfin_out;
}

double hc_out_func()
{
        std::string hc_out_pattern("hc_out");
        std::ifstream hc_out_in("options");

        if (!hc_out_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string hc_out_line;
        bool hc_out_found = false;
        while (getline(hc_out_in, hc_out_line))
        {
                if (std::string::npos != hc_out_line.find(hc_out_pattern))
                {
                        hc_out_found = true;
                        vector<string> hc_out_v;
                        split(hc_out_line, '=', hc_out_v);
                        istringstream ss(hc_out_v[1]);
                        ss >> hc_out;
                }
        }

        if (!hc_out_found)
                std::cout << '"' << hc_out_pattern << "\" not found.\n";
        return hc_out;
}

double la_out_func()
{
        std::string la_out_pattern("la_out");
        std::ifstream la_out_in("options");

        if (!la_out_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string la_out_line;
        bool la_out_found = false;
        while (getline(la_out_in, la_out_line))
        {
                if (std::string::npos != la_out_line.find(la_out_pattern))
                {
                        la_out_found = true;
                        vector<string> la_out_v;
                        split(la_out_line, '=', la_out_v);
                        istringstream ss(la_out_v[1]);
                        ss >> la_out;
                }
        }

        if (!la_out_found)
                std::cout << '"' << la_out_pattern << "\" not found.\n";
        return la_out;
}

double T_hot_func()
{
        std::string T_hot_pattern("T_hot");
        std::ifstream T_hot_in("options");

        if (!T_hot_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string T_hot_line;
        bool T_hot_found = false;
        while (getline(T_hot_in, T_hot_line))
        {
                if (std::string::npos != T_hot_line.find(T_hot_pattern))
                {
                        T_hot_found = true;
                        vector<string> T_hot_v;
                        split(T_hot_line, '=', T_hot_v);
                        istringstream ss(T_hot_v[1]);
                        ss >> T_hot;
                }
        }

        if (!T_hot_found)
                std::cout << '"' << T_hot_pattern << "\" not found.\n";
        return T_hot;
}

double T_cold_func()
{
        std::string T_cold_pattern("T_cold");
        std::ifstream T_cold_in("options");

        if (!T_cold_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string T_cold_line;
        bool T_cold_found = false;
        while (getline(T_cold_in, T_cold_line))
        {
                if (std::string::npos != T_cold_line.find(T_cold_pattern))
                {
                        T_cold_found = true;
                        vector<string> T_cold_v;
                        split(T_cold_line, '=', T_cold_v);
                        istringstream ss(T_cold_v[1]);
                        ss >> T_cold;
                }
        }

        if (!T_cold_found)
                std::cout << '"' << T_cold_pattern << "\" not found.\n";
        return T_cold;
}

double cross_section_func()
{
        std::string cross_section_pattern("cross_section");
        std::ifstream cross_section_in("options");

        if (!cross_section_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string cross_section_line;
        bool cross_section_found = false;
        while (getline(cross_section_in, cross_section_line))
        {
                if (std::string::npos != cross_section_line.find(cross_section_pattern))
                {
                        cross_section_found = true;
                        vector<string> cross_section_v;
                        split(cross_section_line, '=', cross_section_v);
                        istringstream ss(cross_section_v[1]);
                        ss >> cross_section;
                }
        }

        if (!cross_section_found)
                std::cout << '"' << cross_section_pattern << "\" not found.\n";
        return cross_section;
}

int n_TEGs_func()
{
        std::string n_TEGs_pattern("n_TEGs");
        std::ifstream n_TEGs_in("options");

        if (!n_TEGs_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string n_TEGs_line;
        bool n_TEGs_found = false;
        while (getline(n_TEGs_in, n_TEGs_line))
        {
                if (std::string::npos != n_TEGs_line.find(n_TEGs_pattern))
                {
                        n_TEGs_found = true;
                        vector<string> n_TEGs_v;
                        split(n_TEGs_line, '=', n_TEGs_v);
                        istringstream ss(n_TEGs_v[1]);
                        ss >> n_TEGs;
                }
        }

        if (!n_TEGs_found)
                std::cout << '"' << n_TEGs_pattern << "\" not found.\n";
        return n_TEGs;
}

double pipe_diameter_func()
{
        std::string pipe_diameter_pattern("pipe_diameter");
        std::ifstream pipe_diameter_in("options");

        if (!pipe_diameter_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string pipe_diameter_line;
        bool pipe_diameter_found = false;
        while (getline(pipe_diameter_in, pipe_diameter_line))
        {
                if (std::string::npos != pipe_diameter_line.find(pipe_diameter_pattern))
                {
                        pipe_diameter_found = true;
                        vector<string> pipe_diameter_v;
                        split(pipe_diameter_line, '=', pipe_diameter_v);
                        istringstream ss(pipe_diameter_v[1]);
                        ss >> pipe_diameter;
                }
        }

        if (!pipe_diameter_found)
                std::cout << '"' << pipe_diameter_pattern << "\" not found.\n";
        return pipe_diameter;
}

double pipe_length_func()
{
        std::string pipe_length_pattern("pipe_length");
        std::ifstream pipe_length_in("options");

        if (!pipe_length_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string pipe_length_line;
        bool pipe_length_found = false;
        while (getline(pipe_length_in, pipe_length_line))
        {
                if (std::string::npos != pipe_length_line.find(pipe_length_pattern))
                {
                        pipe_length_found = true;
                        vector<string> pipe_length_v;
                        split(pipe_length_line, '=', pipe_length_v);
                        istringstream ss(pipe_length_v[1]);
                        ss >> pipe_length;
                }
        }

        if (!pipe_length_found)
                std::cout << '"' << pipe_length_pattern << "\" not found.\n";
        return pipe_length;
}

double particle_flow_func()
{
        std::string particle_flow_pattern("particle_flow");
        std::ifstream particle_flow_in("options");

        if (!particle_flow_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string particle_flow_line;
        bool particle_flow_found = false;
        while (getline(particle_flow_in, particle_flow_line))
        {
                if (std::string::npos != particle_flow_line.find(particle_flow_pattern))
                {
                        particle_flow_found = true;
                        vector<string> particle_flow_v;
                        split(particle_flow_line, '=', particle_flow_v);
                        istringstream ss(particle_flow_v[1]);
                        ss >> particle_flow;
                }
        }

        if (!particle_flow_found)
                std::cout << '"' << particle_flow_pattern << "\" not found.\n";
        return particle_flow;
}

double price_func()
{
        std::string price_pattern("price");
        std::ifstream price_in("options");

        if (!price_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string price_line;
        bool price_found = false;
        while (getline(price_in, price_line))
        {
                if (std::string::npos != price_line.find(price_pattern))
                {
                        price_found = true;
                        vector<string> price_v;
                        split(price_line, '=', price_v);
                        istringstream ss(price_v[1]);
                        ss >> price;
                }
        }

        if (!price_found)
                std::cout << '"' << price_pattern << "\" not found.\n";
        return price;
}

double cost_of_Al_func()
{
        std::string cost_of_Al_pattern("cost_of_Al");
        std::ifstream cost_of_Al_in("options");

        if (!cost_of_Al_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string cost_of_Al_line;
        bool cost_of_Al_found = false;
        while (getline(cost_of_Al_in, cost_of_Al_line))
        {
                if (std::string::npos != cost_of_Al_line.find(cost_of_Al_pattern))
                {
                        cost_of_Al_found = true;
                        vector<string> cost_of_Al_v;
                        split(cost_of_Al_line, '=', cost_of_Al_v);
                        istringstream ss(cost_of_Al_v[1]);
                        ss >> cost_of_Al;
                }
        }

        if (!cost_of_Al_found)
                std::cout << '"' << cost_of_Al_pattern << "\" not found.\n";
        return cost_of_Al;
}

double cost_of_thermo_func()
{
        std::string cost_of_thermo_pattern("cost_of_thermo");
        std::ifstream cost_of_thermo_in("options");

        if (!cost_of_thermo_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string cost_of_thermo_line;
        bool cost_of_thermo_found = false;
        while (getline(cost_of_thermo_in, cost_of_thermo_line))
        {
                if (std::string::npos != cost_of_thermo_line.find(cost_of_thermo_pattern))
                {
                        cost_of_thermo_found = true;
                        vector<string> cost_of_thermo_v;
                        split(cost_of_thermo_line, '=', cost_of_thermo_v);
                        istringstream ss(cost_of_thermo_v[1]);
                        ss >> cost_of_thermo;
                }
        }

        if (!cost_of_thermo_found)
                std::cout << '"' << cost_of_thermo_pattern << "\" not found.\n";
        return cost_of_thermo;
}

double fin_thickness_func()
{
        std::string fin_thickness_pattern("fin_thickness");
        std::ifstream fin_thickness_in("options");

        if (!fin_thickness_in.is_open())
        {
                std::cout << "Unable to open file options\n";
        }

        std::string fin_thickness_line;
        bool fin_thickness_found = false;
        while (getline(fin_thickness_in, fin_thickness_line))
        {
                if (std::string::npos != fin_thickness_line.find(fin_thickness_pattern))
                {
                        fin_thickness_found = true;
                        vector<string> fin_thickness_v;
                        split(fin_thickness_line, '=', fin_thickness_v);
                        istringstream ss(fin_thickness_v[1]);
                        ss >> fin_thickness;
                }
        }

        if (!fin_thickness_found)
                std::cout << '"' << fin_thickness_pattern << "\" not found.\n";
        return fin_thickness;
}

