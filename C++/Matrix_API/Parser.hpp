#include <string>
#include <vector>

class Parser{
public:
    void parse_var_or_num (std::string line);
    void parse_operator (std::string line);

    void parse_num (std::string line);
    bool is_comma_or_space_then_another_number (std::string line);
    void define_matrix(std::string number, std::string line, std::vector<double>& column);
    bool is_semi_colon_then_another_number (std::string line);

private:
    int index = 0;
    std::string variable;
    std::string number;
    std::vector<std::vector<double>> rows;
    std::vector<double> column;
};
