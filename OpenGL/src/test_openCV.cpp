#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat image = cv::imread("test.jpg");

    if (image.empty()) {
        std::cout << "エラー: 画像を開けませんでした。" << std::endl;
        std::cin.get();
        return -1;
    }

    std::cout << "成功！ OpenCVは正しく設定されています。" << std::endl;
    std::cout << "画像サイズ: " << image.cols << " x " << image.rows << std::endl;

    // 結果が見えるようにキー入力を待つ
    std::cin.get();
    return 0;
}
