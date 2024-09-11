#include <iostream>
#include "ship.cpp"

using namespace std;

vector<std::vector<char>> AllCoords(){
    vector<std::vector<char>> available_coords;
    vector<char> letters{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    for(int i = 0; i < 10; i++){
        available_coords.push_back(letters);
    }
    return available_coords;
}

int Shoot(vector<Ship> &ships, vector<map<int, char>> &hit_shots, vector<map<int, char>> &missed_shots, int &ship_count){
    bool flag = true;
    string coords;
    while(flag != false){
        cout << "Please enter coordinates to fire at like this: 2, A (number first then letter)" << endl;
        cout << "You can enter numbers 1-10 and A-J" << endl;
        getline(cin, coords);

        if(coords.size() == 4){
            int y = coords.at(0) - 48;
            char x = coords.at(3);
            x = toupper(x);
            if(y < 10 && x >= 65 && x <= 75){
                map<int, char> shot = {{y, x}};
                for(int i = 0; i < ships.size(); i++){
                    if(find(ships.at(i).placement.begin(), ships.at(i).placement.end(), shot) != ships.at(i).placement.end() || shot == ships.at(i).placement.back()){
                        if(find(hit_shots.begin(), hit_shots.end(), shot) == hit_shots.end()){
                            cout << "You hit a ship!" << endl;
                            ship_count -= ships.at(i).Hit();
                            hit_shots.push_back(shot);
                            flag = false;
                        }
                        else{
                            cout << "You've already hit a shot there!" << endl;
                            flag = false;
                        }
                    }
                }
                if(flag == true){
                    cout << "You missed :/" << endl;
                    missed_shots.push_back(shot);
                    flag = false;
                }
            }
            else{
                cout << "Please enter in the correct format" << endl;
            }
        }
        else{
            cout << "Wrong length of string :(" << endl;
        }
    }
    return 0;
}

void PastShots(const vector<map<int, char>> hit_shots, const vector<map<int, char>> missed_shots, int ship_count){
    if(hit_shots.empty() && missed_shots.empty()){
        cout << "You haven't shot yet!" << endl;
        return;
    }
    cout << "These are the shots you've hit:" << endl;
    for(int i = 0; i < hit_shots.size(); i++){
        for(auto j : hit_shots.at(i)){
            cout << j.first << " , " << j.second << endl;
        }
    }

    cout << "These are the shots you've missed:" << endl;
    for(int i = 0; i < missed_shots.size(); i++){
        for(auto j : missed_shots.at(i)){
            cout << j.first << " , " << j.second << endl;
        }
    }

    cout << "There are " << ship_count << " ships left." << endl;
    
}

int main(){
    vector<vector<char>> usable_coords = AllCoords();
    vector<map<int, char>> hit_shots;
    vector<map<int, char>> missed_shots;
    vector<Ship> ships;

    T_Ship t_ship(3);
    Ship long_ship(4);
    Ship small_ship(2);
    Ship average_ship(3);

    t_ship.AssignCoords(usable_coords, 4);
    // for(int i = 0; i < t_ship.placement.size(); i++){
    //     for(auto i : t_ship.placement.at(i)){
    //         cout << i.first << " , " << i.second << endl;
    //     }
    // }
    ships.push_back(t_ship);

    // small_ship.TestAssign(usable_coords, 2, 4, 3);
    small_ship.AssignCoords(usable_coords, 2);
    // for(int i = 0; i < small_ship.placement.size(); i++){
    //     for(auto j : small_ship.placement.at(i)){
    //         cout << j.second << " , " << j.first << endl;
    //     }
    // }
    ships.push_back(small_ship);

    // long_ship.TestAssign(usable_coords, 3, 1, 2);
    long_ship.AssignCoords(usable_coords, 3);
    // for(int i = 0; i < long_ship.placement.size(); i++){
    //     for(auto i : long_ship.placement.at(i)){
    //         cout << i.second << " , " << i.first << endl;
    //     }
    // }
    ships.push_back(long_ship);

    // average_ship.TestAssign(usable_coords, 0, 1, 1);
    average_ship.AssignCoords(usable_coords, 1);
    // for(int i = 0; i < average_ship.placement.size(); i++){
    //     for(auto i : average_ship.placement.at(i)){
    //         cout << i.second << " , " << i.first << endl;
    //     }
    // }
    ships.push_back(average_ship);

    cout << "The board has been set, in a 10 by 10 grid with 4 ships" << endl;
    int ship_count = 4;

    string input;
    while(input != "q"){
        cout << "What would you like to do?:" << endl;
        cout << "f = fire" << endl;
        cout << "p = past shots" << endl;
        cout << "q = quit" << endl;
        getline(cin, input);

        if(input == "f" || input == "F"){
            Shoot(ships, hit_shots, missed_shots, ship_count);
        }
        else if(input == "p" || input == "P"){
            PastShots(hit_shots, missed_shots, ship_count);
        }
        else if(input == "q" || input == "Q"){
            break;
        }
        else{
            cout << "Please input a proper character" << endl;
        }
        if(ship_count <= 0){
            cout << "Congrats! You won the game!" << endl;
            break;
        }
    }

    


    return 0;
}



// for(int i = 0; i < usable_coords.size(); i++){
//     cout << i << ": ";
//     for(int j = 0; j < usable_coords.at(i).size(); j++){
//         cout << " , " << usable_coords.at(i).at(j);
//     }
//     cout << endl;
// }