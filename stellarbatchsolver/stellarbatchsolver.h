#ifndef STELLARBATCHSOLVER_H
#define STELLARBATCHSOLVER_H

#include <QMainWindow>
#include <QApplication>
#include "structuredefinitions.h"
#include "ssolverutils/fileio.h"
#include "stellarsolver.h"
#include "wcsdata.h"
#include <QDir>

namespace Ui {

class StellarBatchSolver;
}

// This is a struct with the estimated Image Scales
typedef struct ImageScale
{
    double scale_low;
    double scale_high;
    ScaleUnits scale_units;

} ImageScale;

typedef struct Image
{
    QString fileName;
    FITSImage::Statistic stats;
    bool hasSolved = false;
    FITSImage::Solution solution;
    bool hasExtracted = false;
    bool hasHFRData = false;
    QList<FITSImage::Star> stars;
    QList<fileio::Record> m_HeaderRecords;
    QImage rawImage;
    bool hasWCSData = false;
    WCSData wcsData;

    uint8_t *m_ImageBuffer { nullptr };
    FITSImage::wcs_point *searchPosition { nullptr };
    ImageScale *searchScale{ nullptr };

}Image;

class StellarBatchSolver : public QMainWindow
{
    Q_OBJECT
public:
    explicit StellarBatchSolver(QString outputDir, QStringList imgFiles, int index);

public slots:

    void addImages();
    void loadImage(int num);
    void removeSelectedImage();
    void removeImage(int index);
    void removeAllImages();
    void resetImages();

    void addIndexDirectory();
    void selectOutputDirectory();
    void logOutput(QString text);
    void displayImage();
    void clearLog();

    void startProcessing();
    void abortProcessing();

    void clearCurrentImageBuffer();
    void processImage(int num);
    void solveImage();
    void solverComplete();
    void extractImage();
    void extractorComplete();
    void finishProcessing();
    void saveImage();
    void saveStarList();
    void processNextImage();

private:

    bool selectOutputDirectoryByParam(QString destDir);
    bool addImagesByParam(QStringList fileURLs);

private:
    Ui::StellarBatchSolver *ui;
    StellarSolver stellarSolver;
    QList<Image> images;
    int currentRow = -1;

    QStringList indexFileDirectories = StellarSolver::getDefaultIndexFolderPaths();
    QString outputDirectory;
    QString dirPath = QDir::homePath();

    bool aborted = false;
    Image *currentImage = nullptr;
    int currentImageNum = -1;
    int currentProgress = 0;
    bool solvingBlind = false;


signals:

};

#endif // STELLARBATCHSOLVER_H
