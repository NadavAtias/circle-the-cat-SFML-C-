#configure_file ("my_file1.jpg" ${CMAKE_BINARY_DIR}/resources COPYONLY)
#configure_file ("my_file2.jpg" ${CMAKE_BINARY_DIR}/resources COPYONLY)

file           (MAKE_DIRECTORY     ${CMAKE_BINARY_DIR}/resources)
configure_file ("boardScreen2.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Win.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("You Lose.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Cat.png"          ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Baguette.ttf"     ${CMAKE_BINARY_DIR} COPYONLY)
