#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

struct SHttpServerSettings
{
    std::string host{"0.0.0.0"};
    uint16_t port{8080};
    uint32_t max_connections{100};
    uint32_t timeout_ms{5000};
    bool enable_ssl{false};
    std::vector<std::string> allowed_origins{};

    bool operator==(const SHttpServerSettings& other) const
    {
        return host == other.host &&
               port == other.port &&
               max_connections == other.max_connections &&
               timeout_ms == other.timeout_ms &&
               enable_ssl == other.enable_ssl &&
               allowed_origins == other.allowed_origins;
    }

private:
    friend class boost::serialization::access;

    template <class Archive>
    void save(Archive& ar, const unsigned int version) const;

    template <class Archive>
    void load(Archive& ar, const unsigned int version);

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

BOOST_CLASS_VERSION(SHttpServerSettings, 4)

void SaveToXml(const SHttpServerSettings& settings, const std::string& path);
SHttpServerSettings LoadFromXml(const std::string& path);