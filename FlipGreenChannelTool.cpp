#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
const std::string flipStr = "-GFLIP";

bool isFileExists(const std::string &name) {
    std::ifstream f(name.c_str());
    return f.good();
}

int handle(const char *ch) {
    const std::string imagePath = ch;
    std::string suffix = imagePath;
    std::string newImagePrefix = imagePath;
    std::string newImagePath;

    std::cout << "Input: " << imagePath << std::endl;

    for (int i = imagePath.size() - 1; i > 0; --i) {
        if (imagePath[i] == '.') {
            newImagePrefix = imagePath.substr(0, i);
            suffix = imagePath.substr(i + 1);
            break;
        }
    }
    if (suffix == imagePath) {
        std::cout << "Cannot find a dot in " << imagePath << std::endl;
        suffix = "";
    }
    newImagePath = suffix == "" ? newImagePrefix + flipStr
                                : newImagePrefix + flipStr + "." + suffix;
    if (isFileExists(newImagePath)) {
        std::cout << newImagePath << " already exists." << std::endl;
        system("pause");
        return 3;
    }
    bool containsflipStr = true;
    for (size_t i = 0; i < flipStr.size(); ++i) {
        if (newImagePrefix[newImagePrefix.size() - 1 - i] !=
            flipStr[flipStr.size() - 1 - i]) {
            containsflipStr = false;
            break;
        }
    }
    if (containsflipStr) {
        newImagePath = suffix == ""
                           ? newImagePrefix.substr(
                                 0, newImagePrefix.size() - flipStr.size())
                           : newImagePrefix.substr(
                                 0, newImagePrefix.size() - flipStr.size()) +
                                 "." + suffix;
        if (isFileExists(newImagePath)) {
            std::cout << newImagePath << " already exists." << std::endl;
            system("pause");
            return 3;
        }
    }

    transform(suffix.begin(), suffix.end(), suffix.begin(), tolower);
    Mat image = imread(imagePath, IMREAD_UNCHANGED);
    if (image.empty()) {
        std::cout << "Cannot read " << imagePath << std::endl;
        system("pause");
        return 1;
    }
    // std::cout << image.size << endl;
    // std::cout << image.depth() << endl;
    // std::cout << image.channels() << endl;
    if (image.channels() < 3) {
        std::cout << imagePath << " has less than 3 channels." << std::endl;
        system("pause");
        return 2;
    } else if (image.channels() == 3) {
        switch (image.depth()) {
        case CV_16F:
        case CV_32F: {
            auto it_beg = image.begin<Vec3f>();
            const auto it_end = image.end<Vec3f>();
            for (; it_beg != it_end; ++it_beg) {
                (*it_beg)[1] = 1.0 - (*it_beg)[1];
            }
            break;
        }
        case CV_8U: {
            auto it_beg = image.begin<Vec3b>();
            const auto it_end = image.end<Vec3b>();
            for (; it_beg != it_end; ++it_beg) {
                (*it_beg)[1] = 255 - (*it_beg)[1];
            }
            break;
        }
        default: {
            std::cout << imagePath << " has unknown image type."
                      << std::endl;
            system("pause");
            break;
        }
        }
    } else if (image.channels() == 4) {
        switch (image.depth()) {
        case CV_16F:
        case CV_32F: {
            auto it_beg = image.begin<Vec4f>();
            const auto it_end = image.end<Vec4f>();
            for (; it_beg != it_end; ++it_beg) {
                (*it_beg)[1] = 1.0 - (*it_beg)[1];
            }
            break;
        }
        case CV_8U: {
            auto it_beg = image.begin<Vec4b>();
            const auto it_end = image.end<Vec4b>();
            for (; it_beg != it_end; ++it_beg) {
                (*it_beg)[1] = 255 - (*it_beg)[1];
            }
            break;
        }
        default: {
            std::cout << imagePath << " has unknown image type."
                      << std::endl;
            system("pause");
            break;
        }
        }
    } else {
        std::cout << imagePath << " has morn than 4 channels." << std::endl;
        system("pause");
        return 3;
    }
    std::vector<int> param;
    switch (image.depth()) {
    case CV_16F: {
        param = {IMWRITE_EXR_TYPE, IMWRITE_EXR_TYPE_HALF};
        break;
    }
    case CV_32F: {
        param = {IMWRITE_EXR_TYPE, IMWRITE_EXR_TYPE_FLOAT};
        break;
    }
    case CV_8U: {
        if (suffix == "png") {
            param = {IMWRITE_PNG_COMPRESSION, 1};
        } else if (suffix == "jpg" || suffix == "jpeg") {
            param = {IMWRITE_JPEG_QUALITY, 95};
        }
        break;
    }
    }
    imwrite(newImagePath, image, param);
    std::cout << "Complete." << std::endl;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Please input image files." << std::endl;
        return 0;
    }
    _putenv("OPENCV_IO_ENABLE_OPENEXR=1");
    for (size_t i = 1; i < argc; ++i) {
        handle(argv[i]);
    }
    return 0;
}
