#include <utility>
#include <list>

///////////////////////////////////////////////////////////////////////////////
// move
//
// Used to represent a possible move on the board.
// Also contains a list of possible alternative moves.
///////////////////////////////////////////////////////////////////////////////

class move{
public:
    move() = default;
    move(const move&) = default;
    move(move&&) = default;
    move& operator=(const move&) = default;
    move& operator=(move&&) = default;

    bool operator<(const move& rhs) const;
    bool operator>(const move& rhs) const;
    bool operator==(const move& rhs) const;

    move(double piece1_x, double piece1_y, double piece2_x, double piece2_y, double hole_x, double hole_y);
    void add_further_moves(std::list<move> further_moves);
    bool can_move(std::pair<double, double>& next_piece1, std::pair<double, double>& next_piece2, std::pair<double, double>& next_hole);
    void get_next_move(std::pair<double, double>& piece1, std::pair<double, double>& piece2, std::pair<double, double>& hole);
private:
    std::pair<double, double> hole;
    std::pair<double, double> piece1;
    std::pair<double, double> piece2;
    std::list<move> list_of_further_moves;

    bool moved;
};
