#ifndef F10700D3_2D82_4684_8EA3_BF404D588995
#define F10700D3_2D82_4684_8EA3_BF404D588995
#include "module/SwitchModule.h"
#include "module/RelayModule.h"
#include "library/Logger/Logger.h"
class RestoreButtonObserver
{
private:
    SwitchModule switchModule;
    RelayModule relayModule;

public:
    RestoreButtonObserver(SwitchModule &_switchModule, RelayModule &_relayModule) : switchModule(_switchModule), relayModule(_relayModule) {}
    void restoreIfButtonIsPressed();
};

#endif /* F10700D3_2D82_4684_8EA3_BF404D588995 */
