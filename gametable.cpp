#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "gametable.h"
#include <fstream>

using namespace std;

void GameTable::Reset()
{
    Cards carddesk;
    carddesk.new_card(0,0,0,0);
    Cards cards;
    cards.new_card(0,0,0,0);
    Cards secret;
    secret.new_card(5,14,0,0);
    set_base(0);
    set_numberdeck(5);
    set_size(0,0);
    set_deck(carddesk);
    card.resize(10);
    for (int i=0; i<card.size(); i++)
    {
        if (i<4)
            card[i].resize(6);
        else
            card[i].resize(5);
        for (int j=0; j<card[i].size(); j++)
        {
            card[i][j]=secret;
        }
    }
}

void GameTable::Reset_Card(int i,int j)
{
    if ((i==(card.size()-1))&&(j==(card[i].size()-1)))
        card[i].pop_back();
    else if ((i>=card.size())&&(j>=card[i].size()))
        cout << "Error reset\n";
    else
    {
        for (int j1=j; j1<card[i].size()-1; j1++)
        {
        set_card(i,j1,get_card(i,j1+1));
        }
        card[i].pop_back();
    }

}

void GameTable::set_card(int i,int j,Cards cards)
{
    if ((i<card.size())&&(j<card[i].size()))
        card[i][j]=cards;
    else if ((i<card.size())&&(j==card[i].size()))
        card[i].push_back(cards);
    else
        cout << "Error\n";

}

void GameTable::set_base(int basetable)
{
    base=basetable;
}

void GameTable::set_numberdeck(int deck)
{
    numberdeck=deck;
}

void GameTable::set_size(int width,int height)
{
    widthcards=width;
    heightcards=height;
}

void GameTable::set_deck(Cards carddesk)
{
    deck=carddesk;
}

Cards GameTable::get_card(int i,int j)
{
    Cards cardzero;
    cardzero.reset();
    if ((i<card.size())&&(j<card[i].size()))
        cardzero=card[i][j];
    else
    {

        cout <<i<<" "<<j<< "Not card\n";
    }

    return cardzero;
}

int GameTable::get_base()
{
    return base;
}

int GameTable::get_numberdeck()
{
    return numberdeck;
}

Cards GameTable::get_deck()
{
    return deck;
}

int GameTable::get_widthcards()
{
    return widthcards;
}

int GameTable::get_heightcards()
{
    return heightcards;
}

int GameTable::get_sizecard(int i)
{
    return card[i].size();
}

void GameTable::Print_full()
{
    cout<<"base: "<<get_base()<<endl;
    cout<<"numberdeck: "<<get_numberdeck()<<endl;
    cout<<"width: "<<get_widthcards()<<" heigh: "<<get_heightcards()<<endl;
    cout<<"deck: ";
    deck.Print_low();
    cout<<"  x: "<<deck.get_x()<<" y: "<<deck.get_y()<<endl;
    int j=0;int maxj=0;
    for(auto card1:card)
        if (card1.size()>maxj)
            maxj=card1.size();
    while (1)
    {
        int i=0;
        while (i<card.size())
        {
            if (j<card[i].size())
            {
                card[i][j].Print_low();
                cout<<" ";
            }
            else
                cout<<"       ";
            i++;
        }
        cout<<endl;
        if (j==(maxj-1))
            break;
        else
            j++;
    }

}

void GameTable::Print_low()
{
    int j=0;int maxj=0;
    for(auto card1:card)
        if (card1.size()>maxj)
            maxj=card1.size();
    while (1)
    {
        int i=0;
        while (i<card.size())
        {
            if (j<card[i].size())
            {
                card[i][j].Print_low();
                cout<<" ";
            }
            else
                cout<<"       ";
            i++;
        }
        cout<<endl;
        if (j==(maxj-1))
            break;
        else
            j++;
    }
}

void GameTable::Save_to_file(char *filename)
{
    char strfile[400],strbuf[10];
    ofstream fout(filename,ios_base::trunc | ios_base::out);
    fout<<"base: "<<get_base()<<endl;
    fout<<"numberdeck: "<<get_numberdeck()<<endl;
    fout<<"width: "<<get_widthcards()<<" heigh: "<<get_heightcards()<<endl;
    deck.Write_string(strbuf);
    fout<<"deck: "<<strbuf<<"  x: "<<deck.get_x()<<" y: "<<deck.get_y()<<endl;
    int j=0;
    int i;
    int maxj=0;
    for(auto card1:card)
        if (card1.size()>maxj)
            maxj=card1.size();
    while (1)
    {
        i=0;
        while (i<card.size())
        {
            if (j<card[i].size())
            {
                card[i][j].Write_string(strbuf);
                if ((i==0))
                    strcpy(strfile,strbuf);
                else
                    strcat(strfile,strbuf);

            }
            else if ((i==0))
                strcpy(strfile,"______");
            else
                strcat(strfile,"______");

            strcat(strfile," ");
            i++;
        }
        fout << strfile<<endl;
        if (j==(maxj-1))
            break;
        else
            j++;
    }
    fout.close();
}

