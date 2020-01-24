#include <array>

///////////////////////////////////////////////////////////////////////////////
// pin
//
// Used to represent the pin in the board
///////////////////////////////////////////////////////////////////////////////

class pin {
public:
    pin() = delete;
    pin(const pin&) = default;
    pin(pin&&) = default;
    pin& operator=(const pin&) = default;
    pin& operator=(pin&&) = default;

    bool operator<(const pin& rhs) const;
    bool operator>(const pin& rhs) const;
    bool operator==(const pin& rhs) const;

    pin(double x, double y);
    pin(double x, double y, int row, int column);
    bool exists(double x, double y);

private:
    double x_coord;
    double y_coord;
    int row;
    int column;

    bool can_move_to_here(double x, double y);

    std::array <double, 6> move_angles = {60.0, 90.0, 150.0, 210.0, 270.0, 330.0};
};
