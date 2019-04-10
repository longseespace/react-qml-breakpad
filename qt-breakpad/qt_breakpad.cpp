#include "qt_breakpad.h"
#include <QDebug>

#if TARGET_OS_IPHONE
#include "vendor/breakpad/src/common/long_string_dictionary.h"
using google_breakpad::LongStringDictionary;

// Mutex for thread-safe access to the key/value dictionary used by breakpad.
// It's a global instead of an instance variable of Breakpad
// since it can't live in a protected memory area.
pthread_mutex_t gDictionaryMutex;

//=============================================================================
// We want any memory allocations which are used by breakpad during the
// exception handling process (after a crash has happened) to be read-only
// to prevent them from being smashed before a crash occurs.  Unfortunately
// we cannot protect against smashes to our exception handling thread's
// stack.
//
// NOTE: Any memory allocations which are not used during the exception
// handling process may be allocated in the normal ways.
//
// The ProtectedMemoryAllocator class provides an Allocate() method which
// we'll using in conjunction with placement operator new() to control
// allocation of C++ objects.  Note that we don't use operator delete()
// but instead call the objects destructor directly:  object->~ClassName();
//
ProtectedMemoryAllocator *gMasterAllocator = NULL;
ProtectedMemoryAllocator *gKeyValueAllocator = NULL;
ProtectedMemoryAllocator *gBreakpadAllocator = NULL;
#endif

QtBreakpad *QtBreakpad::_instance = NULL;

void QtBreakpad::init(
    const QString &reportPath,
    google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
    google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
    void *callbackContext) {
  QtBreakpad::replaceInstance(new QtBreakpad(
      reportPath, filterCallBack, minidumpCallback, callbackContext));
}

void QtBreakpad::init(const QString &reportPath,
                      QMinidumpCallback qMinidumpCallback,
                      void *callbackContext) {
  QtBreakpad::replaceInstance(
      new QtBreakpad(reportPath, qMinidumpCallback, callbackContext));
}

QtBreakpad::QtBreakpad(
    const QString &reportPath,
    google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
    google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
    void *callbackContext) {
  this->buildBreakpadHandler(reportPath, filterCallBack, minidumpCallback,
                             callbackContext);
}

void QtBreakpad::buildBreakpadHandler(
    const QString &reportPath,
    google_breakpad::ExceptionHandler::FilterCallback filterCallBack,
    google_breakpad::ExceptionHandler::MinidumpCallback minidumpCallback,
    void *callbackContext) {
#if defined(Q_OS_WIN32)
  std::wstring pathAsStr = (const wchar_t *)reportPath.utf16();
  this->_breakpad_handler = new google_breakpad::ExceptionHandler(
      pathAsStr, filterCallBack, minidumpCallback, callbackContext, true);
#elif defined(Q_OS_LINUX)
  std::string pathAsStr = reportPath.toStdString();
  google_breakpad::MinidumpDescriptor md(pathAsStr);
  this->_breakpad_handler = new google_breakpad::ExceptionHandler(
      md, filterCallBack, minidumpCallback, callbackContext, true, -1);
#elif defined(Q_OS_MAC)

#if TARGET_OS_IPHONE
  // copy from Breakpad.mm
  try {
    int breakpad_pool_size = 4096;

    /*
     sizeof(Breakpad)
     + sizeof(google_breakpad::ExceptionHandler)
     + sizeof( STUFF ALLOCATED INSIDE ExceptionHandler )
     */

    gBreakpadAllocator = new ProtectedMemoryAllocator(breakpad_pool_size);

    // FIXME: temporarily disable
    //    gBreakpadAllocator->Protect();

    // Can uncomment this line to figure out how much space was actually
    // allocated using this allocator
    printf("gBreakpadAllocator allocated size = %d\n",
           gBreakpadAllocator->GetAllocatedSize());
  } catch (...) { // don't let exceptions leave this C API
    fprintf(stderr, "BreakpadCreate() : error\n");
  }
#endif
  std::string pathAsStr = reportPath.toStdString();
  this->_breakpad_handler = new google_breakpad::ExceptionHandler(
      pathAsStr, filterCallBack, minidumpCallback, callbackContext, true, NULL);
#endif
}

QtBreakpad::QtBreakpad(const QString &reportPath,
                       QMinidumpCallback qMinidumpCallback,
                       void *callbackContext) {
  this->_qMinidumpContextWrapper = new QtBreakpad::QMinidumpContextWrapper(
      qMinidumpCallback, callbackContext);

  this->buildBreakpadHandler(
      reportPath,
      NULL, // filter callback
      reinterpret_cast<google_breakpad::ExceptionHandler::MinidumpCallback>(
          &QtBreakpad::qMinidumpWrapper),
      this->_qMinidumpContextWrapper);
}

#if defined(Q_OS_WIN32)
bool QtBreakpad::qMinidumpWrapper(const wchar_t *dump_path,
                                  const wchar_t *minidump_id,
                                  QMinidumpContextWrapper *contextWrapper,
                                  EXCEPTION_POINTERS *exinfo,
                                  MDRawAssertionInfo *assertion,
                                  bool succeeded) {
  Q_UNUSED(exinfo);
  Q_UNUSED(assertion);
#elif defined(Q_OS_LINUX)
bool QtBreakpad::qMinidumpWrapper(
    const google_breakpad::MinidumpDescriptor &descriptor,
    QMinidumpContextWrapper *contextWrapper, bool succeeded) {
#elif defined(Q_OS_MAC)
bool QtBreakpad::qMinidumpWrapper(const char *dump_dir, const char *minidump_id,
                                  QMinidumpContextWrapper *contextWrapper,
                                  bool succeeded) {
#endif
  // if there's no dump file, not much to do
  if (!succeeded) {
    return false;
  }

  QMinidumpCallback qMinicudmpCallback = contextWrapper->qMinicudmpCallback;
  void *context = contextWrapper->context;

  QString minidumpFileName;

#if defined(Q_OS_WIN32)
  QDir minidumpDir = QDir(QString::fromWCharArray(dump_path));
  minidumpFileName = minidumpDir.absoluteFilePath(
      QString::fromWCharArray(minidump_id) + ".dmp");
#elif defined(Q_OS_LINUX)
  minidumpFileName = descriptor.path();
#elif defined(Q_OS_MAC)
  QDir minidumpDir = QDir(QString(dump_dir));
  minidumpFileName =
      minidumpDir.absoluteFilePath(QString(minidump_id) + ".dmp");
#endif

  QFile minidumpFile(minidumpFileName);

  return qMinicudmpCallback(minidumpFile, context);
}

void QtBreakpad::replaceInstance(QtBreakpad *newInstance) {
  // there can only be one handler
  if (QtBreakpad::_instance) {
    delete QtBreakpad::_instance;
  }

  QtBreakpad::_instance = newInstance;
}

QtBreakpad::~QtBreakpad() {
  delete this->_breakpad_handler;
  delete this->_qMinidumpContextWrapper;
}
