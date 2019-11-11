#include "UnionFind.h"

Grid::Grid(int N)
{
	vector<vector<int>> temp(N, vector<int>(N, 0));
	grid = temp;

	op = 0;
}

void Grid::process()
{
	int N = grid.size();
	srand(time(nullptr));

	UnionFind union_find(N);

	while (!perlocates(union_find))
	{
		int i = rand() % N, j = rand() % N;
		if (open(i, j))	connect(i, j, union_find);
	}
	threshold = op / (double(N)*double(N));
}

bool Grid::open(int row, int col)
{
	if (grid[row][col] == 0)
	{
		grid[row][col] = 1;
		op++;
		return true;
	}
	else return false;
}

void Grid::connect(int row, int col, UnionFind &union_find) const
{
	int N = grid.size();
	if (row == 0) union_find.u_f[col] = union_find.u_f[union_find.u_f.size() - 2];
	else if (row == grid.size() - 1) union_find.u_f[row*grid.size() + col] = union_find.u_f[union_find.u_f.size() - 1];
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
						int ind_p = row*N + col, ind_c = (row + a)*N + col + b;
						int root_p = union_find.find(ind_p), root_c = union_find.find(ind_c);
						union_find.un(root_p, root_c);
					}
				}
				catch (out_of_range &ex) {}
			}
		}
	}

}

bool Grid::perlocates(UnionFind &union_find) const
{
	int root1 = union_find.find(union_find.u_f.size() - 1), root2 = union_find.find(union_find.u_f.size() - 2);
	if (root1 != root2) return false;
	else return true;
}

double Grid::get_threshold() const
{
	return threshold;
}

Grid::UnionFind::UnionFind(int N)
{
	vector<int> utemp;
	for (int i = 0; i < N*N + 2; i++)
	{
		utemp.push_back(i);
	}

	u_f = utemp;
}

void Grid::UnionFind::un(int root_p, int root_c)
{
	u_f[root_c] = u_f[root_p];
}

int Grid::UnionFind::find(int ind)
{
	vector<int> indexes;
	do
	{
		indexes.push_back(ind);
		ind = u_f[ind];
	} while (u_f[ind] != ind);
	indexes.push_back(ind);
	for (int i = 0; i < indexes.size(); i++)
	{
		u_f[indexes[i]] = ind;
	}
	return ind;
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