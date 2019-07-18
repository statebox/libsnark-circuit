include_directories(.)
add_executable(
  div_by_3

  div_by_3.cpp
)
target_link_libraries(
  div_by_3

  snark
)
target_include_directories(
  div_by_3

  PUBLIC
  ${DEPENDS_DIR}/libsnark
  ${DEPENDS_DIR}/libsnark/depends/libfqfft
  ${DEPENDS_DIR}/libsnark/depends/libff
)
add_executable(
  prime_under_16

  prime_under_16.cpp
)
target_link_libraries(
  prime_under_16

  snark
)
target_include_directories(
  prime_under_16

  PUBLIC
  ${DEPENDS_DIR}/libsnark
  ${DEPENDS_DIR}/libsnark/depends/libfqfft
  ${DEPENDS_DIR}/libsnark/depends/libff
)
