
#include <iostream>

#include "opencv2/opencv_modules.hpp"

#include <opencv2/flann.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <cstdint>
#include <cstring>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "CV.h"

using namespace cv;
using namespace std;



Key::Key(vector<DMatch> bestMatches,vector<KeyPoint> keyImg1,vector<KeyPoint> keyImg2)
    {
        vector<int> pointx_img_1((int)bestMatches.size()),pointy_img_1((int)bestMatches.size()),pointx_img_2((int)bestMatches.size()),pointy_img_2((int)bestMatches.size());
        int minx=1000;
        int maxx=0;
        int miny=1000;
        int maxy=0;

        for( int i = 0; i < (int)bestMatches.size(); i++ )
        {
            pointx_img_1.operator[](i)=(int)keyImg1[bestMatches[i].queryIdx].pt.x;
            pointy_img_1.operator[](i)=(int)keyImg1[bestMatches[i].queryIdx].pt.y;
            pointx_img_2.operator[](i)=(int)keyImg2[bestMatches[i].trainIdx].pt.x;
            pointy_img_2.operator[](i)=(int)keyImg2[bestMatches[i].trainIdx].pt.y;
        }
        for( int i = 0; i < (int)bestMatches.size(); i++ )
        {
            if (pointx_img_1.operator[](i)<minx)
                minx=pointx_img_1.operator[](i);
            if (pointx_img_1.operator[](i)>maxx)
                maxx=pointx_img_1.operator[](i);
            if (pointy_img_1.operator[](i)<miny)
                miny=pointy_img_1.operator[](i);
            if (pointy_img_1.operator[](i)>maxy)
                maxy=pointy_img_1.operator[](i);
        }
        deltax=(maxx-minx)/2;
        deltay=(maxy-miny)/2;

        vector<int> point_2((int)bestMatches.size());
        numincpoints=0;

        for( int i = 0; i < (int)bestMatches.size(); i++ )
        {
            point_2[i]=0;
            for( int j = 0; j < (int)bestMatches.size(); j++ )
                if ((((pointx_img_2.operator[](i)-deltax)<=pointx_img_2.operator[](j))&&(pointx_img_2.operator[](j)<=(pointx_img_2.operator[](i)+deltax))) &&(((pointy_img_2.operator[](i)-deltay)<=pointy_img_2.operator[](j))&&(pointy_img_2.operator[](j)<=(pointy_img_2.operator[](i)+deltay))))
                    point_2[i]++;

                if(numincpoints<point_2.operator[](i))
                {
                    numincpoints=point_2.operator[](i);
                    x=pointx_img_2.operator[](i);
                    y=pointy_img_2.operator[](i);
                }
        }
        persentpoint=(float)numincpoints/bestMatches.size()*100.0;
        print_key();

    }

