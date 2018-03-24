#include <vector>
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

class Cards
{
protected:
    int suit;
    int name;
    int position[2]; //position[0]=x position[1]=y
public:
    void new_card( int, int, int, int);
    void reset();
    void set_suit(int );
    void set_name(int );
    void set_position(int , int );
    void Write_string(char*);
    void Read_string(char*);
    void Read_key();
    void Print_full();
    void Print_low();
    int get_suit();
    int get_name();
    int get_x();
    int get_y();
    bool operator ==(Cards);
    bool operator !=(Cards);
    void operator =(Cards);
};




