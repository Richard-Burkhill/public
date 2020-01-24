#include <iostream> 
#include <set> 
#include <iterator> 
#include <fstream>
#include <string>
#include <cstring>

bool is_anagram (std::string word1, std::string word2)
{
   bool return_value = false;
   std::multiset <char> potential_anagram;
   std::multiset <char> of_word;

   const char* cstr_word1 = word1.c_str();
   const char* cstr_word2 = word2.c_str();
   for (size_t i = 0; i < word1.length(); i++)
   { 
      potential_anagram.insert(cstr_word1[i]);
   }

   for (size_t i = 0; i < word2.length(); i++)
   { 
      of_word.insert(cstr_word2[i]);
   }

   if (potential_anagram == of_word)
   {
      return_value = true;
   }
   return return_value;	
}

int main(int argc, char** argv) 
{ 
   if (argc == 2)
   {
      std::ifstream dictionary_of_words_on_each_line1 ("words.txt", std::ifstream::in);

      std::string word1;
      while (std::getline(dictionary_of_words_on_each_line1, word1))
      {
         std::ifstream dictionary_of_words_on_each_line2 ("words.txt", std::ifstream::in);

         //std::string word2;
         int count = 0;
         //while (std::getline(dictionary_of_words_on_each_line2, word2))
         //{
         //   if (is_anagram(word1, word2))
         //   {
         //      count++;
         //   }
         //}
         if (is_anagram(word1, argv[1]))
         {
            count++;
         }

         if (count > 0)
         {
            std::cout << word1 << std::endl;
         }
         dictionary_of_words_on_each_line2.close();
      }
      dictionary_of_words_on_each_line1.close();
   }
}
