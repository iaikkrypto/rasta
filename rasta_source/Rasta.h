#ifndef __Rasta_h__
#define __Rasta_h__

#include <bitset>
#include <vector>
#include <string>

const unsigned blocksize = 219;   // Block size in bits
const unsigned rounds = 6; // Number of rounds


typedef std::bitset<blocksize> block; // Store messages and states
typedef std::bitset<blocksize> keyblock;
typedef unsigned long long int UINT64;
typedef UINT64 tKeccakLane;
typedef unsigned char UINT8;
enum instanceGeneration{all_new,lu,randall};


class Rasta {
public:
    Rasta (keyblock k = 0, instanceGeneration instance = all_new) {
        key = k;
        instance_ = instance;
        squeezedbits = 0;
    };

    block crypt (const block message, const UINT64 nonce, const UINT64 counter);
    void set_key (keyblock k);
    instanceGeneration instance_;

private:
// Rasta private data members //
    std::vector<std::vector<block>> LinMatrices;
        // Stores the binary matrices for each round
    std::vector<block> roundconstants;
        // Stores the round constants
    keyblock key = 0;
        //Stores the master key

// Shake private data members
    UINT8 shakestate[200];
    static const unsigned int shakerate=1088;
    unsigned int squeezedbits;

//Shake private functions
    void KeccakF1600_StatePermute(void *state);
    int LFSR86540(UINT8 *LFSR);

// Rasta private functions //
    block Substitution (const block x);
        // The substitution layer

    block MultiplyWithGF2Matrix
        (const std::vector<block> matrix, const block message);
    std::vector<block> MultiplyGF2Matrix
            (const std::vector<block> A, const std::vector<block> B);
    std::vector<block> MultiplyGF2MatrixTransposed
                (const std::vector<block> A, const std::vector<block> B);
        // For the linear layer

    void generate_Instance_all_new(const UINT64 nonce, const UINT64 counter);
    void generate_Instance_lu(const UINT64 nonce, const UINT64 counter);
    void generate_Instance_randall(const UINT64 nonce, const UINT64 counter);
        //Fills the matrices and roundconstants with pseudorandom bits 
   
// Binary matrix functions //   
    unsigned rank_of_Matrix (const std::vector<block> matrix);

// Random bits functions //
    void  initrand (const UINT64 nonce, const UINT64 counter);
    block getrandblock ();
    block getrandblockfirstone (const unsigned int length);
    bool  getrandbit ();

};

#endif
