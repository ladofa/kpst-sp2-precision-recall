#include <iostream>
#include <string>
#include <fstream>

#include <random>
#define N 100000

void main()
{
	double x[N];
	char c[N];
	char d[N];

	std::default_random_engine generator;

	//std::normal_distribution<double> norm_c1(40, 10);
	//std::normal_distribution<double> norm_c2(67, 1);

	std::normal_distribution<double> norm_c1(50, 8);
	std::normal_distribution<double> norm_c2(79, 4);

	int p[10] = {};

	//샘플 생성
	for (int i = 0; i < N; i++) {
		if (i % 10 == 0)
		{
			x[i] = norm_c2(generator);
			c[i] = 1;
		}
		else
		{
			x[i] = norm_c1(generator);
			c[i] = 0;
		}
	}


	double precision[100];
	double recall[100];
	int __tp[100];
	int __fp[100];
	int __fn[100];
	for (int split = 0; split < 100; split++)
	{
		//판별
		for (int i = 0; i < N; i++)
		{
			//d[i] = rand() % 2;
			//continue;
			if (x[i] > split)
			{
				d[i] = 1;
			}
			else
			{
				d[i] = 0;
			}
		}

		//평가
		int fp = 0, fn = 0, tp = 0, tn = 0;
		for (int i = 0; i < N; i++)
		{
			if (d[i] == 1)
			{
				if (c[i] == 1)
					tp++;
				else
					fp++;
			}
			else
			{
				if (c[i] == 1)
					fn++;
				else
					tn++;
			}
		}

		__tp[split] = tp;
		__fp[split] = fp;
		__fn[split] = fn;

		precision[split] = tp / double(tp + fp);
		recall[split] = tp / double(tp + fn);
	}

	std::ofstream file("asdf.txt", std::ofstream::out);
	
	for (int split = 0; split < 100; split++)
	{
		printf("%.3lf\t%.3lf\n", precision[split], recall[split]);
		file << recall[split] << "\t" << precision[split] << std::endl;
	}

	file.close();
}