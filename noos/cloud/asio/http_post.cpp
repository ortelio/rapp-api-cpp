#include "http_post.hpp"
namespace noos {
namespace cloud {

http_post::http_post(std::string boundary)
: boundary_(boundary)
{}

void http_post::add_content(
                            const std::string name, 
                            const std::string content,
                            bool newline
                           )
{
	if (name.empty() || content.empty()) {
		throw std::runtime_error("empty param(s)");
	}
	data_ += "--" + boundary_ + "\r\n";
	data_ += "Content-Disposition: form-data; name=\"" + name + "\"\r\n\r\n";
	data_ += content;  
	if (newline) {
		data_ += "\r\n";
	}
}

void http_post::add_content(
                            const std::string name,
                            const std::string filename,
                            const std::vector<noos::types::byte> bytes
                           )
{
	if (name.empty() || filename.empty() || bytes.size() == 0) {
		throw std::runtime_error("empty param(s)");
	}
	data_ += "--" + boundary_ + "\r\n";
	data_ += "Content-Disposition: form-data; name=\"" + name + "\"\r\n";
	data_ += "Content-Type: application/octet-stream\r\n\r\n";
	data_.insert(data_.end(), bytes.begin(), bytes.end());
	data_ += "\r\n";
}

void http_post::end()
{
	if (open_) {
		open_ = false;
  	    data_ += "--" + boundary_ + "--\r\n";
	}
}

std::string http_post::to_string() const
{
    if (!data_.empty()) {
        return data_;
    }
    else {
        return "";
    }
}

unsigned int http_post::size() const
{
    if (!data_.empty()) {
        return data_.size() * sizeof(std::string::value_type);
    }
    else {
        return 0;
    }
}

}
}