void GameTable::Load_from_file(char *filename)
{
    char strfile[100];
    int w,h,x,y;
    ifstream fin(filename);

    if (!fin.is_open())
        cout << "Error\n";
    else
    {
        fin >> strfile;
        fin >> strfile;
        set_base(atoi(strfile));
        fin >> strfile;
        fin >> strfile;
        set_numberdeck(atoi(strfile));
        fin >> strfile;
        fin >> strfile;
        w=atoi(strfile);
        fin >> strfile;
        fin >> strfile;
        h=atoi(strfile);
        set_size(w,h);
        fin >> strfile;
        fin >> strfile;
        deck.Read_string(strfile);
        fin >> strfile;
        fin >> strfile;
        x=atoi(strfile);
        fin >> strfile;
        fin >> strfile;
        y=atoi(strfile);
        deck.set_position(x,y);
        card.resize(10);
        for (int i=0; i<card.size(); i++)
            card[i].clear();
        while(1)
        {
            int flag=0;
            for (int i=0; i<card.size(); i++)
            {
                fin >> strfile;
                if ((strfile[0]!='\0')&&(strfile[0]!='_'))
                {
                    Cards cardbuf;
                    cardbuf.Read_string(strfile);
                    card[i].push_back(cardbuf);
                }
                else if (strfile[0]=='\0')
                    flag++;
                strfile[0]='\0';
            }
            if (flag==(card.size()))
                break;
        }

        fin.close();
    }
}

bool GameTable::true_card(int i ,int j)
{
    bool flag=false;

    if ((i>=card.size())||(j>=card[i].size()))
        return flag;

    Cards cardij=get_card(i,j);

    if ((cardij.get_name()==14) &&(cardij.get_suit()==5))
        return flag;
    else if ((i<card.size())&&(j==(card[i].size()-1)))
    {
        //cout<<"true_card"<<i<<" "<<j<<endl;
        flag=true;
        return flag;
    }
    else
    {
        Cards card_next;
        int namecard=cardij.get_name()-1;
        int j1=j+1;

        while (1)
        {
            card_next=get_card(i,j1);
            cout<<"true_card"<<i<<" "<<j1<<endl;
            if (j1==(card[i].size()-1))
            {
                //cout<<"true_card"<<i<<" "<<j<<endl;
                flag=true;
                break;
            }
            else if ((card_next.get_name()==namecard)&&(card_next.get_suit()==cardij.get_suit()))
            {
                j1++;
                namecard--;
            }
            else
            {
                flag=false;
                break;
            }

        }
        return flag;
    }

}

bool GameTable::true_step(int i ,int j,Cards cardij)
{
    bool flag=false;

    if ((i>=card.size())||(j>card[i].size()))
    {
        cout<<"Eror 1:"<<i<<" "<<j<<" "<<card[i].size()<<endl;
        return flag;
    }

    Cards card_prev=get_card(i,j-1);

    if ((i<card.size())&&(j<=card[i].size()))
        if ((card_prev.get_name()==14) &&(card_prev.get_suit()==5))
            return flag;
        else if (card_prev.get_name()==(cardij.get_name()+1))
        {
            flag=true;
            //cout<<"true_card "<<i<<" "<<j<<endl;
            //card_prev.Print_low();
           // cout<<" ";
           // cardij.Print_low();
           // cout<<endl;
            return flag;
        }
        else
            return flag;
}


vector <Cards> GameTable::true_cards()
{
    vector <Cards> seria;
    for (int i=0; i<card.size(); i++)
        for (int j=card[i].size()-1; j>=0; j--)
            if (true_card(i ,j))
                seria.push_back(get_card(i,j));
    return seria;
}

vector <Steps> GameTable::true_steps()
{
    vector <Steps> serias;
    for (int i=0; i<card.size(); i++)
        for (int j=card[i].size()-1; j>=0; j--)
            if (true_card(i ,j))
            {
                for (int i1=0; i1<card.size(); i1++)
                        if (i1!=i)
                        {
                            if (true_step(i1 ,card[i1].size(),get_card(i,j)))
                            {
                                Steps seria;

                                seria.New_Step(cloculation_raiting(i,j,i1,card[i1].size()-1),i,j,get_card(i,j),i1,card[i1].size(),get_card(i1,card[i1].size()-1));

                                serias.push_back(seria);
                                //break;

                            }
                        }
                break;
            }
    return serias;
}

