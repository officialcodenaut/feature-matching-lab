#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/features.hpp>
#include <cstdio>
#include <vector>

int main(){
    std::vector<cv::KeyPoint> keypoints;
    cv::Ptr<cv::ORB> orb;
    cv::Mat input = cv::imread("images\\input\\siegestor.jpg");

    if(input.empty()){
        std::printf("Failed to load input image\n");
        return 1;
    }

    std::printf("Columns: %d\nRows: %d\n", input.cols, input.rows);

    orb = cv::ORB::create(10000);
    orb->detect(input, keypoints);

    std::printf("Number of detected keypoints: %zu\n", keypoints.size());

    cv::Mat output;

    cv::drawKeypoints(input, keypoints, output);

    if(!cv::imwrite("images\\output\\01_siegestor_keypoints.jpg", output)){
        std::printf("Failed to save keypoint image\n");
        return 2;
    }
    return 0;
}