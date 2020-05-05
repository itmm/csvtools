
#line 4 "join.md"

	
#line 27 "join.md"

	#include "libs/cmp.h"
	#include "libs/file.h"
	#include "libs/ranges.h"
	#include <fstream>
	#include <iostream>
	#include <string>

#line 57 "join.md"

	void write_line(
		const Entries &entries1,
		const Entries &entries2
	) {
		bool first { entries1.write(true, false) };
		entries2.write(first, true);
	}

#line 5 "join.md"
;
	int main(
		int argc, const char *argv[]
	) {
		
#line 38 "join.md"

	if (argc != 5) {
		std::cerr << "wrong number of arguments\n";
		std::exit(EXIT_FAILURE);
	}
	std::ifstream file1 { argv[1] };
	std::ifstream file2 { argv[2] };
	File in1 { file1 };
	File in2 { file2 };
	Ranges rngs1 { parse_ranges(
		in1, argv + 3, 1
	) };
	Ranges rngs2 { parse_ranges(
		in2, argv + 4, 1
	) };

#line 69 "join.md"

	write_line(in1.header(), in2.header());
	bool has1 { in1.next_line() };
	bool has2 { in2.next_line() };
	Entries empty1; empty1.empty(in1.columns());
	Entries empty2; empty2.empty(in2.columns());
	while (has1 && has2) {
		int sort { compare(in1.entries(), rngs1, in2.entries(), rngs2) };
		if (sort < 0) {
			write_line(in1.entries(), empty2);
			has1 = in1.next_line();
		} else if (sort > 0) {
			write_line(empty1, in2.entries());
			has2 = in2.next_line();
		} else {
			write_line(in1.entries(), in2.entries());
			has1 = in1.next_line();
			has2 = in2.next_line();
		}
	}
	while (has1) {
		write_line(in1.entries(), empty2);
		has1 = in1.next_line();
	}
	while (has2) {
		write_line(empty1, in2.entries());
		has2 = in2.next_line();
	}

#line 9 "join.md"
;
	}
