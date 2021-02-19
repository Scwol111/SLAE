#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include "../includes/FPI.hpp"
#include "../includes/Seidel.hpp"

struct Data
{
	bool input_data;
	bool input_start;
	bool get_epsi;
	bool full;
	int		epsi;
};

void	fill_data(Data &d)
{
	d.input_data = false;
	d.input_start = false;
	d.get_epsi = false;
	d.full = false;
	d.epsi = 5;
}

void	ft_parse(std::string const &str, Data &d)
{
	if (d.get_epsi)
	{
		d.epsi = std::stoi(str);
		d.get_epsi = false;
	}
	if (str == " --input ")
		d.input_data = true;
	if (str == " --start ")
		d.input_start = true;
	if (str == " --epsilon")
		d.get_epsi = true;
	if (str == " --full ")
		d.full = true;
}

double count_epsilon(int x)
{
	double res = 1;
	for (int i = 0; i < x; i++)
		res /= 10;
	return res;
}

int main(int argc, char **argv)
{
	Data dt;
	std::vector<std::vector<double> > data;

	std::srand(std::time(nullptr));
	fill_data(dt);
	for (int i = 1; i < argc; i++)
	{
		std::string s(argv[i]);
		ft_parse(" " + s + " ", dt);
	}
	if (dt.input_data)
	{
		size_t size;
		FPI *r1, *r3;
		Seidel *r2, *r4;
		std::vector<double> d;
		std::cout << "Please enter size of matrix A: ";
		std::cin >> size;
		for (size_t i = 0; i < size; i++)
		{
			d = std::vector<double>(size + 1);
			for (size_t j = 0; j < size + 1; j++)
				std::cin >> d[j];
			data.push_back(d);
			d.clear();
		}
		if (dt.input_start)
		{
			std::cout << "Please enter start iteration with size " << size << std::endl;
			d = std::vector<double>(size);
			for (size_t i = 0; i < size; i++)
				std::cin >> d[i];
			r1 = new FPI(data, d, count_epsilon(dt.epsi));
			r2 = new Seidel(data, d, count_epsilon(dt.epsi));
			r3 = new FPI(data, d, count_epsilon(5));
			r4 = new Seidel(data, d, count_epsilon(5));
		}
		else
		{
			r1 = new FPI(data, count_epsilon(dt.epsi));
			r2 = new Seidel(data, count_epsilon(dt.epsi));
			r3 = new FPI(data, count_epsilon(5));
			r4 = new Seidel(data, count_epsilon(5));
		}	
		if (dt.full)
		{
			r1->fullSolve();
			std::cout << std::endl;
			r2->fullSolve();
			std::cout << std::endl;
			r3->fullSolve();
			std::cout << std::endl;
			r4->fullSolve();
		}
		else
		{
			r1->solve();
			std::cout << std::endl;
			r2->solve();
			std::cout << std::endl;
			r3->solve();
			std::cout << std::endl;
			r4->solve();
		}
		delete r1;
		delete r2;
		delete r3;
		delete r4;
	}
	else
	{
		std::ifstream ifs(argv[argc - 1]);
		std::vector<double> d;
		std::string str;
		FPI *r1, *r3;
		Seidel *r2, *r4;
		if (!ifs.is_open())
		{
			std::cout << "bad_file" << std::endl;
			return 1;
		}
		while (std::getline(ifs, str, '\n'))
		{
			double x;
			size_t sz = 0;
			while ((x = std::stod(str)))
			{
				d.push_back(x);
				if ((sz = str.find(" ")) != std::string::npos)
					str = std::string(str, sz + 1);
				else
					break;
			}
			d.push_back(std::stod(str));
			data.push_back(d);
			d.clear();
		}
		if (dt.input_start)
		{
			std::cout << "Please enter start iteration with size " << data.size() << std::endl;
			d = std::vector<double>(data.size());
			for (size_t i = 0; i < d.size(); i++)
				std::cin >> d[i];
			r1 = new FPI(data, d, count_epsilon(dt.epsi));
			r2 = new Seidel(data, d, count_epsilon(dt.epsi));
			r3 = new FPI(data, d, count_epsilon(5));
			r4 = new Seidel(data, d, count_epsilon(5));
		}
		else
		{
			r1 = new FPI(data, count_epsilon(dt.epsi));
			r2 = new Seidel(data, count_epsilon(dt.epsi));
			r3 = new FPI(data, count_epsilon(5));
			r4 = new Seidel(data, count_epsilon(5));
		}
		if (dt.full)
		{
			r1->fullSolve();
			std::cout << std::endl;
			r2->fullSolve();
			std::cout << std::endl;
			r3->fullSolve();
			std::cout << std::endl;
			r4->fullSolve();
		}
		else
		{
			r1->solve();
			std::cout << std::endl;
			r2->solve();
			std::cout << std::endl;
			r3->solve();
			std::cout << std::endl;
			r4->solve();
			std::cout << std::endl;
		}
		delete r1;
		delete r3;
		delete r4;
		delete r2;
	}
	return 0;
}