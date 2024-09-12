#include "ship.h"

// using namespace std;

Ship::Ship(int given_length){
    size = given_length;
    health = given_length;
    og_health = given_length;
}

int Ship::Hit(){
    health--;
    if(health == 0){
        if(og_health > 4){
            std::cout << "You got the T-ship!" << std::endl;
            return 1;
        }
        std::cout << "You got the " << size << " long ship!" << std::endl;
        return 1;
    }
    
    return 0;
}

void Ship::AssignCoords(vector<vector<char>> &usable_coords, int seed){
    // Providing a seed value
    srand(time(NULL) * seed);

	// Get a random number
	int num_letter = (rand() * 3) % 10;
    // int num_letter = 5;
    int number = rand() % 10;
    // int number = 9;
    int direction = rand() % 4;
    // int direction = 0;

    // make the random number a letter
    char letter = num_letter + 65;
    // the board is 10 by 10 so just make sure that all 10 by 10 numbers/letters are there and if not adjust properly
    int proper_size = 10;
    // flag to make sure a certain direction works so it can set coords in that direction.
    bool flag = false;

    //sets the y position of the ship and makes sure it actually works and goes to the next number if the vector is empty
    while(usable_coords.at(number).size() == 0){
        if(usable_coords.size() < proper_size){
            number -= (proper_size - usable_coords.size());
        }
        else if(usable_coords.at(number).size() == 0 && number + 1 < proper_size && number >= 0){
            number++;
        }
        else if (usable_coords.at(number).size() == 0){
            number = 0;
        }
    }

    // used to find where the letter you need is in the vector
    int letter_pos = num_letter;

    // can tell if the vector has shrunk and by how much then accounts for it when finding where to look for the adjecent letters
    if(proper_size > usable_coords.at(number).size()){
        letter_pos -= proper_size - usable_coords.at(number).size();
        if(letter_pos < 0){
            letter_pos = 0;
        }
    }

    //makes sure the letter is usable but if not it goes to the next letter to see if its usable
    while(flag != true){
        if(usable_coords.at(number).at(letter_pos) == letter){
            flag = true;
            break;
        }
        else if(letter < 'J'){
            letter++;
        }
        else{
            letter = 'A';
        }
    }

    // resets the value of num_letter to match the letter it's actually going for
    num_letter = letter - 65;
    flag = false;
    int count = 0;


    while(count < 4 && flag == false){
        switch(direction){
        case 0:
            // go to left
            //checks to see if the ship will go out of the boundries if it goes this direction
            if(letter >= (usable_coords.at(number).at(0) + size - 1)){
                //checks to see if the coords needed for this direction are available
                for(int i = 1; i < size; i++){
                    flag = true;
                    if(letter - i != usable_coords.at(number).at(letter_pos - i)){
                        flag = false;
                        break;
                    }
                }
                if(flag == true){
                    map<int, char> temp;
                    //fills the vector with the coords its now taking up
                    for(int i = 0; i < size; i++){
                        temp = {{number, letter - i}};
                        placement.push_back(temp);
                        temp.clear();
                    }
                    // erases the used coords from the available coords vector
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos - i));
                    }
                    break;
                }
            }
            count++;
        case 1:
            //right
            if((letter + size - 1) <= usable_coords.at(number).at(usable_coords.at(number).size() - 1)){
                for(int i = 1; i < size; i++){
                    flag = true;
                    if(letter + i != usable_coords.at(number).at(letter_pos + i)){
                        flag = false;
                        break;
                    }
                }
                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number, letter + i}};
                        placement.push_back(temp);
                        temp.clear();
                    }
                    // erases the used coords from the available coords vector
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos));
                    }
                    break;
                }
            }
            count++;
        case 2:
            //up
            if(number - (size - 1) >= 0){
                for(int i = number; i > (number - (size - 1)); i--){
                    flag = true;
                    if(std::find(usable_coords.at(number).begin(), usable_coords.at(number).end(), letter) == usable_coords.at(number).end() && usable_coords.at(number).back() != letter){
                        flag = false;
                        break;
                    }
                }
                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number - i, letter}};
                        placement.push_back(temp);
                        temp.clear();
                    }
                    // erases the used coords from the available coords vector
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number - i).erase(usable_coords.at(number - i).begin() + (letter_pos));
                    }
                    break;
                }
            }
            count++;
        case 3:
            //down
            if(number + (size - 1) < usable_coords.size()){
                for(int i = 0; i < size; i++){
                    flag = true;
                    if(std::find(usable_coords.at(number).begin(), usable_coords.at(number).end(), letter) == usable_coords.at(number).end() && usable_coords.at(number).back() != letter){
                        flag = false;
                        break;
                    }
                }
                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number + i, letter}};
                        placement.push_back(temp);
                        temp.clear();
                    }
                    // erases the used coords from the available coords vector
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number + 1).erase(usable_coords.at(number + 1).begin() + (letter_pos));
                    }
                    break;
                }
            }
            if(direction == 3){
                direction = 0;
            }
            count++;
        }

    } 
    
}

