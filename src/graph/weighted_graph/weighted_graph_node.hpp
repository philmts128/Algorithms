#pragma once

#include <string>
#include <vector>
#include <cstdint>


namespace dsa
{
    /*-------------------------------*/
    struct weighted_graph_node
    {
        /*-------------------------------*/
        std::string label;
        bool visited { false };

        /*-------------------------------*/
        weighted_graph_node() {}

        /*-------------------------------*/
        weighted_graph_node(std::string_view label) {
            this->label = label;
        }
    };
}
