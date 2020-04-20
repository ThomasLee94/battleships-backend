#include "player.h"

#include <string>
#include <iostream>

namespace battleship {

Player::Player(const std::string name)
        : name_(name) {
}

const int * Player::GetBoardSize() const {
    static const int kMinBoardSize[] = {2, 3};  // Min board size: (rows, cols)
    int *size = new int[2]();  // Store user-chosen board size: (rows, cols)
    // Ask user for each dimension of board size: first rows, then cols
    std::cout << "Choose board size (example: 6 rows, 8 columns)" << std::endl;
    int dimension = 0;  // Dimension of board size: 0 = rows, 1 = cols
    while (dimension < 2) {
        const std::string rows_or_cols = (dimension == 0 ? "rows" : "columns");
        std::cout << "Enter number of " << rows_or_cols << ":   ";
        std::cin >> size[dimension];
        // Check if user-chosen size is valid
        if (size[dimension] >= kMinBoardSize[dimension])
            ++dimension;  // Valid, so get next dimension (rows -> cols -> done)
        else
            std::cout << "Invalid number of " << rows_or_cols << ": " <<
                                                 size[dimension] << std::endl;
    }
    // Once validated, show user their chosen board size
    std::cout << "Chosen board size: " << size[0] << " rows, " <<
                                          size[1] << " columns" << std::endl;
    return size;
}

const int * Player::GetShipCoords(const Board& board) const {
    const int *board_size = board.Size();  // Board size: (rows, cols)
    int *coords = new int[4]();  // Ship coordinates: (row, col, size, vertical)

    // Ask user for ship orientation: vertical or horizontal
    std::cout << "Choose ship orientation: vertical or horizontal" << std::endl;
    std::string v_or_h, orientation;  // Strings for user input and output
    bool vertical, horizontal;  // Ship orientation: vertical xor horizontal
    while (true) {
        std::cout << "Enter 'v' or 'h': ";
        std::cin >> v_or_h;
        // Check first letter or response: vertical if "v" or horizontal if "h"
        vertical   = strncmp(v_or_h.c_str(), "v", 1) == 0;
        horizontal = strncmp(v_or_h.c_str(), "h", 1) == 0;
        // Check if user-chosen ship orientation is valid
        if (vertical || horizontal)
            break;  // Valid, so advance to choosing ship size
        else
            std::cout << "Invalid input:    " << v_or_h << std::endl;
    }
    // Once validated, show user their chosen ship orientation
    orientation = (vertical ? "vertical" : "horizontal");
    std::cout << "Chosen ship orientation: " << orientation << std::endl;
    coords[3] = static_cast<int>(vertical);

    // Calculate min and max ship size considering ship orientation (dimension)
    const int ship_dimension = static_cast<int>(horizontal);  // false/true -> 0/1 (rows/cols)
    const int min_ship_size = std::min(board_size[ship_dimension], 2);
    const int max_ship_size = std::min(board_size[ship_dimension], 5);
    // Ask user for ship size
    std::cout << "Choose ship size (min: " << min_ship_size <<
                                 ", max: " << max_ship_size << ")" << std::endl;
    int size = 0;
    while (true) {
        std::cout << "Enter size:   ";
        std::cin >> size;
        // Check if user-chosen ship size is valid (in range on its dimension)
        if (min_ship_size <= size && size <= max_ship_size)
            break;  // Valid, so advance to choosing ship coordinates
        else
            std::cout << "Invalid size: " << size << std::endl;
    }
    // Once validated, show user their chosen ship size
    std::cout << "Chosen ship size: " << size << std::endl;
    coords[2] = size;

    // Ask user for each dimension of ship coordinates: first row, then col
    std::cout << "Choose ship coordinates: (row, column)" << std::endl;
    int dimension = 0;  // Dimension of ship coordinates: 0 = row, 1 = col
    while (dimension < 2) {
        const std::string row_or_col = (dimension == 0 ? "row" : "column");
        std::cout << "Enter " << row_or_col << ":   ";
        std::cin >> coords[dimension];
        // Check if user-chosen ship coordinate is valid considering ship size
        const int ship_size_this_dim = (dimension == horizontal ? size : 1);
        const int max_ship_coord = board_size[dimension] - ship_size_this_dim;
        if (0 <= coords[dimension] && coords[dimension] <= max_ship_coord)
            ++dimension;  // Valid, so get next dimension (row -> col -> done)
        else
            std::cout << "Invalid " << row_or_col << ": " <<
                                       coords[dimension] << std::endl;
    }
    // Once validated, show user their chosen ship coordinates
    std::cout << "Chosen ship coordinates: " << Board::CoordStr(coords[0], coords[1]) << std::endl;
    std::cout << "Chosen ship placement summary: " << orientation <<
        " ship with size " << size << " at " << Board::CoordStr(coords[0], coords[1]) << std::endl;
    return coords;
}

const int * Player::GetMissileCoords(const Board& board) const {
    const int *board_size = board.Size();  // Board size: (rows, cols)
    int *coords = new int[2]();  // Missile coordinates: (row, col)

    // Ask user for each dimension of missile coordinates: first row, then col
    std::cout << "Choose missile coordinates: (row, column)" << std::endl;
    int dimension = 0;  // Dimension of missile coordinates: 0 = row, 1 = col
    while (dimension < 2) {
        const std::string row_or_col = (dimension == 0 ? "row" : "column");
        std::cout << "Enter " << row_or_col << ":   ";
        std::cin >> coords[dimension];
        // Check if user-chosen missile coordinate is valid
        if (0 <= coords[dimension] && coords[dimension] < board_size[dimension])
            ++dimension;  // Valid, so get next dimension (row -> col -> done)
        else
            std::cout << "Invalid " << row_or_col << ": " <<
                                       coords[dimension] << std::endl;
    }
    // Once validated, show user their chosen missile coordinates
    std::cout << "Chosen missile coordinates: " << Board::CoordStr(coords[0], coords[1]) << std::endl;
    return coords;
}

} // namepace battleship
