#include "main.hpp"
#include "qounter.hpp"

#include <sstream>
#include <iomanip>

#include "UnityEngine/UI/Image_Origin360.hpp"
#include "System/Action.hpp"

DEFINE_TYPE(VisualScoreQounter, Qounter);

using namespace QountersMinus;

bool VSQ::Enabled = false;
int VSQ::Position = static_cast<int>(QounterPosition::BelowEnergy);
float VSQ::Distance = 1.0f;
bool VSQ::HideBaseGame = true;
bool VSQ::RingIsNextRankColor = true;
float VSQ::RingScale = 1;
int VSQ::DecimalPlaces = 0;
float VSQ::WholeFontSize = 7;
float VSQ::DecimalFontSize = 3.5;
float VSQ::WholeOffsetX = 0;
float VSQ::WholeOffsetY = 0.7;
float VSQ::DecimalOffsetX = 0;
float VSQ::DecimalOffsetY = -3;

using Color = UnityEngine::Color;
Color VSQ::Color100 = {1, 1, 1, 1};
Color VSQ::Color99 = {1, 1, 0.6885, 1};
Color VSQ::Color98 = {0.1372, 0.9527, 0.2503, 1};
Color VSQ::Color97 = {0.9108, 1, 0, 1};
Color VSQ::Color96 = {1, 0.5137, 0.0706, 1};
Color VSQ::Color95 = {0.9706, 0.7994, 0.9706, 1};
Color VSQ::Color94 = {0.4727, 0.0253, 0.8719, 1};
Color VSQ::Color93 = {0.9054, 1, 1, 1};
Color VSQ::Color92 = {0.3498, 1, 0.3794, 1};
Color VSQ::Color91 = {0.4745, 0.6598, 1, 1};
Color VSQ::Color90 = {0.7176, 0.0984, 1, 1};
Color VSQ::Color89 = {1, 1, 1, 1};
Color VSQ::Color88 = {1, 1, 1, 1};
Color VSQ::Color85 = {0.5, 0.5, 0.5, 1};
Color VSQ::Color80 = {0.5, 0.5, 0.5, 1};
Color VSQ::Color65 = {0, 1, 0, 1};
Color VSQ::Color50 = {1, 0.92, 0.016, 1};
Color VSQ::Color35 = {1, 0.5, 0, 1};
Color VSQ::Color20 = {1, 0, 0, 1};
Color VSQ::Color0 = {1, 0, 0, 1};

#define RegisterColorSegment(num) \
    QounterRegistry::RegisterConfig<VSQ>({ \
        .ptr = &Color##num, \
        .field = "Color"#num, \
        .displayName = #num" Color", \
        .helpText = "What color to display for "#num"%", \
        .type = QounterRegistry::ConfigType::Color, \
    });

