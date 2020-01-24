#include "all_pins.hpp"

#include <math.h>
#include <algorithm>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// Constructor to initialize the board.
//      /I\
//     /I I\
//    /I I I\
//   /I I I I\
//  /I I I I I\
///////////////////////////////////////////////////////////////////////////////
all_pins::all_pins (int pins_on_side)
   : game_size (pins_on_side)
{
    double x_coord = 0.0;
    double y_coord = 0.0;

    int pins_on_row = game_size;

    for (int column = 0; column < game_size; column++)
    {
        y_coord = column;
        for (int row = 0; row < pins_on_row; row++)
        {
            x_coord = (row + (column * sin(triangle_angle*to_radians))); //degrees to radians
            vector_of_pins.insert(vector_of_pins.end(), pin(x_coord, y_coord, row, column));
        }
        pins_on_row--;
    }
    remove(std::pair<double, double>(0.0, 0.0));
    find_holes();
}

///////////////////////////////////////////////////////////////////////////////
// List the possible moves to this location (of a hole)
///////////////////////////////////////////////////////////////////////////////
bool all_pins::list_moves_to_here(double x, double y)
{
    move next_hole;
    std::list<move> list_of_moves_into_hole;
    bool return_value = false;
    double first_piece_x_coord = 0.0;
    double first_piece_y_coord = 0.0;
    double second_piece_x_coord = 0.0;
    double second_piece_y_coord = 0.0;

    if (!exists(x, y)){
        for(auto angle : move_angles){
            first_piece_x_coord = x + sin(angle*to_radians);
            first_piece_y_coord = round (y + cos(angle*to_radians));
            if (exists(first_piece_x_coord, first_piece_y_coord)){
				second_piece_x_coord = first_piece_x_coord + sin(angle*to_radians);
				second_piece_y_coord = round (first_piece_y_coord + cos(angle*to_radians));
				if (exists(second_piece_x_coord, second_piece_y_coord)){
					if (return_value){
						list_of_moves_into_hole.push_back(move(first_piece_x_coord, first_piece_y_coord, second_piece_x_coord, second_piece_y_coord, x, y));
					}
					else{
						next_hole = move(first_piece_x_coord, first_piece_y_coord, second_piece_x_coord, second_piece_y_coord, x, y);
					}
					return_value = true;
				}
            }
        }
    }

    if (return_value){
    	next_hole.add_further_moves(list_of_moves_into_hole);
        list_of_holes.push_back(next_hole);
    }
    return return_value;
}

///////////////////////////////////////////////////////////////////////////////
// Does the pin at this location exist
///////////////////////////////////////////////////////////////////////////////
bool all_pins::exists(double x, double y)
{
    bool return_value = false;

    std::vector<pin>::const_iterator result;
    result = find_if (vector_of_pins.begin(), vector_of_pins.end(), [x, y] (pin const& each_pin) { return (pin(x, y) == each_pin);});
    if (result != vector_of_pins.end()){
        return_value = true;
    }

    return return_value;
}

///////////////////////////////////////////////////////////////////////////////
// Find all the holes on the board
///////////////////////////////////////////////////////////////////////////////
bool all_pins::find_holes()
{
    double x_coord = 0.0;
    double y_coord = 0.0;
    int pins_on_row = game_size;

    bool return_value = false;
    for (int column = 0; column < game_size; column++)
    {
        y_coord = column;
        for (int row = 0; row < pins_on_row--; row++)
        {
            x_coord = (row + (column * sin(triangle_angle*to_radians))); //degrees to radians
            if (!exists(x_coord, y_coord))
            {
                list_moves_to_here(x_coord, y_coord);
                return_value = true;
            }
        }
    }
    return return_value;
}

///////////////////////////////////////////////////////////////////////////////
// Play all the moves until win or stale-mate
///////////////////////////////////////////////////////////////////////////////
void all_pins::play_moves()
{
    std::pair<double, double> piece1;
    std::pair<double, double> piece2;
    std::pair<double, double> hole;
    int pin_count = 0;
    int move_count = 0;

    for(move next_hole : list_of_holes){

		while (next_hole.can_move(piece1, piece2, hole)){
			//then move
			play_move(piece1, piece2, hole);
			move_count++;
		}
		std::cout << std::endl;
		for (int i=0; i<move_count; i++){
			std::cout << "\t";
		}
		while (!next_hole.can_move(piece1, piece2, hole)){
			//count the number of pins left on the board
			for (auto each_pin : vector_of_pins){
				pin_count++;
			}
			reverse_move(piece1, piece2, hole);
			move_count--;
		}
		play_moves();
    }
}
///////////////////////////////////////////////////////////////////////////////
// Play the move, a pin must jump over another pin, to fill the hole.
// Remove the pin that is jumped.
///////////////////////////////////////////////////////////////////////////////
void all_pins::play_move(std::pair<double, double> piece1, std::pair<double, double> piece2, std::pair<double, double> hole)
{
    //hole is filled with piece2
    remove (piece2);
    add (hole);

    //piece1 is deleted
    remove (piece1);
}

///////////////////////////////////////////////////////////////////////////////
// Reverse the move, so we may explore the other possible moves.
// Move the pin back to make the hole again.
// Replace the jumped pin.
///////////////////////////////////////////////////////////////////////////////
void all_pins::reverse_move(std::pair<double, double> piece1, std::pair<double, double> piece2, std::pair<double, double> hole)
{
    //piece2 is filled with hole
    add (piece2);
    remove (hole);

    //piece1 is replaced
    add (piece1);
}

///////////////////////////////////////////////////////////////////////////////
// Remove, a piece from the board
///////////////////////////////////////////////////////////////////////////////
void all_pins::remove(std::pair<double, double> piece)
{
    std::vector<pin>::iterator result;
    result = find_if (vector_of_pins.begin(), vector_of_pins.end(), [piece] (pin const& each_pin) { return (pin(piece.first, piece.second) == each_pin);});
    if (result != vector_of_pins.end()){
        vector_of_pins.erase(result);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Add, a piece to the board
///////////////////////////////////////////////////////////////////////////////
void all_pins::add(std::pair<double, double> piece)
{
    vector_of_pins.push_back(pin(piece.first, piece.second));
}
