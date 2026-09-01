#pragma once

// Pantallas navegables de la tablet del GamePad.
// Se agregan mas adelante (MapView, Settings, etc). Empezamos con las dos
// para las que ya tenemos assets: leyenda de controles y coleccionables.
enum class EGamePadScreen
{
    ControlsLegend,
    Collectibles
};

class GamePadUI
{
public:
    inline static bool s_isVisible = false;

    static void Init();

    // Se llama una vez por frame. Hoy dibuja a una ventana ImGui normal
    // (visible en PC para debug/preview). El dia que exista el backend GX2,
    // este mismo Draw() se redirige a GamePadRenderTarget en vez de a una
    // ventana - la logica de layout no cambia.
    static void Draw();

    static void Open(EGamePadScreen screen = EGamePadScreen::ControlsLegend);
    static void Close();

    static void SetScreen(EGamePadScreen screen);
    static EGamePadScreen GetScreen();
};
