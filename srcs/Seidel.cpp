#include "../includes/Seidel.hpp"

Seidel::Seidel() 
{
}

Seidel::~Seidel() 
{
}

Seidel::Seidel(Seidel const& src) 
{
	*this = src;
}

Seidel::Seidel(std::vector<std::vector<double> > const &data, double psi): _solved(data.size()), _data(data), _epsi(psi)
{
	for (size_t i = 0; i < _solved.size(); i++)
	{
		_solved[i] = std::rand() % 10;
		if (_solved[i] == 0)
			_solved[i]++;
	}
	for (size_t i = 0; i < _data.size(); i++)
	{
		double x = _data[i][i];
		for (size_t j = 0; j < _data[i].size(); j++)
		{
			if (j != i)
				_data[i][j] /= x;
			else
				_data[i][j] = 0;
			if (j + 1 < _data.size())
				_data[i][j] *= -1;
		}
	}
	do
	{
		_path.push_back(_solved);
		for (size_t j = 0; j < _data.size(); j++)
		{
			_solved[j] = 0;
			for (size_t k = 0; k < _data[j].size() - 1; k++)
			{
				double res = _data[j][k] * _solved[k];
				_solved[j] += res;
			}
			_solved[j] += _data[j].back();
		}
	} 
	while (!endIteration());
}

Seidel::Seidel(std::vector<std::vector<double> > const &data, std::vector<double> const &solve, double psi): _solved(solve), _data(data), _epsi(psi)
{
	for (size_t i = 0; i < _data.size(); i++)
	{
		double x = _data[i][i];
		for (size_t j = 0; j < _data[i].size(); j++)
		{
			if (j != i)
				_data[i][j] /= x;
			else
				_data[i][j] = 0;
			if (j + 1 < _data.size())
				_data[i][j] *= -1;
		}
	}
	do
	{
		_path.push_back(_solved);
		for (size_t j = 0; j < _data.size(); j++)
		{
			_solved[j] = 0;
			for (size_t k = 0; k < _data[j].size() - 1; k++)
			{
				double res = _data[j][k] * _solved[k];
				_solved[j] += res;
			}
			_solved[j] += _data[j].back();
		}
	} 
	while (!endIteration());
}

Seidel& Seidel::operator=(Seidel const& src) 
{
	_path = src._path;
	_solved = src._solved;
	_data = src._data;
	_epsi = src._epsi;
	return *this;
}

bool	Seidel::endIteration()
{
	double sum = 0;
	for (size_t i = 0; i < _solved.size(); i++)
	{
		double x = std::abs(_solved[i] - _path.back()[i]);
		if (x <= _epsi)
			return true;
		sum += x;
	}
	if (sum <= _epsi)
		return true;
	return false;
}

void	Seidel::solve()
{
	std::cout << "Seidel: ";
	for (size_t i = 0; i < _solved.size(); i++)
		std::cout << _solved[i] << " ";
	std::cout << std::endl;
}

void	Seidel::fullSolve()
{
	size_t i;
	for (i = 0; i < _path.size(); i++)
	{
		std::cout << "Seidel(" << i << "): ";
		for (size_t j = 0; j < _path[i].size(); j++)
			std::cout << _path[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << "Seidel(" << i << "): ";
	for (size_t j = 0; j < _solved.size(); j++)
		std::cout << _solved[j] << " ";
	std::cout << std::endl;
}

