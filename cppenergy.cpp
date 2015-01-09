#include <vector>
#include <cmath>
#include "cppenergy.h"

namespace coulomb {

double runcpp(std::vector<double>& ri, std::vector<double>& rj,
              double chg1, double chg2)
{
    double dx = ri[0] - rj[0];
    double dy = ri[1] - rj[1];
    double dz = ri[2] - rj[2];
    return chg1 * chg2 / std::sqrt(dx*dx + dy*dy + dz*dz);
}

}
