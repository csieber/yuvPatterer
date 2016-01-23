/*
 * This file is part of the yuvPatterer tool.
 * 
 * Contact:
 * Christian Sieber <sieber@csstuff.info>
 */

#include "generatePattern.h"
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>

int32_t gl_width   = 1280;
int32_t gl_height  = 720;
char*   gl_yuv_buf = 0;
int32_t gl_buf_len = 0;

int generatePattern(ActionList action_list,
                    std::string name_base)
{
        int32_t frame_counter = 0;
        int32_t segment_counter = 0;

        int32_t curr_d = 0;
        int32_t curr_q = 0;

        std::ofstream* outp = newSegmentFile(NULL, name_base, segment_counter);

        if (!outp)
                return 1;

        // Generate buff for the yuv images
        const int32_t size = gl_width * gl_height;
        gl_buf_len = size + size/4 + size/4;

        gl_yuv_buf = new char[gl_buf_len];

        // Loop through all actions
        BOOST_FOREACH (const Action& action, action_list) {

                // Count the frames upwards
                while(true) {

                        /*
                         * If there is action for this frame,
                         * do it.
                         */
                        if (action.frame_nr_ == frame_counter) {

                                switch (action.action_) {

                                case 'C':

                                        curr_d = action.dl_;
                                        curr_q = action.ql_;

                                break;

                                // Create a new segment file
                                case 'N':
                                {
                                        std::cout << "Frame " << frame_counter << " new segment." << std::endl;

                                        segment_counter++;

                                        outp = newSegmentFile(outp, name_base, segment_counter);

                                        if (!outp)
                                                return 1;
                                }
                                break;
                                case 'Q':

                                        std::cout << "Frame " << frame_counter << " quitting." << std::endl;

                                break;
                                default:
                                        // shouldn't happen..
                                        BOOST_ASSERT(false);
                                break;
                                }

                                break;

                        } // If there is action for this frame

                        // There was no action, continue;
                        bool res = readFrame(name_base, frame_counter, curr_d, curr_q);

                        if (!res)
                                return 1;

                        writeYUVFrame(outp);

                        frame_counter++;
                }
        }

        outp->close();
        delete outp;
        delete[] gl_yuv_buf;

        return 0;
}

bool readFrame(std::string name_base, int32_t frame, int32_t dl, int32_t ql)
{
        std::string name = boost::lexical_cast<std::string>(
                                                        boost::format("%s.D%02dQ%02d.yuv")
                                                                % name_base
                                                                % dl % ql);

        std::ifstream ifs(name.c_str());

        if (!ifs.is_open()) {

                std::cerr << "ERR: Failed to open " << name << "!" << std::endl;
                return false;
        }

        bool res = readYUVFrame(&ifs, frame);

        ifs.close();

        return res;
}

std::ofstream* newSegmentFile(std::ofstream* old, std::string stream, int32_t segment_counter)
{
        if (old) {

                old->close();
                delete old;
        }

        std::string name = boost::lexical_cast<std::string>(
				  boost::format("%s.out.%04d.yuv") % stream % segment_counter);

        // Check if file already exists
        std::ifstream test(name.c_str());

        if (test.is_open()) {

                std::cerr << "ERR: File " << name << " already exists!" << std::endl;
                return 0;
        }

        std::ofstream* outp = new std::ofstream(name.c_str());

        if (!outp->is_open()) {

                std::cerr << "ERR: Failed to open " << name << " for writing!" << std::endl;
                delete outp;
                return 0;
        }

        return outp;
}

bool readYUVFrame(std::ifstream* file, int32_t frame)
{
        const int64_t seek_p = static_cast<int64_t>(frame) *
			       static_cast<int64_t>(gl_buf_len);

        file->seekg(seek_p);

        file->read(gl_yuv_buf, gl_buf_len);

        if (file->fail()) {

                std::cerr << "ERR: YUV does not contain enough frames! (frame "
                          << frame << " requested)" << std::endl;
			  
                return false;
        }

        return true;
}

bool writeYUVFrame(std::ofstream* file)
{
        file->write(gl_yuv_buf, gl_buf_len);

        return true;
}
