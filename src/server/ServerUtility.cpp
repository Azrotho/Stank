//
// Created by azrotho on 28/10/2026.
//

#include "ServerUtility.h"

#include <gf/Random.h>

gf::Id ServerUtility::generateId() {
		gf::Random random = gf::Random();
		return random.computeId();
}

std::string ServerUtility::generateRandomName() {
		gf::Random random = gf::Random();
		std::vector<std::string> prefix = {"Armored", "Colossal", "Tanky"};
		std::vector<std::string> suffix = {"Tigre", "Panzer", "T-34", "Leclerc"};
		int randomNumber = random.computeUniformInteger(0, 1000);
		std::string prefixS = prefix[random.computeUniformInteger(0, (int) prefix.size() - 1)];
		std::string suffixS = suffix[random.computeUniformInteger(0, (int) suffix.size() - 1)];
		return prefixS + suffixS + "#" + std::to_string(randomNumber);
}
