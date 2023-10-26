#include <gtest/gtest.h>
#include "someip/factory/someip_header_factory.h"
#include "someip/message_code.h"

class GeneratingHeaderFixture : public testing::TestWithParam<std::tuple<std::uint16_t, std::uint16_t, simba::com::core::data::MessageCode>> {};

TEST_P(GeneratingHeaderFixture, HeaderTesting) {
    const std::uint16_t service_id = std::get<0>(GetParam());
    const std::uint16_t methode_id = std::get<1>(GetParam());
    simba::com::core::data::MessageCode res_flag =  std::get<2>(GetParam());

    simba::com::core::someip::factory::SomeIpHeaderFactory headerFactory;

    EXPECT_EQ(headerFactory.CreateEvent(service_id, methode_id)->GetServiceID(), service_id);
    EXPECT_EQ(headerFactory.CreateEvent(service_id, methode_id)->GetMethodID(), methode_id);

    EXPECT_EQ(headerFactory.CreateRequest(service_id, methode_id)->GetServiceID(), service_id);
    EXPECT_EQ(headerFactory.CreateRequest(service_id, methode_id)->GetMethodID(), methode_id);

    EXPECT_EQ(headerFactory.CreateResponse(service_id, methode_id, res_flag)->GetServiceID(), service_id);
    EXPECT_EQ(headerFactory.CreateResponse(service_id, methode_id, res_flag)->GetMethodID(), methode_id);
    EXPECT_EQ(headerFactory.CreateResponse(service_id, methode_id, res_flag)->GetReturnCode(), res_flag);
}

INSTANTIATE_TEST_SUITE_P(
    GeneratingHeaderTestCases, GeneratingHeaderFixture,
    testing::Values(
        std::make_tuple(22, 11, simba::com::core::data::MessageCode::kEOk),
        std::make_tuple(11111111, 1, simba::com::core::data::MessageCode::kENotOk),
        std::make_tuple(-22, 11, simba::com::core::data::MessageCode::kEWrongProtocolVersion),
        std::make_tuple(22, -11, simba::com::core::data::MessageCode::kEMalformedMessage),
        std::make_tuple(22, 1111111111111111111, simba::com::core::data::MessageCode::kENotReachable)
    )
);
