#include "Header.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Image_extract.h"
using namespace std;
using namespace cv;


int main()
{
	string expression;
	cout << "Enter Expressffion: ";
	getline(cin, expression);
	string nig = postfixer(expression);
	string nig2 = prefixer(expression);
	cout << "Postfix: " << nig << endl;
	cout << "Prefix: " << nig2 << endl;
	cout << "POST TO INFIX: " << infixer(nig) << endl;
	cout << "PRE TO INFIX: " << infixer(nig2) << endl;
	//string name = "../TXTCompiler/data/Test_files/Test-1.txt";
	//read_file(name);
    string img1 = "C:\\Users\\shahz\\Downloads\\A2\\Images\\Img1.png";
    string img2 = "C:\\Users\\shahz\\Downloads\\A2\\Images\\Img2.png";
    //obj_detection(img1);
    //obj_detection(img2);
    return 0;
}