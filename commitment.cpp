#include "commitment.h"

/*
 * Takes a message, prints an access key to that message and returns 
 * the signature of that message.
*/
std::string Bet::commit(std::string msg) {
    std::string nonce = gen_nonce();
    std::cout << "Bet Access Key: \n";
    std::cout << "---------------\n" << nonce << '\n' << std::endl;

    std::string total = msg + nonce;

    return encode(total);
}

/*
 * For a bet to be sincere, the signature of the bet has to be matched
 * by the signature of the string and the associated access key (nonce/salt)
*/
bool Bet::verify(std::string com, std::string msg, std::string nonce) {
    std::string total = msg + nonce;
    
    //std::cout << total << std::endl;
    std::string encoded = encode(total);
    //std::cout << "Hashed: " << encoded << std::endl;
    return (encoded == com);
}


/*
 * Encodes the string (message + nonce is to_encode) to create a signature
*/
std::string Bet::encode(std::string to_encode) {
    std::string ret = merkle_damgard(to_encode);
    // merkle ensures that ret is a fixed length (128 bit)
    return ret;
}


/*
 * Uses Merkle-Damgard construction to turn to_fold into equally sized blocks 
 * to use cipher on, and returns a fixed length string of length 16
*/
std::string Bet::merkle_damgard(std::string to_fold) {
    size_t tot_len = to_fold.length();
    size_t m_n = 32;                    // Represents 256 bits, 32 chars
    size_t chop = 0;

    // initialization vector must be 16 chars (128 bits), arbitrary construction
    std::string init_vector = "XALSJ$DI189D#KLF";
    // final stores the 128 bit folded output of the input to hash
    std::string final = init_vector;

    while (chop < tot_len) {
        std::string cur = to_fold.substr(chop, m_n);
        while (cur.length() < m_n) {
            // include padding for extra space
            cur += "5";    // padding char is arbitrary
        }

        // hash final + cur first (still 384 bit), then compress
        final = hash(final + cur);
        final = compress(final);        // turn to 128 bit
        //std::cout << final << '\n';   // prints every step of the merkle-damgard
        chop += m_n;
    }

    // final is the compressed & standardized string (128 bit)
    return final;
}

/*
 * Turns 48 chars (384 bits) to 16 chars (128 bits) by adding the ASCII
 * values of each triplet and turning that into a character of its own
*/
std::string Bet::compress(std::string to_comp) {
    // sum every 3 characters together, convert to new ASCII char

    std::string compressed;
    for(size_t chunk = 0; chunk < to_comp.length(); chunk += 3) {
        int cur = to_comp[chunk];
        cur ^= to_comp[chunk+1];
        cur ^= to_comp[chunk+2];
        compressed.push_back(convert_char(cur));     // turn to valid character
    }

    return compressed;
}

/*
 * Maps an int to a domain of ASCII values
*/
char Bet::convert_char(int key) {
    return (char) (33 + (key % 92));
}

/*
 * Hashes a single block 1:1 with Autokey cipher as encryption scheme 'E'
 * Uses Davies-Meyer construction to XOR encryption with to_hash to avoid collisions
*/
std::string Bet::hash(std::string to_hash) {
    std::string encryption;

    /*
        Block Cipher E turns to_hash into encryption
        Here, we use Autokey Cipher with key 'V'
    */

    // creating the key
    int sum = 0;
    for (int c = 0; c < to_hash.length(); c++) {
        sum += to_hash[c];
    }

    char autokey = convert_char(sum);

    // cipher logic
    encryption.push_back(convert_char(((int) autokey) + ((int) to_hash[0])));
    for (int ptr = 0; ptr < to_hash.length(); ptr++) {
        encryption.push_back(convert_char(((int) to_hash[ptr]) + ((int) to_hash[ptr+1])));
    }

    // Davies-Meyer construction to ensure collision-resistancy (XOR with message)
    for (int idx = 0; idx < encryption.length(); idx++) {
        encryption[idx] = encryption[idx] ^ to_hash[idx];
    }
    return encryption;
}

/*
 * Generate random key (Bet Access Key), also known as 'salt'
*/
std::string Bet::gen_nonce() {
    std::string nonce;
    srand(time(NULL));
    for(int idx = 0; idx < 25; idx++) {
        nonce.push_back(convert_char(rand()));
    }
    return nonce;
}