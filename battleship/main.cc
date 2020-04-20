#include <unistd.h>  // Need usleep function (Unix systems only: Mac and Linux)
#include <iostream>

#include "random.h"
#include "board.h"
#include "player.h"

using namespace battleship;

static const int timestep = 1e6;  // Delay to use when sleeping: 1e6 = 1 second

int * AskUserForBoardSize() {
    // Ask user for Board size (number of rows and columns)
    int rows = 0, cols = 0;
    std::cout << "Choose board size (example: 6 rows, 8 columns)" << std::endl;
    std::cout << "Enter number of rows:    ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;
    if (rows <= 0 || cols <= 0) {
        // Set default Board size if either user-chosen size is invalid
        std::cout << "Chosen size is invalid: " << Board::CoordStr(rows, cols);
        rows = 6;
        cols = 8;
        std::cout << " -> Default: " << Board::CoordStr(rows, cols) << std::endl;
    }
    int *size = new int[2];
    size[0] = rows;
    size[1] = cols;
    return size;
}

void PlaceShipsFixed(Board& board) {
    // Place ships at fixed coordinates
    bool result;
    std::cout << "Placing ships at fixed coordinates..." << std::endl;
    usleep(2 * timestep);  // Sleep before placing ships
    // This ship placement should succeed
    std::cout << "Placing ship from (1, 3) to (2, 3)";
    result = board.PlaceShipVertical(1, 2, 3);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should succeed
    std::cout << "Placing ship from (2, 1) to (4, 1)";
    result = board.PlaceShipVertical(2, 4, 1);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should succeed
    std::cout << "Placing ship from (1, 5) to (1, 7)";
    result = board.PlaceShipHorizontal(1, 5, 7);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should fail because its last cell is out of bounds
    std::cout << "Placing ship from (3, 2) to (6, 2)";
    result = board.PlaceShipVertical(3, 6, 2);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should succeed
    std::cout << "Placing ship from (4, 3) to (4, 6)";
    result = board.PlaceShipHorizontal(4, 3, 6);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should fail because it overlaps with another ship
    std::cout << "Placing ship from (2, 4) to (5, 4)";
    result = board.PlaceShipVertical(2, 5, 4);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    usleep(timestep);  // Sleep after placing ship
    // This ship placement should succeed
    std::cout << "Placing ship from (3, 7) to (5, 7)";
    result = board.PlaceShipVertical(3, 5, 7);
    std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
    board.Print();
    std::cout << "Placed ships at fixed coordinates" << std::endl;
    usleep(timestep);  // Sleep after placing ship
}

void PlaceShipsRandom(Board& board) {
    // Place ships at random coordinates
    std::cout << "Placing ships at random coordinates..." << std::endl;
    usleep(2 * timestep);  // Sleep before placing ships
    const int kShips = 5;
    RandomGenerator random;
    int row, col, size, count = 0;
    bool vertical, result;
    std::string orientation;
    for (int ship = 1; ship <= kShips; ++ship) {
        // Generate random ship orientation, size, and coordinates
        vertical = static_cast<bool>(random.RandomInt(0, 1));
        size = random.RandomInt(1, (vertical ? board.Rows() : board.Cols()));
        row = random.RandomInt(0, board.Rows() - (vertical ? size : 1));
        col = random.RandomInt(0, board.Cols() - (vertical ? 1 : size));
        orientation = (vertical ? "vertically" : "horizontally");
        std::cout << "Placing ship #" << ship << " " << orientation <<
            " at " << Board::CoordStr(row, col) << " with size " << size;
        if (vertical)
            result = board.PlaceShipVertical(row, row + size - 1, col);
        else
            result = board.PlaceShipHorizontal(row, col, col + size - 1);
        count += static_cast<int>(result);
        std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
        board.Print();
        usleep(timestep);  // Sleep after placing ship
    }
    std::cout << "Placed " << kShips << " ships at random coordinates (" <<
        count << " succeeded, " << kShips - count << " failed)" << std::endl;
    usleep(timestep);  // Sleep after placing all ships
}

void PlaceShipsUser(Board& board) {
    // Place ships at user-chosen coordinates
    const int kShips = 3;
    int row, col, size, count = 0;
    bool vertical, result;
    std::string v_or_h, orientation;
    for (int ship = 1; ship <= kShips; ++ship) {
        std::cout << "Place ship #" << ship << "..." << std::endl;
        std::cout << "Vertical or horizontal?  Enter v or h: ";
        std::cin >> v_or_h;
        // Vertical if first letter is "v" or horizontal if any other letter
        vertical = strncmp(v_or_h.c_str(), "v", 1) == 0;
        orientation = (vertical ? "vertically" : "horizontally");
        std::cout << "Enter size:   ";
        std::cin >> size;
        std::cout << "Enter row:    ";
        std::cin >> row;
        std::cout << "Enter column: ";
        std::cin >> col;
        std::cout << "Placing ship #" << ship << " " << orientation <<
            " at " << Board::CoordStr(row, col) << " with size " << size;
        if (vertical)
            result = board.PlaceShipVertical(row, row + size - 1, col);
        else
            result = board.PlaceShipHorizontal(row, col, col + size - 1);
        count += static_cast<int>(result);
        std::cout << " -> " << (result ? "succeeded" : "failed") << std::endl;
        board.Print();
        usleep(timestep);  // Sleep after placing ship
    }
    std::cout << "Placed " << kShips << " ships at chosen coordinates (" <<
        count << " succeeded, " << kShips - count << " failed)" << std::endl;
    usleep(timestep);  // Sleep after placing all ships
}

