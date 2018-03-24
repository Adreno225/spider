#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "steps.h"
#include <fstream>

using namespace std;


void Steps::Reset()
{
    set_rating_step(0);
    set_position_start(0,0);
    card_start.reset();
    set_position_end(0,0);
    card_end.reset();
}

void Steps::New_Step(int rating,int i1,int j1,Cards start,int i2, int j2,Cards c_end)
{
    set_rating_step(rating);
    set_position_start(i1,j1);
    card_start=start;
    set_position_end(i2,j2);
    card_end=c_end;
}


void Steps::set_rating_step(int raiting)
{
    rating_step=raiting;
}

void Steps::add_rating_step(int raiting)
{
    rating_step+=raiting;
}

void Steps::set_position_start(int i,int j)
{
    position_start[0]=i;
    position_start[1]=j;
}

void Steps::set_card_start(Cards card)
{
    card_start=card;
}

void Steps::set_position_end(int i,int j)
{
    position_end[0]=i;
    position_end[1]=j;
}

void Steps::set_card_end(Cards card)
{
    card_end=card;
}

int Steps::get_rating_step()
{
    return rating_step;
}

int Steps::get_position_start_x()
{
    return position_start[0];
}

int Steps::get_position_start_y()
{
    return position_start[1];
}

Cards Steps::get_card_start()
{
    return card_start;
}

int Steps::get_position_end_x()
{
    return position_end[0];
}

int Steps::get_position_end_y()
{
    return position_end[1];
}

Cards Steps::get_card_end()
{
    return card_end;
}

void Steps::Print_full()
{
    cout<<"rating: "<<get_rating_step()<<endl;
    cout<<"start: i-"<<get_position_start_x()<<" j-"<<get_position_start_y()<<endl;
    cout<<"card: ";
    card_start.Print_low();
    cout<<endl;
    cout<<"end: i-"<<get_position_end_x()<<" j-"<<get_position_end_y()<<endl;
    cout<<"card: ";
    card_end.Print_low();
    cout<<endl;
}

void Steps::Print_low()
{
    cout<<"rating: "<<get_rating_step();
    cout<<"  start: i-"<<get_position_start_x()<<" j-"<<get_position_start_y();
    cout<<"  card: ";
    card_start.Print_low();

    cout<<"  end: i-"<<get_position_end_x()<<" j-"<<get_position_end_y();
    cout<<"  card: ";
    card_end.Print_low();
    cout<<endl;
}

bool Steps::operator ==(Steps step)
{
    return ((position_start[0]==step.get_position_start_x()) && (position_start[1]==step.get_position_start_y()) && (position_end[0]==step.get_position_end_x()) && (card_start==step.get_card_start()) && (card_end==step.get_card_end()));
}

bool Steps::operator !=(Steps step)
{
    return ((position_start[0]!=step.get_position_start_x()) || (position_start[1]!=step.get_position_start_y()) || (position_end[0]!=step.get_position_end_x()) || (card_start!=step.get_card_start()) || (card_end!=step.get_card_end()));
}
