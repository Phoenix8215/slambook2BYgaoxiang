project(imageBasics)

add_executable(imageBasics imageBasics.cpp)
# 链接OpenCV库
target_link_libraries(imageBasics ${OpenCV_LIBS})

# add_executable(undistortImage undistortImage.cpp)
add_executable(undistortImage demo.cpp)
# 链接OpenCV库
target_link_libraries(undistortImage ${OpenCV_LIBS})
