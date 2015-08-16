#ifndef RAPP_CLOUD_SETDENOISEPROFILE
#define RAPP_CLOUD_SETDENOISEPROFILE
#include "Includes.ihh"
namespace rapp {
namespace cloud {
/**
 * @class setDenoiseProfile
 * @brief 
 * @version 1
 * @date 15-August-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class setDenoiseProfile : public rapp::services::asio_service_http
{
public:

    /**
     * This class does not return something, it only captures an error
     */
    setDenoiseProfile (
                         const std::shared_ptr<audio> file,
                         const std::string user
                      )
    : rapp::services::asio_service_http ()
    {
                assert( file );

        // Create a new random boundary
        std::string boundary = randomBoundary();
        
        // --boundary
        // Content-Disposition: form-data; name="user"
        //
        // alex
        // --boundary

        // Create the name for the audio file - TODORandomize file name instead of 'audio.wav'
        post_ = "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"filename\"\r\n\r\n";
        post_ += "audio.wav\r\n";
        
        // Create the Multi-form POST field
        //      (wav) audio/x-wav; audio/wav
        //      (wav) audio/vnd.wave; codec=123 - when we know the codec
        
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"file_uri\"; filename=\"audio.wav\"\r\n";
        post_ += "Content-Type: audio/wav\r\n";
        post_ += "Content-Transfer-Encoding: binary\r\n\r\n";
        
        // Append binary data
        auto imagebytes = audio->bytearray();
        post_.insert( post_.end(), imagebytes.begin(), imagebytes.end() );
        post_ += "\r\n";
        post_ += "--" + boundary + "--";
        
        // Count Data size
        auto size = post_.size() * sizeof( std::string::value_type );
        
        // Form the Header
        header_ =  "POST /hop/speech_detection_sphinx4 HTTP/1.1\r\n";
        header_ += "Host: " + std::string( rapp::cloud::address ) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( size ) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        
        // bind the base class callback, to our handle_reply
        callback_ = std::bind ( &setDenoiseProfile::handle_reply, this, std::placeholders::_1 );
    }

private:

    void handle_reply ( boost::asio::streambuf & buffer )
    {
        std::string json ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
        std::stringstream ss ( json );
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json( ss, tree );

            // Check for error response from api.rapp.cloud
            for ( auto child : tree.get_child( "error" ) )
            {
                const std::string value = child.second.get_value<std::string>();
                if ( !value.empty() )
                    std::cerr << "setDenoiseProfile error: " << value << std::endl;
            }
        }
        catch( boost::property_tree::json_parser::json_parser_error & je )
        {
            std::cerr << "setDenoiseProfile::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
    }

    
};
}
}
