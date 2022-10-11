#ifndef E08214A9_6B96_43B6_A058_ABCBF5B79CB5
#define E08214A9_6B96_43B6_A058_ABCBF5B79CB5
#include "module/CurrentModule.h"
#include "library/Logger/Logger.h"
class CurrentDataAggregator
{
private:
    static const int BUFFER_MAX_SIZE = 60;
    double buffer[BUFFER_MAX_SIZE];
    int currentIdx = 0;
    bool isBufferFull = false;

public:
    void collect(double current);
    double calculateAverageCurrent();
    void reset();
};

#endif /* E08214A9_6B96_43B6_A058_ABCBF5B79CB5 */
