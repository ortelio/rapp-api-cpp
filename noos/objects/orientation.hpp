#ifndef NOOS_OBJECT_ORIENTATION
#define NOOS_OBJECT_ORIENTATION
#include "includes.ihh"
/*
 * LICENSE HERE
 */
namespace noos {
namespace object {
/**
 * @struct orientation
 * @brief Encapsulate euler angles (roll, pitch, yaw)
 * @version 0.7.3
 * @date 12.07.2017
 */
template <class value_type>
struct orientation
{
    /// Roll angle in radians
	value_type roll = 0;
    /// Pitch angle in radians
    value_type pitch = 0;
    /// Yaw angle in radians
    value_type yaw = 0;

    /// @brief Default constructor
    orientation() = default;

    /// @brief Constructor taking roll, pitch and yaw (in radians)
    orientation(value_type roll,
                value_type pitch,
                value_type yaw);

    /// @brief Construct using library "json for modern c++"
    orientation(const json::const_iterator & it);
   
    /// @brief Converts the data to a json format
    /// @return a JSON object
    json::object_t to_json() const;
   
    /// @brief Equality operator
    bool operator==(const noos::object::orientation<value_type> & rhs) const;
};
#include "orientation.tpl"
}
}
#endif
