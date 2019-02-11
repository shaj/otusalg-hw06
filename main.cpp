
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iterator>
#include <functional>
#include <fstream>

#include "oa_sort.h"
#include "heap.h"
#include "mergesort.h"
#include "quicksort.h"
#include "generators.h"

// Отсюда
// https://stackoverflow.com/a/21995693
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
	// typedef typename TimeT::rep type;
	using type = typename TimeT::rep;

	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
							(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};



int main(int argc, char const *argv[])
{

	using namespace std::placeholders;
	using restype=measure<std::chrono::microseconds>::type;

	// otusalg::print_gen_test(std::cout, 30);

	std::vector<int> gen;
	std::vector<int> v;
	std::vector<int> sizes {10000, 20000, 32768, 65536, 131072, 262144, 524288, 1048576};
	// std::vector<otusalg::gen_func> func_vec;
	std::vector<otusalg::gen_func> func_vec
		{
			std::bind(&otusalg::gen_type1<int>, _1, _2), 
			std::bind(&otusalg::gen_type2<int>, _1, _2),
			std::bind(&otusalg::gen_type3<int>, _1, _2), 
			std::bind(&otusalg::gen_type4<int>, _1, _2), 
			std::bind(&otusalg::gen_type5<int>, _1, _2), 
			std::bind(&otusalg::gen_type6<int>, _1, _2), 
			std::bind(&otusalg::gen_type7<int>, _1, _2), 
			std::bind(&otusalg::gen_type8<int>, _1, _2), 
			std::bind(&otusalg::gen_type9<int>, _1, _2) 
		};

	int alg_cnt = 7;   // Количество тестируемых алгоритмов
	int sample_cnt = sizes.size() * func_vec.size() * alg_cnt;

	std::vector<std::vector<std::vector<restype>>> vres(sizes.size(), std::vector<std::vector<restype>>(func_vec.size(), std::vector<restype>(alg_cnt, 0)));

	std::cout << "Sample: " << std::setw(5) << sample_cnt << "\r" << std::flush;

	for(int i=0; i<sizes.size(); i++)
	{

		for(int j=0; j<func_vec.size(); j++)
		{
			func_vec[j](sizes[i], gen);

			v.clear();
			std::copy(gen.begin(), gen.end(), std::back_inserter(v));
			vres[i][j][0] = measure<std::chrono::microseconds>::execution([&]()
			{
				std::sort(v.begin(), v.end(), std::less<int>());
			});
			if(!std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector NOT sorted [0] std::sort\n";
			std::cout << "Sample: " << std::setw(5) << --sample_cnt << "\r" << std::flush;


			if(gen.size() < 100000)
			{
				v.clear();
				std::copy(gen.begin(), gen.end(), std::back_inserter(v));
				vres[i][j][1] = measure<std::chrono::microseconds>::execution([&]()
				{
					otusalg::insertion_sort(v, std::less<int>());
				});
				if(!std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector NOT sorted [1] otusalg::insertion_sort\n";
				std::cout << "Sample: " << std::setw(5) << --sample_cnt << "\r" << std::flush;


				v.clear();
				std::copy(gen.begin(), gen.end(), std::back_inserter(v));
				vres[i][j][2] = measure<std::chrono::microseconds>::execution([&]()
				{
					otusalg::ins_sort(v.begin(), v.end(), std::less<int>());
				});
				if(!std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector NOT sorted [2] otusalg::ins_sort\n";
				std::cout << "Sample: " << std::setw(5) << --sample_cnt << "\r" << std::flush;
			}
			else
			{
				vres[i][j][1] = 0;
				vres[i][j][2] = 0;
				sample_cnt -= 2;
			}


			v.clear();
			std::copy(gen.begin(), gen.end(), std::back_inserter(v));
			vres[i][j][3] = measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::shell_sort_c(v);
			});
			if(!std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector NOT sorted [3] otusalg::shell_sort_c\n";
			std::cout << "Sample: " << std::setw(5) << --sample_cnt << "\r" << std::flush;


			std::vector<int> steps {1750, 701, 301, 132, 57, 23, 10, 4, 1};
			v.clear();
			std::copy(gen.begin(), gen.end(), std::back_inserter(v));
			vres[i][j][4] = measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::shell_sort_ck(v, steps);
			});
			if(!std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector NOT sorted [4] otusalg::shell_sort_ck\n";
			std::cout << "Sample: " << std::setw(5) << --sample_cnt << "\r" << std::flush;


			otusalg::heap<int> h;
			std::vector<int> vvv;
			v.clear();
			std::copy(gen.begin(), gen.end(), std::back_inserter(v));
			vres[i][j][5] = measure<std::chrono::microseconds>::execution([&]()
			{
				h.buildHeap(v.begin(), v.end());
				vvv = std::move(h.getSorted());
			});
			if(!std::is_sorted(vvv.begin(), vvv.end(), std::greater<int>())) std::cout << "vector NOT sorted [5] heap\n";
			std::cout << "Sample: " << std::setw(5) << --sample_cnt << "\r" << std::flush;


			v.clear();
			std::copy(gen.begin(), gen.end(), std::back_inserter(v));
			vres[i][j][6] = measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::merge_sort(v, std::less<int>());
			});
			if(!std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector NOT sorted [6] otusalg::merge_sort\n";
			std::cout << "Sample: " << std::setw(5) << --sample_cnt << "\r" << std::flush;
		}
	}

	std::cout << std::endl;
	std::ofstream fos;

	fos.open("alg.tsv");
	fos << "\n";
	for(int i=0; i<alg_cnt; i++)
	{
		fos << "Algorithm " << i << "\n";
		fos << "Size\tshaffle\trandom\taccending\tdecending\t3 random exchanges\t10 random at the end\trandomly replace 1%\tmany duplicates\tall equal\n"; 
		for(int j=0; j<sizes.size(); j++)
		{
			fos << sizes[j] << "\t";
			for(int k=0; k<func_vec.size(); k++)
			{
				fos << vres[j][k][i] << "\t";
			}
			fos << "\n";
		}
		fos << "\n";
	}
	fos.close();


	fos.open("gen.tsv");
	fos << "\n";
	for(int k=0; k<func_vec.size(); k++)
	{
		fos << "Generator " << k << "\n";
		fos << "Size\tstd::sort\totusalg::insertion_sort\totusalg::ins_sort\totusalg::shell_sort_c\totusalg::shell_sort_ck\totusalg::heap\totusalg::merge_sort\n"; 
		for(int j=0; j<sizes.size(); j++)
		{
			fos << sizes[j] << "\t";
			for(int i=0; i<alg_cnt; i++)
			{
				fos << vres[j][k][i] << "\t";
			}
			fos << "\n";
		}
		fos << "\n";
	}
	fos.close();


	fos.open("size.tsv");
	fos << "\n";
	for(int j=0; j<sizes.size(); j++)
	{
		fos << "Size " << sizes[j] << "\n";
		fos << "Generator\tstd::sort\totusalg::insertion_sort\totusalg::ins_sort\totusalg::shell_sort_c\totusalg::shell_sort_ck\totusalg::heap\totusalg::merge_sort\n"; 
		for(int k=0; k<func_vec.size(); k++)
		{
			fos << "\t";
			for(int i=0; i<alg_cnt; i++)
			{
				fos << vres[j][k][i] << "\t";
			}
			fos << "\n";
		}
		fos << "\n";
	}
	fos.close();


	return 0;
}

