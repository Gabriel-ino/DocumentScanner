#include "ImageProcesser.hpp"

const void ImageProcesser::ImageProcesser::preprocessing(cv::Mat &img, cv::Mat &imgGray, cv::Mat &imgBlur, cv::Mat &imgCanny, cv::Mat &imgDil, cv::Mat &imgErode){
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3,3), 3, 0);
    cv::Canny(imgBlur, imgCanny, 25, 75);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    cv::dilate(imgCanny, imgDil, kernel);
    cv::erode(imgDil, imgErode, kernel);

}


const points ImageProcesser::ImageProcesser::getContours(cv::Mat &img){
    std::vector<points> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<points> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    points biggest;

    int maxArea{0};

    cv::Point myPoint;

    for (std::size_t i{}; i < contours.size(); ++i){
        int area = cv::contourArea(contours[i]);
        std::cout << area << '\n';

        std::string objectType;

        if (area > 1000){
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);


            if (area > maxArea && conPoly[i].size()==4){
                //cv::drawContours(img, conPoly, i, cv::Scalar(255, 255, 0), 2);
                biggest = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;

            }

            cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 0, 255), 5);
            
        }
    }

    return biggest;

}


const void ImageProcesser::ImageProcesser::getWarp(cv::Mat &img, cv::Mat &imgWarp, points &mPoints, const float &width, const float &height){
    cv::Point2f src[4] = {mPoints[0], mPoints[1], mPoints[2], mPoints[3]};
    cv::Point2f dst[4] = {{0.0f, 0.0f}, {width, 0.0f}, {0.0f, height}, {width, height}};
    cv::Mat matrix = cv::getPerspectiveTransform(src, dst);

    cv::warpPerspective(img, imgWarp, matrix, cv::Point(width, height));
}

