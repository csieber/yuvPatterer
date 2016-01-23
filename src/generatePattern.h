/*
 * This file is part of the yuvPatterer tool.
 * 
 * Contact:
 * Christian Sieber <sieber@csstuff.info>
 */

#ifndef GENERATEPATTERN_H_
#define GENERATEPATTERN_H_

#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/shared_array.hpp>
#include <inttypes.h>
#include "readPatternFile.h"

extern int32_t gl_width;
extern int32_t gl_height;
extern char* gl_yuv_buf;
extern int32_t gl_buf_len;

int generatePattern(ActionList action_list,
		    std::string name_base);

std::ofstream* newSegmentFile(std::ofstream* old, std::string stream, int32_t segment_counter);

typedef boost::tuple<
            boost::shared_array<const char>, int32_t> DataLenPair;

bool readFrame(std::string name_base, int32_t frame, int32_t dl, int32_t ql);

bool readYUVFrame(std::ifstream* file, int32_t frame);
bool writeYUVFrame(std::ofstream* file);

#endif /* GENERATEPATTERN_H_ */
