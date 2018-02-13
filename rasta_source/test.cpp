#include "Rasta.h"
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <array>
#include <set>

//////////////////
//     MAIN     //
//////////////////

//int main () {
//    // Example usage of the Rasta class
//
//    Rasta cipher(0, randall);
//
//    std::mt19937 generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
//    std::uniform_int_distribution<unsigned long long> randomstate;
//
//
//    unsigned int iter = 100;
//
//    for(unsigned int i = 0; i < iter; ++i){
//      block m = randomstate(generator);
//      block c1 = 0;
//      block m2 = 0;
//      keyblock key;
//      for(unsigned int j = 0; j < blocksize; j++)
//        key[j] = randomstate(generator) & 1;
//      cipher.set_key(key);
//      c1 = cipher.crypt(m,0,i);
//      m2 = cipher.crypt(c1,0,i);
//      if(m != m2){
//       std::cout << "Error!" << std::endl;
//       return -1;
//      }
//    }
//
//    std::cout << "Test passed." << std::endl;
//
//    return 0;
//}

//int main () {
//    // Example usage of the Rasta class
//    Rasta cipher(0, randall);
//
//    std::mt19937 generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
//    std::uniform_int_distribution<unsigned long long> randomstate;
//
//    unsigned int iter = 100;
//
//    for(unsigned int i = 0; i < iter; ++i){
//      block m = 0;;
//      m = cipher.crypt(m,0,i);
//      std::cout << m << std::endl;
//    }
//
//
//    return 0;
//}

int main() {
  // Example usage of the Rasta class
  // Blocksize and number of rounds can be configured in Rasta.h
  Rasta cipher(0xFFD54AA, randall);
  block m;
  keyblock key;

  std::mt19937 generator(
      std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<unsigned long long> randomstate;

  for (unsigned int j = 0; j < blocksize; j++)
    key[j] = randomstate(generator) & 1;
  cipher.set_key(key);

  for (unsigned int j = 0; j < blocksize; j++)
    m[j] = randomstate(generator) & 1;

  std::cout << "Plaintext:" << std::endl;
  std::cout << m << std::endl;
  m = cipher.crypt(m, 0, 1);
  std::cout << "Ciphertext:" << std::endl;
  std::cout << m << std::endl;
  m = cipher.crypt(m, 0, 1);
  std::cout << "Encryption followed by decryption of plaintext:" << std::endl;
  std::cout << m << std::endl;

  return 0;
}

