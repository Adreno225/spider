#include <opencv2/opencv.hpp>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include "mainmodule.h"
#include "CV.h"
#include "mousecamscreen.h"




vector <Mat> read_template ()
{
    vector <Mat> template_card;

    template_card.push_back(imread("card1/100.png", IMREAD_GRAYSCALE));
    for (int suits=1; suits<5; suits++)
        for (int namecart=1; namecart<14; namecart++)
        {
            int numbercard=suits*100+namecart;
            string f_str=to_string(numbercard);
            string filename="card1/"+f_str+".png";
            template_card.push_back(imread(filename, IMREAD_GRAYSCALE));

        }

    return template_card;

}

vector<Cards>  serch_card2(vector <Mat> template_card)
{
    Mat img=imread("table/img_screen.png", IMREAD_GRAYSCALE);


    vector <double> linetable;

    vector< vector<Point>>PointNone=matchig_contours(img);
    vector< Mat>imgNone;

    for (int i=0; i<PointNone.size(); i++)
    {
        vector<Point>pn=PointNone[i];

        Point UPLEFT=pn[0];
        Point DOWNRIGHT=pn[1];
        //cout << "x="<<UPLEFT.x<<" y="<<UPLEFT.y<<" deltax="<<UPLEFT.x-DOWNRIGHT.x<<" deltax="<<DOWNRIGHT.y-UPLEFT.y<<endl;

        Rect r( UPLEFT.x, DOWNRIGHT.y,DOWNRIGHT.x-UPLEFT.x, UPLEFT.y-DOWNRIGHT.y );

        Mat Cardimg=img(r);


        //imshow("Card",Cardimg);
        //waitKey(1000);
        imgNone.push_back(Cardimg);
        string f_str=to_string(i);
        string filename="table/"+f_str+".png";
        imwrite(filename,Cardimg);
    }

    vector<Cards> card;
    Cards card1;
    card1.new_card(5,14,0,0);
    card.push_back(card1);

    for (int suits=1; suits<5; suits++)
        for (int namecart=1; namecart<14; namecart++)
        {
            card1.new_card(suits,namecart,0,0);
            card.push_back(card1);
        }

    vector <int> numcard=matching_card2(imgNone,template_card);

    // for (auto in:imgNone)
    //{
    // numcard.push_back( matching_card(in,template_card));
    // cout << "numcard="<<numcard.back()<<endl;
    //}

    for(int i=-5; i<=5; i++)
        linetable.push_back(960+(89*2*i));

    vector<Cards> cardres;


    for (int i=0; i<linetable.size()-1; i++)
    {
        //cout <<linetable[i]<< "--"<<linetable[i+1]<<endl;
        Cards cardone;
        cardone.new_card(0,0,0,1080);
        for (int j=0; j<PointNone.size(); j++)
        {

            vector<Point>pn=PointNone[j];
            Point UPLEFT=pn[0];
            if ((UPLEFT.x>linetable[i])&&(UPLEFT.x<linetable[i+1]))
                if (UPLEFT.y<cardone.get_y())
                {

                    cardone=card[numcard[j]];
                    cardone.set_position(UPLEFT.x,UPLEFT.y);
                    //cardone.Print_full();
                }
        }

        cardres.push_back(cardone);
    }

    return  cardres;
}


void transfer_cards(xdo_t *xdo,GameTable *table,SeriesSteps seria)
{


    for (int i=0; i<seria.get_size_step(); i++)
    {

        int numbernonecard=0;
        Cards cardstart=table->get_card( seria.step[i].get_position_start_x(),seria.step[i].get_position_start_y());
        //cardstart.Print_low();

        for (int i1=cardstart.get_name()+1; i1<=13; i1++)
        {
            Cards cardreal=table->get_card(seria.step[i].get_position_start_x(),seria.step[i].get_position_start_y()-numbernonecard-1);
            if ((cardreal.get_suit()==cardstart.get_suit())&&(i1==cardreal.get_name()))
                numbernonecard++;
            else
                break;
        }
        cout <<i<<"  numbernonecard "<<i<<" - "<<numbernonecard<<")\n";




        if (seria.step[i].get_rating_step()>=1000)
        {
            table->serach_column(1);
            table->set_base(table->get_base()+1);
        }
        else
            table->transfer_step(seria.step[i]);

        cout << "start ("<< seria.step[i].get_position_start_x()<<","<< seria.step[i].get_position_start_y()<<")\n";
        cout << "end ("<< seria.step[i].get_position_end_x()<<","<< seria.step[i].get_position_end_y()<<")\n";

        int y1= seria.step[i].get_position_start_y()+numbernonecard;
        cout << "y1="<<y1<<")\n";
        transfer_to_key(xdo,seria.step[i].get_position_start_x(),y1,
                        seria.step[i].get_position_end_x(), seria.step[i].get_position_end_y());
    }

}



void tap_deck_key (GameTable *table,xdo_t *xdo)
{
    Cards DECK=table->get_deck();
    key_click(xdo,"Return");
    table->set_numberdeck(table->get_numberdeck()-1);
    //serch_deck2(table,xdo);
}


void get_line(Mat *img,double deltax)
{

    for(int i=0; i<=5; i++)
    {
        line(*img,Point(960-(deltax*2*i),0.0),Point(960-(deltax*2*i),1080.0), Scalar(0, 255, 0), 3 );
        line(*img,Point(960+(deltax*2*i),0.0),Point(960+(deltax*2*i),1080.0), Scalar(0, 255, 0), 3 );
    }

}


int main(int, char**)
{
    Display *display = NULL;
    xdo_t *xdo = NULL;
    display = XOpenDisplay(NULL);
    if(display == NULL)
    {
        fprintf(stderr, "can't open display!\n");

    }

    xdo = xdo_new((char*) display);


    transfer_window(xdo);
    waitKey(1000);

    vector <Mat> template_card=read_template ();
    GameTable table;
    table.Reset();
    vector<SeriesSteps>serias;
    int step_game=0;
    bool flag=true;
    for(;;)
    {

        cout << "////////////////////////// STEP "<<step_game<<" //////////////////////////"<< endl;
        if (flag)
        {
            get_screen(xdo);
            table.add_card(serch_card2(template_card));
            table.Print_full();
            //table.Save_to_file("table.txt");
        }
        flag=true;
        SeriesSteps seria;
        seria.Reset();
        seria=set_steps(table);
        seria.print_series();

        if ((seria.get_size_step()!=0)&&(!seria.search_seras(serias)))
        {
            transfer_cards(xdo,&table,seria);
            table.Print_full();
            serias.push_back(seria);

        }
        else if (table.get_numberdeck()!=0)
        {
            tap_deck_key (&table,xdo);
            waitKey(15000);
            get_screen(xdo);
            table.add_deck(serch_card2(template_card));
            table.Print_full();

            //table.Save_to_file("table.txt");
            flag=false;
        }
        else if (table.get_base()==8)
        {
            cout << "////////////////////////// YOU WIN //////////////////////////"<< endl;
            table.Print_full();
            break;
        }
        else
        {
            cout << "////////////////////////// YOU LOSE //////////////////////////"<< endl;
            break;
        }
        cout << "////////////////////////// END STEP "<<step_game<<" //////////////////////////"<< endl;
        step_game++;
        waitKey(1000);

        //if (step_game>1)
         //waitKey(0);
    }



    return 0;
}

