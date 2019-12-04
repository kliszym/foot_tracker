#include "pch.h"

#include "FootTracker.h"

#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

static std::vector<Point> people_;

static float m_width_;
static float m_height_;

static int error_;

bool imageRead(cv::Mat& image, char* path) {
	image = cv::imread(path, cv::IMREAD_GRAYSCALE);
	if (image.empty()) {
		error_ = FILE_NOT_FOUND;
		return false;
	}
	return true;
}

void keypointsSave(const cv::Mat& image, const std::vector<cv::KeyPoint>& keypoints) {
	m_width_ = (float)image.rows * ((float)image.channels() / 2.f);
	m_height_ = (float)image.cols * ((float)image.channels() / 2.f);

	for (auto keypoint : keypoints) {
		people_.push_back({ keypoint.pt.x, keypoint.pt.y });
	}
}

void peopleFindByFoot(char* path) {
			
	cv::Mat image;
	if (!imageRead(image, path))
		return;

	cv::SimpleBlobDetector::Params params;

	params.filterByArea = true;
	params.minArea = 500;
	params.maxArea = std::numeric_limits<float>::max();

	params.filterByCircularity = true;
	params.minCircularity = 0.81f;
	params.maxCircularity = std::numeric_limits<float>::max();

	params.filterByConvexity = true;
	params.minConvexity = 0.6f;
	params.maxConvexity = std::numeric_limits<float>::max();

	params.filterByInertia = true;
	params.maxInertiaRatio = 0.2f;
	params.maxInertiaRatio = 0.5f;

	cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
	std::vector<cv::KeyPoint> keypoints;
	detector->detect(image, keypoints);
	keypointsSave(image, keypoints);
}

int errorCheck() {
	return error_;
}

int peopleCount() {
	return (int)people_.size();
}

Point peopleCoords(int number) {
	if (number >= peopleCount()) {
		error_ = OUT_OF_BUFFER;
		return { 0, 0 };
	}
	return people_[number];
}

Point peopleCoordsNormalized(int number) {
	Point value = peopleCoordsPixels(number);
	value.x = value.x / m_width_;
	value.y = value.y/ m_height_;
	return value;
}

Point peopleCoordsPixels(int number) {
	Point value = peopleCoords(number);
	value.x = value.x - m_width_;
	value.y = value.y - m_height_;
	return value;
}

Point peopleCoordsMeters(int number) {
	Point value = peopleCoordsNormalized(number);
	value.x = value.x * CAVE_SIZE;
	value.y = value.y * CAVE_SIZE;
	return value;
}

Point peopleCoordsPixelsCorner(int number) {
	Point value = peopleCoords(number);
	return value;
}
