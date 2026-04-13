#include "AppPaths.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

namespace AppPaths {

// Walk up from the .exe until we see data/realtor_data.csv (fixes running from build/Debug).
QString projectRoot() {
    QDir dir(QCoreApplication::applicationDirPath());
    for (int i = 0; i < 6; ++i) {
        const QString candidate = dir.filePath(QStringLiteral("data/realtor_data.csv"));
        if (QFileInfo::exists(candidate)) {
            return dir.absolutePath();
        }
        if (!dir.cdUp()) {
            break;
        }
    }
    return QCoreApplication::applicationDirPath();
}

} // namespace AppPaths
