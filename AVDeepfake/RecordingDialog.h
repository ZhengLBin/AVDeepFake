#ifndef RECORDINGDIALOG_H
#define RECORDINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QElapsedTimer>
#include <QAudioRecorder>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class RecordingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordingDialog(QWidget* parent = nullptr);
    QString getSavedFilePath() const { return savedFilePath; }

signals:
    void recordingSaved(const QString& filePath);

private slots:
    void toggleRecording();
    void stopRecording();
    void updateTimer();

private:
    void initAudioRecorder();
    void startRecording();
    void pauseRecording();

    QAudioRecorder* audioRecorder;
    QTimer* timer;
    QElapsedTimer recordTimer;

    QLabel* timeLabel;
    QPushButton* toggleButton;
    QPushButton* stopButton;

    QString savedFilePath;
    bool isRecording = false;
};

#endif // RECORDINGDIALOG_H