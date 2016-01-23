/*
 * This file is part of the yuvPatterer tool.
 * 
 * Contact:
 * Christian Sieber <sieber@csstuff.info>
 */

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/assert.hpp>
#include <fstream>
#include "readPatternFile.h"
#include "generatePattern.h"

void printPreamble() {

        std::cout << "\nyuvPatterer - YUV Switching Pattern Generator \n\n"
                          << "Usage: svcPatter [OPTION] [YUV-Base]" << std::endl;
}

int main(int argc, char** argv) {

        /*
         * Read command line options.
         */
        namespace po = boost::program_options;

        po::options_description desc("Options");
        desc.add_options()
            ("help", "Help")
            ("yuv-base,i", po::value<std::string>()->required(), "Input YUV base filename")
            ("width,w", po::value<int32_t>()->required(), "Input YUV width")
            ("height,h", po::value<int32_t>()->required(), "Input YUV height")
            ("pattern,p", po::value<std::string>()->required(), "Pattern file");

        po::positional_options_description pos_opt;
        pos_opt.add("yuv-base,i", 1);

        po::variables_map vm;

        try {
                po::store(
                                po::command_line_parser(argc, argv).
                                        options(desc).positional(pos_opt).run(),
                                vm);

                po::notify(vm);
        }
        catch (boost::program_options::required_option& ex) {

                printPreamble();
                std::cerr << "Required option '" << ex.get_option_name()
                                  << "' is missing!" << std::endl << std::endl
                                  << desc << std::endl;

                return 1;
        }
        catch (boost::program_options::invalid_option_value& ex) {

                printPreamble();
                std::cerr << "Option '" << ex.get_option_name()
                                  << "' has an invalid value!" << std::endl << std::endl
                                  << desc << std::endl;

                return 1;
        }
        catch (boost::program_options::unknown_option& ex) {

                printPreamble();
                std::cerr << "Unknown option '" << ex.get_option_name()
                                  << "'!" << std::endl << std::endl
                                  << desc << std::endl;

                return 1;
        }
        catch (boost::program_options::invalid_command_line_syntax& ex) {

                printPreamble();
                std::cerr << "Invalid syntax! What(): '" << ex.what() << std::endl << std::endl
                                  << desc << std::endl;

                return 1;
        }

        if (vm.count("help")) {
                printPreamble();
            std::cout << desc << "\n";
            return 1;
        }

        gl_width = vm["width"].as<int32_t>();
        gl_height = vm["height"].as<int32_t>();

        std::cout << "Start reading pattern file.." << std::endl;

        ActionList action_list = readPatternFile(vm["pattern"].as<std::string>());

        std::cout << "Finished reading pattern file.." << std::endl;

        if (action_list.empty()) {

                std::cerr << "Empty action list, quitting!" << std::endl;
                return 1;
        }

        return generatePattern(action_list, vm["yuv-base"].as<std::string>());
//        return parseStream(action_list, vm["svc"].as<std::string>());
}
