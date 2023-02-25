#include "main.hpp"
#include "qounter.hpp"

static ModInfo modInfo;

Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;

    getLogger().info("Completed setup!");
}

extern "C" void load() {
    il2cpp_functions::Init();

    Modloader::requireMod("Qounters-");
    getLogger().info("Registering qounter!");
    VSQ::Register();
}
