#ifndef SEIDEL_HPP
#define SEIDEL_HPP
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

class Seidel 
{
private:
	std::vector<std::vector<double> >	_path;
	std::vector<double>					_solved;
	std::vector<std::vector<double> >	_data;
	double								_epsi;

	bool	endIteration();
	Seidel();

public:
	virtual ~Seidel();
	Seidel& operator=(Seidel const& src);
	Seidel(Seidel const& src);
	Seidel(std::vector<std::vector<double> > const &, double);
	Seidel(std::vector<std::vector<double> > const &, std::vector<double> const &, double);

	void	fullSolve();
	void	solve();
};

#endif // !SEIDEL_HPP
