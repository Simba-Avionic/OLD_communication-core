#include <gtest/gtest.h>
#include "someip/someip_header.h"

class SomeipHeaderFixture : public testing::TestWithParam<std::tuple<std::uint16_t, std::uint16_t, std::uint32_t, std::uint16_t, std::uint16_t, std::uint8_t, std::uint8_t, std::uint8_t>> {};

TEST_P(SomeipHeaderFixture, HeaderTests) {
    const std::uint16_t service_id = std::get<0>(GetParam());
    const std::uint16_t methode_id = std::get<1>(GetParam());
    const std::uint32_t length = std::get<2>(GetParam());
    const std::uint16_t client_id = std::get<3>(GetParam());
    const std::uint16_t session_id = std::get<4>(GetParam());
    const std::uint8_t interface_ver = std::get<5>(GetParam());
    const std::uint8_t message_type = std::get<6>(GetParam());
    const std::uint8_t return_code = std::get<7>(GetParam());

    simba::com::core::someip::SomeIpHeader header(service_id, methode_id, length, client_id, session_id, interface_ver, message_type, return_code);

    EXPECT_EQ(header.GetServiceID(), service_id);
    EXPECT_EQ(header.GetMethodID(), methode_id);
    EXPECT_EQ(header.GetLength(), length+8);
    EXPECT_EQ(header.GetClientID(), client_id);
    EXPECT_EQ(header.GetSessionID(), session_id);
    EXPECT_EQ(header.GetInterfaceVersion(), interface_ver);
    EXPECT_EQ(header.GetMessageType(), message_type);
    EXPECT_EQ(header.GetReturnCode(), return_code);

    header.SetServiceID(service_id);
    header.SetMethodID(methode_id);
    header.SetLength(length);
    header.SetClientID(client_id);
    header.SetSessionID(session_id);
    header.SetInterfaceVersion(interface_ver); 
    header.SetMessageType(message_type);
    header.SetReturnCode(return_code);

    EXPECT_EQ(header.GetServiceID(), service_id);
    EXPECT_EQ(header.GetMethodID(), methode_id);
    EXPECT_EQ(header.GetLength(), length+8);
    EXPECT_EQ(header.GetClientID(), client_id);
    EXPECT_EQ(header.GetSessionID(), session_id);
    EXPECT_EQ(header.GetInterfaceVersion(), interface_ver);
    EXPECT_EQ(header.GetMessageType(), message_type);
    EXPECT_EQ(header.GetReturnCode(), return_code);
}

INSTANTIATE_TEST_SUITE_P(
    SomeipHeaderTestCases, SomeipHeaderFixture,
    testing::Values(
        std::make_tuple(200, 13, 13, 33, 22, 1, 1, 0),
        std::make_tuple(210, 13, 13, 33, 22, 1, 1, 0)
    )
);
