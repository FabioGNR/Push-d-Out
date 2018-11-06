#include "OtherMap.h"
namespace engine {
namespace input {

    void OtherMap::add(engine::input::Keys key, int axisValue)
    {
        test[key] = axisValue;
    }

    int OtherMap::getAxesValue(engine::input::Keys key)
    {
        return test[key];
    }

    void OtherMap::update()
    {
        auto it = test.begin();
        while (it != test.end()) {
            it = test.erase(it);
        }
    }

    bool OtherMap::axisChanged(engine::input::Keys key) {
        if(test[key] == 0){
            return false;
        }else{
            return true;
        }
    }
}
}