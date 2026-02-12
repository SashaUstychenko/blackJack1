#include "sound.h"


Sound::Sound(QObject *parent)
{
    cardSoundPlayer.setAudioOutput(&audioOutput);
    audioOutput.setVolume(1.0);
    cardSoundPlayer.setSource(QUrl("qrc:/sound/swish.m4a"));
    cardSoundPlayer.setLoops(QMediaPlayer::Once);

    backgroundSound.setAudioOutput(&audioOutput1);
    audioOutput1.setVolume(0.3);
    backgroundSound.setSource(QUrl("qrc:/sound/fon.mp3"));
    backgroundSound.setLoops(QMediaPlayer::Infinite);

    soundClick.setAudioOutput(&audioOutput2);
    audioOutput2.setVolume(1.0);
    backgroundSound.setSource(QUrl("qrc:/sound/button1.mp3"));
    backgroundSound.setLoops(QMediaPlayer::Once);



}

void Sound::playCardSound()
{
    cardSoundPlayer.play();

}

void Sound::backgroundSoundF()
{
    backgroundSound.play();
}

void Sound::clickButton()
{
    soundClick.play();
}

void Sound::setBackgroundVolume(qreal volume)
{
    volume = qBound(0.0, volume, 1.0);
    audioOutput1.setVolume(volume);
}

void Sound::stopBackgroundSound()
{
    backgroundSound.stop();
}

void Sound::stopcardSound()
{
    cardSoundPlayer.stop();
}

void Sound::stopClicSound()
{
    soundClick.stop();
}
