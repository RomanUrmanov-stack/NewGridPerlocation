#include "UnionFind.h"

int main()
{
	GridStat stat;
	int N = 20;
	ofstream file;
	try 
	{
		file.open("GridStat.txt");
	}
	catch (exception &ex)
	{
		cout << "Error" << endl;
		cout << ex.what() << endl;
	}

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 250; i++)
		{
			UnionFind grid(N);
			grid.process();
			stat.thres_stat.push_back(grid.get_threshold());
		}
		file << "N = " << N << "\n";
		file << "mean = " << stat.mean() << "\n";
		file << "stddev = " << stat.stddev() << "\n";
		file << "confHi = " << stat.confHi() << "\n";
		file << "confLo = " << stat.confLo() << "\n";

		N++;
	}

	file.close();

	system("pause");
	return 0;
}