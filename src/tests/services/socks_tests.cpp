#include "tests/services/socks_fixture_test.h"

#include "services/user_services/socks.h"

template <class SocksTest>
class SocksWildcardTest : public SocksTest {
  void SetServerConfig(ssf::config::Config& config) override {
    const char* new_config = R"RAWSTRING(
{
    "ssf": {
        "services" : {
            "stream_listener": { "gateway_ports": true }
        }
    }
}
)RAWSTRING";

    boost::system::error_code ec;
    config.UpdateFromString(new_config, ec);
    ASSERT_EQ(ec.value(), 0) << "Could not update server config from string "
                             << new_config;
  }

  void SetClientConfig(ssf::config::Config& config) override {
    const char* new_config = R"RAWSTRING(
{
    "ssf": {
        "services" : {
            "stream_listener": { "gateway_ports": true }
        }
    }
}
)RAWSTRING";

    boost::system::error_code ec;
    config.UpdateFromString(new_config, ec);
    ASSERT_EQ(ec.value(), 0) << "Could not update client config from string "
                             << new_config;
  }
};

class Socks4Test : public SocksFixtureTest<ssf::services::Socks,
                                           tests::socks::Socks4DummyClient> {
  std::shared_ptr<ServiceTested> ServiceCreateServiceOptions(
      boost::system::error_code& ec) override {
    return ServiceTested::CreateServiceOptions(":9051", ec);
  }
};

class Socks4WildcardTest : public SocksWildcardTest<Socks4Test> {
  std::shared_ptr<typename Socks4Test::ServiceTested>
  ServiceCreateServiceOptions(boost::system::error_code& ec) override {
    return ServiceTested::CreateServiceOptions(":9053", ec);
  }
};

TEST_F(Socks4Test, startStopTransmitSSFSocks) {
  ASSERT_TRUE(Wait());
  Run("9051", "9052");
}

TEST_F(Socks4WildcardTest, startStopTransmitSSFSocks) {
  ASSERT_TRUE(Wait());

  Run("9053", "9054");
}

class Socks5Test : public SocksFixtureTest<ssf::services::Socks,
                                           tests::socks::Socks5DummyClient> {
  std::shared_ptr<ServiceTested> ServiceCreateServiceOptions(
      boost::system::error_code& ec) override {
    return ServiceTested::CreateServiceOptions(":9055", ec);
  }
};

class Socks5WildcardTest : public SocksWildcardTest<Socks5Test> {
  std::shared_ptr<typename Socks5Test::ServiceTested>
  ServiceCreateServiceOptions(boost::system::error_code& ec) override {
    return ServiceTested::CreateServiceOptions(":9057", ec);
  }
};

TEST_F(Socks5Test, startStopTransmitSSFSocks) {
  ASSERT_TRUE(Wait());
  Run("9055", "9056");
}

TEST_F(Socks5WildcardTest, startStopTransmitSSFSocks) {
  ASSERT_TRUE(Wait());

  Run("9057", "9058");
}