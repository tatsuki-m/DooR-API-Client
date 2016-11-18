#include "unix_client.h"

int
main() {
    //  include configure valiable
    auto config = cpptoml::parse_file("config.toml");


    UnixClient client = UnixClient();
    client.run();


    return 0;
}
