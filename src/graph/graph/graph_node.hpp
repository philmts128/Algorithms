#pragma once

#include <iostream>
#include <vector>
#include <string>


namespace dsa
{
    /*----------------------------------*/
    struct graph_node
    {
        /*----------------------------------*/
        dsa::graph_node* prev { nullptr };
        std::vector<graph_node*> neighbors;
        std::string label;
        bool visited { false };

        /*----------------------------------*/
        graph_node() {}

        /*----------------------------------*/
        graph_node(std::string_view label) {
            this->label = label;
        }
    };
}
