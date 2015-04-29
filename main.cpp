#include "function.h"

//argc: arguments number
//argv: folder,reference, source 
int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Usage: " << endl;
		cout << "GlobalTransfer.exe folder reference source " << endl;
	}

	string folder = argv[1];             // ../../colorcorrection_data/art
	string refIm  = argv[2];             // view1.png
	string srcIm  = argv[3];             // view5E2.png

	string refImFn = folder + "/" + refIm ;
	string srcImFn = folder + "/" + srcIm ;

	cout << "reference: " << refImFn << endl;
	cout << "source: " << srcImFn << endl;

	Mat refImg = imread(refImFn);
	if (refImg.data == NULL)
	{
		cout << "failed to open reference " << refImFn << endl;
		return -1;
	}
	Mat srcImg = imread(srcImFn);
	if (srcImg.data == NULL)
	{
		cout << "failed to open source " << srcImFn << endl;
		return -1;
	}

	
	Mat new_srcImg; //RGB
	GlobalColorTransfer(refImg, srcImg, new_srcImg);

	string outImFn = folder + "/GL_" + argv[3] ;
	imwrite(outImFn, new_srcImg);

	cout << "correct source: " <<  outImFn << endl;

	return 1;
}