#include "vectors.hpp"

namespace vectors
{
    std::vector<int> reverse(std::vector<int>* old)
    {
        if(old->size() == 0)
        {
            return {};
        }
        else
        {
            std::vector<int> nowy;
            for(int i = old->size() - 1; i >= 0; i--)
                nowy.push_back((*old)[i]);
            return nowy;
        }
    }

    int max(std::vector<int>* vec)
    {
        int maks = (*vec)[0];
        for(int i = 1; i < vec->size(); i++)
        {
            if((*vec)[i] > maks)
                maks = (*vec)[i];
        }
        return maks;
    }
}