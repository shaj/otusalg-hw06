
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iterator>
#include <functional>
#include <fstream>

#include "mergesort.h"
#include "quicksort.h"

// Отсюда
// https://stackoverflow.com/a/21995693
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
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



void read_data(std::istream &is, std::vector<int> &v)
{
	std::string slen;
	std::getline(is, slen);
	v.clear();
	v.reserve(std::stoi(slen));
	for(std::string line; std::getline(is, line);)
	{
		v.emplace_back(std::stoi(line));
	}
}


int main(int argc, char const *argv[])
{

	if(argc > 1)
	{
		std::cout << "'" << argv[1] << "'\n";

		std::vector<int> v;
		std::ifstream fs;
		fs.open(argv[1], std::ios::in);
 
		if(fs.is_open())
		{
			read_data(fs, v);
			fs.close();

			std::cout << "merge_sort: " << measure<std::chrono::microseconds>::execution([&]()
				{
					otusalg::merge_sort(v, std::less<int>());
				}) << " us\n";

			if(std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;

			// std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

			fs.open(argv[1]);
			read_data(fs, v);
			fs.close();

			std::cout << "merge_sort_mt: " << measure<std::chrono::microseconds>::execution([&]()
				{
					otusalg::merge_sort_mt(v, std::less<int>());
				}) << " us\n";

			if(std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;

		}
		else
		{
			std::cout << "File '" << argv[1] << "' does not exist" << std::endl;
		}
	}

	return 0;
}

