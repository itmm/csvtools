
#line 4 "add.md"

	
#line 23 "add.md"

	#include "libs/file.h"
	#include <iostream>
	#include <string>

#line 37 "add.md"

	void write_line(
		const Entries &entries,
		const char **argv, int argc
	) {
		bool first { entries.write(true, false) };
		for (int i { 0 }; i < argc; ++i) {
			std::string v { argv[i] };
			for (int j { 1 }; j <= entries.columns(); ++j) {
				std::string key = "${" + std::to_string(j) + "}";
				size_t pos { v.find(key) };
				while( pos != std::string::npos) {
					v.replace(pos, key.size(), entries[j]);
					pos = v.find(key, pos + entries[j].size());
				}
			}
			if (first) { 
				first = false;
			} else {
				std::cout << ',';
			}
			std::cout << Entries::escape(v);
		}
		std::cout << "\r\n";
	}

#line 5 "add.md"

	int main(
		int argc, const char *argv[]
	) {
		
#line 31 "add.md"

	File in { std::cin };

#line 66 "add.md"

	write_line(in.header(), argv + 1, argc - 1);
	while (in.next_line()) {
		write_line(in.entries(), argv + 1, argc - 1);
	}

#line 9 "add.md"

	}
