/**
 * @file        Processing.h
 * @brief
 * @author      Belinda Kneubühler
 * @date        2020-08-18
 * @copyright   GNU General Public License v2.0
 *
 * @details
 */
#ifndef OBP_PROCESSING_H
#define OBP_PROCESSING_H

#include <vector>
#include <comedilib.h>
#include <Iir.h>

#include "common.h"
#include "CppThread.h"
#include "Datarecord.h"
#include "ISubject.h"
#include "ComediHandler.h"
#include "OBPDetection.h"

// Class dependant configuration values:
#define MAX_PUMPUP 250
#define IIRORDER 4

//! The Processing class handles the data acquisition and processing.
/*!
 * What happens here ...
 */
class Processing : public CppThread, public ISubject{

    enum class ProcState {
        Config,
        Idle,
        Inflate,
        Deflate,
        Empty,
        Restults,
    };

public:
    explicit Processing(double fcLP = 10.0, double fcHP = 0.5);
    ~Processing() override;

    void stopThread();

    void startMeasurement();
    void stopMeasurement();
    inline ProcState getCurrentState() const;
    void setAmbientVoltage(double voltage);

    void setRatioSBP(double val);
    double getRatioSBP();
    void setRatioDBP(double val);
    double getRatioDBP();
    void setMinNbrPeaks(int val);
    int getMinNbrPeaks();
    void setPumpUpValue(int val);
    int getPumpUpValue();
    void resetConfigValues();


private:
    void run() override;
    static QString getFilename();
    void processSample(double newSample);
    [[nodiscard]] double getmmHgValue(double voltageValue) const;
    bool checkAmbient();
    std::vector<double> rawData;

    Iir::Butterworth::LowPass<IIRORDER> *iirLP;
    Iir::Butterworth::HighPass<IIRORDER> *iirHP;

    Datarecord *record;
    ComediHandler *comedi;
    OBPDetection *obpDetect;
    std::atomic<bool> bRunning; // process is running and displaying data on screen, but not necessary recording/measuring blood pressure it.
    std::atomic<bool> bMeasuring;
    ProcState currentState;

    /**
     * Important data acquisition values SI: 1mmHg = 133.322 Pa
     * 7.5006157584566 wiki: 7.5006157584
     */
    const double mmHg_per_kPa = 7.5006157584566; // literature
    const double kPa_per_mmHg = 0.133322;
    const double kPa_per_V = 50; // data sheet

    double sampling_rate;
    std::atomic<double> mmHgInflate = 180.0;
    double ambientVoltage = 0.7;
    double corrFactor = 2.6; // due to voltage divider

};


#endif //OBP_PROCESSING_H
