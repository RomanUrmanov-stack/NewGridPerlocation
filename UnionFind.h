#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <ctime>

class Grid
{
public:
	class UnionFind
	{
	public:
		UnionFind(int N);
		void un(int root_p, int root_c);
		int find(int ind);

		std::vector<int> u_f;
	};

	Grid(int N);

	void process();
	bool open(int row, int col);
	bool perlocates(UnionFind &union_find) const;
	void connect(int row, int col, UnionFind &union_find) const;
	double get_threshold() const; 

private:
	std::vector<std::vector<int>> grid;
	int op;
	double threshold;
};

class GridStat
{
public:
	double mean() const;
	double stddev() const;
	double confLo() const;
	double confHi() const;

	std::vector<double> thres_stat;
};