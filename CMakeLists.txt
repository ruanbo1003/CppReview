cmake_minimum_required(VERSION 3.21)
project(CppReview)

include_directories("/usr/local/include/")
include_directories("./src")
set(CMAKE_CXX_STANDARD 17)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors -fsanitize=address")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")

# google sanitizers
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(CppReview src/main.cpp src/main.h src/cpp11/entry.h src/syntax/entry.h src/syntax/class.cpp src/comm/log.cpp src/comm/log.h src/syntax/raii.cpp src/syntax/inherit.cpp src/syntax/static.cpp src/syntax/array.cpp src/syntax/pointer.cpp src/syntax/reference.cpp src/syntax/this.cpp src/syntax/template.cpp src/syntax/const.cpp src/stl/entry.h src/stl/vector.cpp src/cpp11/functor.cpp src/lambda/entry.h src/lambda/basic.cpp src/lambda/syntax.cpp src/lambda/principle.cpp src/lambda/application.cpp src/threads/entry.h src/threads/basic.cpp src/threads/race_condition.cpp src/threads/mutex.cpp src/cpp11/variadic_template.cpp src/threads/condition_variable.cpp src/syntax/noncopyable.cpp src/syntax/singleton.cpp src/stl/list.cpp src/stl/map.cpp src/cpp11/unordered_containter.cpp src/cpp11/function_bind.cpp src/cpp11/call_once.cpp src/cpp11/thread.cpp src/util/util.h src/util/thread.cpp src/cpp11/auto_decltype.cpp src/cpp11/type_alias.cpp src/cpp11/smart_pointer.cpp src/cpp11/docs/smart-pointer.md src/cpp11/memory_model.cpp src/codeanalysis/entry.h src/codeanalysis/memory.cpp src/codeanalysis/core_dump.cpp src/cpp11/thread_local.cpp src/cpp11/array.cpp src/cpp11/constexpr.cpp src/cpp11/literals.cpp src/cpp14/entry.h src/cpp14/type_deduction.cpp src/cpp14/lambda.cpp src/cpp14/template.cpp src/cpp14/separator.cpp src/cpp14/exchange.cpp src/cpp17/entry.h src/cpp17/constexpr.cpp src/cpp17/structure_binding.cpp src/cpp17/condition_initialize.cpp src/stl/any.cpp src/stl/optional.cpp src/cpp17/nested_namespace.cpp src/cpp17/type_deduce.cpp src/cpp17/fold_expr.cpp src/stl/apply.cpp src/cpp17/file_system.cpp src/threads/shared_mutex_lock.cpp src/ipc/head.h src/ipc/shared_memory_write.cpp src/ipc/shared_memory_read.cpp src/libs/redis.cpp src/libs/head.h src/cpp11/rvalue/head.h src/cpp11/rvalue/rvalue.cpp src/templates/with_hash_function.cpp src/templates/StudentTemplateHash.cpp src/templates/StudentTemplateHash.h src/nets/head.h src/nets/tcp_server.cpp src/nets/socket_options/reuseaddr.cpp src/nets/tcp_client.cpp src/nets/socket_options/reuseport.cpp src/nets/socket_options/bufsize.cpp src/nets/socket_options/reuseport_multiprocess.cpp src/nets/socket_options/nodelay.cpp src/nets/select_tcp.cpp src/optimize/head.h src/optimize/simd.cpp src/cpp11/move/head.h src/cpp11/move/why_move.cpp src/optimize/string.cpp)

#MESSAGE(STATUS "platform: ${CMAKE_SYSTEM_NAME}")
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    MESSAGE("OS-MACOS")
    target_link_libraries(CppReview /usr/local/lib/libhiredis.dylib)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    MESSAGE("OS-LINUX")
    target_link_libraries(CppReview /usr/local/lib/libhiredis.so)
else()
    # TODO: error
endif()
