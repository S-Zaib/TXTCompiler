#include "Header.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Image_extract.h"
using namespace std;
using namespace cv;


int main()
{
	/*string expression;
	cout << "Enter Expressffion: ";
	getline(cin, expression);
	string nig = postfixer(expression);
	string nig2 = prefixer(expression);
	cout << "Postfix: " << nig << endl;
	cout << "Prefix: " << nig2 << endl;
	cout << "POST TO INFIX: " << infixer(nig) << endl;
	cout << "PRE TO INFIX: " << infixer(nig2) << endl;*/
	string name = "../TXTCompiler/data/Test_files/Test-", ext = ".txt";
	int file_num = 7;
	file_data files[7];
	for (int i = 0; i < 7; i++)
	{
		files[i].filename = name + char(i + 1 + '0') + ext;
		//cout << files[i].filename << endl;
	}
		parse_file(files[6]);
    /*string img1 = "C:\\Users\\shahz\\Downloads\\A2\\Images\\Img1.png";
    string img2 = "C:\\Users\\shahz\\Downloads\\A2\\Images\\Img2.png";
    obj_detection(img1);
    obj_detection(img2);*/
    return 0;
}