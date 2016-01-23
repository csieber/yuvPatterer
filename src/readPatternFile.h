/*
 * This file is part of the yuvPatterer tool.
 * 
 * Contact:
 * Christian Sieber <sieber@csstuff.info>
 */

#ifndef READPATTERNFILE_H_
#define READPATTERNFILE_H_

#include <string>
#include <inttypes.h>
#include <list>

struct Action {

        Action() {
                frame_nr_ = 0;
                action_ = 0x00;
                dl_ = 0;
                tl_ = 0;
                ql_ = 0;
        }

        int32_t frame_nr_;
        char action_;
        int32_t dl_;
        int32_t tl_;
        int32_t ql_;

        bool operator <(const Action& rh) {

                if (this->frame_nr_ < rh.frame_nr_)
                        return true;
                else
                        return false;
        }
};

typedef std::list<Action> ActionList;

ActionList readPatternFile(std::string file);


#endif /* READPATTERNFILE_H_ */
