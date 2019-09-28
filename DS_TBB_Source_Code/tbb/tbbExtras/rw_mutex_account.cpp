#include "tbb/tbb.h"
#include <cstdlib>
#include <iostream>
#include <thread>

class account {
    long balance;

public:
    account() : balance(0) {}

    bool adjust(int adjustment) {
        if (balance_available(adjustment)) {
            apply_adjustment(adjustment);
            return true;
        }

        return false;
    }

    bool balance_available(int adjustment) {
        return (balance - adjustment > 0);
    }

    void apply_adjustment(long adjustment) {
        balance += adjustment;
    }

    long get_balance() {
        return balance;
    }
};



void apply_adjustments_serial(account& account, const std::vector<int> &adjustments) {
    std::for_each(adjustments.begin(), adjustments.end(), [&account](int adjustment) {
        account.adjust(adjustment);
    });
}
    
void apply_adjustments_parallel(account& account, const std::vector<int> &adjustments) {
    tbb::parallel_do(adjustments, [&account](int adjustment) {
        account.adjust(adjustment);
    });
}

int create_adjustment() {
    return rand() % 10001 + (-1000);
}

void apply_adjustments() {
    std::vector<int> adjustments(100000);
    std::generate(adjustments.begin(), adjustments.end(), create_adjustment);

    account serial;
    account parallel;

//    auto start = tbb::tick_count::now();
    apply_adjustments_serial(serial, adjustments);
//    auto time = tbb::tick_count::now() - start;
//    std::cout << "Serial:   " << serial.get_balance() << " " << time.seconds() << std::endl;

//    start = tbb::tick_count::now();
    apply_adjustments_serial(parallel, adjustments);
    //time = tbb::tick_count::now() - start;
    //std::cout << "Parallel: " << serial.get_balance() << " " << time.seconds() << std::endl;

    if (serial.get_balance() != parallel.get_balance()) {
        std::cout << "BALANCE IS OUT OF SYNC!" << std::endl;
    }

}