Key::Key(vector<DMatch> bestMatches,vector<KeyPoint> keyImg1,vector<KeyPoint> keyImg2,Key One)
    {
        vector<int> pointx_img_1((int)bestMatches.size()),pointy_img_1((int)bestMatches.size()),pointx_img_2((int)bestMatches.size()),pointy_img_2((int)bestMatches.size());
        int minx=1000;
        int maxx=0;
        int miny=1000;
        int maxy=0;

        for( int i = 0; i < (int)bestMatches.size(); i++ )
        {
            pointx_img_1.operator[](i)=(int)keyImg1[bestMatches[i].queryIdx].pt.x;
            pointy_img_1.operator[](i)=(int)keyImg1[bestMatches[i].queryIdx].pt.y;
            pointx_img_2.operator[](i)=(int)keyImg2[bestMatches[i].trainIdx].pt.x;
            pointy_img_2.operator[](i)=(int)keyImg2[bestMatches[i].trainIdx].pt.y;
        }
        for( int i = 0; i < (int)bestMatches.size(); i++ )
        {
            if (pointx_img_1.operator[](i)<minx)
                minx=pointx_img_1.operator[](i);
            if (pointx_img_1.operator[](i)>maxx)
                maxx=pointx_img_1.operator[](i);
            if (pointy_img_1.operator[](i)<miny)
                miny=pointy_img_1.operator[](i);
            if (pointy_img_1.operator[](i)>maxy)
                maxy=pointy_img_1.operator[](i);
        }
        deltax=(maxx-minx)/2;
        deltay=(maxy-miny)/2;

        vector<int> point_2((int)bestMatches.size());
        numincpoints=0;

        for( int i = 0; i < (int)bestMatches.size(); i++ )
        {
            point_2[i]=0;

            for( int j = 0; j < (int)bestMatches.size(); j++ )
                if ((((pointx_img_2.operator[](i)-deltax)<=pointx_img_2.operator[](j))&&(pointx_img_2.operator[](j)<=(pointx_img_2.operator[](i)+deltax))) &&(((pointy_img_2.operator[](i)-deltay)<=pointy_img_2.operator[](j))&&(pointy_img_2.operator[](j)<=(pointy_img_2.operator[](i)+deltay))))
                    point_2[i]++;
        if ((((One.x+One.deltax)<pointx_img_2.operator[](i))||((One.x-One.deltax)>pointx_img_2.operator[](i)))&&(((One.y+One.deltay)<pointy_img_2.operator[](i))||((One.y-One.deltay)>pointy_img_2.operator[](i))))
            if(numincpoints<point_2.operator[](i))
            {
                numincpoints=point_2.operator[](i);
                x=pointx_img_2.operator[](i);
                y=pointy_img_2.operator[](i);
            }
        }
        persentpoint=(float)numincpoints/bestMatches.size()*100.0;
        print_key();
    }


void Key::show_rectangle(Mat img)
    {
        rectangle(img,Point(x-deltax,y+deltay),Point(x+deltax,y-deltay), Scalar(0, 255, 0), 3 );
    }


void Key::print_key()
{
    cout<<"x="<<x<<" y="<<y<<"; numincpoints="<<numincpoints<<" ; persentpoint="<<persentpoint<<"%"<<endl;
}

bool  Key::overlap_key(vector<Key> Keycard)
{
    bool flag=true;


    for (auto Key1:Keycard)//if (((x-deltax)<=Key1.x-Key1.deltax) && ((x+deltax)>=Key1.x-Key1.deltax)||((x-deltax)<=Key1.x+Key1.deltax) && ((x+deltax)>=Key1.x+Key1.deltax))
                {
                    if (persentpoint<Key1.persentpoint)
                        flag=false;
                    if  ((persentpoint==Key1.persentpoint)&&(numincpoints<Key1.numincpoints))
                        flag=false;
                    if  ((persentpoint==Key1.persentpoint)&&(numincpoints==Key1.numincpoints)&&(deltax<Key1.deltax))
                        flag=false;

                }

    if (!flag)
        print_key();
    return flag;
}


