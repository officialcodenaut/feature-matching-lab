# Feature Matching Lab (FML)

A C++ and OpenCV project exploring local feature detection, feature descriptors, and image matching.

## Goal

The goal of this project is to understand how computer vision algorithms detect distinctive points in images, describe their local appearance, and match corresponding features across different views.

The project is developed incrementally through small experiments, with an emphasis on understanding the underlying algorithms and data structures rather than relying entirely on high-level abstractions.

## Implemented Features

- [x] Detect keypoints in images using ORB
- [x] Visualize detected keypoints
- [x] Compute and inspect ORB feature descriptors
- [x] Match descriptors using a brute-force matcher with Hamming distance
- [x] Inspect match distances and basic matching statistics
- [ ] Filter matches by descriptor distance
- [ ] Visualize matches between images
- [ ] Experiment with changes in viewpoint, scale, and lighting

## Technologies

- C++
- OpenCV
- CMake
- Git
- Visual Studio Code

## Project Structure

```text
03-feature-matching-lab/
├── images/
│   ├── input/
│   │   ├── siegestor.jpg
│   │   ├── siegestor2.jpg
│   │   └── ATTRIBUTION.md
│   └── output/
│       ├── 01_siegestor_keypoints_i1.jpg
│       └── 02_siegestor_keypoints_i2.jpg
├── src/
│   └── main.cpp
├── .gitignore
├── CMakeLists.txt
└── README.md
```

- `src/` - C++ source code.
- `images/input/` - source images used in feature detection and matching experiments.
- `images/output/` - generated images visualizing detected keypoints and other experimental results.

## Current Experiments

The current implementation uses two photographs of the Siegestor monument in Munich.

ORB detects keypoints and computes a binary descriptor for each detected feature. The descriptors are then compared using `cv::BFMatcher` with the Hamming distance metric, which is suitable for ORB's binary descriptors.

The program currently reports:

- Number of detected keypoints in each image
- Descriptor matrix dimensions
- Number of matches
- Minimum and maximum match distances
- Number of matches with a zero Hamming distance

These experiments provide a foundation for investigating match quality, filtering unreliable correspondences, and visualizing matches between images.

## Learning Objectives

- Understand local image features and keypoints
- Explore binary feature descriptors and Hamming distance
- Learn how brute-force feature matching works
- Investigate the difference between descriptor similarity and reliable correspondence
- Build computer vision applications in C++ using OpenCV

## Status

Early development. ORB keypoint detection, descriptor extraction, and brute-force descriptor matching are implemented. The next steps are to filter matches and visualize the correspondences between the two images.

## Image Attribution

Input images and their licensing information are documented in [`images/input/ATTRIBUTION.md`](images/input/ATTRIBUTION.md).
