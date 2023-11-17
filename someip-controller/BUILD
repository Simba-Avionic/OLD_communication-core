cc_library(
    name = "someip_interface",
    hdrs = [
        "Isomeip_controller.h",
    ],
    visibility = ["@communication_core//:__subpackages__"],
    deps = ["@core"],
)

cc_library(
    name = "someip_controller",
    srcs = ["someip_controller.cc"],
    hdrs = [
        "transfer.h",
        "someip_controller.h",
    ],
    visibility = ["@communication_core//:__subpackages__"],
    deps = [
        ":someip_interface",
        "@core",
    ],
)
