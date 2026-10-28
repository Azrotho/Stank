//
// Created by azrotho on 28/10/2026.
//

#include "ServerUtility.h"

#include <gf/Random.h>

gf::Id ServerUtility::generateId() {
		gf::Random random = gf::Random();
		return random.computeId();
}
