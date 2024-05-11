#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

//MapElement
MapElement::MapElement(ElementType in_type) : type(in_type) {}

Path::Path() : MapElement(ElementType::PATH) {}

Wall::Wall() : MapElement(ElementType::WALL) {}

FakeWall::FakeWall() : MapElement(ElementType::FAKE_WALL) {}

int FakeWall::getReqExp(int r, int c) const { 
    return ( r*257 + c*139 +89)% 900 + 1; 
}
MapElement::~MapElement() {}

ElementType MapElement::getType() const {
    return type;
}

//Map
    Map::Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) : num_rows(num_rows), num_cols(num_cols) {
        map = new MapElement**[num_rows];
        for(int i = 0; i < num_rows; i++){
            map[i] = new MapElement*[num_cols];
            for(int j = 0; j < num_cols; j++){
                map[i][j] = new Path();
            }
        }
        for(int i = 0; i < num_walls; i++){
            map[array_walls[i].getRow()][array_walls[i].getCol()] = new Wall();
        }
        for(int i = 0; i < num_fake_walls; i++){
            map[array_fake_walls[i].getRow()][array_fake_walls[i].getCol()] = new FakeWall();
        }
    }

    Map :: ~Map(){
        for(int i = 0; i < num_rows; i++){
            for(int j = 0; j < num_cols; j++){
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
    }

//MovingObject
    /*MovingObject(int index, const Position pos, Map * map, const string & name="");
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
*/
MovingObject::MovingObject(int index, const Position pos, Map * map, const string & name) : index(index), pos(pos), map(map), name(name) {
    if(name == ""){
        this->name = "MovingObject";
    }
}

MovingObject::~MovingObject() {}


Position::Position(int r, int c) : r(r), c(c) {}

Position::Position(const string & str_pos){
    stringstream ss(str_pos);
    char discard;
    ss >> discard >> r >> discard >> c >> discard;
}

int Position::getRow() const {
    return r;
}
int Position::getCol() const {
    return c;
}
void Position::setRow(int r) {
    this->r = r;
}
void Position::setCol(int c) {
    this->c = c;
}

string Position::str() const {
    return "(" + to_string(r) + "," + to_string(c) + ")";
}
bool Position::isEqual(int in_r, int in_c) const {
    return r == in_r && c == in_c;
}
bool Position::isEqual(const Position& other) const {
    return r == other.r && c == other.c;
}


const Position Position::npos = Position(-1, -1);

Position MovingObject::getCurrentPosition() const {
    return pos;
}
// SHERLOCK
//Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
Sherlock :: Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) : MovingObject(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(checkHP(init_hp)), exp(checkEXP(init_exp)) {

}
Position Sherlock::getNextPosition(){
    Position next_pos = pos;
    for(int i = 0; i < moving_rule.length(); i++){
        switch(moving_rule[i]){
            case 'U':
                next_pos.setRow(next_pos.getRow() - 1);
                break;
            case 'D':
                next_pos.setRow(next_pos.getRow() + 1);
                break;
            case 'L':
                next_pos.setCol(next_pos.getCol() - 1);
                break;
            case 'R':
                next_pos.setCol(next_pos.getCol() + 1);
                break;
        }
    }
    return next_pos;
}
int Sherlock::checkHP(int init_hp){
    if(init_hp < 0){
        init_hp = 0;
    }else if(init_hp > 500){
        init_hp = 500;
    }
    return init_hp;
}
int Sherlock :: checkEXP(int init_exp){
    if(init_exp < 0){
        init_exp = 0;
    }else if(init_exp > 500){
        init_exp = 500;
    }
    return init_exp;
}
string Sherlock::getName(){
    return "Sherlock";
}

void Sherlock::move() {
    Position nextPosition = getNextPosition();
    if(!nextPosition.isEqual(Position::npos)) {
        pos = nextPosition;
    }
    else 
    {
    }
}
string Sherlock :: str() const {
    return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}
// WATSON
//    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
Watson :: Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) : MovingObject(index, init_pos, map, "Waston"), moving_rule(moving_rule), hp(checkHP(init_hp)), exp(checkEXP(init_exp)) {

}
int Watson :: checkHP(int init_hp){
    if(init_hp < 0){
        init_hp = 0;
    }else if(init_hp > 500){
        init_hp = 500;
    }
    return init_hp;
}
int Watson :: checkEXP(int init_exp){
    if(init_exp < 0){
        init_exp = 0;
    }else if(init_exp > 500){
        init_exp = 500;
    }
    return init_exp;
}
string Watson::getName(){
    return "Watson";
}
void Watson::move() {
    // Call getNextPosition to get the next position
    Position nextPosition = getNextPosition();
    // Check if the next position is valid (assuming npos is defined somewhere)
    if(!nextPosition.isEqual(Position::npos)) {
        // If it's a valid move, update the position
        pos = nextPosition;
    } else {
        // If it's not a valid move, do nothing
    }
}
Position Watson::getNextPosition(){
    Position next_pos = pos;
    for(int i = 0; i < moving_rule.length(); i++){
        switch(moving_rule[i]){
            case 'U':
                next_pos.setRow(next_pos.getRow() - 1);
                break;
            case 'D':
                next_pos.setRow(next_pos.getRow() + 1);
                break;
            case 'L':
                next_pos.setCol(next_pos.getCol() - 1);
                break;
            case 'R':
                next_pos.setCol(next_pos.getCol() + 1);
                break;
        }
    }
    return next_pos;
}
string Watson :: str() const {
    return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}
// con` 2 function move cua class sherlock va watson

// CRIMINAL
//constructor Criminal
// Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
Criminal::Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson) : MovingObject(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson), moving_rule("RDLU") {

}
Position Criminal::getNextPosition(){
    Position next_pos = pos;
    for(int i = 0; i < moving_rule.length(); i++){
        switch(moving_rule[i]){
            case 'U':
                next_pos.setRow(next_pos.getRow() - 1);
                break;
            case 'D':
                next_pos.setRow(next_pos.getRow() + 1);
                break;
            case 'L':
                next_pos.setCol(next_pos.getCol() - 1);
                break;
            case 'R':
                next_pos.setCol(next_pos.getCol() + 1);
                break;
        }
    }
    return next_pos;
}
void Criminal::move() {
    // Call getNextPosition to get the next position
    Position nextPosition = getNextPosition();
    // Check if the next position is valid (assuming npos is defined somewhere)
    if(!nextPosition.isEqual(Position::npos)) {
        // If it's a valid move, update the position
        pos = nextPosition;
    } else {
        // If it's not a valid move, do nothing
    }
}
string Criminal::getName(){
    return "Criminal";
}
string Criminal::str() const {
    return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
}