void VSQ::Register() {
    QounterRegistry::Register<VSQ>("Visual Score", "Visual Score Qounter", "VisualScoreConfig");
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &HideBaseGame,
        .field = "HideBaseGame",
        .displayName = "Hide Base Game Score",
        .helpText = "Hides the base game rank and percentage counter",
        .type = QounterRegistry::ConfigType::Bool,
    });
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &RingIsNextRankColor,
        .field = "RingIsNextRankColor",
        .displayName = "Ring Shows Next Rank Color",
        .helpText = "Makes the ring around the accuracy numbers display the color of the next rank instead of the current",
        .type = QounterRegistry::ConfigType::Bool,
    });
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &RingScale,
        .field = "RingScale",
        .displayName = "Ring Scale",
        .helpText = "Adjusts the size of the ring by this multiple",
        .type = QounterRegistry::ConfigType::Float,
        .floatMin = 0.5,
        .floatMax = 1.5,
        .floatStep = 0.1,
    });
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &DecimalPlaces,
        .field = "DecimalPlaces",
        .displayName = "Decimal Places",
        .helpText = "How many decimals should be shown underneath the percentage?",
        .type = QounterRegistry::ConfigType::Int,
        .intMin = 0,
        .intMax = 4,
    });
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &WholeFontSize,
        .field = "WholeFontSize",
        .displayName = "Whole Number Font Size",
        .helpText = "Adjusts the size of the text that displays the whole number part of the percentage",
        .type = QounterRegistry::ConfigType::Float,
        .floatMin = 2,
        .floatMax = 12,
        .floatStep = 0.5,
    });
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &DecimalFontSize,
        .field = "DecimalFontSize",
        .displayName = "Decimal Font Size",
        .helpText = "Adjusts the size of the text that displays the decimal part of the percentage",
        .type = QounterRegistry::ConfigType::Float,
        .floatMin = 1,
        .floatMax = 6,
        .floatStep = 0.25,
    });
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &WholeOffsetX,
        .field = "WholeOffsetX",
        .displayName = "Whole Number X Offset",
        .helpText = "Moves the whole number of the accuracy percentage left/right",
        .type = QounterRegistry::ConfigType::Float,
        .floatMin = -5,
        .floatMax = 5,
        .floatStep = 0.2,
    });
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &WholeOffsetY,
        .field = "WholeOffsetY",
        .displayName = "Whole Number Y Offset",
        .helpText = "Moves the whole number of the accuracy percentage up/down",
        .type = QounterRegistry::ConfigType::Float,
        .floatMin = -5,
        .floatMax = 5,
        .floatStep = 0.2,
    });
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &DecimalOffsetX,
        .field = "DecimalOffsetX",
        .displayName = "Decimal X Offset",
        .helpText = "Moves the decimals of the accuracy percentage left/right",
        .type = QounterRegistry::ConfigType::Float,
        .floatMin = -5,
        .floatMax = 5,
        .floatStep = 0.2,
    });
    QounterRegistry::RegisterConfig<VSQ>({
        .ptr = &DecimalOffsetY,
        .field = "DecimalOffsetY",
        .displayName = "Decimal Y Offset",
        .helpText = "Moves the decimals of the accuracy percentage up/down",
        .type = QounterRegistry::ConfigType::Float,
        .floatMin = -5,
        .floatMax = 5,
        .floatStep = 0.2,
    });
    RegisterColorSegment(100)
    RegisterColorSegment(99)
    RegisterColorSegment(98)
    RegisterColorSegment(97)
    RegisterColorSegment(96)
    RegisterColorSegment(95)
    RegisterColorSegment(94)
    RegisterColorSegment(93)
    RegisterColorSegment(92)
    RegisterColorSegment(91)
    RegisterColorSegment(90)
    RegisterColorSegment(89)
    RegisterColorSegment(88)
    RegisterColorSegment(85)
    RegisterColorSegment(80)
    RegisterColorSegment(65)
    RegisterColorSegment(50)
    RegisterColorSegment(35)
    RegisterColorSegment(20)
    RegisterColorSegment(0)
}

