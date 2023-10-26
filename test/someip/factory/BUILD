
cc_test(
    name = "someip_factory_test",
    srcs = [
        "someip_header_factory_test.cc", 
        "someip_message_factory_test.cc", 
        ],
    deps = [
        "@com_google_googletest//:gtest_main",
        "@communication_core//someip/factory:someip_header_factory",
        "@communication_core//someip/factory:someip_message_factory"
        ],
    visibility = ["@communication_core//:__subpackages__"]
)
