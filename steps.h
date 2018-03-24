#include <vector>
#include "card.h"
using namespace std;

/**

//suits
#define NONESUIT    0
#define SPADES      1 //бубны
#define CLUBS       2 //крести
#define HEARTS      3 //черви
#define DIAMONDS    4 //пики
#define SECRETSUIT  5

//namecart
#define NONE        0
#define ACE         1
#define TWO         2
#define THREE       3
#define FOUR        4
#define FIVE        5
#define SIX         6
#define SEVEN       7
#define EIGHT       8
#define NINE        9
#define TEN         10
#define JACK        11
#define QUEEN       12
#define KING        13
#define SECRET      14
                        */


class Steps
{
protected:
    int rating_step;
    int position_start[2];
    Cards card_start;
    int position_end[2];
    Cards card_end;
public:
    void Reset();
    void New_Step(int,int,int,Cards,int,int,Cards);
    void set_rating_step(int);
    void add_rating_step(int);
    void set_position_start(int,int);
    void set_card_start(Cards);
    void set_position_end(int,int);
    void set_card_end(Cards);

    int get_rating_step();
    int get_position_start_x();
    int get_position_start_y();
    Cards get_card_start();
    int get_position_end_x();
    int get_position_end_y();
    Cards get_card_end();

    void Print_full();
    void Print_low();

    bool operator ==(Steps);
    bool operator !=(Steps);
};