void VSQ::Start() {
    auto child = UnityEngine::GameObject::New_ctor("VisualScoreQounter")->get_transform();
    child->SetParent(gameObject->get_transform(), false);
    child->set_localScale({10, 10, 10});

    wholeText = CreateBasicTitle("0");
    wholeText->get_transform()->SetParent(child, false);
    wholeText->set_fontSize(WholeFontSize);
    wholeText->get_rectTransform()->set_anchoredPosition({WholeOffsetX, WholeOffsetY});

    decimalText = CreateBasicTitle("0");
    decimalText->get_transform()->SetParent(child, false);
    decimalText->set_fontSize(DecimalFontSize);
    decimalText->get_rectTransform()->set_anchoredPosition({DecimalOffsetX, DecimalOffsetY});

    static UnityEngine::Vector3 baseRingSize({1.175, 1.175, 1.175});
    auto ringSprite = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Sprite*>().First([](auto i) { return i->get_name() == "Circle"; });

    auto bgRing = CreateRing(child, ringSprite);
    bgRing->CrossFadeAlpha(0.05, 1, false);
    bgRing->get_transform()->set_localScale(baseRingSize * RingScale / 10);

    ringImage = CreateRing(child, ringSprite);
    ringImage->set_type(UnityEngine::UI::Image::Type::Filled);
    ringImage->set_fillMethod(UnityEngine::UI::Image::FillMethod::Radial360);
    ringImage->set_fillOrigin(UnityEngine::UI::Image::Origin360::Top);
    ringImage->set_fillClockwise(true);
    ringImage->set_fillAmount(1);
    ringImage->get_transform()->set_localScale(baseRingSize * RingScale / 10);

    bool scoreQounterEnabled = *(bool*) QounterRegistry::registry[{"QountersMinus::Qounters", "ScoreQounter"}].staticFieldRefs["Enabled"];
    if(HideBaseGame && !scoreQounterEnabled) {
        auto scoreUIController = refs->coreGameHUDController->GetComponentInChildren<GlobalNamespace::ScoreUIController*>();
        UnityEngine::Object::Destroy(scoreUIController->get_gameObject());
        UnityEngine::Object::Destroy(refs->coreGameHUDController->relativeScoreGO);
        UnityEngine::Object::Destroy(refs->coreGameHUDController->immediateRankGO);
    }

    // OnScoreUpdated is cool but this might improve compatiblity with anything messing with the regular score panel
    refs->relativeScoreAndImmediateRankCounter->add_relativeScoreOrImmediateRankDidChangeEvent(il2cpp_utils::MakeDelegate<System::Action*>(
        classof(System::Action*), this, +[](VSQ* self) {
            self->UpdateScore();
        }
    ));
    UpdateScore();
}

HMUI::ImageView* VSQ::CreateRing(UnityEngine::Transform* parent, UnityEngine::Sprite* sprite) {
    using namespace UnityEngine;
    auto gameObject = GameObject::New_ctor("VisualScoreQounterRing");
    auto image = gameObject->AddComponent<HMUI::ImageView*>();
    auto noGlowMaterial = Resources::FindObjectsOfTypeAll<Material*>().First([](auto m) { return m->get_name() == "UINoGlow"; });
    image->set_material(noGlowMaterial);
    image->get_transform()->SetParent(parent, false);
    image->set_sprite(sprite);
    return image;
}

Color VSQ::GetColorForPercent(float score) {
    if(score >= 1)
        return Color100;
    if(score >= 0.99)
        return Color99;
    if(score >= 0.98)
        return Color98;
    if(score >= 0.97)
        return Color97;
    if(score >= 0.96)
        return Color96;
    if(score >= 0.95)
        return Color95;
    if(score >= 0.94)
        return Color94;
    if(score >= 0.93)
        return Color93;
    if(score >= 0.92)
        return Color92;
    if(score >= 0.91)
        return Color91;
    if(score >= 0.90)
        return Color90;
    if(score >= 0.89)
        return Color89;
    if(score >= 0.88)
        return Color88;
    if(score >= 0.85)
        return Color85;
    if(score >= 0.80)
        return Color80;
    if(score >= 0.65)
        return Color65;
    if(score >= 0.50)
        return Color50;
    if(score >= 0.35)
        return Color35;
    if(score >= 0.20)
        return Color20;
    return Color0;
}

std::string VSQ::DecimalString(float remainder) {
    if(DecimalPlaces == 0)
        return "";
    std::stringstream stream;
    stream << std::fixed << std::setprecision(DecimalPlaces) << abs(remainder);
    std::string ret = stream.str();
    return ret.substr(2);
}

void VSQ::UpdateScore() {
    float score = refs->relativeScoreAndImmediateRankCounter->relativeScore;

    Color rankColor = GetColorForPercent(score);
    wholeText->set_color(rankColor);
    decimalText->set_color(rankColor);
    int percent = score * 100;
    float remainder = (score * 100) - percent;
    wholeText->set_text(std::to_string(percent));
    decimalText->set_text(DecimalString(remainder));

    Color ringColor = RingIsNextRankColor ? GetColorForPercent(score + 0.01) : rankColor;
    ringImage->set_color(ringColor);
    ringImage->set_fillAmount(remainder);
    ringImage->SetVerticesDirty();
}
