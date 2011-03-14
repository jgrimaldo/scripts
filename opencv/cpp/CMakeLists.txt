project(OpenCvUtil)
cmake_minimum_required(VERSION 2.6)

add_executable(extract_bb 
	extract_bb_from_segmentation.cpp     
)

add_executable(imrandom 
	imrandom.cpp     
)

target_link_libraries(extract_bb
	highgui
	cv
	boost_filesystem-mt
)

target_link_libraries(imrandom
	highgui
	cv	
    boost_filesystem-mt
)

