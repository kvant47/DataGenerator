import qbs

CppApplication {
    consoleApplication: true
    files: [
        "CarDataGenerator.cpp",
        "CarDataGenerator.h",
        "DataGenerator.cpp",
        "DataGenerator.h",
        "HarmonicMotionDataGenerator.cpp",
        "HarmonicMotionDataGenerator.h",
        "main.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
