cc_library(
    name = "someip_interface",
    hdrs = [
        "Isomeip_controller.h",
    ],
    visibility = ["@communication_core//:__subpackages__"],
    deps = [
        "@communication_core//someip:someip_header",
        "@communication_core//someip:someip_types",
        "@communication_core//someip/factory:someip_message_factory",
        "@core",
    ],
)

cc_library(
    name = "someip_controller",
    srcs = ["someip_controller.cc"],
    hdrs = [
        # "method.h",
        # "method_result.h",
        "someip_controller.h",
        "transfer.h",
    ],
    visibility = ["@communication_core//:__subpackages__"],
    deps = [
        ":someip_interface",
        "@communication_core//database:DatabaseLib",
        "@communication_core//json-parser:JsonParser",
        "@communication_core//sockets:socket_interface",
        "@communication_core//someip:someip_header",
        "@communication_core//someip:someip_types",
        "@communication_core//someip/factory:someip_header_factory",
        "@communication_core//someip/factory:someip_message_factory",
        "@core",
    ],
)
