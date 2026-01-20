include(FetchContent)

set(IMGUI_VERSION 1.91.1)

#-------------
# SFML
# TODO Move into here, and out of root CMake.
#-------------

# FetchContent_Declare(
  # sfml
  # URL https://github.com/SFML/SFML/archive/refs/tags/2.5.1.zip
  # URL_MD5 2c4438b3e5b2d81a6e626ecf72bf75be
# )
# add_subdirectory(sfml)

#-------------
# SFML Button Library
#-------------

# FetchContent_Declare(
    # sfml-button
    # GIT_REPOSITORY https://github.com/Pyromagne/SFML-Button.git
    # GIT_TAG        a4ec70970140f918d5dc03f1f885bd7ad498d6dc
# )
# FetchContent_MakeAvailable(sfml-button)

#-------------
# Fmt
#-------------

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        12.1.0
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(fmt)

#-------------
# Spdlog
#-------------

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(spdlog)

#-------------
# ImGui
#-------------

FetchContent_Declare(imgui
  URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0
    GIT_SHALLOW ON
    )

add_subdirectory(imgui-sfml)
