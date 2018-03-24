#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "card.h"
#include <fstream>

using namespace std;

char* itoa(int value, char* result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36)
    {
        *result = '\0';
        return result;
    }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    }
    while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}




///////////////////////////////////////////

void Cards::new_card( int suitcart, int namecart, int x, int y)
{
    set_suit(suitcart);
    set_name(namecart);
    set_position(x,y);
}

void Cards::reset()
{
    set_suit(0);
    set_name(0);
    set_position(0,0);
}

void Cards::set_suit(int suitcart)
{
    suit=suitcart;
}

void Cards::set_name(int namecart)
{
    name=namecart;
}

void Cards::set_position(int x, int y)
{
    position[0]=x;
    position[1]=y;
}

int Cards::get_suit()
{
    return suit;
}

int Cards::get_name()
{
    return name;
}

int Cards::get_x()
{
    return position[0];
}

int Cards::get_y()
{
    return position[1];
}

void Cards::Print_full()
{
    cout<<"suit: "<<get_suit()<<endl;
    cout<<"name: "<<get_name()<<endl;
    cout<<"x: "<<get_x()<<" y:"<<get_y()<<endl;
}

void Cards::Print_low()
{
    cout<<'['<<get_name()<<','<<get_suit()<<']';
}

void Cards::Read_key()
{
    int suitcart,namecart,y,x;
    cout<<"suit: "<<endl;
    cin>>suitcart;
    cout<<"name: "<<endl;
    cin>>namecart;
    cout<<"x: "<<endl;
    cin>>x;
    cout<<"y: "<<endl;
    cin>>y;

    set_suit(suitcart);
    set_name(namecart);
    set_position(x,y);
}

void Cards::Read_string(char* stringcard)
{
    int suitcart,namecart;
    int i=0;
    char buf[2];
    while (stringcard[i]!=']')
    {
        if (stringcard[i]=='[')
        {
            if (stringcard[i+2]==';')
            {
                buf[0]='0';
                buf[1]=stringcard[i+1];
            }
            else
            {
                buf[0]=stringcard[i+1];
                buf[1]=stringcard[i+2];
            }
            namecart=atoi(buf);
        }
        if (stringcard[i]==',')
        {

            if (stringcard[i+2]==']')
            {
                buf[0]='0';
                buf[1]=stringcard[i+1];
            }
            else
            {
                buf[0]=stringcard[i+1];
                buf[1]=stringcard[i+2];
            }
            suitcart=atoi(buf) ;
        }

        i++;
    }
    set_suit(suitcart);
    set_name(namecart);
}

void Cards::Write_string( char* str )
{
    char namestr[3];
    char suitstr[3];
    itoa(get_suit(), suitstr, 10);
    itoa(get_name(), namestr, 10);
    strcpy(str,"[");
    strcat(str,namestr);
    strcat(str,",");
    strcat(str,suitstr);
    strcat(str,"]");
    //strcat(str,'0/');
}


bool Cards::operator ==(Cards card)
{
    return ((suit==card.get_suit())&&(name==card.get_name()));
}

bool Cards::operator !=(Cards card)
{
    return ((suit!=card.get_suit())||(name!=card.get_name()));
}

void Cards::operator =(Cards card)
{
    suit=card.get_suit();
    name=card.get_name();
    position[0]=card.get_x();
    position[1]=card.get_y();
}