void Serch_point_card(Mat frame,vector <Mat> object,vector<Key> *Keycard)
{

    string typeDesc;
    string typeAlgoMatch;

    //typeDesc="AKAZE-DESCRIPTOR_KAZE_UPRIGHT";    // see http://docs.opencv.org/trunk/d8/d30/classcv_1_1AKAZE.html
    //typeDesc="AKAZE";    // see http://docs.opencv.org/trunk/d8/d30/classcv_1_1AKAZE.html
    //typeDesc="ORB";      // see http://docs.opencv.org/trunk/de/dbf/classcv_1_1BRISK.html
    //typeDesc="BRISK";    // see http://docs.opencv.org/trunk/db/d95/classcv_1_1ORB.html
    //typeDesc="AgastFeatureDetector";
    typeDesc="KAZE";

    typeAlgoMatch="BruteForce";
   //typeAlgoMatch="BruteForce-L1";
    //typeAlgoMatch="BruteForce-Hamming";
   // typeAlgoMatch="BruteForce-Hamming(2)";  FLANNBASED
   //typeAlgoMatch="FlannBased";
    Ptr<Feature2D> b;

    Ptr<DescriptorMatcher> descriptorMatcher;

    if (typeDesc == "AKAZE-DESCRIPTOR_KAZE_UPRIGHT")
        b = AKAZE::create(AKAZE::DESCRIPTOR_KAZE_UPRIGHT);

    if (typeDesc == "AKAZE")
        b = AKAZE::create();

    if (typeDesc == "ORB")
        b = ORB::create();

    if (typeDesc == "BRISK")
        b = BRISK::create();
    if (typeDesc == "AgastFeatureDetector")
        b = AgastFeatureDetector::create();
    if (typeDesc == "KAZE")
        b = KAZE::create();

    vector<KeyPoint> keyImg2;
    Mat descImg2;

    b->detectAndCompute(frame, Mat(), keyImg2, descImg2,false);

    for (auto img1 : object)
    {

        vector<DMatch> matches;
        Mat descImg1;
        vector<DMatch> bestMatches;
        vector<KeyPoint> keyImg1;

        b->detectAndCompute(img1, Mat(), keyImg1, descImg1,false);
                // Match method loop
        descriptorMatcher = DescriptorMatcher::create(typeAlgoMatch);

        descriptorMatcher->match(descImg1, descImg2, matches, Mat());
        // Keep best matches only to have a nice drawing.
        // We sort distance between descriptor matches
        Mat index;
        int nbMatch=int(matches.size());
        Mat tab(nbMatch, 1, CV_32F);
        for (int i = 0; i<nbMatch; i++)
        {
            tab.at<float>(i, 0) = matches[i].distance;
        }
        sortIdx(tab, index, SORT_EVERY_COLUMN + SORT_ASCENDING);
        for (int i = 0; i<matches.size(); i++)
        {
            bestMatches.push_back(matches[index.at<int>(i, 0)]);
        }
        cout<<"------------------------------------------------"<<endl;
        Key One(bestMatches, keyImg1, keyImg2);
        cout<<"------------------------------------------------"<<endl;
        Key Two(bestMatches, keyImg1, keyImg2,One);
        Keycard->push_back(One);
        Keycard->push_back(Two);

    }
}




Key Serch_point_icon (Mat frame,Mat img1)
{

    string typeDesc;
    string typeAlgoMatch;

    //typeDesc="AKAZE-DESCRIPTOR_KAZE_UPRIGHT";    // see http://docs.opencv.org/trunk/d8/d30/classcv_1_1AKAZE.html
    //typeDesc="AKAZE";    // see http://docs.opencv.org/trunk/d8/d30/classcv_1_1AKAZE.html
    //typeDesc="ORB";      // see http://docs.opencv.org/trunk/de/dbf/classcv_1_1BRISK.html
    //typeDesc="BRISK";    // see http://docs.opencv.org/trunk/db/d95/classcv_1_1ORB.html
    //typeDesc="AgastFeatureDetector";
    typeDesc="KAZE";

    typeAlgoMatch="BruteForce";
   //typeAlgoMatch="BruteForce-L1";
    //typeAlgoMatch="BruteForce-Hamming";
   // typeAlgoMatch="BruteForce-Hamming(2)";  FLANNBASED
   //typeAlgoMatch="FlannBased";
    Ptr<Feature2D> b;

    Ptr<DescriptorMatcher> descriptorMatcher;

    if (typeDesc == "AKAZE-DESCRIPTOR_KAZE_UPRIGHT")
        b = AKAZE::create(AKAZE::DESCRIPTOR_KAZE_UPRIGHT);

    if (typeDesc == "AKAZE")
        b = AKAZE::create();

    if (typeDesc == "ORB")
        b = ORB::create();

    if (typeDesc == "BRISK")
        b = BRISK::create();
    if (typeDesc == "AgastFeatureDetector")
        b = AgastFeatureDetector::create();
    if (typeDesc == "KAZE")
        b = KAZE::create();

    vector<KeyPoint> keyImg2;
    Mat descImg2;

    b->detectAndCompute(frame, Mat(), keyImg2, descImg2,false);


    vector<DMatch> matches;
    Mat descImg1;
    vector<DMatch> bestMatches;
    vector<KeyPoint> keyImg1;

    b->detectAndCompute(img1, Mat(), keyImg1, descImg1,false);
                // Match method loop
    descriptorMatcher = DescriptorMatcher::create(typeAlgoMatch);

    descriptorMatcher->match(descImg1, descImg2, matches, Mat());
        // Keep best matches only to have a nice drawing.
        // We sort distance between descriptor matches
    Mat index;
    int nbMatch=int(matches.size());
    Mat tab(nbMatch, 1, CV_32F);
    for (int i = 0; i<nbMatch; i++)
    {
        tab.at<float>(i, 0) = matches[i].distance;
    }
    sortIdx(tab, index, SORT_EVERY_COLUMN + SORT_ASCENDING);
    for (int i = 0; i<100; i++)
    {
        bestMatches.push_back(matches[index.at<int>(i, 0)]);
    }

    Key One(bestMatches, keyImg1, keyImg2);
    return One;
}

