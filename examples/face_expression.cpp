#include <noos/noos>
#include <iostream>
/*
 * @brief Example which recognises the facial expressions of a person
 */
int main()
{
    using namespace noos::cloud;
    // 
    // The image is loaded from disk.
    // This particular image is of a happy man, so the result should reflect that.
    // 
    auto pic = noos::object::picture("data/object_classes_picture_9.jpg");
    // 
    // In this example we'll pass an inline lambda as the callback.
    // It will receive a vector of pairs, where the `first` is the label (string)
    // and the `second` is the assigned probability (float) for that label
    // 
    auto callback = [&](std::vector<std::pair<std::string,float>> arg) {
        for (const auto & pair : arg) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    };
    //
    // We need to create a platform object with our user and password for using 
    // the NOOS Cloud 
    // IMPORTANT: You have to change your user and password. The example doesn't work
    //
    platform node = {"demo.noos.cloud", "9001", "your_pass", "your_user"};
    
    // 
    // We make a callable object using `face_expression` as the template parameter
    // and construct the callable data in one go. This connection won't be kept alive (false)
    // @see noos::cloud::face_expression
    // 
    callable<face_expression,false> query(callback, node, pic);
    query.send();
    return 0;
}
