#pragma once

#include "qounters-minus/shared/QounterRegistry.hpp"

DECLARE_CLASS_CUSTOM(VisualScoreQounter, Qounter, QountersMinus::Qounter,
    static bool Enabled;
    static int Position;
    static float Distance;
    static bool HideBaseGame;
    static bool RingIsNextRankColor;
    static float RingScale;
    static int DecimalPlaces;
    static float WholeFontSize;
    static float DecimalFontSize;
    static float WholeOffsetX;
    static float WholeOffsetY;
    static float DecimalOffsetX;
    static float DecimalOffsetY;

    using Color = UnityEngine::Color;
    static Color Color100, Color99,  Color98,
                 Color97,  Color96,  Color95,
                 Color94,  Color93,  Color92,
                 Color91,  Color90,  Color89,
                 Color88,  Color85,  Color80,
                 Color65,  Color50,  Color35,
                 Color20,  Color0;

    DECLARE_DEFAULT_CTOR();
    DECLARE_STATIC_METHOD(void, Register);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, UpdateScore);

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, wholeText);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, decimalText);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, ringImage);

    private:
    HMUI::ImageView* CreateRing(UnityEngine::Transform* parent, UnityEngine::Sprite* sprite);
    Color GetColorForPercent(float score);
    std::string DecimalString(float remainder);
)

using VSQ = VisualScoreQounter::Qounter;
