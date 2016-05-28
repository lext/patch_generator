#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
int main(int argc, char** argv) {
    if (argc != 6) {
        std::cout << "Specify the filename, patch width, patch height, stride and the output folder!" << std::endl;
        return -1;
    }

    cv::Mat im = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    std::cout << argv[1] << std::endl;
    if(!im.data) 
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    int patch_width = atoi(argv[2]);
    int patch_height = atoi(argv[3]);
    int stride = atoi(argv[4]);

    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    for(int i = 0; i < im.rows; i += stride) {
        for (int j = 0; j < im.cols; j+= stride) {
            if((i+patch_height > im.rows) || (j +patch_width > im.cols))
                continue;

            cv::Mat patch;
            cv::Rect roi(j, i, patch_width, patch_height);
            im(roi).copyTo(patch);

            std::ostringstream stm;

            stm << argv[5] << "/" << i << "_" << j << "_" << patch_width << "_" << patch_height;
            std::string fname = stm.str()+".png";
            std::cout << fname << std::endl;
            imwrite(fname, patch, compression_params);
        }
    }
    
    return 0;
}
