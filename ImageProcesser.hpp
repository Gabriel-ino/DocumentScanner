#ifndef IMAGEPROCESSER_HPP
#define IMAGEPROCESSER_HPP

#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>


typedef std::vector<cv::Point> points;

namespace ImageProcesser{

    class ImageProcesser{

        public:
            ImageProcesser(){};
            const void preprocessing(cv::Mat &img, cv::Mat &imgGray, cv::Mat &imgBlur, cv::Mat &imgCanny, cv::Mat &imgDil, cv::Mat &imgErode);
            const std::vector<cv::Point> getContours(cv::Mat &img);
            const void getWarp(cv::Mat &img, cv::Mat &imgWarp, points &mPoints, const float &width, const float &height);

    };

    class Drawner{
        public:
            Drawner(){};

            inline void drawPoints(cv::Mat &img, points &m_points, const cv::Scalar &color){for (auto &i : m_points) {cv::circle(img, i, img.size().width / 30, color, cv::FILLED, cv::LINE_4);}};
            inline void putText(cv::Mat &img, points &m_points, const cv::Scalar &color){for (std::size_t i{}; i < m_points.size(); ++i) {cv::putText(img, std::to_string(i), m_points[i], cv::FONT_HERSHEY_PLAIN, 4, color, 4);}};


    };

}


#endif


