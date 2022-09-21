#ifndef AWSQT_GLOBAL_H
#define AWSQT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AWSQT_LIBRARY)
#  define AWSQT_EXPORT Q_DECL_EXPORT
#else
#  define AWSQT_EXPORT Q_DECL_IMPORT
#endif

#endif // AWSQT_GLOBAL_H
