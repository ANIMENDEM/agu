#include "HttpServerSettings.hpp"

#include <fstream>
#include <stdexcept>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

template <class Archive>
void SHttpServerSettings::save(Archive& ar, const unsigned int /*version*/) const
{
    ar& BOOST_SERIALIZATION_NVP(host);
    ar& BOOST_SERIALIZATION_NVP(port);
    ar& BOOST_SERIALIZATION_NVP(max_connections);
    ar& BOOST_SERIALIZATION_NVP(timeout_ms);
    ar& BOOST_SERIALIZATION_NVP(enable_ssl);
    ar& BOOST_SERIALIZATION_NVP(allowed_origins);
}

template <class Archive>
void SHttpServerSettings::load(Archive& ar, const unsigned int version)
{
    if (version == 1)
    {
        ar& BOOST_SERIALIZATION_NVP(host);
        ar& BOOST_SERIALIZATION_NVP(port);
        max_connections = 100;
        timeout_ms = 5000;
        enable_ssl = false;
        allowed_origins.clear();
    }
    else if (version == 2)
    {
        ar& BOOST_SERIALIZATION_NVP(host);
        ar& BOOST_SERIALIZATION_NVP(port);
        ar& BOOST_SERIALIZATION_NVP(max_connections);
        timeout_ms = 5000;
        enable_ssl = false;
        allowed_origins.clear();
    }
    else if (version == 3)
    {
        ar& BOOST_SERIALIZATION_NVP(host);
        ar& BOOST_SERIALIZATION_NVP(port);
        ar& BOOST_SERIALIZATION_NVP(max_connections);
        ar& BOOST_SERIALIZATION_NVP(timeout_ms);
        enable_ssl = false;
        allowed_origins.clear();
    }
    else if (version >= 4)
    {
        ar& BOOST_SERIALIZATION_NVP(host);
        ar& BOOST_SERIALIZATION_NVP(port);
        ar& BOOST_SERIALIZATION_NVP(max_connections);
        ar& BOOST_SERIALIZATION_NVP(timeout_ms);
        ar& BOOST_SERIALIZATION_NVP(enable_ssl);
        ar& BOOST_SERIALIZATION_NVP(allowed_origins);
    }
    else
    {
        throw std::runtime_error("Unsupported SHttpServerSettings archive version");
    }
}

template void SHttpServerSettings::save<boost::archive::xml_oarchive>(
    boost::archive::xml_oarchive&, const unsigned int) const;
template void SHttpServerSettings::load<boost::archive::xml_iarchive>(
    boost::archive::xml_iarchive&, const unsigned int);

void SaveToXml(const SHttpServerSettings& settings, const std::string& path)
{
    std::ofstream ofs(path);
    if (!ofs.is_open())
    {
        throw std::runtime_error("Failed to open file for writing: " + path);
    }
    boost::archive::xml_oarchive oa(ofs);
    oa& BOOST_SERIALIZATION_NVP(settings);
}

SHttpServerSettings LoadFromXml(const std::string& path)
{
    std::ifstream ifs(path);
    if (!ifs.is_open())
    {
        throw std::runtime_error("Failed to open file for reading: " + path);
    }
    SHttpServerSettings settings{};
    boost::archive::xml_iarchive ia(ifs);
    ia& BOOST_SERIALIZATION_NVP(settings);
    return settings;
}