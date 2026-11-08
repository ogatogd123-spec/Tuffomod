
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class TuffoPanel : public CCLayer {
protected:
    int m_tab = 0;
    CCMenu* m_options = nullptr;
    CCLabelBMFont* m_title = nullptr;

    bool init() {
        if (!CCLayer::init())
            return false;

        auto win = CCDirector::sharedDirector()->getWinSize();

        auto dim = CCLayerColor::create(ccc4(0, 0, 0, 170));
        dim->setContentSize(win);
        dim->setPosition(CCPointZero);
        this->addChild(dim);

        auto panel = CCLayerColor::create(
            ccc4(35, 25, 65, 255), 420, 260
        );
        panel->setPosition({
            (win.width - 420) / 2,
            (win.height - 260) / 2
        });
        this->addChild(panel);

        auto title = CCLabelBMFont::create(
            "TUFFO MOD", "bigFont.fnt"
        );
        title->setPosition({win.width / 2, win.height / 2 + 105});
        title->setScale(0.7f);
        this->addChild(title);

        auto tabs = CCMenu::create();
        tabs->setPosition(CCPointZero);
        this->addChild(tabs);

        const char* names[] = {
            "PLAYER", "GAMEPLAY", "INTERFACE", "MISC"
        };

        for (int i = 0; i < 4; i++) {
            auto item = CCMenuItemSpriteExtra::create(
                ButtonSprite::create(names[i]),
                this,
                menu_selector(TuffoPanel::onTab)
            );

            item->setTag(i);
            item->setPosition({
                win.width / 2 - 145,
                win.height / 2 + 55 - i * 48
            });
            tabs->addChild(item);
        }

        auto close = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("CLOSE"),
            this,
            menu_selector(TuffoPanel::onClose)
        );

        auto closeMenu = CCMenu::create(close, nullptr);
        closeMenu->setPosition({
            win.width / 2 + 155,
            win.height / 2 - 105
        });
        this->addChild(closeMenu);

        m_title = title;
        refreshOptions();

        return true;
    }

    void addOption(
        const char* label,
        const char* setting,
        int tag,
        float y
    ) {
        bool enabled =
            Mod::get()->getSettingValue<bool>(setting);

        auto text = fmt::format(
            "{}: {}",
            label,
            enabled ? "ON" : "OFF"
        );

        auto item = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(text.c_str()),
            this,
            menu_selector(TuffoPanel::onToggle)
        );

        item->setTag(tag);
        item->setPosition({100, y});
        m_options->addChild(item);
    }

    void refreshOptions() {
        if (m_options) {
            m_options->removeFromParent();
            m_options = nullptr;
        }

        auto win = CCDirector::sharedDirector()->getWinSize();

        m_options = CCMenu::create();
        m_options->setPosition({
            win.width / 2 + 35,
            win.height / 2
        });
        this->addChild(m_options);

        const char* titles[] = {
            "PLAYER", "GAMEPLAY", "INTERFACE", "MISC"
        };

        m_title->setString(titles[m_tab]);

        if (m_tab == 0) {
            addOption("Visual Effects", "visual-effects", 4, 35);
        }

        if (m_tab == 1) {
            addOption("Show FPS", "show-fps", 5, 55);
            addOption("Attempts", "show-attempts", 6, 5);
        }

        if (m_tab == 2) {
            addOption("Custom Interface", "custom-interface", 7, 55);
            addOption("Quick Options", "quick-options", 8, 5);
            addOption("Menu Button", "show-menu-button", 9, -45);
        }

        if (m_tab == 3) {
            auto info = CCLabelBMFont::create(
                "TUFFO MOD v1.0\nMade for GD 2.2091",
                "bigFont.fnt"
            );
            info->setPosition({100, 25});
            info->setScale(0.45f);
            m_options->addChild(info);
        }
    }

    void onTab(CCObject* sender) {
        m_tab = sender->getTag();
        refreshOptions();
    }

    void onToggle(CCObject* sender) {
        int tag = sender->getTag();

        const char* keys[] = {
            "", "", "", "", "visual-effects",
            "show-fps", "show-attempts",
            "custom-interface", "quick-options",
            "show-menu-button"
        };

        if (tag < 4 || tag > 9)
            return;

        auto key = keys[tag];
        bool current = Mod::get()->getSettingValue<bool>(key);

        Mod::get()->setSettingValue<bool>(key, !current);

        refreshOptions();
    }

    void onClose(CCObject*) {
        this->removeFromParent();
    }

public:
    static TuffoPanel* create() {
        auto ret = new TuffoPanel();

        if (ret->init()) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};

class $modify(TuffoMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        if (!Mod::get()->getSettingValue<bool>("show-menu-button"))
            return true;

        auto menu = CCMenu::create();

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("TUFFO"),
            this,
            menu_selector(TuffoMenuLayer::openTuffo)
        );

        menu->addChild(button);

        auto win = CCDirector::sharedDirector()->getWinSize();

        menu->setPosition({
            win.width * 0.18f,
            win.height * 0.28f
        });

        this->addChild(menu, 100);

        return true;
    }

    void openTuffo(CCObject*) {
        auto panel = TuffoPanel::create();

        if (panel) {
            CCDirector::sharedDirector()
                ->getRunningScene()
                ->addChild(panel, 999);
        }
    }
};

