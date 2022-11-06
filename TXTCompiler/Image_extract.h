#pragma once
#include "Queue_Stack.h"
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

bool obj_exist(float**& imgARR, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (imgARR[i][j] == 255)
				return true;
	return false;
}

int obj_detection(string name, bool show_img = true)
{
	Mat actual_image = imread(name, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
	const int rows = actual_image.rows, cols = actual_image.cols;
	Queue<int> q;
	string obj_num = name + "_obj_", ext = ".png", obj_name;
	float** imgARR = new float* [rows];
	for (int i = 0; i < rows; i++)
	{
		imgARR[i] = new float[cols];
		for (int j = 0; j < cols; j++)
			imgARR[i][j] = (actual_image.at<Vec3b>(i, j)[0] + actual_image.at<Vec3b>(i, j)[1] + actual_image.at<Vec3b>(i, j)[2]) / 3;
	}
	int obj_count = 0;
	while (obj_exist(imgARR, rows, cols))
	{
		float** imgARR2 = new float* [rows];
		for (int i = 0; i < rows; i++)
			imgARR2[i] = new float[cols] {0};
		int start_x = 0, start_y = 0;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (imgARR[i][j] == 255)
				{
					start_x = i;
					start_y = j;
					i = rows;
					j = cols;
					break;
				}
		q.enqueue(start_x);
		q.enqueue(start_y);
		while (!q.isEmpty())
		{
			int x = q.dequeue(), y = q.dequeue();
			if (imgARR[x][y] == 255)
			{
				imgARR[x][y] = 0;
				imgARR2[x][y] = 255;
				if (x + 1 < rows)
				{
					if (imgARR[x + 1][y] == 255)
					{
						q.enqueue(x + 1);
						q.enqueue(y);
					}
				}
				if (y + 1 < cols)
				{
					if (imgARR[x][y + 1] == 255)
					{
						q.enqueue(x);
						q.enqueue(y + 1);
					}
				}
				if (x - 1 >= 0)
				{
					if (imgARR[x - 1][y] == 255)
					{
						q.enqueue(x - 1);
						q.enqueue(y);
					}
				}
				if (y - 1 >= 0)
				{
					if (imgARR[x][y - 1] == 255)
					{
						q.enqueue(x);
						q.enqueue(y - 1);
					}
				}
				if (x + 1 < rows && y + 1 < cols)
				{
					if (imgARR[x + 1][y + 1] == 255)
					{
						q.enqueue(x + 1);
						q.enqueue(y + 1);
					}
				}
				if (x + 1 < rows && y - 1 >= 0)
				{
					if (imgARR[x + 1][y - 1] == 255)
					{
						q.enqueue(x + 1);
						q.enqueue(y - 1);
					}
				}
				if (x - 1 >= 0 && y + 1 < cols)
				{
					if (imgARR[x - 1][y + 1] == 255)
					{
						q.enqueue(x - 1);
						q.enqueue(y + 1);
					}
				}
				if (x - 1 >= 0 && y - 1 >= 0)
				{
					if (imgARR[x - 1][y - 1] == 255)
					{
						q.enqueue(x - 1);
						q.enqueue(y - 1);
					}
				}
			}
		}
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (imgARR[i][j])
				{
					actual_image.at<Vec3b>(i, j)[0] = 255;
					actual_image.at<Vec3b>(i, j)[1] = 255;
					actual_image.at<Vec3b>(i, j)[2] = 255;

				}
				else
				{
					actual_image.at<Vec3b>(i, j)[0] = 0;
					actual_image.at<Vec3b>(i, j)[1] = 0;
					actual_image.at<Vec3b>(i, j)[2] = 0;
				}
		if(show_img)
			imshow("OG IMAGE", actual_image);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (imgARR2[i][j])
				{
					actual_image.at<Vec3b>(i, j)[0] = 255;
					actual_image.at<Vec3b>(i, j)[1] = 255;
					actual_image.at<Vec3b>(i, j)[2] = 255;

				}
				else
				{
					actual_image.at<Vec3b>(i, j)[0] = 0;
					actual_image.at<Vec3b>(i, j)[1] = 0;
					actual_image.at<Vec3b>(i, j)[2] = 0;
				}
		if (show_img)
			imshow("OBJ IMAGE", actual_image);
		waitKey(0);
		cout << "Object " << ++obj_count << endl;
		obj_name = obj_num + char(obj_count + '0') + ext;
		cout << "Object Name:" << obj_name<< endl;
		imwrite(obj_name, actual_image);
	}
	cout << "Done!" << endl;
	return obj_count;
}