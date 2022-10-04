#include "ImageProcesser.hpp"

#include <memory>
#include <algorithm>


cv::Mat img, imgGray, imgThre, imgCanny, imgBlur, imgDil, imgErode, imgWarp, rawImg, imgCrop;
points initialPoints, docPoints;

const points reorder(points &mPoints){
    points newPoints;
    std::vector<int> sumPoints, subPoints;

    for (auto &i:mPoints){
        sumPoints.push_back(i.x + i.y);
        subPoints.push_back(i.x - i.y);
    }

    newPoints.push_back(mPoints[std::min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
	newPoints.push_back(mPoints[std::max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //1
	newPoints.push_back(mPoints[std::min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2
	newPoints.push_back(mPoints[std::max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3

    return newPoints;

}


int main(){
    const float width = 420;
    const float height = 596;
    const int cropValue = 5;
    auto imageprocesser = std::make_unique<ImageProcesser::ImageProcesser>();
    auto imagedrawner = std::make_unique<ImageProcesser::Drawner>();

    img = cv::imread("paper.jpg");
    cv::resize(img, img, cv::Size(), 0.5, 0.5);
    rawImg = img.clone();

    imageprocesser->preprocessing(img, imgGray, imgBlur, imgCanny, imgDil, imgErode);
    points m_points = imageprocesser->getContours(imgDil);
    points reorderedPoints = reorder(m_points);

    std::cout << "Points: " << m_points << '\n'; 

    imagedrawner->drawPoints(img, reorderedPoints, cv::Scalar(255,127,0));
    imagedrawner->putText(img, reorderedPoints, cv::Scalar(0,0,0));

    imageprocesser->getWarp(rawImg, imgWarp, reorderedPoints, width, height);

    cv::Rect roi(cropValue, cropValue, width-(2*cropValue), height-(2*cropValue));

    imgCrop = imgWarp(roi);

    cv::imwrite("Scanned_Document.png", imgCrop);


    return 0;
}