void serch_test(string nameobject,string nametable)
{
    vector<String> typeDesc;
    vector<String> typeAlgoMatch;
    vector<String> fileName;
    // This descriptor are going to be detect and compute
    typeDesc.push_back("AKAZE-DESCRIPTOR_KAZE_UPRIGHT");    // see http://docs.opencv.org/trunk/d8/d30/classcv_1_1AKAZE.html
   typeDesc.push_back("AKAZE");    // see http://docs.opencv.org/trunk/d8/d30/classcv_1_1AKAZE.html
    typeDesc.push_back("ORB");      // see http://docs.opencv.org/trunk/de/dbf/classcv_1_1BRISK.html
    typeDesc.push_back("BRISK");    // see http://docs.opencv.org/trunk/db/d95/classcv_1_1ORB.html
     typeDesc.push_back("AgastFeatureDetector");
     typeDesc.push_back("GFTTDetector");
     typeDesc.push_back("KAZE");
     typeDesc.push_back("MSER");
     typeDesc.push_back("SimpleBlobDetector");
      typeDesc.push_back("FAST");


   // This algorithm would be used to match descriptors see http://docs.opencv.org/trunk/db/d39/classcv_1_1DescriptorMatcher.html#ab5dc5036569ecc8d47565007fa518257
    typeAlgoMatch.push_back("FlannBased");
    typeAlgoMatch.push_back("BruteForce");
    typeAlgoMatch.push_back("BruteForce-L1");
    typeAlgoMatch.push_back("BruteForce-Hamming");
    typeAlgoMatch.push_back("BruteForce-Hamming(2)");


    Mat img1 = imread(nameobject, IMREAD_GRAYSCALE);
    Mat img2 = imread(nametable, IMREAD_GRAYSCALE);

    vector<double> desMethCmp;
    Ptr<Feature2D> b;

    // Descriptor loop
    vector<String>::iterator itDesc;
    for (itDesc = typeDesc.begin(); itDesc != typeDesc.end(); ++itDesc)
    {
        Ptr<DescriptorMatcher> descriptorMatcher;
        // Match between img1 and img2
        vector<DMatch> matches;
        // keypoint  for img1 and img2
        vector<KeyPoint> keyImg1, keyImg2;
        // Descriptor for img1 and img2
        Mat descImg1, descImg2;
        vector<String>::iterator itMatcher = typeAlgoMatch.end();
        if (*itDesc == "AKAZE-DESCRIPTOR_KAZE_UPRIGHT"){
            b = AKAZE::create(AKAZE::DESCRIPTOR_KAZE_UPRIGHT);
            }
        if (*itDesc == "AKAZE"){
            b = AKAZE::create();
            }
        if (*itDesc == "ORB"){
            b = ORB::create();
        }
        if (*itDesc == "BRISK"){
            b = BRISK::create();
        }
        if (*itDesc == "AgastFeatureDetector"){
            b = AgastFeatureDetector::create();
        }
        if (*itDesc == "KAZE"){
            b = KAZE::create();
        }
        if (*itDesc == "MSER"){
            b = MSER::create();
        }
        if (*itDesc == "SimpleBlobDetector"){
            b = SimpleBlobDetector::create();
        }
        else
            if (*itDesc == "FAST"){
                b = FastFeatureDetector::create();
            }
        try
        {
            // We can detect keypoint with detect method
            b->detect(img1, keyImg1, Mat());
            // and compute their descriptors with method  compute
            b->compute(img1, keyImg1, descImg1);
            // or detect and compute descriptors in one step
            b->detectAndCompute(img2, Mat(),keyImg2, descImg2,false);
            // Match method loop
            for (itMatcher = typeAlgoMatch.begin(); itMatcher != typeAlgoMatch.end(); ++itMatcher){
                descriptorMatcher = DescriptorMatcher::create(*itMatcher);
                if ((*itMatcher == "BruteForce-Hamming" || *itMatcher == "BruteForce-Hamming(2)") && (b->descriptorType() == CV_32F || b->defaultNorm() <= NORM_L2SQR))
                {
                    cout << "**************************************************************************\n";
                    cout << "It's strange. You should use Hamming distance only for a binary descriptor\n";
                    cout << "**************************************************************************\n";
                }
                if ((*itMatcher == "BruteForce" || *itMatcher == "BruteForce-L1") && (b->defaultNorm() >= NORM_HAMMING))
                {
                    cout << "**************************************************************************\n";
                    cout << "It's strange. You shouldn't use L1 or L2 distance for a binary descriptor\n";
                    cout << "**************************************************************************\n";
                }
                try
                {
                    descriptorMatcher->match(descImg1, descImg2, matches, Mat());
                    // Keep best matches only to have a nice drawing.
                    // We sort distance between descriptor matches
                    Mat index;
                    int nbMatch=int(matches.size());
                    Mat tab(nbMatch, 1, CV_32F);
                    for (int i = 0; i<nbMatch; i++)
                    {
                        tab.at<float>(i, 0) = matches[i].distance;
                    }
                    sortIdx(tab, index, SORT_EVERY_COLUMN + SORT_ASCENDING);
                    vector<DMatch> bestMatches;
                    for (int i = 0; i<30; i++)
                    {
                        bestMatches.push_back(matches[index.at<int>(i, 0)]);
                    }
                    Mat result;
                    drawMatches(img1, keyImg1, img2, keyImg2, bestMatches, result);

                    namedWindow(*itDesc+": "+*itMatcher, WINDOW_AUTOSIZE);
                    imshow(*itDesc + ": " + *itMatcher, result);
                    // Saved result could be wrong due to bug 4308

                    vector<DMatch>::iterator it;
                    cout<<"**********Match results**********\n";
                    cout << "Index \tIndex \tdistance\n";
                    cout << "in img1\tin img2\n";
                    // Use to compute distance between keyPoint matches and to evaluate match algorithm
                    double cumSumDist2=0;
                    for (it = bestMatches.begin(); it != bestMatches.end(); ++it)
                    {
                        cout << it->queryIdx << "\t" <<  it->trainIdx << "\t"  <<  it->distance << "\n";
                        Point2d p=keyImg1[it->queryIdx].pt-keyImg2[it->trainIdx].pt;

                        cumSumDist2=p.x*p.x+p.y*p.y;
                    }
                    desMethCmp.push_back(cumSumDist2);
                    waitKey();
                }
                catch (Exception& e)
                    {
                    cout << e.msg << endl;
                    cout << "Cumulative distance cannot be computed." << endl;
                    desMethCmp.push_back(-1);
                    }
                }
        }
        catch (Exception& e)
        {
            cout << "Feature : " << *itDesc << "\n";
            if (itMatcher != typeAlgoMatch.end())
            {
                cout << "Matcher : " << *itMatcher << "\n";
            }
            cout << e.msg << endl;
        }
    }
    int i=0;
    cout << "Cumulative distance between keypoint match for different algorithm and feature detector \n\t";
    cout << "We cannot say which is the best but we can say results are differents! \n\t";
    for (vector<String>::iterator itMatcher = typeAlgoMatch.begin(); itMatcher != typeAlgoMatch.end(); ++itMatcher)
    {
        cout<<*itMatcher<<"\t";
    }
    cout << "\n";
    for (itDesc = typeDesc.begin(); itDesc != typeDesc.end(); ++itDesc)
    {
        cout << *itDesc << "\t";
        for (vector<String>::iterator itMatcher = typeAlgoMatch.begin(); itMatcher != typeAlgoMatch.end(); ++itMatcher, ++i)
        {
            cout << desMethCmp[i]<<"\t";
        }
        cout<<"\n";
    }
}

