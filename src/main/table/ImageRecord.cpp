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
 * @file ImageRecord.cpp
 *
 * @date 22 Jun 2014
 * @author Nicholas Wright
 * @brief Container for Imagerecords
 */
#include "ImageRecord.hpp"

namespace imageHasher {
namespace db {
namespace table {

ImageRecord::ImageRecord() {
	this->image_id = 0;
	this->path = "";
	this->hash = NULL;
}

ImageRecord::ImageRecord(std::string path, Hash *hash) {
	this->image_id = 0;
	this->path = path;
	this->hash = hash;
}

Hash ImageRecord::get_hash() {
	return *(this->hash);
}

bool ImageRecord::is_valid() {
	if(this->path.empty()) {
		return false;
	}else{
		return true;
	}
}

} /* namespace table */
} /* namespace db */
} /* namespace imageHasher */
