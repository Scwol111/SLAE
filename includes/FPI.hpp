#ifndef FPI_HPP
#define FPI_HPP
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

class FPI 
{
private:
	std::vector<std::vector<double> >	_path;
	std::vector<double>					_solved;
	std::vector<std::vector<double> >	_data;
	double								_epsi;

	bool	endIteration();
	FPI();

public:
	virtual ~FPI();
	FPI& operator=(FPI const& src);
	FPI(FPI const& src);
	FPI(std::vector<std::vector<double> > const &, double);
	FPI(std::vector<std::vector<double> > const &, std::vector<double> const &, double);

	void	fullSolve();
	void	solve();
	void	table();
};

#endif // !FPI_HPP
