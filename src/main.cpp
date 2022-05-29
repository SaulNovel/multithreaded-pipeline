#include "Image.h"
#include "Pipeline.h"

#include <iostream>
#include <sstream>

namespace
{

void logger(const std::string& message) {
    std::ostringstream out;
    out << message << " -> thread '" << std::this_thread::get_id() << "'\n";
    std::cout << out.str();
}

}

Image getImageFromDevice() {
    static int counter = 0;
    const std::string name = "Image_" + std::to_string(++counter);
    const std::string message = " > Loading image '" + name + "' from input device\n";
    std::cout << message;
    
    return Image(name);
}

Image applyTransform0(Image& image) {
    //logger(__PRETTY_FUNCTION__);

    std::this_thread::sleep_for(std::chrono::microseconds(30));

    return Image(image.getName() + "_transform0");
}

Image applyTransform1(Image& image) {
    //logger(__PRETTY_FUNCTION__);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return Image(image.getName() + "_transform1");
}

Image applyTransform2(Image& image) {
    //logger(__PRETTY_FUNCTION__);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    return Image(image.getName() + "_transform2");
}

Image applyTransform3(Image& image) {
    //logger(__PRETTY_FUNCTION__);

    std::this_thread::sleep_for(std::chrono::microseconds(100));

    return Image(image.getName() + "_transform3");
}

void outputImageToDevice(const Image& image) {
    const std::string message = " < Image '" + image.getName() + "' loaded in ouput device\n";
    std::cout << message;
}


void processImages(int number_of_images) {

    Pipeline<Image> pipe;

    for (int i=0; i<number_of_images; i++) {
        pipe.addStage(getImageFromDevice);
    }
    pipe.addStage(applyTransform0);
    pipe.addStage(applyTransform1);
    pipe.addStage(applyTransform2);
    pipe.addStage(applyTransform3);
    pipe.addStage(outputImageToDevice);

    pipe.run(); 
}

int main() {
    int number_of_images = 5;
    processImages(number_of_images);

    return 0;
}