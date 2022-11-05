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
	//file_data F, F1, F2, F3, F4, F5;
	//F.filename = "../TXTCompiler/data/Test_files/Test-1.txt";
	//F.priorty = 34;
	//F1.filename = "../TXTCompiler/data/Test_files/Test-2.txt";
	//F1.priorty = 5434;
	//F2.filename = "../TXTCompiler/data/Test_files/Test-3.txt";
	//F2.priorty = 234;
	//F3.filename = "../TXTCompiler/data/Test_files/Test-4.txt";
	//F3.priorty = 232134;
	//F4.filename = "../TXTCompiler/data/Test_files/Test-5.txt";
	//F4.priorty = 14;
	//F5.filename = "../TXTCompiler/data/Test_files/Test-6.txt";
	//F5.priorty = 114;
	//LRU lru(4);
	//lru.add(F);
	//lru.add(F1);
	//lru.add(F2);
	//lru.add(F3);
	//lru.add(F4);
	//lru.add(F5);
	//lru.add(F3);
	//lru.print();
		string name = "../TXTCompiler/data/Test_files/Test-", ext = ".txt";
	int file_num = 7;
	file_data files[7], temp;
	for (int i = 0; i < 7; i++)
	{
		files[i].filename = name + char(i + 1 + '0') + ext;
		files[i].priorty = parse_file(files[i]).priorty;	
	}
	//parse_file(files[5]);
    /*string img1 = "C:\\Users\\shahz\\Downloads\\A2\\Images\\Img1.png";
    string img2 = "C:\\Users\\shahz\\Downloads\\A2\\Images\\Img2.png";
    obj_detection(img1);
    obj_detection(img2);*/
    return 0;
}


