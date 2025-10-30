#include "precomp.h"
#include "Audio.h"

void Audio::Init()
{
    if (ma_engine_init(nullptr, &engine) != MA_SUCCESS)
    {
        printf("Engine pointer: %p\n", static_cast<void*>(&engine));
        printf("Engine init failed.\n");
        return;
    }

    //  Muziek
    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/music/menu.mp3", MA_SOUND_FLAG_STREAM, NULL, NULL, &musicMenu) == MA_SUCCESS)
    {
        ma_sound_set_looping(&musicMenu, MA_TRUE);
        //ma_sound_start(&musicMenu);
    }
    else printf("Failed to load menu.mp3\n");

    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/music/game_01.mp3", MA_SOUND_FLAG_STREAM, NULL, NULL, &musicLvl1) == MA_SUCCESS)
    {
        //ma_sound_set_looping(&musicLvl1, MA_TRUE);
        //ma_sound_start(&musicLvl1);
    }
    else printf("Failed to load game_01.mp3\n");

    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/music/game_02.mp3", MA_SOUND_FLAG_STREAM, NULL, NULL, &musicLvl2) == MA_SUCCESS)
    {
        ma_sound_set_looping(&musicLvl2, MA_TRUE);
        //ma_sound_start(&musicLvl2);
    }
    else printf("Failed to load game_02.mp3\n");

    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/music/game_over.mp3", MA_SOUND_FLAG_STREAM, NULL, NULL, &musicGameOver) == MA_SUCCESS)
    {
        ma_sound_set_looping(&musicGameOver, MA_TRUE);
        //ma_sound_start(&musicGameOver);
    }
    else printf("Failed to load game_over.mp3\n");

    //  Sound effects
    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/sfx/explosion.wav", 0, NULL, NULL, &explosionSound) != MA_SUCCESS)
        printf("Failed to load explosion.wav\n");

    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/sfx/place_bomb.wav", 0, NULL, NULL, &placeBombSound) != MA_SUCCESS)
        printf("Failed to load place_bomb.wav\n");

    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/sfx/player_death.wav", 0, NULL, NULL, &playerDeathSound) != MA_SUCCESS)
        printf("Failed to load player_death.wav\n");

    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/sfx/walk_hor.wav", 0, NULL, NULL, &walkHorSound) != MA_SUCCESS)
        printf("Failed to load walk_hor.wav\n");

    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/sfx/walk_ver.wav", 0, NULL, NULL, &walkVerSound) != MA_SUCCESS)
        printf("Failed to load walk_ver.wav\n");

    if (ma_sound_init_from_file(&engine, "assets/Bomberman Audio/sfx/game_over.wav", 0, NULL, NULL, &gameOverSound) != MA_SUCCESS)
        printf("Failed to load game_over.wav\n");

}


void Audio::Shutdown()
{
	ma_sound_uninit(&musicLvl1);
	ma_sound_uninit(&musicLvl2);
	ma_sound_uninit(&musicMenu);
	ma_sound_uninit(&musicGameOver);

	ma_sound_uninit(&explosionSound);
	ma_sound_uninit(&placeBombSound);
	ma_sound_uninit(&playerDeathSound);
	ma_sound_uninit(&walkHorSound);
	ma_sound_uninit(&walkVerSound);
	ma_sound_uninit(&gameOverSound);
}

void Audio::Play(ma_sound& sound)
{
    ma_result theResult = ma_sound_start(&sound);
    if (theResult != MA_SUCCESS) printf("Failed to play sound: %d\n", theResult);
}

void Audio::Stop(ma_sound& sound)
{
    ma_result theResult = ma_sound_stop(&sound);
    if (theResult != MA_SUCCESS) printf("Failed to stop sound: %d\n", theResult);
}