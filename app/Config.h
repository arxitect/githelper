#ifndef GIT_HELPER_CONFIG_H
#define GIT_HELPER_CONFIG_Hs

#include <string>

namespace App {

class Config {
private:
    explicit Config() = default;
    static Config* config;
public:
    Config(Config &) = delete;
    void operator=(const Config &) = delete;

    static Config* getInstance() ;
    void loadStyles() const;
};

}
#endif //GIT_HELPER_CONFIG_H
