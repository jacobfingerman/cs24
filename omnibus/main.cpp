#include "Atlas.h"
#include "Helpers.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {

	Atlas* atlas = nullptr;
	std::ifstream file("data/chessboard.txt");
	atlas = Atlas::create(file);


	int max = 'H' - 'A';

	srand(1);


	for (size_t i = 0; i < 100; i++) {
		/*std::string b = std::to_string(rand() % max + 1);
		std::string c = std::to_string(rand() % max + 1);
		std::string d = std::to_string(rand() % max + 1);
		std::string e = std::to_string(rand() % max + 1);

		std::string st1 = "Station " + b + "-" + d;
		std::string st2 = "Station " + c + "-" + e;*/

		int b1 = rand() % max + 'A';
		int c1 = rand() % max + 'A';
		std::string d = std::to_string(rand() % max );
		std::string e = std::to_string(rand() % max );

		char b = b1;
		char c = c1;

		std::string st1 = b + d;
		std::string st2 = c + e;


		try{ 
			Trip trip = atlas->route(st1, st2); 
			std::cout << "Start at " << trip.start << '\n';
			for (const Trip::Leg& leg : trip.legs) {
				std::cout << " - " << leg.line << " to " << leg.stop << '\n';
			}
			std::cout << "\n";
		}
	    catch(const std::exception& e) {
			std::cout << st1 << " -> " << st2 << "\n";
	        std::cout << "Error: " << e.what() << "\n\n";
	    }
		
	}
	
	/*Trip trip;
	try { trip = atlas->route("Station 107-14", "Station 31-169"); }
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << '\n';
	}*/



	std::cout << "\n all good";

	

	delete atlas;

	return 0;
}

//
//int main(int argc, char** argv) {
//    if(argc != 2) {
//        std::cout << "USAGE: " << argv[0] << " [data-file]\n";
//        std::exit(1);
//    }
//
//    Atlas* atlas = nullptr;
//    try {
//        std::ifstream file(argv[1]);
//        if(file.fail()) {
//            throw std::runtime_error("Could not open file.");
//        }
//
//        atlas = Atlas::create(file);
//    }
//    catch(const std::exception& e) {
//        std::cout << "Error reading file: " << e.what() << '\n';
//        std::exit(1);
//    }
//
//    std::string sname;
//    std::string dname;
//
//    std::cout << "From: ";
//    while(std::getline(std::cin, sname)) {
//        std::cout << "To:   ";
//        if(!std::getline(std::cin, dname)) {
//            break;
//        }
//
//        try {
//            Trip trip = atlas->route(sname, dname);
//            std::cout << "Start at " << trip.start << '\n';
//            for(const Trip::Leg& leg: trip.legs) {
//                std::cout << " - " << leg.line << " to " << leg.stop << '\n';
//            }
//        }
//        catch(const std::exception& e) {
//            std::cout << "Error: " << e.what() << '\n';
//        }
//
//        std::cout << "From: ";
//    }
//
//    delete atlas;
//    return 0;
//}
//
//
//
//
//
