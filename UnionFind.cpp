#include "UnionFind.h"

UnionFind::UnionFind(int N)
{
	vector<vector<int>> temp(N, vector<int>(N, 0));
	grid = temp;

	vector<int> utemp;
	for (int i = 0; i < N*N + 2; i++)
	{
		utemp.push_back(i);
	}

	union_find = utemp;

	op = 0;
}

void UnionFind::process()
{
	int N = grid.size();
	srand(time(nullptr));

	while (!perlocates())
	{
		int i = rand() % N, j = rand() % N;
		if (open(i, j))	connect(i, j);
	}
	threshold = op / (double(N)*double(N));
}

bool UnionFind::open(int row, int col)
{
	if (grid[row][col] == 0)
	{
		grid[row][col] = 1;
		op++;
		return true;
	}
	else return false;
}

void UnionFind::connect(int row, int col)
{
	if (row == 0) union_find[col] = union_find[union_find.size() - 2];
	else if (row == grid.size() - 1) union_find[row*grid.size() + col] = union_find[union_find.size() - 1];
	for (int a = -1; a < 2; a++)
	{
		for (int b = -1; b < 2; b++)
		{
			if (row + col + a + b == row + col + 1 || row + col + a + b == row + col - 1)
			{
				try
				{
					if (grid.at(row + a).at(col + b) == 1)
					{
						un(row, col, a, b);
					}
				}
				catch (out_of_range &ex) {}
			}
		}
	}

}

void UnionFind::un(int row, int col, int a, int b)
{
	int N = grid.size();
	int ind_p = row*N + col, ind_c = (row + a)*N + col + b;;
	vector<int> indexes_c = find(ind_c), indexes_p = find(ind_p);
	for (int i = 0; i < indexes_c.size(); i++)
	{
		union_find[indexes_c[i]] = indexes_p[indexes_p.size() - 1];
	}
}

vector<int> UnionFind::find(int ind)
{
	vector<int> indexes;
	do
	{
		indexes.push_back(ind);
		ind = union_find[ind];
	} while (union_find[ind] != ind);
	indexes.push_back(ind);
	return indexes;
}

bool UnionFind::perlocates()
{
	vector<int> temp1 = find(union_find.size() - 1), temp2 = find(union_find.size() - 2);
	if (temp1[temp1.size() - 1] != temp2[temp2.size() - 1]) return false;
	else return true;
}

double UnionFind::get_threshold()
{
	return threshold;
}

double GridStat::mean() const
{
	double sum = accumulate(thres_stat.begin(), thres_stat.end(), 0.0);
	double size = thres_stat.size();

	return sum / size;
}

double GridStat::stddev() const
{
	vector<double>::const_iterator it = thres_stat.begin();

	double sum = 0;
	for (int i = 0; i < thres_stat.size(); i++)
	{
		sum += pow(*it - mean(), 2);
		it++;
	}
	return sum = sqrt(sum / thres_stat.size());
}

double GridStat::confHi() const
{
	return mean() + 1.96*sqrt(stddev()) / sqrt(thres_stat.size());
}

double GridStat::confLo() const
{
	return mean() - 1.96*sqrt(stddev()) / sqrt(thres_stat.size());
}