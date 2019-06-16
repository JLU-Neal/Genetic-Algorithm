// GA.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//主函数入口
#include"gene.h"
#include <string.h>
#include <iostream>
#include<time.h>
using namespace std;


int main(int argc, char*argv[])
{

	clock_t start, finish;
	double totaltime;
	start = clock();

	Gene *gene = new Gene;     //实例化类，返回指针

	int gen = 0;
	int oldMaxPop, k;
	double oldMax;

	srand((unsigned)time(NULL));
	gene->initPop();
	memcpy(&gene->newPop, &gene->oldPop, POP_SIZE * sizeof(struct Gene::population));
	gene->statistics(gene->newPop);    //计算种群的最大适应度和最小适应度以及适应度的下表号。
	gene->report(gene->newPop, gen);

	while (gen < CENERAION_NUM)
	{
		gen += 1;
		if (gen % 100 == 0) {
			srand((unsigned)time(NULL));
		}
		oldMax = gene->maxFitness;   //oldmax为种群中最大适应度
		oldMaxPop = gene->maxPop;    //oldMaxPop指种群中最大适应度的个体
		gene->generation();
		gene->statistics(gene->newPop);

		if (gene->maxFitness < oldMax) {
			for (k = 0; k < CHROM_SIZE; k++) {
				gene->newPop[gene->minPop].chrom[k] = gene->oldPop[oldMaxPop].chrom[k];
			}
			gene->newPop[gene->minPop].fitness = gene->oldPop[oldMaxPop].fitness;
			gene->newPop[gene->minPop].weight = gene->oldPop[oldMaxPop].weight;
			gene->newPop[gene->minPop].volume = gene->oldPop[oldMaxPop].volume;
			gene->newPop[gene->minPop].parent1 = gene->oldPop[oldMaxPop].parent1;
			gene->newPop[gene->minPop].parent2 = gene->oldPop[oldMaxPop].parent2;
			gene->newPop[gene->minPop].cross = gene->oldPop[oldMaxPop].cross;
			gene->statistics(gene->newPop);
		}
		else if (gene->maxFitness > oldMax) {
			gene->report(gene->newPop, gen);
		}
		memcpy(&gene->oldPop, &gene->newPop, POP_SIZE * sizeof(struct Gene::population));
	}

	//delete[] gene;    //销毁对象占用空间
	//system("pause");

	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "Genetic algorithm 's runningtime is " << totaltime << " sec " << endl;

	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
