#include "tetriminostock.hh"

TetriminoStock::TetriminoStock() {
    factories[0] = createITetrimino;
    factories[1] = createJTetrimino;
    factories[2] = createLTetrimino;
    factories[3] = createOTetrimino;
    factories[4] = createTTetrimino;
    factories[5] = createSTetrimino;
    factories[6] = createZTetrimino;

    selectedFactory = 0;
}

std::shared_ptr<Tetrimino> TetriminoStock::draw() {
    std::shared_ptr<Tetrimino> tetrimino = factories[selectedFactory]();
    selectedFactory++;
    selectedFactory %= numberOfTetriminos;
    return tetrimino;
}
