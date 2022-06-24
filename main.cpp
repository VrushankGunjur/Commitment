#include "main.h"

/*
 * Initiates main loop allowing users to commit to and verify bets
*/
int main(int argc, char ** argv)
{
    Bet my_bet;

    char ch = '_';

    while (ch != 'q') {
        std::cout << "Commit: c \nVerify: v \nQuit: q \n" << std::endl;
        std::cin >> ch;
        char dummy = getchar();
        std::cout << std::endl;
        if (ch == 'c') {
            std::cout << "Enter Bet: " << std::endl;
            std::cout << "----------" << std::endl;
            std::string bet;
            getline(std::cin, bet); 
            std::cout << "\n";
            std::string promise = my_bet.commit(bet);
            std::cout << "Promise: \n";
            std::cout << "---------\n" << promise << "\n" << std::endl;
        }
        else if (ch == 'v') {
            std::cout << "Enter Promise: " << '\n';
            std::cout << "--------------" << std::endl;
            std::string promise;
            getline(std::cin, promise);
            std::cout << "\nEnter Bet EXACTLY: " << std::endl;
            std::cout << "-------------------\n";
            std::string bet;
            getline(std::cin, bet);
            std::cout << "\nEnter Bet Access Key: " << std::endl;
            std::cout << "---------------------\n";
            std::string access_key;
            getline(std::cin, access_key);

            if (my_bet.verify(promise, bet, access_key)) {
                std::cout << "\nChecks Out!\n";
            }
            else {
                std::cout << "\nIncorrect!\n";
            }
            std::cout << std::endl; // flush stream & newline
        }
    }
    return 0;
}