
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// ========================================
// TUFFO MOD - PAINEL PRINCIPAL
// ========================================

class TuffoPanel : public CCLayer {
protected:
    int m_tab = 0;
    CCMenu* m_options = nullptr;
    CCLabelBMFont* m_title = nullptr;

    bool init() {
        if (!CCLayer::init())
            return false;

        auto win = CCDirector::sharedDirector()->getWinSize();

        // Fundo escuro
        auto dim = CCLayerColor::create(
            ccc4(0, 0, 0, 170)
        );
        dim->setContentSize(win);
        dim->setPosition(CCPointZero);
        this->addChild(dim);

        // Painel
        auto panel = CCLayerColor::create(
            ccc4(35, 25, 65, 255),
            420,
            260
        );

        panel->setPosition({
            (win.width - 420) / 2,
            (win.height - 260) / 2
        });

        this->addChild(panel);

        // Título
        m_title = CCLabelBMFont::create(
            "TUFFO MOD",
            "bigFont.fnt"
        );

        m_title->setPosition({
            win.width / 2,
            win.height / 2 + 105
        });

        m_title->setScale(0.7f);
        this->addChild(m_title);

        // Abas laterais
        auto tabs = CCMenu::create();
        tabs->setPosition(CCPointZero);
        this->addChild(tabs);

        const char* names[] = {
            "PLAYER",
            "GAMEPLAY",
            "INTERFACE",
            "MISC"
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

        // Botão fechar
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
            "PLAYER",
            "GAMEPLAY",
            "INTERFACE",
            "MISC"
        };

        m_title->setString(titles[m_tab]);

        // PLAYER
        if (m_tab == 0) {
            addOption(
                "Visual Effects",
                "visual-effects",
                4,
                35
            );
        }

        // GAMEPLAY
        if (m_tab == 1) {
            addOption(
                "Show FPS",
                "show-fps",
                5,
                55
            );

            addOption(
                "Attempts",
                "show-attempts",
                6,
                5
            );
        }

        // INTERFACE
        if (m_tab == 2) {
            addOption(
                "Custom Interface",
                "custom-interface",
                7,
                55
            );

            addOption(
                "Quick Options",
                "quick-options",
                8,
                5
            );

            addOption(
                "Menu Button",
                "show-menu-button",
                9,
                -45
            );
        }

        // MISC
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
            "", "", "", "",
            "visual-effects",
            "show-fps",
            "show-attempts",
            "custom-interface",
            "quick-options",
            "show-menu-button"
        };

        if (tag < 4 || tag > 9)
            return;

        auto key = keys[tag];

        bool current =
            Mod::get()->getSettingValue<bool>(key);

        Mod::get()->setSettingValue<bool>(
            key,
            !current
        );

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

// ========================================
// BOTÃO TUFFO NO MENU PRINCIPAL
// ========================================

class $modify(TuffoMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        if (!Mod::get()->getSettingValue<bool>(
            "show-menu-button"
        )) {
            return true;
        }

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

// ========================================
// GAMEPLAY - FPS E TENTATIVAS
// ========================================

class $modify(TuffoPlayLayer, PlayLayer) {
    struct Fields {
        CCLabelBMFont* fpsLabel = nullptr;
        CCLabelBMFont* attemptsLabel = nullptr;

        float elapsed = 0.f;
        float attemptsTimer = 0.f;
        int frames = 0;
    };

    bool init(
        GJGameLevel* level,
        bool dontCreateObjects
    ) {
        if (!PlayLayer::init(level, dontCreateObjects))
            return false;

        auto win = CCDirector::sharedDirector()->getWinSize();

        // Contador de FPS
        m_fields->fpsLabel = CCLabelBMFont::create(
            "FPS: --",
            "bigFont.fnt"
        );

        m_fields->fpsLabel->setScale(0.45f);
        m_fields->fpsLabel->setAnchorPoint({0.f, 1.f});

        m_fields->fpsLabel->setPosition({
            12.f,
            win.height - 12.f
        });

        this->addChild(m_fields->fpsLabel, 999);

        // Contador de tentativas
        m_fields->attemptsLabel = CCLabelBMFont::create(
            "ATTEMPTS: 0",
            "bigFont.fnt"
        );

        m_fields->attemptsLabel->setScale(0.45f);
        m_fields->attemptsLabel->setAnchorPoint({0.f, 1.f});

        m_fields->attemptsLabel->setPosition({
            12.f,
            win.height - 32.f
        });

        this->addChild(m_fields->attemptsLabel, 999);

        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        // --------------------
        // FPS
        // --------------------

        auto fps = m_fields->fpsLabel;

        if (fps) {
            bool enabled =
                Mod::get()->getSettingValue<bool>(
                    "show-fps"
                );

            fps->setVisible(enabled);

            if (enabled && dt > 0.f) {
                m_fields->elapsed += dt;
                m_fields->frames++;

                if (m_fields->elapsed >= 0.5f) {
                    float value =
                        m_fields->frames /
                        m_fields->elapsed;

                    auto text = fmt::format(
                        "FPS: {:.0f}",
                        value
                    );

                    fps->setString(text.c_str());

                    m_fields->elapsed = 0.f;
                    m_fields->frames = 0;
                }
            }
        }

        // --------------------
        // TENTATIVAS
        // --------------------

        auto attempts = m_fields->attemptsLabel;

        if (attempts) {
            bool enabled =
                Mod::get()->getSettingValue<bool>(
                    "show-attempts"
                );

            attempts->setVisible(enabled);

            if (enabled) {
                m_fields->attemptsTimer += dt;

                if (m_fields->attemptsTimer >= 0.25f) {
                    auto text = fmt::format(
                        "ATTEMPTS: {}",
                        this->m_attempts
                    );

                    attempts->setString(text.c_str());

                    m_fields->attemptsTimer = 0.f;
                }
            }
        }
    }
};