void FireMissilesFixed(Board& board) {
    // Fire missiles at fixed coordinates
    std::cout << "Firing missiles at fixed coordinates..." << std::endl;
    usleep(2 * timestep);  // Sleep before firing missiles
    const int kMissiles = board.Rows() * board.Cols() / 4;
    int row = 1, col = 1, count = 0;
    bool result;
    for (int missile = 1; missile <= kMissiles; ++missile) {
        // Generate diagonal missile coordinates
        row = (row + 1) % board.Rows();
        col = (col + 2) % board.Cols();
        std::cout << "Firing missile #" << missile << " at " <<
            Board::CoordStr(row, col);
        result = board.FireMissile(row, col);
        count += static_cast<int>(result);
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        // Print board after half and all missiles have been fired
        if (missile % (kMissiles / 2) == 0) {
            board.Print();
        }
        usleep(timestep / 2);  // Sleep after firing missile
    }
    std::cout << "Fired " << kMissiles << " missiles at fixed coordinates (" <<
        count << " hit, " << kMissiles - count << " missed)" << std::endl;
    usleep(timestep);  // Sleep after firing all missiles
}

void FireMissilesRandom(Board& board) {
    // Fire missiles at random coordinates
    std::cout << "Firing missiles at random coordinates..." << std::endl;
    usleep(2 * timestep);  // Sleep before firing missiles
    const int kMissiles = board.Rows() * board.Cols() / 4;
    RandomGenerator random;
    int row, col, count = 0;
    bool result;
    for (int missile = 1; missile <= kMissiles; ++missile) {
        // Generate random missile coordinates
        row = random.RandomInt(0, board.Rows() - 1);
        col = random.RandomInt(0, board.Cols() - 1);
        std::cout << "Firing missile #" << missile << " at " <<
            Board::CoordStr(row, col);
        result = board.FireMissile(row, col);
        count += static_cast<int>(result);
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        // Print board after half and all missiles have been fired
        if (missile % (kMissiles / 2) == 0)
            board.Print();
        usleep(timestep / 2);  // Sleep after firing missile
    }
    std::cout << "Fired " << kMissiles << " missiles at random coordinates (" <<
        count << " hit, " << kMissiles - count << " missed)" << std::endl;
    usleep(timestep);  // Sleep after firing all missiles
}

void FireMissilesUser(Board& board) {
    // Fire missiles at user-chosen coordinates
    const int kMissiles = 10;
    int row, col, count = 0;
    bool result;
    for (int missile = 1; missile <= kMissiles; ++missile) {
        std::cout << "Fire missile #" << missile << "..." << std::endl;
        std::cout << "Enter row:    ";
        std::cin >> row;
        std::cout << "Enter column: ";
        std::cin >> col;
        std::cout << "Firing missile at " << Board::CoordStr(row, col);
        result = board.FireMissile(row, col);
        count += static_cast<int>(result);
        std::cout << " -> " << (result ? "HIT" : "MISS") << std::endl;
        board.Print();
        usleep(timestep / 2);  // Sleep after firing missile
    }
    std::cout << "Fired " << kMissiles << " missiles at chosen coordinates (" <<
        count << " hit, " << kMissiles - count << " missed)" << std::endl;
}

void TestPlayer(const Board& board) {
    // Create a new Player with a default name
    Player player = Player("Name");
    // Test method to get board size from user
    const int *size = player.GetBoardSize();
    std::cout << "Returned board size: " << size[0] << " rows, " <<
                                            size[1] << " columns" << std::endl;
    delete [] size;
    // Test method to get ship orientation, size, and coordinates from user
    const int *ship_coords = player.GetShipCoords(board);
    const std::string orientation = (ship_coords[3] == 1 ? "vertical" : "horizontal");
    std::cout << "Returned ship placement info: " << orientation << " ship with size " <<
        ship_coords[2] << " at " << Board::CoordStr(ship_coords[0], ship_coords[1]) << std::endl;
    delete [] ship_coords;
    // Test method to get missile coordinates from user
    const int *missile_coords = player.GetMissileCoords(board);
    std::cout << "Returned missile coordinates: " << Board::CoordStr(missile_coords[0], missile_coords[1]) << std::endl;
    delete [] missile_coords;
}

int main(int argc, const char * argv[]) {
    int rows = 6, cols = 8;
    // Ask user for board size, then update rows and cols
    // int *size = AskUserForBoardSize();
    // rows = size[0];
    // cols = size[1];
    // delete [] size;
    // Create a new Board
    Board board = Board(rows, cols);
    // board.Print();
    // PlaceShipsFixed(board);
    // PlaceShipsRandom(board);
    // PlaceShipsUser(board);
    // FireMissilesFixed(board);
    // FireMissilesRandom(board);
    // FireMissilesUser(board);
    TestPlayer(board);
}