void GameTable::add_card(vector <Cards> cardin)
{
    for (int i=0; i<card.size(); i++)
    {
        Cards cardone=get_card(i,card[i].size()-1);
        if ((cardone.get_name()==14) && (cardone.get_suit()==5))
        {
                set_card(i,card[i].size()-1,cardin[i]);
        }
        else if (cardone==cardin[i])
            cout<<"done "<<i<<endl;
        else
            cout<<"err "<<i<<endl;
    }
}

void GameTable::add_deck(vector <Cards> cardin)
{
    for (int i=0; i<card.size(); i++)
        set_card(i,card[i].size(),cardin[i]);
}


void GameTable::transfer_step(Steps step)
{
    while (1)
    {
        Cards cardbuf;
        cardbuf=get_card(step.get_position_start_x(),step.get_position_start_y());
        set_card(step.get_position_end_x(),step.get_position_end_y(),cardbuf);
        Reset_Card(step.get_position_start_x(),step.get_position_start_y());
        step.Print_full();
        cout<<"transfer "<<card[step.get_position_start_x()].size()<<" "<<step.get_position_start_y()<<endl;
        if((card[step.get_position_start_x()].size()-1<=step.get_position_start_y())||(card[step.get_position_start_x()].size()==0))
            break;
    }

}

bool GameTable::serach_column( bool delet)
{
    int position[2];
    bool flag=false;
    for (int i=0; i<card.size(); i++)
    {
        if(card[i].size()>=13)
            if ((card[i][card[i].size()-1].get_name()==1))
                for (int j=card[i].size()-2; j>=card[i].size()-13; j--)
                {
                    int name=2;
                    if ((card[j][i].get_name()==name)&&(card[j][i].get_suit()==card[j][card[i].size()-1].get_suit()))
                    {
                        name++;
                        if (name==13)
                        {
                            flag=true;
                            position[0]=i;
                            position[1]=j;
                            break;
                        }

                    }
                    else
                    {
                        break;
                    }
                }
    }

    if (delet && flag)
    {
        for (int j=position[1]; j<position[1]+13; j++)
        {
            card[position[0]].pop_back();
        }
    }

    return flag;

}


bool GameTable::blank_column()
{
    bool flag=false;
    for (int i=0; i<card.size(); i++)
        if (card[i].size()==0)
            flag=true;
    return flag;
}

bool GameTable::secret_last_card()
{
    bool flag=false;
    for (int i=0; i<card.size(); i++)
        if (card[i].size()>0)
            if ((card[i][card[i].size()-1].get_name()==14) && (card[i][card[i].size()-1].get_suit()==5))
                flag=true;
    return flag;
}

bool GameTable::complite_task(Steps *step)
{
    bool flag=false;
    if (secret_last_card())
    {
        step->add_rating_step(100);
        flag=true;
    }
    if (blank_column())
    {
        step->add_rating_step(400);
        flag=true;
    }
    if (serach_column(0))
    {
        step->add_rating_step(1000);
        flag=true;
    }
    return flag;
}



int GameTable::cloculation_raiting(int i1,int j1, int i2, int j2)
{
    Cards cardst=get_card(i1,j1);
    int rating=0;

    if (card[i2].size()==0)
    {
        if (cardst.get_name()==13)
            rating=20;
    }
    else
    {
        //cout<<"start_card "<<i1<<" "<<j1<<" end_card "<<i2<<" "<<j2<<endl;
        Cards carden=get_card(i2,j2);

        if (cardst.get_suit()==carden.get_suit())
        {

            int multiplier=1;
            for (int i=1; i<13; i++)
                if ((card[i2][j2-i].get_suit()==carden.get_suit())&&((carden.get_name()+i)==card[i2][j2-i].get_name()))
                    multiplier++;
                else
                    break;

            multiplier +=card[i1].size()-j1-1;
            rating=4*multiplier;
            cout<<"multiplier "<<multiplier<<endl;
        }
        else if (cardst.get_suit()!=carden.get_suit())
        {
            rating=2;
            if(((cardst.get_suit()==1)&&(carden.get_suit()==2))||((cardst.get_suit()==3)&&(carden.get_suit()==4)))
                rating=3;
            if(((cardst.get_suit()==2)&&(carden.get_suit()==1))||((cardst.get_suit()==4)&&(carden.get_suit()==3)))
                rating=3;
        }
    }
    return rating;
}
