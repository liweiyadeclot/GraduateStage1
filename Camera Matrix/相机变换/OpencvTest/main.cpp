
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void main()
{
	ifstream fin("calibdata.txt");             /* �궨����ͼ���ļ���·�� */
	ofstream fout("caliberation_result.txt");  /* ����궨������ļ� */

	// ��ȡÿһ��ͼ�񣬴�����ȡ���ǵ㣬Ȼ��Խǵ���������ؾ�ȷ��
	int image_count = 0;  /* ͼ������ */
	Size image_size;      /* ͼ��ĳߴ� */
	Size board_size = Size(9, 6);             /* �궨����ÿ�С��еĽǵ��� */
	vector<Point2f> image_points_buf;         /* ����ÿ��ͼ���ϼ�⵽�Ľǵ� */
	vector<vector<Point2f>> image_points_seq; /* �����⵽�����нǵ� */
	string filename;      // ͼƬ��
	vector<string> filenames;

	while (getline(fin, filename))
	{
		++image_count;
		Mat imageInput = imread(filename);
		filenames.push_back(filename);

		// �����һ��ͼƬʱ��ȡͼƬ��С
		if (image_count == 1)
		{
			image_size.width = imageInput.cols;
			image_size.height = imageInput.rows;
		}

		//imshow("Camera Calibration", imageInput);
		/* ��ȡ�ǵ� */
		if (0 == findChessboardCorners(imageInput, board_size, image_points_buf))
		{
			cout << "can not find chessboard corners!\n";  // �Ҳ����ǵ�
			exit(1);
		}
		else
		{
			Mat view_gray;
			cvtColor(imageInput, view_gray, cv::COLOR_BGR2GRAY);  // ת�Ҷ�ͼ

			/* �����ؾ�ȷ�� */
			// image_points_buf ��ʼ�Ľǵ�����������ͬʱ��Ϊ����������λ�õ����
			// Size(5,5) �������ڴ�С
			// ��-1��-1����ʾû������
			// TermCriteria �ǵ�ĵ������̵���ֹ����, ����Ϊ���������ͽǵ㾫�����ߵ����
			cornerSubPix(view_gray, image_points_buf, Size(5, 5), Size(-1, -1), TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.1));

			image_points_seq.push_back(image_points_buf);  // ���������ؽǵ�

			/* ��ͼ������ʾ�ǵ�λ�� */
			drawChessboardCorners(view_gray, board_size, image_points_buf, false); // ������ͼƬ�б�ǽǵ�

			cv::namedWindow("Camera Calibration", cv::WINDOW_NORMAL);  // ����һ���ɵ�����С�Ĵ���
			cv::resizeWindow("Camera Calibration", 1280, 960);  // �������ڴ�СΪ640x480

			imshow("Camera Calibration", view_gray);       // ��ʾͼƬ

			waitKey(500); //��ͣ0.5S      
		}
	}
	int CornerNum = board_size.width * board_size.height;  // ÿ��ͼƬ���ܵĽǵ���

	//-------------������������궨------------------

	/*������ά��Ϣ*/
	Size square_size = Size(10, 10);         /* ʵ�ʲ����õ��ı궨����ÿ�����̸�Ĵ�С */
	vector<vector<Point3f>> object_points;   /* ����궨���Ͻǵ����ά���� */

	/*�������*/
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0));  /* ������ڲ������� */
	vector<int> point_counts;   // ÿ��ͼ���нǵ������
	Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0));       /* �������5������ϵ����k1,k2,p1,p2,k3 */
	vector<Mat> tvecsMat;      /* ÿ��ͼ�����ת���� */
	vector<Mat> rvecsMat;      /* ÿ��ͼ���ƽ������ */

	/* ��ʼ���궨���Ͻǵ����ά���� */
	int i, j, t;
	for (t = 0; t < image_count; t++)
	{
		vector<Point3f> tempPointSet;
		for (i = 0; i < board_size.height; i++)
		{
			for (j = 0; j < board_size.width; j++)
			{
				Point3f realPoint;

				/* ����궨�������������ϵ��z=0��ƽ���� */
				realPoint.x = i * square_size.width;
				realPoint.y = j * square_size.height;
				realPoint.z = 0;
				tempPointSet.push_back(realPoint);
			}
		}
		object_points.push_back(tempPointSet);
	}

	/* ��ʼ��ÿ��ͼ���еĽǵ��������ٶ�ÿ��ͼ���ж����Կ��������ı궨�� */
	for (i = 0; i < image_count; i++)
	{
		point_counts.push_back(board_size.width * board_size.height);
	}

	/* ��ʼ�궨 */
	// object_points ��������ϵ�еĽǵ����ά����
	// image_points_seq ÿһ���ڽǵ��Ӧ��ͼ�������
	// image_size ͼ������سߴ��С
	// cameraMatrix ������ڲξ���
	// distCoeffs ���������ϵ��
	// rvecsMat �������ת����
	// tvecsMat �����λ������
	// 0 �궨ʱ�����õ��㷨
	calibrateCamera(object_points, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, 0);

	//------------------------�궨���------------------------------------

	// -------------------�Ա궨�����������------------------------------

	double total_err = 0.0;         /* ����ͼ���ƽ�������ܺ� */
	double err = 0.0;               /* ÿ��ͼ���ƽ����� */
	vector<Point2f> image_points2;  /* �������¼���õ���ͶӰ�� */
	fout << "ÿ��ͼ��ı궨��\n";

	for (i = 0; i < image_count; i++)
	{
		vector<Point3f> tempPointSet = object_points[i];

		/* ͨ���õ������������������Կռ����ά���������ͶӰ���㣬�õ��µ�ͶӰ�� */
		projectPoints(tempPointSet, rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points2);

		/* �����µ�ͶӰ��;ɵ�ͶӰ��֮������*/
		vector<Point2f> tempImagePoint = image_points_seq[i];
		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
		Mat image_points2Mat = Mat(1, image_points2.size(), CV_32FC2);

		for (int j = 0; j < tempImagePoint.size(); j++)
		{
			image_points2Mat.at<Vec2f>(0, j) = Vec2f(image_points2[j].x, image_points2[j].y);
			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
		}
		err = norm(image_points2Mat, tempImagePointMat, NORM_L2);
		total_err += err /= point_counts[i];
		fout << "��" << i + 1 << "��ͼ���ƽ����" << err << "����" << endl;
	}
	fout << "����ƽ����" << total_err / image_count << "����" << endl << endl;

	//-------------------------�������---------------------------------------------

	//-----------------------���涨����------------------------------------------- 
	Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0));  /* ����ÿ��ͼ�����ת���� */
	fout << "����ڲ�������" << endl;
	fout << cameraMatrix << endl << endl;
	fout << "����ϵ����\n";
	fout << distCoeffs << endl << endl << endl;

	// ��һ��ͼ�����ת����
	cv::Mat R1;
	// ��һ��ͼ���ƽ������
	cv::Mat T1;
	for (int i = 0; i < image_count; i++)
	{
		fout << "��" << i + 1 << "��ͼ�����ת������" << endl;
		fout << tvecsMat[i] << endl;

		/* ����ת����ת��Ϊ���Ӧ����ת���� */
		Rodrigues(tvecsMat[i], rotation_matrix);
		fout << "��" << i + 1 << "��ͼ�����ת����" << endl;
		fout << rotation_matrix << endl;
		fout << "��" << i + 1 << "��ͼ���ƽ��������" << endl;
		fout << rvecsMat[i] << endl << endl;

		if (i != 0)
		{
			fout << "---------------------------------------" << endl;
			cv::Mat RiInvert;
			cv::invert(rotation_matrix, RiInvert);
			cv::Mat RMatFromCurrCameraToFirstCamera = R1 * RiInvert;
			fout << "��" << i + 1 << "������Ե�һ���������ת����" << endl;
			fout << RMatFromCurrCameraToFirstCamera << endl;

			fout << "��" << i + 1 << "������Ե�һ�������ƽ������" << endl;
			fout << rotation_matrix * (rvecsMat[i] - T1) << endl;
			fout << "---------------------------------------" << endl;
		
		}
		else
		{
			// ��¼��һ���������궨��֮��Ĺ�ϵ
			R1 = rotation_matrix;
			T1 = rvecsMat[i];
		}
	}
	fout << endl;

	//--------------------�궨����������-------------------------------

	//----------------------��ʾ������--------------------------------

	Mat mapx = Mat(image_size, CV_32FC1);
	Mat mapy = Mat(image_size, CV_32FC1);
	Mat R = Mat::eye(3, 3, CV_32F);
	string imageFileName;
	std::stringstream StrStm;
	for (int i = 0; i != image_count; i++)
	{
		initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, image_size, CV_32FC1, mapx, mapy);
		Mat imageSource = imread(filenames[i]);
		Mat newimage = imageSource.clone();
		remap(imageSource, newimage, mapx, mapy, INTER_LINEAR);
		StrStm.clear();
		imageFileName.clear();
		StrStm << i + 1;
		StrStm >> imageFileName;
		imageFileName += "_d.jpg";
		imwrite(imageFileName, newimage);
	}

	fin.close();
	fout.close();
	return;
}
