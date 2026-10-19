# Feature Matching Lab (FML)

**Feature Matching Lab (FML)** is a C++ and OpenCV project exploring local feature detection, binary descriptors, image matching, and geometric verification.

The project focuses on practical experiments designed to develop a deeper understanding of computer vision algorithms, their underlying mathematics, and their behavior on real images.

## Overview

FML investigates how distinctive visual features can be detected in two images, matched across different viewpoints, and filtered according to geometric consistency.

The project uses two photographs of the Siegestor monument in Munich to explore the following pipeline:

**ORB -> Descriptor Matching -> Lowe's Ratio Test -> Homography Estimation -> RANSAC**

## Project Status

The original scope of FML is complete. The project implements a feature-matching pipeline using ORB, binary descriptor matching, Lowe's ratio test, homography estimation, and RANSAC-based geometric verification.

Additional experiments explored the effects of RANSAC reprojection thresholds and the limitations of projecting an entire image between different viewpoints. The results and observations are documented in the repository.

Further algorithm comparisons and more advanced experiments are outside the scope of this version.

## Implementation

### Feature Detection and Description

The project uses ORB (Oriented FAST and Rotated BRIEF) to detect keypoints and compute binary descriptors in both images.

Detected keypoints are visualized, while descriptor matrix dimensions and keypoint counts are reported for inspection.

### Descriptor Matching

Descriptors are compared using `cv::BFMatcher` with `cv::NORM_HAMMING`, a distance metric appropriate for ORB's binary descriptors.

K-nearest-neighbor matching retrieves the two nearest candidates for each query descriptor. Lowe's ratio test, configured with a threshold of `0.75`, filters out ambiguous correspondences.

### Geometric Verification

The surviving correspondences are used to estimate a homography with `cv::findHomography()` and RANSAC.

RANSAC identifies inliers that are consistent with the estimated projective transformation. The resulting inlier mask is used to filter the matches and visualize the geometrically consistent correspondences.

Experiments with different reprojection thresholds demonstrate how parameter selection affects the number of accepted inliers and the resulting visualization.

A larger inlier count does not necessarily imply a better geometric model. The spatial distribution of matches and the plausibility of the estimated transformation also matter. A homography that fits selected correspondences well does not necessarily provide a reliable projection of the entire image.

## Experimental Results

The repository contains visualizations from different stages of the matching pipeline.

| Output | Description |
|---|---|
| `01_siegestor_keypoints_i1.jpg` | ORB keypoints detected in the first image |
| `02_siegestor_keypoints_i2.jpg` | ORB keypoints detected in the second image |
| `03_siegestor_matches_all_found.jpg` | Initial descriptor-match visualization |
| `04_siegestor_matches_filter40.jpg` | Matches filtered using a distance threshold of 40 |
| `05_siegestor_matches_filter30.jpg` | Matches filtered using a distance threshold of 30 |
| `06_siegestor_matches_filter50.jpg` | Matches filtered using a distance threshold of 50 |
| `07_siegestor_matches_ratio.jpg` | Matches retained by Lowe's ratio test |
| `08_siegestor_matches_RANSAC.jpg` | Matches filtered using RANSAC |
| `09_siegestor_matches_RANSAC_0_5.jpg` | RANSAC results with a 0.5-pixel reprojection threshold |
| `10_siegestor_matches_RANSAC_1.jpg` | RANSAC results with a 1.0-pixel reprojection threshold |
| `11_siegestor_matches_RANSAC_3.jpg` | RANSAC results with a 3.0-pixel reprojection threshold |

The output images document the evolution of the experiment, from initial descriptor matching to geometric verification. They also illustrate how the selected parameters affect the resulting correspondences.

## Project Structure

```text
feature-matching-lab/
├── images/
│   ├── input/
│   │   ├── ATTRIBUTION.md
│   │   ├── siegestor.jpg
│   │   └── siegestor2.jpg
│   └── output/
│       ├── 01_siegestor_keypoints_i1.jpg
│       ├── 02_siegestor_keypoints_i2.jpg
│       ├── 03_siegestor_matches_all_found.jpg
│       ├── 04_siegestor_matches_filter40.jpg
│       ├── 05_siegestor_matches_filter30.jpg
│       ├── 06_siegestor_matches_filter50.jpg
│       ├── 07_siegestor_matches_ratio.jpg
│       ├── 08_siegestor_matches_RANSAC.jpg
│       ├── 09_siegestor_matches_RANSAC_0_5.jpg
│       ├── 10_siegestor_matches_RANSAC_1.jpg
│       └── 11_siegestor_matches_RANSAC_3.jpg
├── src/
│   └── main.cpp
├── .gitignore
├── CMakeLists.txt
└── README.md
```

- `src/` contains the C++ implementation.
- `images/input/` contains the source images and their attribution information.
- `images/output/` contains visualizations generated during the experiments.
- `CMakeLists.txt` defines the build configuration.
- `.gitignore` excludes generated build files and other local artifacts from version control.

## Technologies

- **C++** - implementation language
- **OpenCV** - feature detection, descriptor matching, and geometric estimation
- **CMake** - build configuration
- **Git and GitHub** - version control and project documentation
- **Visual Studio Code** - development environment

## Learning Focus

FML explores several core computer vision concepts:

- Local features and keypoint detection
- Binary descriptors and Hamming distance
- Brute-force and k-nearest-neighbor matching
- Ambiguous correspondences and Lowe's ratio test
- Homography estimation and projective transformations
- RANSAC, inlier selection, and reprojection thresholds
- The difference between descriptor similarity and geometric consistency
- The limitations of estimating geometric transformations from real image correspondences

## Image Attribution

Sources and licensing information for the input images are documented in [`images/input/ATTRIBUTION.md`](images/input/ATTRIBUTION.md).