T_Ship::T_Ship(int given_length){
    size = given_length;
    health = given_length + 2;
    og_health = given_length + 2;
}

void T_Ship::AssignCoords(std::vector<std::vector<char>> &usable_coords, int seed){
    // Providing a seed value
    srand(time(NULL) * seed);

	// Get a random number
	int num_letter = (rand() * 3) % 10;
    // int num_letter = 9;
    int number = rand() % 10;
    // int number = 0;
    int direction = rand() % 4;
    // int direction = 3;

    // make the random number a letter
    char letter = num_letter + 65;
    // the board is 10 by 10 so just make sure that all 10 by 10 numbers/letters are there and if not adjust properly
    int proper_size = 10;
    // flag to make sure a certain direction works so it can set coords in that direction.
    bool flag = false;

    //sets the y position of the ship and makes sure it actually works and goes to the next number if the vector is empty
    while(usable_coords.at(number).size() == 0){
        if(usable_coords.size() < proper_size){
            number -= (proper_size - usable_coords.size());
        }
        else if(usable_coords.at(number).size() <= 4 && number + 1 < proper_size && number >= 0){
            number++;
        }
        else if (usable_coords.at(number).size() == 0){
            number = 0;
        }
    }

    // used to find where the letter you need is in the vector
    int letter_pos = num_letter;

    // can tell if the vector has shrunk and by how much then accounts for it
    if(proper_size > usable_coords.at(number).size()){
        letter_pos -= proper_size - usable_coords.at(number).size();
        if(letter_pos < 0){
            letter_pos = 0;
        }
    }

    //makes sure the letter is usable but if not it goes to the next letter to see if its usable
    while(flag != true){
        if(usable_coords.at(number).at(letter_pos) == letter){
            flag = true;
            break;
        }
        else if(letter < 'J'){
            letter++;
        }
        else{
            letter = 'A';
        }
    }

    // resets the value of num_letter to match the letter it's actually going for in case it changed
    num_letter = letter - 65;
    flag = false;
    int count = 0;


    while(/*count < 4 &&*/ flag == false){
        switch(direction){
        case 0:
            // go to left
            //checks to see if the ship will go out of the boundries if it goes this direction
            if(letter >= (usable_coords.at(number).at(0) + size - 1) && number < proper_size - 1 && number > 0){
                //checks to see if the coords needed for this direction are available
                for(int i = 1; i < size; i++){
                    flag = true;
                    if(letter - i != usable_coords.at(number).at(letter_pos - i)){
                        flag = false;
                        break;
                    }
                }
                
                // checks to see if it'll fit up and down
                if(find(usable_coords.at(number + 1).begin(), usable_coords.at(number + 1).end(), letter) == usable_coords.at(number + 1).end() && usable_coords.at(number + 1).back() != letter){
                    flag = false;
                    break;
                }
                else if (find(usable_coords.at(number - 1).begin(), usable_coords.at(number - 1).end(), letter) == usable_coords.at(number - 1).end() && usable_coords.at(number - 1).back() != letter){
                    flag = false;
                    break;
                }

                if(flag == true){
                    map<int, char> temp;
                    //fills the vector with the coords its now taking up
                    for(int i = 0; i < size; i++){
                        temp = {{number, letter - i}};
                        placement.push_back(temp);
                        temp.clear();
                    }

                    // takes care of up and down
                    temp = {{number - 1, letter}};
                    placement.push_back(temp);
                    temp.clear();
                    temp = {{number + 1, letter}};
                    placement.push_back(temp);
                    temp.clear();

                    // erases the used coords from the available coords vector
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos - i));
                    }
                    // takes care of up and down
                    usable_coords.at(number + 1).erase(usable_coords.at(number + 1).begin() + letter_pos);
                    usable_coords.at(number - 1).erase(usable_coords.at(number - 1).begin() + letter_pos);

                    break;
                }
            }
            count++;
        case 1:
            //right
            if((letter + size - 1) <= usable_coords.at(number).at(usable_coords.at(number).size() - 1) && number < proper_size - 1 && number > 0){
                for(int i = 1; i < size; i++){
                    flag = true;
                    if(letter + i != usable_coords.at(number).at(letter_pos + i)){
                        flag = false;
                        break;
                    }
                }
                if(find(usable_coords.at(number + 1).begin(), usable_coords.at(number + 1).end(), letter) == usable_coords.at(number + 1).end() && usable_coords.at(number + 1).back() != letter){
                    flag = false;
                    break;
                }
                else if (find(usable_coords.at(number - 1).begin(), usable_coords.at(number - 1).end(), letter) == usable_coords.at(number - 1).end() && usable_coords.at(number - 1).back() != letter){
                    flag = false;
                    break;
                }
                
                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number, letter + i}};
                        placement.push_back(temp);
                        temp.clear();
                    }

                    temp = {{number - 1, letter}};
                    placement.push_back(temp);
                    temp.clear();
                    temp = {{number + 1, letter}};
                    placement.push_back(temp);
                    temp.clear();

                    // erases the used coords from the available coords vector
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos));
                    }
                    usable_coords.at(number + 1).erase(usable_coords.at(number + 1).begin() + letter_pos);
                    usable_coords.at(number - 1).erase(usable_coords.at(number - 1).begin() + letter_pos);

                    break;
                }
            }
            count++;
        case 2:
            //up
            if(number - (size - 1) >= 0 && letter_pos < proper_size - 1 && letter_pos > 0){
                for(int i = number; i > (number - (size - 1)); i--){
                    flag = true;
                    if(std::find(usable_coords.at(number).begin(), usable_coords.at(number).end(), letter) == usable_coords.at(number).end() && usable_coords.at(number).back() != letter){
                        flag = false;
                        break;
                    }
                }
                if(letter - 1 != usable_coords.at(number).at(letter_pos - 1)){
                    flag = false;
                    break;
                }
                if(letter + 1 != usable_coords.at(number).at(letter_pos + 1)){
                    flag = false;
                    break;
                }

                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number - i, letter}};
                        placement.push_back(temp);
                        temp.clear();
                    }

                    temp = {{number, letter - 1}};
                    placement.push_back(temp);
                    temp.clear();
                    temp = {{number, letter + 1}};
                    placement.push_back(temp);
                    temp.clear();

                    // erases the used coords from the available coords vector
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number - i).erase(usable_coords.at(number - i).begin() + (letter_pos));
                    }
                    usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos));
                    usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos - 1));
                    break;
                }
            }
            count++;
        case 3:
            //down
            if(number + (size - 1) < usable_coords.size() && letter_pos < proper_size - 1 && letter_pos > 0){
                for(int i = 0; i < size; i++){
                    flag = true;
                    if(std::find(usable_coords.at(number).begin(), usable_coords.at(number).end(), letter) == usable_coords.at(number).end() && usable_coords.at(number).back() != letter){
                        flag = false;
                        break;
                    }
                }
                if(letter - 1 != usable_coords.at(number).at(letter_pos - 1)){
                    flag = false;
                    break;
                }
                if(letter + 1 != usable_coords.at(number).at(letter_pos + 1)){
                    flag = false;
                    break;
                }

                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number + i, letter}};
                        placement.push_back(temp);
                        temp.clear();
                    }

                    temp = {{number, letter - 1}};
                    placement.push_back(temp);
                    temp.clear();
                    temp = {{number, letter + 1}};
                    placement.push_back(temp);
                    temp.clear();

                    // erases the used coords from the available coords vector
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number + i).erase(usable_coords.at(number + i).begin() + (letter_pos));
                    }
                    usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos));
                    usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos - 1));
                    
                    break;
                }
            }
            count++;

            if(direction == 3){
                direction = 0;
            }
            if(count >= 4 && number == proper_size - 1){
                number = 0;
            }
            else if(count >= 4){
                number++;
            }
            
        }

    }
}




