#include <vector>
#include "steps.h"
using namespace std;

class GameTable
{
   protected:
        vector< vector<Cards> > card;
        int base;
        Cards deck;
        int numberdeck;
        int widthcards;
        int heightcards;
    public:
        void Reset();
        void Reset_Card(int,int);
        void set_card(int,int,Cards);
        void set_base(int );
        void set_deck(Cards );
        void set_numberdeck(int );
        void set_size(int ,int);
        Cards get_card(int,int);
        void add_card(vector <Cards>);
        void add_deck(vector <Cards>);
        Cards get_deck();
        int get_base();
        int get_numberdeck();
        int get_widthcards();
        int get_heightcards();
        int get_sizecard(int);
        void Print_full();
        void Print_low();
        void Save_to_file(char*);
        void Load_from_file(char*);
        bool true_card(int ,int);
        vector <Cards> true_cards();
        bool true_step(int ,int,Cards);
        vector <Steps> true_steps();
        void transfer_step(Steps);
        bool serach_column(bool);
        bool blank_column();
        bool secret_last_card();
        int cloculation_raiting(int, int, int, int);
        bool complite_task(Steps*);

};





