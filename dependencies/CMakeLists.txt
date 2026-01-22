include(FetchContent)

# Don't change this, ImGui-SFML depends on a specific version
# https://github.com/SFML/imgui-sfml?tab=readme-ov-file#dependencies
# Dear ImGui >= 1.91.1, < 1.92.0
set(IMGUI_VERSION 1.91.1)


#-------------
# SFML
#-------------
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

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
# SimpleIni
#-------------

FetchContent_Declare(simpleini
  GIT_REPOSITORY https://github.com/brofield/simpleini.git
  GIT_TAG        v4.25
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(simpleini)

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
