#include "speech_recognition.hpp"
namespace rapp {
namespace cloud {

const std::string speech_recognition_google::google_speech_post__ = "POST /hop/speech_detection_google HTTP/1.1\r\n";
const std::string speech_recognition_sphinx4::sphinx4_speech_post__ = "POST /hop/speech_detection_sphinx4 HTTP/1.1\r\n";
const std::string set_noise_profile::noise_post__ = "POST /hop/set_noise_profile HTTP/1.1\r\n"; 

speech_recognition_google::speech_recognition_google(
                                                      const std::vector<rapp::types::byte> audio_bytearray,
                                                      const rapp::types::audio_source audio_src,
                                                      const std::string language,
                                                      std::function<void(std::vector<std::string>, 
                                                                         std::vector<std::vector<std::string>>)> callback
                                                    )
: http_request(google_speech_post__), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string audio_type;
    std::string audio_format;
    switch(audio_src) {
        case 0: 
            audio_type = "nao_ogg";
            audio_format = "ogg";
            break;
        case 1:
            audio_type = "nao_wav_1_ch";
            audio_format = "wav";
            break;
        case 2:
            audio_type = "nao_wav_4_ch";
            audio_format = "wav";
            break;
        case 3:
            audio_type = "headset";
            audio_format = "wav";
            break;
        default:
            std::cerr << "Error: not the correct audio source" <<std::endl;
    }

    json json_doc = {{"audio_source", audio_type},
                     {"language", language}};
    http_request::add_content("json", json_doc.dump(-1), true);
    std::string fname = rapp::misc::random_boundary() + "." + audio_format;
    http_request::add_content("file", fname, audio_bytearray);
    http_request::close();
}

void speech_recognition_google::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        delegate_(json_f["words"], json_f["alternatives"]);
    }
}

speech_recognition_sphinx4::speech_recognition_sphinx4(
                                                        const std::vector<rapp::types::byte> audio_bytearray,
                                                        const rapp::types::audio_source audio_src,
                                                        const std::string language,
                                                        const std::vector<std::string> grammar,
                                                        const std::vector<std::string> words,
                                                        const std::vector<std::string> sentences,
                                                        std::function<void(std::vector<std::string> words)> callback
                                                      )
: http_request(sphinx4_speech_post__), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string audio_type;
    std::string audio_format;
    switch(audio_src) {
        case 0: 
            audio_type = "nao_ogg";
            audio_format = "ogg";
            break;
        case 1:
            audio_type = "nao_wav_1_ch";
            audio_format = "wav";
            break;
        case 2:
            audio_type = "nao_wav_4_ch";
            audio_format = "wav";
            break;
        case 3:
            audio_type = "headset";
            audio_format = "wav";
            break;
        default:
            std::cerr << "Error: not the correct audio source" <<std::endl;
    }
    json json_doc = {{"language", language},
                     {"audio_source", audio_type},
                     {"words", words},
                     {"sentences", sentences},
                     {"grammar", grammar}};
    http_request::add_content("json", json_doc.dump(-1), true);
    std::string fname = rapp::misc::random_boundary() + "." + audio_format;
    http_request::add_content("file", fname, audio_bytearray);
    http_request::close();
}

void speech_recognition_sphinx4::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        delegate_(json_f["words"]);
    }
}

set_noise_profile::set_noise_profile(
                                       const std::vector<rapp::types::byte> audio_bytearray,
                                       const rapp::types::audio_source audio_src
                                    )
: http_request(noise_post__) 
{
    http_request::make_multipart_form();
    std::string audio_type;
    std::string audio_format;
    switch(audio_src) {
        case 0: 
            audio_type = "nao_ogg";
            audio_format = "ogg";
            break;
        case 1:
            audio_type = "nao_wav_1_ch";
            audio_format = "wav";
            break;
        case 2:
            audio_type = "nao_wav_4_ch";
            audio_format = "wav";
            break;
        case 3:
            audio_type = "headset";
            audio_format = "wav";
            break;
        default:
            std::cerr << "Error: not the correct audio source" <<std::endl;
    }
    json json_doc = {{"audio_source", audio_type}};
    http_request::add_content("json", json_doc.dump(-1), true);
    std::string fname = rapp::misc::random_boundary() + "." + audio_format;
    http_request::add_content("file", fname, audio_bytearray);
    http_request::close();
}

void set_noise_profile::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        std::cout << "Noise_profile created" << std::endl;
    }
}

}
}
