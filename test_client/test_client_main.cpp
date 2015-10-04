#include "echo_proxy.h"
#include <iostream>
#include <codecvt>




enum {
    N_TIMES = 5000
};


void 
test_proc()
{
    std::string outstr;
    for (int i = 0; i < N_TIMES; i++) {
	outstr = echo_proxy("127.0.0.1", "6688")("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	if (outstr == "") {
	    std::cout << "failed" << std::endl;
	}
    }
}


int
main(int argc, char * argv[])
{
   
    std::string instr, outstr;
    clock_t start, finished;
    start = clock();
    std::vector<std::thread> thread_pool;
    std::cout << "Enter the str & 'exit' to exit..." << std::endl;
    do {

	std::getline(std::cin, instr, '\n');
	if ("exit" == iegad::string::to_lwr(instr)) {
	    break;
	}
	std::cout << "echo :" << echo_proxy("127.0.0.1", "6688")(instr) << std::endl;
    } while (true);

 //   for (int i = 0; i < 10; i++) {
	//thread_pool.push_back(std::thread(test_proc));
 //   }

 //   for (int i = 0; i < 10; i++) {
	//thread_pool[i].join();
 //   }


    finished = clock();
    std::cout << (finished - start) / CLOCKS_PER_SEC << std::endl;
exit_case:
    exit(0);
}