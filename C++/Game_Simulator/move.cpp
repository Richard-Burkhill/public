#include "move.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// Constructor for move.
// A move is defined by the location of two pieces and the location of a hole.
///////////////////////////////////////////////////////////////////////////////
move::move(double piece1_x, double piece1_y, double piece2_x, double piece2_y, double hole_x, double hole_y)
    : moved (false)
{
    hole = std::pair<double, double>(hole_x, hole_y);
    piece1 = std::pair<double, double>(piece1_x, piece1_y);
    piece2 = std::pair<double, double>(piece2_x, piece2_y);
}

///////////////////////////////////////////////////////////////////////////////
// Definition of < operator
///////////////////////////////////////////////////////////////////////////////
bool move::operator<(const move& rhs) const
{
    bool return_value = false;
    if (hole < rhs.hole){
        return_value = true;
    }
    else if(hole == rhs.hole){
        if (piece1 < rhs.piece1){
            return_value = true;
        }
    }
    return return_value;
}

///////////////////////////////////////////////////////////////////////////////
// Definition of > operator
///////////////////////////////////////////////////////////////////////////////
bool move::operator>(const move& rhs) const
{
    bool return_value = false;
    if (hole > rhs.hole){
        return_value = true;
    }
    else if(hole == rhs.hole){
        if (piece1 > rhs.piece1){
            return_value = true;
        }
    }
    return return_value;
}

///////////////////////////////////////////////////////////////////////////////
// Definition of equivalence operator
///////////////////////////////////////////////////////////////////////////////
bool move::operator==(const move& rhs) const
{
    return ((hole == rhs.hole) && (piece1 == rhs.piece1));
}

///////////////////////////////////////////////////////////////////////////////
// Add a list of alternative moves
///////////////////////////////////////////////////////////////////////////////
void move::add_further_moves(std::list<move> further_moves)
{
    list_of_further_moves = further_moves;
}

///////////////////////////////////////////////////////////////////////////////
// Are there any listed moves left to execute
///////////////////////////////////////////////////////////////////////////////
bool move::can_move(std::pair<double, double>& next_piece1, std::pair<double, double>& next_piece2, std::pair<double, double>& next_hole)
{
    if (!moved){
        next_hole = hole;
        next_piece1 = piece1;
        next_piece2 = piece2;
        moved = true;
        std::cout << piece2.first << " " << piece2.second << " into " << hole.first << " " << hole.second << " ";
        return true;
    }


    for (std::list<move>::iterator moves_iter = list_of_further_moves.begin(); moves_iter != list_of_further_moves.end(); ++moves_iter)
    {
        if (!(*moves_iter).moved){
            next_hole = (*moves_iter).hole;
            next_piece1 = (*moves_iter).piece1;
            next_piece2 = (*moves_iter).piece2;
            (*moves_iter).moved = true;
            list_of_further_moves.insert(moves_iter, *moves_iter);
            std::cout << (*moves_iter).piece2.first << " " << (*moves_iter).piece2.second << " into " << (*moves_iter).hole.first << " " << (*moves_iter).hole.second << " ";
            return true;
        }
    }

    return false;
}

