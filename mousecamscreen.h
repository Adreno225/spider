#include <opencv2/opencv.hpp>
#include "opencv2/opencv_modules.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
extern "C" {
  #include <xdo.h>
}

using namespace cv;

class ScreenShot
{
    public:
        Display* display;
        Window root;
        int x,y,width,height;
        XImage* img;

        bool init;
        ScreenShot(int , int , int , int );
        void operator()(Mat &);
        ~ScreenShot();



};

void get_screen (xdo_t *xdo);
void get_camera (xdo_t *xdo);
void transfer_to_mouse(xdo_t *xdo,int x1, int y1,int x2, int y2);
void transfer_to_key(xdo_t *xdo,int x1, int y1,int x2, int y2);
void transfer_key(xdo_t *xdo,int x,int y);
void mouse_left_click(xdo_t *xdo,int x, int y,int repeat);
void key_click(xdo_t *xdo,char *key);
void key_click_down(xdo_t *xdo,char *key);
void key_click_up(xdo_t *xdo,char *key);
void transfer_window(xdo_t *xdo);
