HEADERS += $$PWD/qt_breakpad.h
SOURCES += $$PWD/qt_breakpad.cpp

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/vendor/breakpad/src

# windows
win32:HEADERS += $$PWD/vendor/breakpad/src/common/windows/string_utils-inl.h
win32:HEADERS += $$PWD/vendor/breakpad/src/common/windows/guid_string.h
win32:HEADERS += $$PWD/vendor/breakpad/src/client/windows/handler/exception_handler.h
win32:HEADERS += $$PWD/vendor/breakpad/src/client/windows/common/ipc_protocol.h
win32:HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_format.h
win32:HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/breakpad_types.h
win32:HEADERS += $$PWD/vendor/breakpad/src/client/windows/crash_generation/crash_generation_client.h
win32:HEADERS += $$PWD/vendor/breakpad/src/common/scoped_ptr.h
win32:SOURCES += $$PWD/vendor/breakpad/src/client/windows/handler/exception_handler.cc
win32:SOURCES += $$PWD/vendor/breakpad/src/common/windows/string_utils.cc
win32:SOURCES += $$PWD/vendor/breakpad/src/common/windows/guid_string.cc
win32:SOURCES += $$PWD/vendor/breakpad/src/client/windows/crash_generation/crash_generation_client.cc

# linux
linux {
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/cpu_set.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/proc_cpuinfo_reader.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/handler/exception_handler.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/crash_generation/crash_generation_client.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/handler/minidump_descriptor.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/minidump_writer.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/microdump_writer/microdump_writer.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/line_reader.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/linux_dumper.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/directory_reader.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/dump_writer_common/thread_info.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/dump_writer_common/ucontext_reader.h
  HEADERS += $$PWD/vendor/breakpad/src/client/linux/log/log.h
  HEADERS += $$PWD/vendor/breakpad/src/client/minidump_file_writer-inl.h
  HEADERS += $$PWD/vendor/breakpad/src/client/minidump_file_writer.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/linux_libc_support.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/eintr_wrapper.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/ignore_ret.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/file_id.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/memory_mapped_file.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/safe_readlink.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/guid_creator.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/elfutils.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/elfutils-inl.h
  HEADERS += $$PWD/vendor/breakpad/src/common/linux/elf_gnu_compat.h
  HEADERS += $$PWD/vendor/breakpad/src/common/using_std_string.h
  HEADERS += $$PWD/vendor/breakpad/src/common/memory.h
  HEADERS += $$PWD/vendor/breakpad/src/common/basictypes.h
  HEADERS += $$PWD/vendor/breakpad/src/common/memory_range.h
  HEADERS += $$PWD/vendor/breakpad/src/common/string_conversion.h
  HEADERS += $$PWD/vendor/breakpad/src/common/convert_UTF.h
  HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_format.h
  HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_size.h
  HEADERS += $$PWD/vendor/breakpad/src/google_breakpad/common/breakpad_types.h
  HEADERS += $$PWD/vendor/breakpad/src/common/scoped_ptr.h
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/crash_generation/crash_generation_client.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/handler/exception_handler.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/handler/minidump_descriptor.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/minidump_writer.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/microdump_writer/microdump_writer.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/linux_dumper.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/dump_writer_common/thread_info.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/dump_writer_common/ucontext_reader.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/linux/log/log.cc
  SOURCES += $$PWD/vendor/breakpad/src/client/minidump_file_writer.cc
  SOURCES += $$PWD/vendor/breakpad/src/common/linux/linux_libc_support.cc
  SOURCES += $$PWD/vendor/breakpad/src/common/linux/file_id.cc
  SOURCES += $$PWD/vendor/breakpad/src/common/linux/memory_mapped_file.cc
  SOURCES += $$PWD/vendor/breakpad/src/common/linux/safe_readlink.cc
  SOURCES += $$PWD/vendor/breakpad/src/common/linux/guid_creator.cc
  SOURCES += $$PWD/vendor/breakpad/src/common/linux/elfutils.cc
  SOURCES += $$PWD/vendor/breakpad/src/common/string_conversion.cc
  SOURCES += $$PWD/vendor/breakpad/src/common/convert_UTF.c
}

