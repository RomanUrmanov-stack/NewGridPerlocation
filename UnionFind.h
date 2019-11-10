#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <ctime>

using namespace std;

class UnionFind
{
public:
	UnionFind(int N);

	void process();
	bool open(int row, int col);
	bool perlocates();
	void connect(int row, int col);
	void un(int row, int col, int a, int b);
	vector<int> find(int ind);
	double get_threshold();
	
private:
	vector<vector<int>> grid;
	vector<int> union_find;
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

	vector<double> thres_stat;
};