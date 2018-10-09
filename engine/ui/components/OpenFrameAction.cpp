#include "OpenFrameAction.h"

namespace engine {
namespace ui {
    void OpenFrameAction::execute()
    {
        m_system.push(m_targetFrame);
    }
}
}