/*
 * imrandom.cpp
 *
 *  Created on: Mar 13, 2011
 *      Author: grimaldo
 */
#include <cassert>
#include <iostream>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		std::cout << "Usage: imrandom {width} {height} {filename}" << std::endl;
		return EXIT_FAILURE;
	}

	int w = boost::lexical_cast<int>(argv[1]);
	int h = boost::lexical_cast<int>(argv[2]);
	fs::path filename(argv[3]);

	if (fs::exists(filename))
	{
		std::cout << "Cannot create "
				  << "'" << filename.string() << "'"
				  << std::endl;
		return EXIT_FAILURE;
	}

	cv::Mat3b im(w, h);

	srand( time(NULL) );

	for (int i = 0; i < w; ++i )
	{
		for (int j = 0; j < h; j++)
		{
			im[i][j][0] = rand();
			im[i][j][1] = rand();
			im[i][j][2] = rand();
		}
	}

	cv::imwrite(filename.string(), im);

	return 0;
}
