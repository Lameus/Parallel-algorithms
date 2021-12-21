#include <stdio.h>
#include <iostream>
#include <typeinfo>


int word_counter(int argc, char* text)
{
	int number = 0;
	bool is_space = true;
	if (argc == 1) 
	{ // if input is empty
		std::cout << "Empty";
		return 0;
	}

    while (*text)
    {
        if (*text == ' ' || *text == '\n' || *text == '\t')
		{
            is_space = true;
        }
		else if (is_space)
		{
			is_space = false;
         	++number;
		}
		++text;
    }
 
    std::cout << "Number of words: " << number << std::endl;
	return 0;
}


int main(int argc, char* argv[]){
	// std::cout << "enter your string here \n";
	// getline(std::cin, text); // because cin considers a space as an end
	word_counter(argc, argv[1]);

	return 0;
}