void Ship::TestAssign(std::vector<std::vector<char>> &usable_coords, int num, int num_let, int direct){
    // Providing a seed value
    // srand(time(NULL) * seed);

	// Get a random number
	// int num_letter = (rand() * 3) % 10;
    int num_letter = num_let;
    // int number = rand() % 10;
    int number = num;
    // int direction = rand() % 4;
    int direction = direct;

    char letter = num_letter + 65;
    int proper_size = 10;
    bool flag = false;

    while(usable_coords.at(number).size() == 0){
        if(usable_coords.size() < proper_size){
            number -= (proper_size - usable_coords.size());
        }
        else if(usable_coords.at(number).size() == 0 && number + 1 < proper_size && number >= 0){
            number++;
        }
        else if (usable_coords.at(number).size() == 0){
            number = 0;
        }
    }
    

    int letter_pos = num_letter;

    //can tell if the vector has shrunk and by how much then accounts for it when finding where to look for the adjecent letters
    if(proper_size > usable_coords.at(number).size()){
        letter_pos -= proper_size - usable_coords.at(number).size();
        if(letter_pos < 0){
            letter_pos = 0;
        }
    }


    while(flag != true){
        if(usable_coords.at(number).at(letter_pos) == letter){
            flag = true;
            break;
        }
        else if(letter < 'J'){
            letter++;
        }
        else{
            letter = 'A';
        }
    }

    num_letter = letter - 65;
    flag = false;
    int count = 0;


    while(count < 4 && flag == false){
        switch(direction){
        case 0:
            // go to left
            if(letter >= (usable_coords.at(number).at(0) + size - 1)){
                for(int i = 1; i < size; i++){
                    flag = true;
                    if(letter - i != usable_coords.at(number).at(letter_pos - i)){
                        flag = false;
                        break;
                    }
                }
                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number, letter - i}};
                        placement.push_back(temp);
                        temp.clear();
                    }
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos));
                    }
                    break;
                }
            }
            count++;
        case 1:
            //right
            if((letter + size - 1) <= usable_coords.at(number).at(usable_coords.at(number).size() - 1)){
                for(int i = 1; i < size; i++){
                    flag = true;
                    if(letter + i != usable_coords.at(number).at(letter_pos + i)){
                        flag = false;
                        break;
                    }
                }
                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number, letter + i}};
                        placement.push_back(temp);
                        temp.clear();
                    }

                    for(int i = 0; i < size; i++){
                        usable_coords.at(number).erase(usable_coords.at(number).begin() + (letter_pos));
                    }
                    break;
                }
            }
            count++;
        case 2:
            //up
            if(number - (size - 1) >= 0){
                for(int i = number; i > (number - (size - 1)); i--){
                    flag = true;
                    if(std::find(usable_coords.at(number).begin(), usable_coords.at(number).end(), letter) == usable_coords.at(number).end() && usable_coords.at(number).back() != letter){
                        flag = false;
                        break;
                    }
                }
                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number - i, letter}};
                        placement.push_back(temp);
                        temp.clear();
                    }
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number - i).erase(usable_coords.at(number - i).begin() + (letter_pos));
                    }
                    break;
                }
            }
            count++;
        case 3:
            //down
            if(number + (size - 1) < usable_coords.size()){
                for(int i = 0; i < size; i++){
                    flag = true;
                    if(std::find(usable_coords.at(number).begin(), usable_coords.at(number).end(), letter) == usable_coords.at(number).end() && usable_coords.at(number).back() != letter){
                        flag = false;
                        break;
                    }
                }
                if(flag == true){
                    map<int, char> temp;
                    for(int i = 0; i < size; i++){
                        temp = {{number + i, letter}};
                        placement.push_back(temp);
                        temp.clear();
                    }
                    for(int i = 0; i < size; i++){
                        usable_coords.at(number + i).erase(usable_coords.at(number + i).begin() + (letter_pos));
                    }
                    break;
                }
            }
            if(direction == 3 && flag == false){
                direction = 1;
            }
            count++;
        }

    }
}
