#ifndef SOUND_H
#define SOUND_H

#include <QAudioOutput>
#include <QObject>


#include <QMediaPlayer>
#include <QUrl>
class Sound :public QObject
{
        Q_OBJECT
private:
    QMediaPlayer cardSoundPlayer;
    QMediaPlayer backgroundSound;
    QMediaPlayer soundClick;

    QAudioOutput audioOutput;
    QAudioOutput audioOutput1;
    QAudioOutput audioOutput2;
public:
    explicit Sound(QObject *parent = nullptr);

    Q_INVOKABLE void playCardSound();
    Q_INVOKABLE void backgroundSoundF();
    Q_INVOKABLE void clickButton();
    Q_INVOKABLE void setBackgroundVolume(qreal volume);
    Q_INVOKABLE void stopBackgroundSound();
    Q_INVOKABLE void stopcardSound();
    Q_INVOKABLE void stopClicSound();
};

#endif // SOUND_H
