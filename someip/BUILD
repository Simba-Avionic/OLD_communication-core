cc_library(
    name = "someip_types",
    hdrs = [
        "message_code.h",
        "message_type.h",
    ],
    visibility = ["//communication_core/:__subpackages__"],
)

cc_library(
    name = "someip_header",
    srcs = ["someip_header.cc"],
    hdrs = [
        "someip_header.h",
    ],
    visibility = ["//communication_core/:__subpackages__"],
    deps = [
        "//communication_core/network-data:network_data_structure",
        "//communication_core/network-data:network_data_type",
    ],
)
