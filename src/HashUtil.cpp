/*
 * HashUil.cpp
 *
 *  Created on: 30 Aug 2013
 *      Author: nicholas
 */

#include <boost/program_options.hpp>
#include <cstdio>

namespace po = boost::program_options;
using namespace std;

int main(int argc, char* argv[]) {
	po::options_description desc = po::options_description("Allowed options");
	desc.add_options()
			("help", "Display this help message")
			("filter", po::value<string>(), "Add files in the directory and subdirectories into filter list")
			("prune", "Remove non-existing file paths from the database")
			("path", po::value<vector<string> >(), "Paths to process")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help") > 0) {
		cout << desc << "\n";
		exit(0);
	}else if(vm.count("path") == 0){
		cout << "No paths given, aborting.\n";
		exit(1);
	}else if((vm.count("filter") == 0) && (vm.count("prune") == 0)){
	cout << "No operation selected, aborting.\n";
		exit(2);
	}

	if(vm.count("filter")){
		cout << "Adding files to filter with reason \"" << vm["filter"].as<string>() << "\"\n";
	}

	if(vm.count("prune")) {
		cout << "Pruning database.\n";
	}

//	cout << "Folders to process:\n" << vm["path"].as<vector<string> >() << "\n";
}

