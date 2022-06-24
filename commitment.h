#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
class Bet {
    public:

        std::string commit(std::string msg);
        bool verify(std::string com, std::string msg, std::string nonce);
    private:

        std::string encode(std::string to_encode);
        std::string merkle_damgard(std::string to_fold);
        std::string compress(std::string to_comp);
        std::string gen_nonce();
        std::string hash(std::string to_hash);
        char convert_char(int key);

};