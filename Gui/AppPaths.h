#ifndef M1OEP_APPPATHS_H
#define M1OEP_APPPATHS_H

#include <QString>

namespace AppPaths {

/// Walks up from the executable directory until data/realtor_data.csv exists (max 6 levels).
QString projectRoot();

} // namespace AppPaths

#endif // M1OEP_APPPATHS_H
