#ifndef QALIOSS_GLOBAL_H
#define QALIOSS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QALIOSS_LIBRARY)
#  define QALIOSSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QALIOSSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QALIOSS_GLOBAL_H
