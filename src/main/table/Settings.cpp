/*
 * imageHasher - C++ version of the Hashing module from SimilarImage
 * Copyright (C) 2014  Nicholas Wright
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file Settings.cpp
 *
 * @date 27 Jul 2014
 * @author Nicholas Wright
 * @brief Contains database related settings
 */

#include "Settings.hpp"

namespace db {
namespace table {

	void Settings::set_value(std::string key, std::string value) {
		this->settings[key] = value;
	}

	std::string Settings::get_value(std::string key) {
		return this->settings[key];
	}

} /* namespace table */
} /* namespace db */
