

#include <iostream>
#include <iterator>
#include <algorithm>
#include "generators.h"




void otusalg::print_gen_test(std::ostream &os, std::size_t sz)
{
	std::vector<int> v;

	os << "Type 1. Shuffle:\n";
	otusalg::gen_type1(sz, v);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	os << "\n\n";

	os << "Type 2. Random:\n";
	otusalg::gen_type2(sz, v);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	os << "\n\n";

	os << "Type 3. Accending:\n";
	otusalg::gen_type3(sz, v);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	os << "\n\n";

	os << "Type 4. Decending:\n";
	otusalg::gen_type4(sz, v);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	os << "\n\n";

	os << "Type 5. 3 random exchange:\n";
	otusalg::gen_type5(sz, v);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	os << "\n\n";

	os << "Type 6. 10 random at end:\n";
	otusalg::gen_type6(sz, v);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	os << "\n\n";

	os << "Type 7. 1%:\n";
	otusalg::gen_type7(sz, v);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	os << "\n\n";

	os << "Type 8. many duplicates:\n";
	otusalg::gen_type8(sz, v, 0, 0);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	os << "\n\n";

	os << "Type 9. all equal:\n";
	otusalg::gen_type9(sz, v);
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	os << "\n\n";
}

