#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <string.h>
#include <vector>
extern "C" {
  #include <xdo.h>
}

#include "mousecamscreen.h"



using namespace cv;
using namespace std;


ScreenShot::ScreenShot(int x, int y, int width, int height)
{
        this->x=x;
        this->y=y;
        this->width=width;
        this->height=height;
        display = XOpenDisplay(nullptr);
        root = DefaultRootWindow(display);

        init = true;
}

void ScreenShot::operator() (Mat& cvImg)
    {

        if(init == true)
            init = false;
        else
            XDestroyImage(img);

        img = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);

        cvImg = Mat(height, width, CV_8UC4, img->data);
    }

ScreenShot::~ScreenShot()
    {
        if(init == false)
            XDestroyImage(img);

        XCloseDisplay(display);
    }


void get_screen (xdo_t *xdo)
{

    ScreenShot screen(0,0,1920,1080);

    Mat img_deck;
    screen(img_deck);
    imwrite("table/img_screen.png", img_deck);

}

void get_camera ()
{

    Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    //cap.open(0);

    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID + apiID);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,1920);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,1080);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
    }


    cap.read(frame);
        // check if we succeeded
    if (frame.empty()) {
        cerr << "ERROR! blank frame grabbed\n";
    }
    imwrite("table/img_camera.png", frame);
}

void transfer_to_mouse(xdo_t *xdo,int x1, int y1,int x2, int y2)
{

    xdo_move_mouse(xdo, x1, y1, 0);
    xdo_mouse_down(xdo, CURRENTWINDOW, Button1);
    xdo_move_mouse(xdo, x2, y2, 0);
    xdo_mouse_up(xdo, CURRENTWINDOW, Button1);

}

void transfer_to_key(xdo_t *xdo,int x1, int y1,int x2, int y2)
{
    int time=50;
    key_click(xdo,"Right");
    waitKey(time);
    key_click(xdo,"Escape");
    waitKey(time);
    key_click(xdo,"Right");
    waitKey(time);
    for (int i=0;i<=x1;i++)
    {
        key_click(xdo,"Right");
        waitKey(time);
    }
    key_click(xdo,"Down");
    waitKey(time);
    for (int i=0;i<y1;i++)
    {
        key_click(xdo,"Down");
        waitKey(time);
    }
    waitKey(time);
    key_click(xdo,"space");
    waitKey(time);

    if (x1<x2)
        for (int i=x1;i<x2;i++)
        {
            key_click(xdo,"Right");
            waitKey(time);
        }
    else
        for (int i=x1;i>x2;i--)
        {
            key_click(xdo,"Left");
            waitKey(time);
        }
    key_click(xdo,"Down");
    for (int i=0;i<y2;i++)
        {
            key_click(xdo,"Down");
            waitKey(time);
        }
    waitKey(time);
    key_click(xdo,"space");
    waitKey(time);
    key_click(xdo,"Escape");
    waitKey(time);
}

void transfer_window(xdo_t *xdo)
{
    key_click_down(xdo,"Alt");
    waitKey(100);
    key_click(xdo,"Tab");
    waitKey(100);
    key_click(xdo,"Tab");
    waitKey(100);
    key_click(xdo,"Tab");
    waitKey(100);
    key_click_up(xdo,"Alt");
}

void transfer_key(xdo_t *xdo,int x, int y)
{
    key_click(xdo,"Right");
    waitKey(100);
    key_click(xdo,"Escape");
    waitKey(100);
    for (int i=0;i<=x;i++)
    {
        key_click(xdo,"Right");
        waitKey(100);
    }
    key_click(xdo,"Down");
    for (int i=1;i<y;i++)
    {
        key_click(xdo,"Down");
        waitKey(100);
    }
}

void mouse_left_click(xdo_t *xdo,int x, int y,int repeat)
{
    xdo_move_mouse(xdo, x, y, 0);
    xdo_click_window_multiple(xdo, CURRENTWINDOW, Button1, repeat, 0);
}


void key_click(xdo_t *xdo,char *key)
{

    xdo_send_keysequence_window(xdo, CURRENTWINDOW, key, 1000);
}


void key_click_down(xdo_t *xdo,char *key)
{

    xdo_send_keysequence_window_down(xdo, CURRENTWINDOW, key, 0);
}

void key_click_up(xdo_t *xdo,char *key)
{
    xdo_send_keysequence_window_up(xdo, CURRENTWINDOW, key, 0);
}
