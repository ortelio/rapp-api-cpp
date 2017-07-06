#include <noos/noos>
#include <iostream>
/*
 * \brief Example to detect qr in a file
 */
int main()
{
    using namespace noos::cloud;
    
    /*
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */    
    auto pic = noos::object::picture("data/asio_classes_qr_code_1.png");

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of noos::object::qr_code and
     * we show the size of the vector to know how many qr_codes have 
     * been found.
     */
    auto qr_request = qr_recognition(pic);
    auto callback = [&](std::vector<noos::object::qr_code> codes) {
        std::cout << "Found " << codes.size() << " QR codes" << std::endl;
        for (const auto code : codes) {
            std::cout << code.message << std::endl;
        }
    };

    /*
     * We make a call to qr_code_detection class to detect qr_codes in the file
     * For more information \see noos::cloud::qr_detection
     */
    callable<qr_recognition,false> cb(qr_request, callback);
    cb.send();

    return 0;
} 
