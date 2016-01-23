/*
 * This file is part of the yuvPatterer tool.
 * 
 * Contact:
 * Christian Sieber <sieber@csstuff.info>
 */

#include "readPatternFile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <inttypes.h>
#include <cstring>

ActionList readPatternFile(std::string file)
{
        std::ifstream pattern(file.c_str());

        if (!pattern.is_open()) {

                std::cerr << "Failed to read " << file << " for reading!" << std::endl;
                return ActionList();
        }

        ActionList action_list;

        int32_t counter = 0;

        while (!pattern.eof()) {

                ++counter;

                const int32_t buf_len = 1024;                          //TODO, BUG: Longer lines then this cause endless loop!

                char buf[buf_len];

                // Read one line
                pattern.getline(buf, buf_len);

                // Discard it if it is too short or if is a comment
                if (strlen(buf) < 2 || buf[0] == ';')
                        continue;

                // Create stringstream to parse the line
                std::stringstream ss(buf);

                Action action;

                ss >> action.frame_nr_;
                ss >> action.action_;

                if (ss.fail()) {
                        std::cerr << "WARN: Syntax error in line " << counter << "!" << std::endl;
                        continue;
                }

                switch (action.action_) {

                // Create a new segment
                case 'N':
//                        std::cout << "Frame " << action.frame_nr_ << ": Creating new segment." << std::endl;
                        // no more parameters required here
                break;
                // Chance the current layer
                case 'C':
                        // read the additional parameters
                        ss >> action.dl_;
                        ss >> action.tl_;
                        ss >> action.ql_;

                        if (ss.fail()) {

                                std::cerr << "WARN: Failed to read additional 'C' parameters in line "
                                                  << counter << "!" << std::endl;
                                continue;
                        }

//                        std::cout << "Frame " << action.frame_nr_ << ": Changing to "
//                                          << action.dl_ << "/" << action.tl_ << "/" << action.ql_ << std::endl;
                break;
                // Quit the parsing
                case 'Q':
//                        std::cout << "Frame " << action.frame_nr_ << ": Quitting." << std::endl;
                        // no more parameters required
                break;
                default:
                        std::cerr << "WARN: Unknown action '" << action.action_ << "' in line "
                                  << counter << "!" << std::endl;
                        break;
                }

                action_list.push_back(action);
        }

        return action_list;
}



