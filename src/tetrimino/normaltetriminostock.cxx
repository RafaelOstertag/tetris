#include "normaltetriminostock.hh"

#include <cassert>
#include <ctime>
#ifndef NDEBUG
#include <iostream>
#endif

namespace {
enum FactoryNumber {
    I_TETRIMINO = 0,
    J_TETRIMINO,
    L_TETRIMINO,
    S_TETRIMINO,
    Z_TETRIMINO,
    T_TETRIMINO,
    O_TETRIMION
};
}

NormalTetriminoStock::NormalTetriminoStock()
    : factories{}, prefetch{nullptr}, random{std::bind(
                                          std::normal_distribution<double>{3.5,
                                                                           1},
                                          std::mt19937(std::time(nullptr)))},
      lastFactoryNumber{-1}, drawsSinceITetrimino{0} {
    factories[I_TETRIMINO] = createITetrimino;
    factories[J_TETRIMINO] = createJTetrimino;
    factories[L_TETRIMINO] = createLTetrimino;
    factories[S_TETRIMINO] = createSTetrimino;
    factories[Z_TETRIMINO] = createZTetrimino;
    factories[T_TETRIMINO] = createTTetrimino;
    factories[O_TETRIMION] = createOTetrimino;

    prefetch = randomTetrimino();
}

std::shared_ptr<Tetrimino> NormalTetriminoStock::draw() {
    auto tetrimino = prefetch;
    prefetch = randomTetrimino();
    return tetrimino;
}

std::shared_ptr<Tetrimino> NormalTetriminoStock::preview() { return prefetch; }

std::shared_ptr<Tetrimino> NormalTetriminoStock::randomTetrimino() {
    int factoryNumber;

    do {
        factoryNumber = random();
    } while (factoryNumber == lastFactoryNumber || factoryNumber < 0 ||
             factoryNumber >= NUMBER_OF_TETRIMINOS);
    assert(factoryNumber >= 0 && factoryNumber < NUMBER_OF_TETRIMINOS);

    if (factoryNumber == I_TETRIMINO) {
        drawsSinceITetrimino = 0;
    } else {
        drawsSinceITetrimino++;
    }

    if (drawsSinceITetrimino > I_TETRIMINO_AT_LEAST_EVERY) {
#ifndef NDEBUG
        std::cout << "Curtesy I Tetrimino draw\n";
#endif
        factoryNumber = I_TETRIMINO;
        drawsSinceITetrimino = 0;
    }

    lastFactoryNumber = factoryNumber;
#ifndef NDEBUG
    std::cout << "Drew Tetrimino #" << factoryNumber << "\n";
#endif
    return factories[factoryNumber]();
}