# macos
macx {
  HEADERS += \
    $$PWD/vendor/breakpad/src/client/mac/handler/exception_handler.h \
    $$PWD/vendor/breakpad/src/common/using_std_string.h \
    $$PWD/vendor/breakpad/src/common/memory_allocator.h \
    $$PWD/vendor/breakpad/src/common/basictypes.h \
    $$PWD/vendor/breakpad/src/common/memory_range.h \
    $$PWD/vendor/breakpad/src/common/string_conversion.h \
    $$PWD/vendor/breakpad/src/client/mac/handler/protected_memory_allocator.h \
    $$PWD/vendor/breakpad/src/common/convert_UTF.h \
    $$PWD/vendor/breakpad/src/common/md5.h \
    $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_format.h \
    $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_size.h \
    $$PWD/vendor/breakpad/src/google_breakpad/common/breakpad_types.h \
    $$PWD/vendor/breakpad/src/common/scoped_ptr.h \
    $$PWD/vendor/breakpad/src/client/minidump_file_writer-inl.h \
    $$PWD/vendor/breakpad/src/client/minidump_file_writer.h

  SOURCES +=  \
    $$PWD/vendor/breakpad/src/client/minidump_file_writer.cc \
    $$PWD/vendor/breakpad/src/client/mac/crash_generation/crash_generation_client.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/exception_handler.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/minidump_generator.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/breakpad_nlist_64.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/dynamic_images.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/protected_memory_allocator.cc \
    $$PWD/vendor/breakpad/src/common/mac/bootstrap_compat.cc \
    $$PWD/vendor/breakpad/src/common/mac/file_id.cc \
    $$PWD/vendor/breakpad/src/common/mac/macho_id.cc \
    $$PWD/vendor/breakpad/src/common/mac/macho_reader.cc \
    $$PWD/vendor/breakpad/src/common/mac/macho_utilities.cc \
    $$PWD/vendor/breakpad/src/common/mac/macho_walker.cc \
    $$PWD/vendor/breakpad/src/common/mac/string_utilities.cc \
    $$PWD/vendor/breakpad/src/common/string_conversion.cc \
    $$PWD/vendor/breakpad/src/common/convert_UTF.c \
    $$PWD/vendor/breakpad/src/common/md5.cc

  OBJECTIVE_SOURCES += \
    $$PWD/vendor/breakpad/src/common/mac/MachIPC.mm

  LIBS += -framework Foundation
}

# ios
ios {
  HEADERS += \
    $$PWD/vendor/breakpad/src/client/mac/handler/exception_handler.h \
    $$PWD/vendor/breakpad/src/client/mac/handler/protected_memory_allocator.h \
    $$PWD/vendor/breakpad/src/common/using_std_string.h \
    $$PWD/vendor/breakpad/src/common/memory_allocator.h \
    $$PWD/vendor/breakpad/src/common/basictypes.h \
    $$PWD/vendor/breakpad/src/common/memory_range.h \
    $$PWD/vendor/breakpad/src/common/string_conversion.h \
    $$PWD/vendor/breakpad/src/common/convert_UTF.h \
    $$PWD/vendor/breakpad/src/common/md5.h \
    $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_format.h \
    $$PWD/vendor/breakpad/src/google_breakpad/common/minidump_size.h \
    $$PWD/vendor/breakpad/src/google_breakpad/common/breakpad_types.h \
    $$PWD/vendor/breakpad/src/common/scoped_ptr.h \
    $$PWD/vendor/breakpad/src/client/minidump_file_writer-inl.h \
    $$PWD/vendor/breakpad/src/client/minidump_file_writer.h

  SOURCES +=  \
    $$PWD/vendor/breakpad/src/client/minidump_file_writer.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/exception_handler.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/minidump_generator.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/breakpad_nlist_64.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/dynamic_images.cc \
    $$PWD/vendor/breakpad/src/client/mac/handler/protected_memory_allocator.cc \
    $$PWD/vendor/breakpad/src/common/mac/file_id.cc \
    $$PWD/vendor/breakpad/src/common/mac/macho_id.cc \
    $$PWD/vendor/breakpad/src/common/mac/macho_reader.cc \
    $$PWD/vendor/breakpad/src/common/mac/macho_utilities.cc \
    $$PWD/vendor/breakpad/src/common/mac/macho_walker.cc \
    $$PWD/vendor/breakpad/src/common/mac/string_utilities.cc \
    $$PWD/vendor/breakpad/src/common/string_conversion.cc \
    $$PWD/vendor/breakpad/src/common/convert_UTF.c \
    $$PWD/vendor/breakpad/src/common/md5.cc

  LIBS += -framework Foundation
}

## breakpad needs debug info inside binaries

win32-msvc* {
    # generate the symbol file
    QMAKE_LFLAGS_RELEASE += /MAP /debug /opt:ref
    QMAKE_CFLAGS_RELEASE += -Zi
    QMAKE_CXXFLAGS_RELEASE += -Zi
}

unix:QMAKE_CFLAGS += -g
unix:QMAKE_CXXFLAGS += -g

# prevent undue optimization, which ruins breakpad's backtrace
QMAKE_CFLAGS_RELEASE -= -O
QMAKE_CFLAGS_RELEASE -= -O1
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