vector< vector <Point> > matchig_contours( Mat table)
{
     Mat object = imread("card/none.png", IMREAD_GRAYSCALE);
   cout<<"IMG1 ____________________________________"<<endl;
    vector<Point> contours1;
    vector<Vec4i> hierarchy1;
    vector<vector<Point> >contours10 ;
    findContours( object, contours10, hierarchy1, RETR_TREE, CHAIN_APPROX_SIMPLE);
    contours1.resize(contours10.size());
        approxPolyDP(Mat(contours10[2]), contours1, 3, true);

    cout<<"IMG2 ____________________________________"<<endl;
    vector<vector<Point> > contours2;
    vector<Vec4i> hierarchy2;
    vector<vector<Point> >contours20 ;
    findContours( table, contours20, hierarchy2, RETR_TREE, CHAIN_APPROX_SIMPLE);
    contours2.resize(contours20.size());

    for( size_t k = 0; k < contours20.size(); k++ )
        approxPolyDP(Mat(contours20[k]), contours2[k], 3, true);

    cout<<"matchShapes_________________________________"<<endl;

    vector<vector<Point> >rescontours ;
    vector<vector<Point> >PointNone;
        double matchM=1000;
        vector<Point> rescont;
        for( size_t m = 0; m < contours20.size(); m++ )
        {
            double match0 = matchShapes(contours20[m], contours10[2], CV_CONTOURS_MATCH_I3,0);
            if(match0<0.05)
            {
                matchM = match0;
                //rescont = contours20[m];
                vector<Point>contur=contours20[m];
                int maxX=0;
                int  minX=2000;
                int  maxY=0;
                int  minY=2000;

                for( int m = 0; m < contur.size(); m++ )
                {
                    Point p=contur[m];

                    if (p.x>maxX)
                        maxX=p.x;
                    if (p.x<minX)
                        minX=p.x;
                    if (p.y>maxY)
                        maxY=p.y;
                     if (p.y<minY)
                        minY=p.y;
                }
                //cout<<"deltax="<<maxX-minX<<" deltay="<<maxY-minY<<endl;
                if (((maxX-minX)>100)&&((maxY-minY)>50)&&((maxX-minX)<200)&&((maxY-minY)<300))
                {
                    vector<Point> pointone;
                    pointone.push_back(Point(minX,maxY));
                    pointone.push_back(Point(maxX,minY));
                    PointNone.push_back(pointone);
                    rescontours.push_back( contours20[m]);
                }
            }
        }

    //cout<<"escontours.size()"<<rescontours.size()<<endl;






    printf("DRAW ____________________________________");
        RNG rng(12345);
      Mat drawing = Mat::zeros( table.size(), CV_8UC3 );
      for( size_t i = 0; i<rescontours.size(); i++ )
         {
           Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

           drawContours( drawing, rescontours, (int)i, color, 2, 8, hierarchy2, 0, Point() );
         }
       // cout<<"END____________________________________"<<rescontours.size()<<endl;
      //namedWindow( "Contours", WINDOW_AUTOSIZE );
      //imshow( "Contours", drawing );
        imwrite("table/contur.png",drawing);

    return PointNone;

}


