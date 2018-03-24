#include <vector>
#include"gametable.h"
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

class SeriesSteps
{
public:
   vector <Steps> step;
   int rating_series;

    void Reset();

    void set_rating_series();
    void set_step(Steps);
    int get_rating_series();
    int get_size_step();
    void transfer_steps(GameTable *);
    void print_series();
    bool serach_step (Steps);
    bool search_seras(vector<SeriesSteps>);
};


    void next_level (GameTable table,SeriesSteps seria_one, vector <SeriesSteps> *seria);
    SeriesSteps max_raiting(vector <SeriesSteps> seria);
    SeriesSteps  set_steps(GameTable table);
    int max_raiting_serias(vector <SeriesSteps> *serias);
    int max_size_seria(vector <SeriesSteps> *serias);



