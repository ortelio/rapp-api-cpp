#include <noos/noos>
#include <iostream>
#include <chrono>
/*
 * \brief Example to do 2D mapping with laser data
 */
/// \brief function to read a json file and it is converted 
//  into a string param
std::string read_json_file(const std::string file)
{
    if (file.empty()){
        throw std::runtime_error("empty file param");
    }
    std::ifstream t(file);
    if (t.good()) {
	std::stringstream buffer;
	buffer << t.rdbuf();
	t.close();
	return buffer.str();
    }
    else {
        throw std::runtime_error("failed to open ifsteam");
    }
}

int main()
{
    using namespace noos::cloud;
    
    /*
     * First, the laser data is filled to allow do the mapping
     * For more information \see noos::object::laser
     */
    std::string string = read_json_file("data/cloud_class_laser_data.json");
    auto json = nlohmann::json::parse(string);
    std::vector<float> laser_ranges = json["ranges"];
    std::vector<int> laser_intensities = json["intensities"];
    noos::object::laser laser;
    laser.ranges = laser_ranges;
    laser.intensities = laser_intensities;
    laser.aperture = 4.71239; //270 degrees
    laser.max_range = 10.0f;
    laser.std_error = 0.02;
    laser.right_to_left = true;
    laser.timestamp = 0;
    laser.pose3d = noos::object::pose<float>(); 

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of noos::object::qr_code and
     * we show the size of the vector to know how many qr_codes have 
     * been found.
     */
    auto icp_request = icp_slam(laser);
    auto callback = [&](noos::object::pose<float> pose3d) {
        std::cout << pose3d;
    };

    /*
     * We make a callable object of qr_recognition class to detect qr_codes in the file
     * and we send the information to the platform.
     * For more information \see noos::cloud::qr_recognition
     */
    callable<icp_slam,true> cb(icp_request, callback);
    for (auto i = 0; i < 1500; i++) {
        cb.send();
        std::cout << i << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}