int matching_card(Mat card,vector <Mat> object)
{

    string typeDesc;
    string typeAlgoMatch;

    //typeDesc="AKAZE-DESCRIPTOR_KAZE_UPRIGHT";    // see http://docs.opencv.org/trunk/d8/d30/classcv_1_1AKAZE.html
    //typeDesc="AKAZE";    // see http://docs.opencv.org/trunk/d8/d30/classcv_1_1AKAZE.html
    //typeDesc="ORB";      // see http://docs.opencv.org/trunk/de/dbf/classcv_1_1BRISK.html
    //typeDesc="BRISK";    // see http://docs.opencv.org/trunk/db/d95/classcv_1_1ORB.html
    //typeDesc="AgastFeatureDetector";
    typeDesc="KAZE";

    typeAlgoMatch="BruteForce";
   //typeAlgoMatch="BruteForce-L1";
    //typeAlgoMatch="BruteForce-Hamming";
   // typeAlgoMatch="BruteForce-Hamming(2)";  FLANNBASED
   //typeAlgoMatch="FlannBased";
    Ptr<Feature2D> b;


    //if (typeDesc == "AKAZE-DESCRIPTOR_KAZE_UPRIGHT")
    //    b = AKAZE::create(AKAZE::DESCRIPTOR_KAZE_UPRIGHT);

    //if (typeDesc == "AKAZE")
   //     b = AKAZE::create();
//
   // if (typeDesc == "ORB")
  //      b = ORB::create();
//
 //   if (typeDesc == "BRISK")
 //       b = BRISK::create();
   // if (typeDesc == "AgastFeatureDetector")
 //       b = AgastFeatureDetector::create();
    if (typeDesc == "KAZE")
        b = KAZE::create();

    vector<KeyPoint> keyImg2;
    Mat descImg2;

    b->detectAndCompute(card, Mat(), keyImg2, descImg2,false);
    double maxpoint=10000.0;
    //Mat i;
    int num=0;
    int numcard;
    for (auto img1 : object)
    {

        Mat descImg1;
        vector<KeyPoint> keyImg1;

        b->detectAndCompute(img1, Mat(), keyImg1, descImg1,false);

           //cout<<"cumSumDist2="<<cumSumDist2<<endl;
        if (keyImg2.size()==keyImg1.size())
        {

            Ptr<DescriptorMatcher> descriptorMatcher;
            vector<DMatch> matches;
            vector<DMatch> bestMatches;               // Match method loop
            descriptorMatcher = DescriptorMatcher::create(typeAlgoMatch);

           descriptorMatcher->match(descImg1, descImg2, matches, Mat());
            // Keep best matches only to have a nice drawing.
            // We sort distance between descriptor matches
            Mat index;
            int nbMatch=int(matches.size());
            Mat tab(nbMatch, 1, CV_32F);
            for (int i = 0; i<nbMatch; i++)
            {
                tab.at<float>(i, 0) = matches[i].distance;
            }
            sortIdx(tab, index, SORT_EVERY_COLUMN + SORT_ASCENDING);
            for (int i = 0; i<matches.size(); i++)
            {
                bestMatches.push_back(matches[index.at<int>(i, 0)]);
            }
            Mat result;
            drawMatches(img1, keyImg1, card, keyImg2, bestMatches, result);

            //namedWindow("1", WINDOW_AUTOSIZE);
            //imshow("1", result);

            //cout<<"------------------------------------------------"<<endl;
           // cout<<"keyImg1.size="<<keyImg1.size()<<" keyImg2.size="<<keyImg2.size()<<" bestMatches.size="<<bestMatches.size()<<endl;
            //cout<<"------------------------------------------------"<<endl;

            vector<DMatch>::iterator it;
                       double cumSumDist2=0;
                   for (it = bestMatches.begin(); it != bestMatches.end(); ++it)
                  {

                        Point2d p=keyImg1[it->queryIdx].pt-keyImg2[it->trainIdx].pt;
//
                       cumSumDist2=p.x*p.x+p.y*p.y;
                    }


            if (maxpoint>cumSumDist2)
            {
              maxpoint=cumSumDist2;
                //cout<<num<<" cumSumDist2"<<maxpoint<<endl;
                numcard=num;
                //imwrite("table/1"+to_string(num)+".png",result);
                //break;
            }

        }
    //cout<<num<<endl;
          //waitKey(100);
        num++;
    }
       return numcard;
}