//ARRAYMOVINGOBJECT

ArrayMovingObject::ArrayMovingObject(int capacity) : capacity(capacity), count(0) {
    arr_mv_objs = new MovingObject*[capacity];
}
ArrayMovingObject::~ArrayMovingObject(){
    for(int i = 0; i < count; i++){
        delete arr_mv_objs[i];
    }
    delete[] arr_mv_objs;
}
bool ArrayMovingObject::isFull() const {
    if(count == capacity){
        return true;
    }
    return false;
}
bool ArrayMovingObject::add(MovingObject * mv_obj){
    if(isFull()){
        return false;
    }
    arr_mv_objs[count] = mv_obj;
    count++;
    return true;
}
MovingObject * ArrayMovingObject::get(int index) const {
    if(index < 0 || index >= count){
        return nullptr;
    }
    return arr_mv_objs[index];
}
string ArrayMovingObject::str() const{
    string str = "ArrayMovingObject [ count =" + to_string(count) + "; capacity =" + to_string(capacity) + ";";
    for(int i = 0; i < count; i++){
        str += arr_mv_objs[i]->str();
        if(i != count - 1){
            str += ";";
        }
    }
    str += "]";
    return str;
}
//CONFIGURATION

Configuration::Configuration(const string & filepath) {
    arr_walls = nullptr;
    arr_fake_walls = nullptr;

    ifstream file(filepath);
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        string key;
        getline(ss, key, '=');
        if(key == "MAP_NUM_ROWS"){
            ss >> map_num_rows;
        }else if(key == "MAP_NUM_COLS"){
            ss >> map_num_cols;
        }else if(key == "MAX_NUM_MOVING_OBJECTS"){
            ss >> max_num_moving_objects;
        }else if(key == "ARRAY_WALLS" || key == "ARRAY_FAKE_WALLS"){
            string walls;
            getline(ss, walls, '=');
            string cleaned_walls;
            for(char c : walls){
                if(c != ' '){ // remove spaces, keep other characters
                    cleaned_walls += c;
                }
            }
            istringstream wallStream(cleaned_walls);
            string wall;
            int wall_count = 0;
            while (getline(wallStream, wall, ';')){
                wall_count++;
            }
            wallStream.clear();
            wallStream.str(cleaned_walls);
            Position * tempWalls = new Position[wall_count];
            int index = 0;
            
            while (getline(wallStream, wall, ';')){
                size_t commaPos = wall.find(',');
                if (commaPos != string::npos){
                    string r_str = wall.substr(1, commaPos - 1);
                    string c_str = wall.substr(commaPos + 1);
                    try {
                        int r = stoi(r_str);
                        int c = stoi(c_str);
                        tempWalls[index] = Position(r, c);
                        index++;
                    } catch (invalid_argument & e){
                        // do nothing
                }
            }    
            }
            if (key == "ARRAY_WALLS"){
                arr_walls = tempWalls;
                num_walls = wall_count;
            } else {
                arr_fake_walls = tempWalls;
                num_fake_walls = wall_count;
            }
        }else if(key == "SHERLOCK_MOVING_RULE"){
            ss >> sherlock_moving_rule;
        }else if(key == "SHERLOCK_INIT_POS"){
            int x,y;
            sscanf(line.c_str(), "SHERLOCK_INIT_POS=(%d,%d)", &x, &y);
            sherlock_init_pos = Position(x, y);
        }else if(key == "SHERLOCK_INIT_HP"){
            ss >> sherlock_init_hp;
        }else if(key == "SHERLOCK_INIT_EXP"){
            ss >> sherlock_init_exp;
        }else if(key == "WATSON_MOVING_RULE"){
            ss >> watson_moving_rule;
        }else if(key == "WATSON_INIT_POS"){
            int x,y;
            sscanf(line.c_str(), "WATSON_INIT_POS=(%d,%d)", &x, &y);
            watson_init_pos = Position(x, y);
        }else if(key == "WATSON_INIT_HP"){
            ss >> watson_init_hp;
        }else if(key == "WATSON_INIT_EXP"){
            ss >> watson_init_exp;
        }else if(key == "CRIMINAL_INIT_POS"){
            int x,y;
            sscanf(line.c_str(), "CRIMINAL_INIT_POS=(%d,%d)", &x, &y);
            criminal_init_pos = Position(x, y);
        }else if(key == "NUM_STEPS"){
            ss >> num_steps;
        }
    }
    file.close();
}

