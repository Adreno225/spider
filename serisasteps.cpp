#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "serisasteps.h"
#include <fstream>

using namespace std;

void SeriesSteps::Reset()
{
    rating_series=0;
    step.~vector();
}

void SeriesSteps::set_rating_series()
{
    rating_series=0;
    for (int i=0; i<step.size(); i++)
        rating_series=rating_series+step[i].get_rating_step();

}

void SeriesSteps::set_step(Steps add_step)
{
    step.push_back(add_step);
    set_rating_series();
}

int SeriesSteps::get_rating_series()
{
    rating_series=0;
    for (int i=0; i<step.size(); i++)
        rating_series=rating_series+step[i].get_rating_step();
    return rating_series;
}

int SeriesSteps::get_size_step()
{
    return step.size();
}


void SeriesSteps::print_series()
{
    cout<<"rating seria: "<<get_rating_series()<<endl;
    for (int i=0; i<step.size(); i++)
        step[i].Print_low();
}


void SeriesSteps::transfer_steps(GameTable *table)
{
    for (int i=0; i<step.size(); i++)
        table->transfer_step(step[i]);
}

bool SeriesSteps::serach_step (Steps stepsearch)
{
    bool flag=false;
    Steps stepreverse;
    stepreverse.New_Step(stepsearch.get_rating_step(),stepsearch.get_position_end_x(),stepsearch.get_position_end_y()
    ,stepsearch.get_card_end(),stepsearch.get_position_start_x(),stepsearch.get_position_start_y(),stepsearch.get_card_end());
    for (int i=0; i<step.size(); i++)
    {
        if (step[i]==stepreverse)
            flag=true;
        if (step[i]==stepsearch)
            flag=true;
    }
    return flag;
}


bool SeriesSteps::search_seras(vector<SeriesSteps> serarias)
{
    bool flag=false;
    for (auto sers:serarias)
    {
        if ((sers.get_rating_series()==rating_series)&&(sers.get_size_step()==step.size()))
        {
            int done=0;
            for(int i=0; i<step.size(); i++)
            {
                if (step[i]!=sers.step[i])
                    break;
                else if ((step.size()-1)==i)
                    flag=true;
            }
        }

    }
    cout<<"serch serias "<<flag<<endl;
    return flag;
}


///////////////////////////////////////////////////////////////////////

void next_level (GameTable table,SeriesSteps seria_one, vector <SeriesSteps> *seria);
SeriesSteps max_raiting(vector <SeriesSteps> seria);
SeriesSteps  set_steps(GameTable table);



SeriesSteps  set_steps(GameTable table)
{
    vector <SeriesSteps> seria;
    SeriesSteps seria_one;
    seria_one.Reset();
    next_level (table,seria_one, &seria);
    seria_one=max_raiting (seria);
    seria.clear();
    return seria_one;


}

void next_level (GameTable table,SeriesSteps seria_one, vector <SeriesSteps> *seria)
{
    if ((seria_one.get_rating_series()>200)||(seria->size()>2000))
    {
        seria->push_back(seria_one);
        cout<<seria->size()<<" seria"<<seria_one.get_rating_series()<<endl;
        cout<<"max_raiting_serias "<<max_raiting_serias(seria)<<endl;
    }
    else
    {
        vector <Steps> step=table.true_steps();
        if (step.size()!=0)
        {
            for (int i=0; i<step.size(); i++)
            {
                if ( seria_one.serach_step(step[i]))
                {
                    cout<<seria->size()<<" seria"<<seria_one.get_rating_series()<<endl;
                    if (seria->size()==0)
                        seria->push_back(seria_one);
                    if (max_raiting_serias(seria)<seria_one.get_rating_series())
                    {
                        cout<<seria->size()<<" seria"<<seria_one.get_rating_series()<<endl;
                        cout<<"max_raiting_serias "<<max_raiting_serias(seria)<<endl;
                        seria->push_back(seria_one);
                    }
                }
                else
                {
                    GameTable table_next=table;
                    table_next.transfer_step(step[i]);
                    //table_next.Print_full();
                    table_next.complite_task(&step[i]);
                    SeriesSteps seria_two=seria_one;
                    seria_two.set_step(step[i]);
                    next_level (table_next,seria_two,seria);
                }
            }
        }
    }

}

SeriesSteps max_raiting(vector <SeriesSteps> serias)
{
    int maxraiting=0;
    SeriesSteps seria;
    for (int i=0; i<serias.size(); i++)
        if (maxraiting<serias[i].get_rating_series())
        {
            maxraiting=serias[i].get_rating_series();
            seria=serias[i];
        }
    return seria;
}

int max_raiting_serias(vector <SeriesSteps> *serias)
{
    int maxraiting=0;
    for (int i=0; i<serias->size(); i++)
        if (maxraiting<(*serias)[i].get_rating_series())
        {
            maxraiting=(*serias)[i].get_rating_series();
        }
    return maxraiting;
}

int max_size_seria(vector <SeriesSteps> *serias)
{
    int maxsize=0;
    for (int i=0; i<serias->size(); i++)
        if (maxsize<serias[i].size())
        {
            maxsize=serias[i].size();
        }
    return maxsize;

}

