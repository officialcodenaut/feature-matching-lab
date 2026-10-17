#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/features.hpp>
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

    std::printf("Columns: %d\nRows: %d\n", input1.cols, input1.rows);

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

    // for(int i = 0; i < 10; i++){
    //     std::printf("Match %d: distance: %f queryIdx: %d trainIdx: %d\n", i, matches[i].distance, matches[i].queryIdx, matches[i].trainIdx);
    // }

    // float minDistance = matches[0].distance;
    // float maxDistance = matches[0].distance;
    // int zeroCount = 0;

    // for(int i = 0; i < matches.size(); i++){

    //     if(matches[i].distance < minDistance){
    //         minDistance = matches[i].distance;
    //     }

    //     else if(matches[i].distance > maxDistance){
    //         maxDistance = matches[i].distance;
    //     }

    //     if(matches[i].distance == 0){
    //         zeroCount++;
    //     }
    // }

    // std::printf("minDistance: %f, maxDistance: %f, zeroCount: %d\n", minDistance, maxDistance, zeroCount);

    cv::Mat output_matches;

    //cv::drawMatches(input1, keypoints_i1, input2, keypoints_i2, matches, output_matches);

    // if(!cv::imwrite("images\\output\\03_siegestor_matches.jpg", output_matches)){
    //     std::printf("Failed to save matches image\n");
    //     return 4;
    // }

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

    return 0;
}