vector <int> matching_card2(vector <Mat> card,vector <Mat> object)
{

    Ptr<Feature2D> b=KAZE::create();

    vector<vector<KeyPoint>> keycard;
    vector<Mat> desccard;

    for (auto img2 : card)
    {
        vector<KeyPoint> keyImg2;
        Mat descImg2;
        b->detectAndCompute(img2, Mat(), keyImg2, descImg2,false);
        keycard.push_back(keyImg2);
        desccard.push_back(descImg2);
    }
    //cout<<"card key"<<keycard.size()<<endl;
    vector<vector<KeyPoint>> keyobject;
    vector<Mat> descobject;

    for (auto img1 : object)
    {
        vector<KeyPoint> keyImg1;
        Mat descImg1;
        b->detectAndCompute(img1, Mat(), keyImg1, descImg1,false);
        keyobject.push_back(keyImg1);
        descobject.push_back(descImg1);
    }
   // cout<<"object key"<<object.size()<<endl;

    vector <int> numcard;

    for (int i=0;i<keycard.size();i++)
    {
        double maxpoint=10000.0;
        int num=0;
        for (int j=0;j<keyobject.size();j++)
        {
            vector<KeyPoint> keyImg2=keycard[i];
            vector<KeyPoint> keyImg1=keyobject[j];
            //cout<<keyImg2.size()<<"--"<<keyImg1.size()<<endl;
            if (keyImg2.size()==keyImg1.size())
            {
                Ptr<DescriptorMatcher> descriptorMatcher;
                vector<DMatch> matches;
                vector<DMatch> bestMatches;
                descriptorMatcher = DescriptorMatcher::create("BruteForce");

                descriptorMatcher->match( descobject[j], desccard[i], matches, Mat());
                Mat index;
                int nbMatch=int(matches.size());
                Mat tab(nbMatch, 1, CV_32F);
                for (int i = 0; i<nbMatch; i++)
                {
                    tab.at<float>(i, 0) = matches[i].distance;
                }
                sortIdx(tab, index, SORT_EVERY_COLUMN + SORT_ASCENDING);
                for (int i = 0; i<matches.size(); i++)
                {
                    bestMatches.push_back(matches[index.at<int>(i, 0)]);
                }

                vector<DMatch>::iterator it;
                double cumSumDist2=0;
                for (it = bestMatches.begin(); it != bestMatches.end(); ++it)
                {
                    Point2d p=keyImg1[it->queryIdx].pt-keyImg2[it->trainIdx].pt;
                    cumSumDist2=p.x*p.x+p.y*p.y;
                }
                //cout<<i<<" cumSumDist2"<<cumSumDist2<<endl;
                if (maxpoint>cumSumDist2)
                {
                    maxpoint=cumSumDist2;
                    num=j;
                }
            }
        }
        //cout<<num<<endl;
        numcard.push_back(num);
    }

       return numcard;
}




