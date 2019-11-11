#include "UnionFind.h"

using namespace std;

int main()
{
	GridStat stat;
	int N = 20;
	ofstream file_mean, file_dev, file_confHi, file_confLo, file_time;
	try 
	{
		file_mean.open("GridMean.txt");
		file_dev.open("GridDev.txt");
		file_confHi.open("GridConfHi.txt");
		file_confLo.open("GridConfLo.txt");
		file_time.open("GridTime.txt");
	}
	catch (exception &ex)
	{
		cout << "Error" << endl;
		cout << ex.what() << endl;
	}

	for (int j = 0; j < 20; j++)
	{
		unsigned int start = clock();
		for (int i = 0; i < 100; i++)
		{
			Grid grid(N);
			grid.process();
			stat.thres_stat.push_back(grid.get_threshold());
		}
		file_mean << N << "\t" << stat.mean()<<"\n";
		file_dev << N << "\t" << stat.stddev()<<"\n";
		file_confHi << N<< "\t" << stat.confHi()<<"\n";
		file_confLo <<N<< "\t"<< stat.confLo()<<"\n";
		file_time << N << "\t" << clock() - start << "\n";

		N++;
	}

	file_mean.close();
	file_dev.close();
	file_confHi.close();
	file_confLo.close();
	file_time.close();

	system("pause");
	return 0;
}