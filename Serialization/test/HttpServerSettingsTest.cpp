#include "HttpServerSettings.hpp"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/test/unit_test.hpp>

namespace fs = std::filesystem;

namespace
{
struct SHttpServerSettingsV1
{
    std::string host;
    uint16_t port;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& BOOST_SERIALIZATION_NVP(host);
        ar& BOOST_SERIALIZATION_NVP(port);
    }
};

struct SHttpServerSettingsV2
{
    std::string host;
    uint16_t port;
    uint32_t max_connections;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& BOOST_SERIALIZATION_NVP(host);
        ar& BOOST_SERIALIZATION_NVP(port);
        ar& BOOST_SERIALIZATION_NVP(max_connections);
    }
};

struct SHttpServerSettingsV3
{
    std::string host;
    uint16_t port;
    uint32_t max_connections;
    uint32_t timeout_ms;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& BOOST_SERIALIZATION_NVP(host);
        ar& BOOST_SERIALIZATION_NVP(port);
        ar& BOOST_SERIALIZATION_NVP(max_connections);
        ar& BOOST_SERIALIZATION_NVP(timeout_ms);
    }
};
} // namespace

BOOST_CLASS_VERSION(SHttpServerSettingsV1, 1)
BOOST_CLASS_VERSION(SHttpServerSettingsV2, 2)
BOOST_CLASS_VERSION(SHttpServerSettingsV3, 3)

BOOST_AUTO_TEST_SUITE(HttpServerSettingsTestSuite)

BOOST_AUTO_TEST_CASE(SaveAndLoadXmlRoundTrip)
{
    const fs::path temp_file = fs::temp_directory_path() / "http_server_settings_v4_test.xml";
    fs::remove(temp_file);

    SHttpServerSettings expected{};
    expected.host = "192.168.1.10";
    expected.port = 8443;
    expected.max_connections = 500;
    expected.timeout_ms = 10000;
    expected.enable_ssl = true;
    expected.allowed_origins = {"https://example.com", "https://admin.example.com"};

    SaveToXml(expected, temp_file.string());
    const SHttpServerSettings actual = LoadFromXml(temp_file.string());

    BOOST_CHECK(actual == expected);
    fs::remove(temp_file);
}

BOOST_AUTO_TEST_CASE(MigrateFromV1ToV4)
{
    const fs::path temp_file = fs::temp_directory_path() / "http_server_settings_v1_test.xml";
    fs::remove(temp_file);

    {
        SHttpServerSettingsV1 v1{"10.0.0.5", 9090};
        std::ofstream ofs(temp_file);
        boost::archive::xml_oarchive oa(ofs);
        const SHttpServerSettingsV1& settings = v1;
        oa& BOOST_SERIALIZATION_NVP(settings);
    }

    const SHttpServerSettings migrated = LoadFromXml(temp_file.string());
    BOOST_CHECK_EQUAL(migrated.host, "10.0.0.5");
    BOOST_CHECK_EQUAL(migrated.port, 9090);
    BOOST_CHECK_EQUAL(migrated.max_connections, 100u);
    BOOST_CHECK_EQUAL(migrated.timeout_ms, 5000u);
    BOOST_CHECK(!migrated.enable_ssl);
    BOOST_CHECK(migrated.allowed_origins.empty());

    fs::remove(temp_file);
}

BOOST_AUTO_TEST_CASE(MigrateFromV2ToV4)
{
    const fs::path temp_file = fs::temp_directory_path() / "http_server_settings_v2_test.xml";
    fs::remove(temp_file);

    {
        SHttpServerSettingsV2 v2{"10.0.0.6", 9091, 250};
        std::ofstream ofs(temp_file);
        boost::archive::xml_oarchive oa(ofs);
        const SHttpServerSettingsV2& settings = v2;
        oa& BOOST_SERIALIZATION_NVP(settings);
    }

    const SHttpServerSettings migrated = LoadFromXml(temp_file.string());
    BOOST_CHECK_EQUAL(migrated.host, "10.0.0.6");
    BOOST_CHECK_EQUAL(migrated.port, 9091);
    BOOST_CHECK_EQUAL(migrated.max_connections, 250u);
    BOOST_CHECK_EQUAL(migrated.timeout_ms, 5000u);
    BOOST_CHECK(!migrated.enable_ssl);
    BOOST_CHECK(migrated.allowed_origins.empty());

    fs::remove(temp_file);
}

BOOST_AUTO_TEST_CASE(MigrateFromV3ToV4)
{
    const fs::path temp_file = fs::temp_directory_path() / "http_server_settings_v3_test.xml";
    fs::remove(temp_file);

    {
        SHttpServerSettingsV3 v3{"10.0.0.7", 9092, 400, 7500};
        std::ofstream ofs(temp_file);
        boost::archive::xml_oarchive oa(ofs);
        const SHttpServerSettingsV3& settings = v3;
        oa& BOOST_SERIALIZATION_NVP(settings);
    }

    const SHttpServerSettings migrated = LoadFromXml(temp_file.string());
    BOOST_CHECK_EQUAL(migrated.host, "10.0.0.7");
    BOOST_CHECK_EQUAL(migrated.port, 9092);
    BOOST_CHECK_EQUAL(migrated.max_connections, 400u);
    BOOST_CHECK_EQUAL(migrated.timeout_ms, 7500u);
    BOOST_CHECK(!migrated.enable_ssl);
    BOOST_CHECK(migrated.allowed_origins.empty());

    fs::remove(temp_file);
}

BOOST_AUTO_TEST_SUITE_END()