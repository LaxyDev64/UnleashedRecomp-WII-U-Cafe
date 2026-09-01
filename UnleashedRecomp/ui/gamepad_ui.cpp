#include "gamepad_ui.h"
#include <gpu/imgui/imgui_snapshot.h>
#include <gpu/video.h>
#include <hid/hid.h>
#include <locale/locale.h>
#include <ui/button_guide.h>
#include <ui/imgui_utils.h>
#include <app.h>
#include <exports.h>
#include <decompressor.h>

// TODO: estos assets vienen de "wii u gamepad ui/Buttons" y "medal solar"
// como PNG sueltos. Todavia no pasaron por el pipeline de tools/file_to_c
// (el mismo que genera res/images/achievements_menu/trophy.dds.h). Hasta que
// eso este hecho, dejamos los includes comentados y el Draw() usa
// placeholders (rectangulos de color) para poder iterar el layout ya mismo.

// #include <res/images/gamepad_ui/controller_diagram.dds.h>
// #include <res/images/gamepad_ui/medal_solar_00.dds.h>
// ... (30 frames de la animacion de giro, sprite-0065 a sprite-0094)

static EGamePadScreen g_currentScreen = EGamePadScreen::ControlsLegend;

static ImFont* g_fntSeurat;

// Animacion de giro de la Medalla del Sol: 30 frames, se angosta de 58px
// a 9px (canto) y vuelve a ensanchar - rotacion completa sobre el eje Y.
constexpr int MEDAL_SPIN_FRAME_COUNT = 30;
constexpr double MEDAL_SPIN_FPS = 24.0;

static int GetMedalSpinFrame(double time)
{
    double loopTime = fmod(time, MEDAL_SPIN_FRAME_COUNT / MEDAL_SPIN_FPS);
    return int(loopTime * MEDAL_SPIN_FPS) % MEDAL_SPIN_FRAME_COUNT;
}

static void DrawControlsLegendScreen()
{
    ImGui::TextUnformatted("Controles");
    ImGui::Separator();

    // Placeholder hasta tener los assets compilados: en el layout final,
    // esto dibuja sprite-0036.png (diagrama completo del control) con los
    // callouts localizados por idioma, tal como se ve en la referencia
    // original de "Buttons/".
    ImGui::TextWrapped(
        "Diagrama del control (sprite-0036) va aca. Los sprites 0053-0056 "
        "son los botones A/B/X/Y sueltos, reusables via EButtonIcon si "
        "en vez de un diagrama completo preferimos una lista simple.");

    ImGui::Spacing();

    // Ejemplo reusando el sistema de iconos que YA existe en el juego
    // (button_guide.h) en vez de nuestros sprites nuevos, para las
    // entradas simples tipo "A: Confirmar".
    struct ControlHint { EButtonIcon icon; const char* label; };
    static const ControlHint hints[] =
    {
        { EButtonIcon::A, "Confirmar / Interactuar" },
        { EButtonIcon::B, "Cancelar / Volver" },
        { EButtonIcon::X, "Accion especial" },
        { EButtonIcon::Y, "Cambiar de pantalla" },
    };

    for (auto& hint : hints)
    {
        // DrawButtonIcon() no existe todavia como funcion publica reusable
        // fuera de ButtonGuide - si queremos llamarla desde aca hay que
        // exponerla (o duplicar el pequeno switch de icono -> textura).
        ImGui::BulletText("%s", hint.label);
    }
}

static void DrawCollectiblesScreen()
{
    ImGui::TextUnformatted("Medallas del Sol");
    ImGui::Separator();

    int frame = GetMedalSpinFrame(ImGui::GetTime());

    // Placeholder: en el layout final esto es
    // g_medalSolarFrames[frame]->descriptorIndex via drawList->AddImage(...)
    ImGui::Text("Frame de animacion actual: %02d / %02d", frame, MEDAL_SPIN_FRAME_COUNT - 1);
    ImGui::TextWrapped(
        "Reemplazar por drawList->AddImage() con la textura del frame "
        "correspondiente una vez compilados los 30 sprites de 'medal solar/'.");

    ImGui::Spacing();
    ImGui::Text("Progreso: %d / 7 medallas obtenidas", 0); // TODO: conectar a save data real
}

void GamePadUI::Init()
{
    g_fntSeurat = ImFontAtlasSnapshot::GetFont("FOT-SeuratPro-M.otf");

    // TODO: cargar texturas via LOAD_ZSTD_TEXTURE una vez existan los
    // headers generados por tools/file_to_c, por ejemplo:
    // g_upControllerDiagram = LOAD_ZSTD_TEXTURE(g_controller_diagram);
    // for (int i = 0; i < MEDAL_SPIN_FRAME_COUNT; i++)
    //     g_medalSolarFrames[i] = LOAD_ZSTD_TEXTURE(g_medal_solar_frames[i]);
}

void GamePadUI::Draw()
{
    if (!s_isVisible)
        return;

    // NOTA IMPORTANTE: por ahora esto dibuja en una ventana ImGui normal
    // (contexto compartido con el juego) solo para poder iterar el layout
    // en PC. Cuando exista GamePadRenderTarget, este bloque se reemplaza
    // por render a la textura offscreen 854x480 - la logica de las
    // funciones DrawControlsLegendScreen()/DrawCollectiblesScreen() de
    // abajo no deberia necesitar cambios.
    ImGui::SetNextWindowSize(ImVec2(854, 480), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("GamePad Preview (DEBUG)", &s_isVisible))
    {
        if (ImGui::Button("< Controles"))
            SetScreen(EGamePadScreen::ControlsLegend);

        ImGui::SameLine();

        if (ImGui::Button("Coleccionables >"))
            SetScreen(EGamePadScreen::Collectibles);

        ImGui::Spacing();

        switch (g_currentScreen)
        {
        case EGamePadScreen::ControlsLegend:
            DrawControlsLegendScreen();
            break;
        case EGamePadScreen::Collectibles:
            DrawCollectiblesScreen();
            break;
        }
    }

    ImGui::End();
}

void GamePadUI::Open(EGamePadScreen screen)
{
    s_isVisible = true;
    g_currentScreen = screen;
}

void GamePadUI::Close()
{
    s_isVisible = false;
}

void GamePadUI::SetScreen(EGamePadScreen screen)
{
    g_currentScreen = screen;
}

EGamePadScreen GamePadUI::GetScreen()
{
    return g_currentScreen;
}
