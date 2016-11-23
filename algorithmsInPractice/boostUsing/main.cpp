#include <boost/lambda/lambda.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	using namespace boost;
	typedef std::istream_iterator<int> in;

	//for_each(in(cin), in(), cout << (_1 * 3) << " ");

	string line;
	regex pat("^Subject: (Re: |Aw: )*(.*)");

	while (cin)
	{
		getline(::cin, line);
		smatch matches;
		if (regex_match(line, matches, pat))
			cout << matches[2] << std::endl;
	}
}
