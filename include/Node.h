#ifndef NODY
#define NODY

#include <string>

class Node
{
    public:
        struct Element
        {
            std::string zString ="";
            float r=-99, i=-99;
        };

        int type;
        Element inh, syn;
        int o_p = -99;
        bool processed = false;
        bool isZ = false;
        bool inside = false;
        int prodno = 0;

        Node(int);
};

#endif
