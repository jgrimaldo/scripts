#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

#include <boost/filesystem.hpp>

#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace fs = boost::filesystem;

cv::Mat2i toMatrix(const std::vector<cv::Point>& points)
{
	cv::Mat2i m((int)points.size(), 1);

	for (unsigned int i = 0; i < points.size(); ++i)
	{
		m[i][0][0] = points[i].x;
		m[i][0][1] = points[i].y;
	}

	return m;
}

inline void contour_draw(
		const std::vector<cv::Point>& c,
		cv::Mat& im,
		cv::Scalar color = CV_RGB(255, 0, 0),
		int thickness = -1)
{
	std::vector< std::vector<cv::Point> > tmp_points;
	tmp_points.push_back(c);

	cv::drawContours(
			im, // Where I will draw
			tmp_points, // What I will draw
			-1, // Index  (-1 for all)
			CV_RGB(255, 0, 0),
			thickness,
			CV_AA
		);
}

int main(int argc, char * argv[])
{
  assert(argc > 1);

  bool interactive = false;

  for (int i = 1; i < argc; ++i)
  {
	std::string arg(argv[i]);

	if (arg == "--interactive")
	{
		cv::namedWindow("default", 0);
		interactive = true;
	}
	else if (fs::exists(argv[i]))
    {
    	const int flag_grayscale = 0;
    	cv::Mat1b im = cv::imread(argv[i], flag_grayscale);
    	cv::Mat1b im_clone = im.clone();

    	std::vector< std::vector<cv::Point> > contours;

    	cv::findContours
    	(
			im_clone, // input gray-scale image
			contours,  // contours will be transferred here
			CV_RETR_EXTERNAL, // only external contours
			CV_CHAIN_APPROX_TC89_KCOS // approximate redudant points
    	);

    	if (contours.size() == 0)
    	{
    		std::cout << "No contours found" << std::endl;
    		return EXIT_FAILURE;
    	}


    	std::map<double, std::vector<cv::Point> *, std::greater<double> > area_map;

    	for (int i = 0; i < contours.size(); i++)
    	{
    		area_map[cv::contourArea(toMatrix(contours[i]))] = &contours[i];
    	}

    	std::vector<cv::Point>& best_contour = *area_map.begin()->second;

		cv::Rect rect = cv::boundingRect(toMatrix(best_contour));
		cv::rectangle(im, rect, CV_RGB(255, 255, 255), 1);

		std::cout << fs::complete(arg) << " "
				  << rect.x      << " "
				  << rect.y      << " "
				  << rect.width  << " "
				  << rect.height << std::endl;

		if (interactive)
		{
			cv::imshow("default", im);
			cv::waitKey(0);
		}
    }
  }  

  return EXIT_SUCCESS;
}
