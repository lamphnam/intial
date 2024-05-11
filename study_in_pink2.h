/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;
class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;
class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
    
protected:
    ElementType type;
public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement {
public:
    Path();
};

class Wall : public MapElement {
public:
    Wall();
};
class FakeWall : public MapElement {
private:
    int req_exp;
public:
    FakeWall();
    int getReqExp(int r, int c) const;
};
class Map {
private:
    int num_rows, num_cols;
    MapElement*** map;
    int x,y;

public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls);
    ~Map();
    static const Position npos ;
    
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;
};
// done 


class Position {
private:
    int r, c;
    
public:
    static const Position npos;

    Position(int r=0, int c=0);

    Position(const string & str_pos);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);

    string str() const;

    bool isEqual(int in_r, int in_c) const;
    bool isEqual(const Position& other) const;
};
// done

class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;

public:
    MovingObject(int index, const Position pos, Map * map, const string & name="");
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
};

class Sherlock : public MovingObject  {
private:
    // TODO
    int init_hp;
    int init_exp;
    Map * map;
    string moving_rule;
    int hp;
    int exp;

public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    int checkHP(int init_hp);
    int checkEXP(int init_exp);
    Position getNextPosition();
    Position getCurrentPosition();
    string getName();
    // move
    void move();

    // str
    string str() const;
    // ...
};

class Watson : public MovingObject {
private:
    int init_hp;
    int init_exp;
    Map * map;
    string moving_rule;
    int hp;
    int exp;

public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    int checkHP(int init_hp);
    int checkEXP(int init_exp);
    Position getNextPosition();
    Position getCurrentPosition();
    string getName();
    // move
    void move();
    // str
    string str() const;
    // ...
};

class Criminal : public MovingObject{
private:
    // TODO
    int init_hp;
    int init_exp;
    Map * map;
    Sherlock * sherlock;
    Watson * watson;
    int hp;
    int exp;
    string moving_rule;

public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    // getNextPosition
    Position getNextPosition();
    Position getCurrentPosition();

    // move
    string getName();
    void move();
    // str
    string str() const;
    // ...
};

class ArrayMovingObject {
private:
    // TODO
    //arr_mv_objs: array of moving objects (MovingObject). Each element in the array needs to demonstrate polymorphism
    MovingObject ** arr_mv_objs;
    int count;
    int capacity;
public:
    //Constructor of ArrayMovingObject takes a parameter to initialize the capacity property. At the same time, the method needs to be allocated appropriately.
    ArrayMovingObject(int capacity);

    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class StudyPinkProgram;

private:
    // TODO
    int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position* arr_walls;
    int num_fake_walls;
    Position* arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

public:
    //Constructor Configuration is declared as below. The constructor accepts filepath which is a string containing the path to the configuration file. The constructor initializes the attributes in accordance with the above descriptions.
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
};

// Robot, BaseItem, BaseBag,...
class Robot {};
class BaseItem {};
class BaseBag {};
class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
