#include "HttpServerSettings.hpp"
#include <iostream>

int main()
{
    SHttpServerSettings cfg;
    cfg.host = "192.168.1.10";
    cfg.port = 8443;
    cfg.max_connections = 500;
    cfg.timeout_ms = 10000;

    const std::string xml_file = "http_server_settings.xml";
    SaveToXml(cfg, xml_file);
    SHttpServerSettings loaded = LoadFromXml(xml_file);

    std::cout << "Loaded: host=" << loaded.host
              << ", port=" << loaded.port
              << ", max_connections=" << loaded.max_connections
              << ", timeout_ms=" << loaded.timeout_ms << std::endl;
    return 0;
}