Configuration::~Configuration(){
    delete[] arr_walls;
    delete[] arr_fake_walls;
}

string Configuration::str() const {
    stringstream ss;
    ss << "Configuration[\n";
    ss << "MAP_NUM_ROWS=" << map_num_rows << "\n";
    ss << "MAP_NUM_COLS=" << map_num_cols << "\n";
    ss << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << "\n";
    ss << "ARRAY_WALLS=[";
    for (int i = 0; arr_walls && i < num_walls; ++i) {
        ss << "(" << arr_walls[i].getRow() << "," << arr_walls[i].getCol() << ");";
    }
    ss << "]\n";
    ss << "ARRAY_FAKE_WALLS=[";
    for (int i = 0; arr_fake_walls && i < num_fake_walls; ++i) {
        ss << "(" << arr_fake_walls[i].getRow() << "," << arr_fake_walls[i].getCol() << ");";
    }
    ss << "]\n";
    ss << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << "\n";
    ss << "SHERLOCK_INIT_POS=(" << sherlock_init_pos.getRow() << "," << sherlock_init_pos.getCol() << ")\n";
    ss << "SHERLOCK_INIT_HP=" << sherlock_init_hp << "\n";
    ss << "SHERLOCK_INIT_EXP=" << sherlock_init_exp << "\n";
    ss << "WATSON_MOVING_RULE=" << watson_moving_rule << "\n";
    ss << "WATSON_INIT_POS=(" << watson_init_pos.getRow() << "," << watson_init_pos.getCol() << ")\n";
    ss << "WATSON_INIT_HP=" << watson_init_hp << "\n";
    ss << "WATSON_INIT_EXP=" << watson_init_exp << "\n";
    ss << "CRIMINAL_INIT_POS=(" << criminal_init_pos.getRow() << "," << criminal_init_pos.getCol() << ")\n";
    ss << "NUM_STEPS=" << num_steps << "\n";
    ss << "]";
    return ss.str();
}
// other member function definitions...
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////