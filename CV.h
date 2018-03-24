using namespace cv;
using namespace std;


class Key
{
    public:
        int x;
        int y;
        float deltax;
        float deltay;
        float persentpoint;
        int numincpoints;

    Key(vector<DMatch> ,vector<KeyPoint> keyImg1,vector<KeyPoint> );
    Key(vector<DMatch> ,vector<KeyPoint> keyImg1,vector<KeyPoint> ,Key );

    void show_rectangle(Mat);
    void print_key();
    bool  overlap_key(vector<Key> );

};


void Serch_point_card(Mat frame,vector <Mat> object,vector<Key> *Keycard);


Key Serch_point_icon (Mat frame,Mat img1);


void serch_test(string nameobject,string nametable);

vector< vector <Point> >  matchig_contours( Mat table);

int matching_card(Mat card,vector <Mat> object);

vector <int> matching_card2(vector <Mat> card,vector <Mat> object);
