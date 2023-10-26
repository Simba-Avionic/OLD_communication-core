#include <gtest/gtest.h>
#include <iostream>
#include <cstdint>
#include <iomanip>
#include "someip/factory/someip_message_factory.h"
#include "someip/factory/someip_header_factory.h"

class GeneratingMessageFixture : public testing::TestWithParam<std::tuple<std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t, std::vector<std::uint8_t>>> {};

TEST_P(GeneratingMessageFixture, UsingHeaderFactoryTest) {
    simba::com::core::someip::factory::SomeIpMessageFactory messageFactory;
    simba::com::core::someip::factory::SomeIpHeaderFactory headerFactory;

    const std::uint16_t service_id = std::get<0>(GetParam());
    const std::uint16_t event_id = std::get<1>(GetParam());
    const std::uint16_t client_id = std::get<2>(GetParam());
    const std::uint16_t transfer_id = std::get<3>(GetParam());
    std::vector<std::uint8_t> payload = std::get<4>(GetParam());

    std::shared_ptr<simba::com::core::someip::SomeIpHeader> header = headerFactory.CreateEvent(service_id, event_id);

    std::vector<std::uint8_t> message = messageFactory.GetBuffor(header, client_id, transfer_id, payload);

    EXPECT_EQ(messageFactory.GetHeader(message)->GetServiceID(), service_id);
    EXPECT_EQ(messageFactory.GetHeader(message)->GetClientID(), client_id); 
    EXPECT_EQ(messageFactory.GetPayload(message), payload);
}

INSTANTIATE_TEST_SUITE_P(
    GeneratingMessageTestCases, GeneratingMessageFixture,
    testing::Values(
        std::make_tuple(1, 26, 3, 5534, std::vector<std::uint8_t>{0x48, 0x65, 0x6C, 0x6C, 0x6F}),
        std::make_tuple(2222, 2, 3, 4, std::vector<std::uint8_t>{0x53, 0x69, 0x65, 0x6D, 0x61, }),
        std::make_tuple(2, 2, 2, 5555552, std::vector<std::uint8_t>{0x73, 0x69, 0x6D, 0x62, 0x61, 0x20, 0x6A, 0x65, 0x73, 0x74, 0x20, 0x73, 0x70, 0x6F, 0x6B,0x6F})
    )
);

class RawDataFixture : public testing::TestWithParam<std::tuple<std::vector<std::uint8_t>>> {};

TEST_P(RawDataFixture, UsingRawDataTest) {
    simba::com::core::someip::factory::SomeIpMessageFactory messageFactory;

    std::vector<std::uint8_t> data = std::get<0>(GetParam());
    std::vector<std::uint8_t> payload(data.begin() + 16, data.end());

    EXPECT_EQ(messageFactory.GetHeader(data)->GetServiceID(), data[1]);
    EXPECT_EQ(messageFactory.GetHeader(data)->GetClientID(), data[9]); 
    EXPECT_EQ(messageFactory.GetPayload(data), payload);
}

INSTANTIATE_TEST_SUITE_P(
    RawDataTestCases, RawDataFixture,
    testing::Values(
        std::make_tuple(std::vector<std::uint8_t>{0, 1, 0, 2, 0, 0, 0, 13, 0, 3, 0 , 1, 1, 1, 2, 0, 'H', 'e', 'l', 'l', 'o'}),
        std::make_tuple(std::vector<std::uint8_t>{0, 200, 0, 13, 0, 0, 0, 19, 0, 55, 0 , 34, 1, 1, 2, 4, 'H', 'e', 'l', 'l', 'o', ' ', 'S', 'i', 'm', 'b', 'a'})
    )
);
