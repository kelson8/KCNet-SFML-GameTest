message(STATUS "Fetching SFML...")

# I may use these in the future, possibly disable the network files
#set(SFML_BUILD_AUDIO FALSE)
#set(SFML_BUILD_NETWORK FALSE)

FetchContent_MakeAvailable(sfml)
