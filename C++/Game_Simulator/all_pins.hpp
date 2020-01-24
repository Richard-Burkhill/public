#include <vector>
#include <list>

#include "pin.hpp"
#include "move.hpp"

#define PI 3.141592653589793238

///////////////////////////////////////////////////////////////////////////////
// all_pins
//
// Used to represent the board containing all the pins.
//      /I\
//     /I I\
//    /I I I\
//   /I I I I\
//  /I I I I I\
//  -----------
///////////////////////////////////////////////////////////////////////////////

class all_pins
{
public:
    all_pins (int pins_on_side);

private:
    bool find_holes();

    bool exists(double x, double y);
    bool list_moves_to_here(double x, double y);

    void play_moves();
    void play_move(std::pair<double, double> piece1, std::pair<double, double> piece2, std::pair<double, double> hole);
    void reverse_move(std::pair<double, double> piece1, std::pair<double, double> piece2, std::pair<double, double> hole);

    void remove(std::pair<double, double> piece);
    void add(std::pair<double, double> piece);

    int game_size;
    static constexpr int triangle_angle = 60;
    static constexpr double to_radians = PI/180.0;

    std::vector<pin> vector_of_pins;
    std::array <double, 6> move_angles = {60.0, 90.0, 150.0, 210.0, 270.0, 330.0};
    std::list<move> list_of_holes;
};
