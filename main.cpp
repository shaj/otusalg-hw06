
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
					otusalg::merge_sort(v.begin(), v.end(), std::less(v));
				}) << " us\n";


			otusalg::heap<int> h;
			std::cout << "buildHeap: " << measure<std::chrono::microseconds>::execution([&]()
				{
					h.buildHeap(v.begin(), v.end());
				}) << " us\n";
			std::ofstream fos("out_1.dot");
			h.printHeap_dot(fos);
			fos.close();

			int rm = v.size() / 3;
			std::cout << "remove: " << measure<std::chrono::microseconds>::execution([&]()
				{
					h.remove(rm);
				}) << " us\n";
			std::cout << "removed item " << rm << std::endl;
			fos.open("out_2.dot");
			h.printHeap_dot(fos);
			fos.close();

		}
		else
		{
			std::cout << "File '" << argv[1] << "' does not exist" << std::endl;
		}
	}

	return 0;
}

