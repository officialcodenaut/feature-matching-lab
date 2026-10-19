#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdio>
#include <vector>

int main(){
    std::vector<cv::KeyPoint> keypoints_i1;
    std::vector<cv::KeyPoint> keypoints_i2;
    std::vector<std::vector<cv::DMatch>> matches;
    cv::Ptr<cv::ORB> orb;
    cv::Ptr<cv::BFMatcher> bfm;
    cv::Mat input1 = cv::imread("images\\input\\siegestor.jpg");
    cv::Mat input2 = cv::imread("images\\input\\siegestor2.jpg");
    cv::Mat descriptors_i1;
    cv::Mat descriptors_i2;

    if(input1.empty()){
        std::printf("Failed to load input1 image\n");
        return 1;
    }

    if(input2.empty()){
        std::printf("Failed to load input2 image\n");
        return 2;
    }

    std::printf("INPUT1: Columns: %d Rows: %d\n", input1.cols, input1.rows);
    std::printf("INPUT2: Columns: %d Rows: %d\n", input2.cols, input2.rows);

    orb = cv::ORB::create(10000);
    
    orb->detectAndCompute(input1, cv::noArray(), keypoints_i1, descriptors_i1, false);
    orb->detectAndCompute(input2, cv::noArray(), keypoints_i2, descriptors_i2, false);

    std::printf("Number of detected keypoints_i1: %zu\n", keypoints_i1.size());
    std::printf("Number of detected keypoints_i2: %zu\n", keypoints_i2.size());

    cv::Mat output_i1;
    cv::Mat output_i2;

    cv::drawKeypoints(input1, keypoints_i1, output_i1);
    cv::drawKeypoints(input2, keypoints_i2, output_i2);

    if(!cv::imwrite("images\\output\\01_siegestor_keypoints_i1.jpg", output_i1)){
        std::printf("Failed to save keypoint_1 image\n");
        return 3;
    }

    if(!cv::imwrite("images\\output\\02_siegestor_keypoints_i2.jpg", output_i2)){
        std::printf("Failed to save keypoint_2 image\n");
        return 4;
    }

    std::printf("Matrix 'descriptors_i1':\nColumns: %d\nRows: %d\n", descriptors_i1.cols, descriptors_i1.rows);
    std::printf("Matrix 'descriptors_i2':\nColumns: %d\nRows: %d\n", descriptors_i2.cols, descriptors_i2.rows);

    bfm = cv::BFMatcher::create(cv::NORM_HAMMING);
    bfm->knnMatch(descriptors_i1, descriptors_i2, matches, 2);

    std::printf("Number of matches: %zu\n", matches.size());

    cv::Mat output_matches;

    std::vector<cv::DMatch> filtered_matches;
    float ratio_threshold = 0.75f;

    for(const auto& candidates : matches){
        if(candidates.size() < 2){
            continue;
        }

        if(candidates[0].distance < ratio_threshold * candidates[1].distance){
            filtered_matches.push_back(candidates[0]);
        }
    }
    cv::drawMatches(input1, keypoints_i1, input2, keypoints_i2, filtered_matches, output_matches);
    std::printf("Matches after ratio test: %zu\n", filtered_matches.size());

    if(!cv::imwrite("images\\output\\07_siegestor_matches_ratio.jpg", output_matches)){
        std::printf("Failed to save matches image\n");
        return 5;
    }

    std::vector<cv::Point2f> points1;
    std::vector<cv::Point2f> points2;

    for(int i = 0; i < filtered_matches.size(); i++){
        points1.push_back(keypoints_i1[filtered_matches[i].queryIdx].pt);
        points2.push_back(keypoints_i2[filtered_matches[i].trainIdx].pt);
    }

    cv::Mat inlier_mask;

    cv::Mat homography = cv::findHomography(points1, points2, cv::RANSAC, 3.0, inlier_mask);

    int inlier_count = cv::countNonZero(inlier_mask);

    std::printf("Inliers after RANSAC: %d\n", inlier_count);

    std::vector<cv::DMatch> inlier_matches;
    cv::Mat flat_mask = inlier_mask.reshape(1, 1);

    for(int i = 0; i < filtered_matches.size(); i++){
        if(flat_mask.at<uchar>(0, i) != 0){
            inlier_matches.push_back(filtered_matches[i]);
        }
    }

    cv::drawMatches(input1, keypoints_i1, input2, keypoints_i2, inlier_matches, output_matches);

    if(!cv::imwrite("images\\output\\11_siegestor_matches_RANSAC_3.jpg", output_matches)){
        std::printf("Failed to save RANSAC image\n");
        return 6;
    }

    return 0;
}
