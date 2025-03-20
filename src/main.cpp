#include <Geode/Geode.hpp>

using namespace geode::prelude;
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class IconSwapMod : public Mod {
private:
    bool m_enabled = true;
    bool m_swapCube = true;
    bool m_swapShip = true;
    bool m_swapBall = true;
    bool m_swapUfo = true;
    bool m_swapWave = true;
    bool m_swapRobot = true;
    bool m_swapSpider = true;
    
    // Store the original icon IDs
    int m_originalCubeID = 1;
    int m_originalShipID = 1;
    int m_originalBallID = 1;
    int m_originalUfoID = 1;
    int m_originalWaveID = 1;
    int m_originalRobotID = 1;
    int m_originalSpiderID = 1;
    
    void randomizeIcon(int& iconID, int maxID) {
        // Store the original icon ID if it's not stored yet
        iconID = rand() % maxID + 1;
    }

public:
    IconSwapMod() {
        // Initialize random number generator
        srand(time(nullptr));
    }
    
    bool init() override {
        // Load settings from mod config
        m_enabled = Mod::get()->getSettingValue<bool>("enabled");
        m_swapCube = Mod::get()->getSettingValue<bool>("swap-cube");
        m_swapShip = Mod::get()->getSettingValue<bool>("swap-ship");
        m_swapBall = Mod::get()->getSettingValue<bool>("swap-ball");
        m_swapUfo = Mod::get()->getSettingValue<bool>("swap-ufo");
        m_swapWave = Mod::get()->getSettingValue<bool>("swap-wave");
        m_swapRobot = Mod::get()->getSettingValue<bool>("swap-robot");
        m_swapSpider = Mod::get()->getSettingValue<bool>("swap-spider");
        
        // Store original icon IDs when the mod initializes
        auto* gm = GameManager::get();
        m_originalCubeID = gm->getPlayerIconType();
        m_originalShipID = gm->getPlayerShipType();
        m_originalBallID = gm->getPlayerBallType();
        m_originalUfoID = gm->getPlayerUfoType();
        m_originalWaveID = gm->getPlayerWaveType();
        m_originalRobotID = gm->getPlayerRobotType();
        m_originalSpiderID = gm->getPlayerSpiderType();
        
        return true;
    }
};

class $modify(ModifiedPlayLayer, PlayLayer) {
    void resetLevel() {
        auto* mod = Mod::get<IconSwapMod>();
        auto* gm = GameManager::get();
        
        if (mod->getSettingValue<bool>("enabled")) {
            // Check if the player died (not a regular reset)
            if (m_isDead) {
                // Swap icons based on settings
                if (mod->getSettingValue<bool>("swap-cube"))
                    gm->setPlayerIconType(rand() % 150 + 1); // Approximate max cube ID
                
                if (mod->getSettingValue<bool>("swap-ship"))
                    gm->setPlayerShipType(rand() % 51 + 1); // Approximate max ship ID
                
                if (mod->getSettingValue<bool>("swap-ball"))
                    gm->setPlayerBallType(rand() % 43 + 1); // Approximate max ball ID
                
                if (mod->getSettingValue<bool>("swap-ufo"))
                    gm->setPlayerUfoType(rand() % 35 + 1); // Approximate max UFO ID
                
                if (mod->getSettingValue<bool>("swap-wave"))
                    gm->setPlayerWaveType(rand() % 35 + 1); // Approximate max wave ID
                
                if (mod->getSettingValue<bool>("swap-robot"))
                    gm->setPlayerRobotType(rand() % 26 + 1); // Approximate max robot ID
                
                if (mod->getSettingValue<bool>("swap-spider"))
                    gm->setPlayerSpiderType(rand() % 17 + 1); // Approximate max spider ID
            }
        }
        
        // Call the original function
        PlayLayer::resetLevel();
    }
};

// Register the mod
$on_mod(IconSwapMod) {
    // Set up mod events
    auto* gm = GameManager::get();
    
    // Reset to original icons when the mod is disabled
    if (!mod->getSettingValue<bool>("enabled")) {
        gm->setPlayerIconType(mod->m_originalCubeID);
        gm->setPlayerShipType(mod->m_originalShipID);
        gm->setPlayerBallType(mod->m_originalBallID);
        gm->setPlayerUfoType(mod->m_originalUfoID);
        gm->setPlayerWaveType(mod->m_originalWaveID);
        gm->setPlayerRobotType(mod->m_originalRobotID);
        gm->setPlayerSpiderType(mod->m_originalSpiderID);
    }
}