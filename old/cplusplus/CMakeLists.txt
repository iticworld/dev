cmake_minimum_required(VERSION 3.8)
project(novemberizingc++)

set(CMAKE_CXX_STANDARD 17)

include_directories(source)

set(sources source/novemberizing.cc
            source/novemberizing/core/memory.cc
            source/novemberizing/timestamp.cc
            source/novemberizing/system.cc
            source/novemberizing/string.cc
            source/novemberizing/string/format.cc
            source/novemberizing/random.cc
            source/novemberizing/descriptor/integer.cc
            source/novemberizing/synchronizer.cc
            source/novemberizing/container.cc
            source/novemberizing/collection.cc
            source/novemberizing/iterator.cc
            source/novemberizing/list.cc
            source/novemberizing/array/list.cc
            source/novemberizing/linked/list.cc
            source/novemberizing/tuple/single.cc
            source/novemberizing/tuple/pair.cc
            source/novemberizing/tuple/triple.cc
            source/novemberizing/dictionary.cc
            source/novemberizing/set.cc
            source/novemberizing/tree.cc
            source/novemberizing/binary/search/tree.cc
            source/novemberizing/red/black/tree.cc
            source/novemberizing/descriptor.cc
            source/novemberizing/message/digest/v5.cc
            source/novemberizing/secure/hash/algorithm/v1.cc
            source/novemberizing/secure/hash/algorithm/v2.cc
            source/novemberizing/uuid.cc
            source/novemberizing/uuid/to.cc
            source/novemberizing/uuid/is.cc
            source/novemberizing/internet/address.cc
            source/novemberizing/executable.cc
            source/novemberizing/input.cc
            source/novemberizing/output.cc
            source/novemberizing/command/line.cc
            source/novemberizing/event.cc
            source/novemberizing/log.cc)

set(headers source/novemberizing.hh
            source/novemberizing/random.hh
            source/novemberizing/synchronizer.hh
            source/novemberizing/container.hh
            source/novemberizing/collection.hh
            source/novemberizing/iterator.hh
            source/novemberizing/list.hh
            source/novemberizing/array/list.hh
            source/novemberizing/linked/list.hh
            source/novemberizing/tuple/single.hh
            source/novemberizing/tuple/pair.hh
            source/novemberizing/tuple/triple.hh
            source/novemberizing/dictionary.hh
            source/novemberizing/set.hh
            source/novemberizing/tree.hh
            source/novemberizing/binary/search/tree.hh
            source/novemberizing/red/black/tree.hh
            source/novemberizing/descriptor.hh
            source/novemberizing/message/digest/v5.hh
            source/novemberizing/secure/hash/algorithm/v1.hh
            source/novemberizing/secure/hash/algorithm/v2.hh
            source/novemberizing/uuid.hh
            source/novemberizing/internet/address.hh
            source/novemberizing/string.hh
            source/novemberizing/bytes.hh
            source/novemberizing/capacity.hh
            source/novemberizing/exception.hh
            source/novemberizing/timestamp.hh
            source/novemberizing/pointer.hh
            source/novemberizing/core.hh
            source/novemberizing/core/memory.hh
            source/novemberizing/executable.hh
            source/novemberizing/input.hh
            source/novemberizing/output.hh
            source/novemberizing/function.hh
            source/novemberizing/command.hh
            source/novemberizing/command/line.hh
            source/novemberizing/event.hh
            source/novemberizing/log.hh
            source/novemberizing/queue.hh)

set(inlines source/novemberizing/core.hp
            source/novemberizing/capacity.hp
            source/novemberizing/system.hp
            source/novemberizing/move.hp
            source/novemberizing/function.hp
            source/novemberizing/exception.hp
            source/novemberizing/core/memory.hp
            source/novemberizing/string.hp
            source/novemberizing/endian.hp
            source/novemberizing/timestamp.hp
            source/novemberizing/bytes.hp
            source/novemberizing/bytes/to.hp
            source/novemberizing/random.hp
            source/novemberizing/integer.hp
            source/novemberizing/integer/to.hp
            source/novemberizing/integer/is.hp
            source/novemberizing/integer/add.hp
            source/novemberizing/pointer.hp
            source/novemberizing/synchronizer.hp
            source/novemberizing/descriptor.hp
            source/novemberizing/descriptor/integer.hp
            source/novemberizing/container.hp
            source/novemberizing/container/base.hp
            source/novemberizing/container/base/accessor.hp
            source/novemberizing/collection.hp
            source/novemberizing/iterator.hp
            source/novemberizing/iterator/accessor.hp
            source/novemberizing/list.hp
            source/novemberizing/array/list.hp
            source/novemberizing/linked/list.hp
            source/novemberizing/linked/list/node.hp
            source/novemberizing/tuple/single.hp
            source/novemberizing/tuple/pair.hp
            source/novemberizing/tuple/triple.hp
            source/novemberizing/dictionary.hp
            source/novemberizing/set.hp
            source/novemberizing/tree.hp
            source/novemberizing/binary/search/tree.hp
            source/novemberizing/binary/search/tree/node.hp
            source/novemberizing/red/black/tree.hp
            source/novemberizing/red/black/tree/rotate.hp
            source/novemberizing/red/black/tree/fix.hp
            source/novemberizing/red/black/tree/node.hp
            source/novemberizing/message/digest/v5.hp
            source/novemberizing/secure/hash/algorithm/v1.hp
            source/novemberizing/secure/hash/algorithm/v2.hp
            source/novemberizing/uuid.hp
            source/novemberizing/uuid/to.hp
            source/novemberizing/uuid/is.hp
            source/novemberizing/internet/address.hp
            source/novemberizing/internet/address/to.hp
            source/novemberizing/executable.hp
            source/novemberizing/input.hp
            source/novemberizing/output.hp
            source/novemberizing/command/line.hp
            source/novemberizing/event.hp
            source/novemberizing/event/engine.hp
            source/novemberizing/event/executor.hp
            source/novemberizing/log.hp
            source/novemberizing/queue.hp)

add_library(novemberizingc++ ${sources} ${headers} ${inlines})

add_subdirectory(sample)

install(DIRECTORY source/ DESTINATION include
        FILES_MATCHING PATTERN "*.hh")

install(DIRECTORY source/ DESTINATION include
        FILES_MATCHING PATTERN "*.hp")

install(TARGETS novemberizingc++ DESTINATION lib)
