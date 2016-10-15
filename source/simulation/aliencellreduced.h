#ifndef ALIENCELLREDUCED
#define ALIENCELLREDUCED

#include "entities/aliencell.h"

#include <QVector3D>
#include <QString>

struct AlienCellReduced {

    AlienCellReduced ();
    AlienCellReduced (AlienCell* cell);
    ~AlienCellReduced ();

    void copyCellProperties (const AlienCellReduced& otherCell);    //copy internal cell data except computer and token data
    void copyClusterProperties (const AlienCellReduced& otherCell); //copy internal cluster data

    //cell properties
    int numCells;
    QVector3D clusterPos;
    QVector3D clusterVel;
    qreal clusterAngle;
    qreal clusterAngVel;
    QVector3D cellPos;
    qreal cellEnergy;
    int cellNumCon;
    int cellMaxCon;
    bool cellAllowToken;
    int cellTokenAccessNum;
    QString cellFunctionName;

    //computer data
    QVector< quint8 > computerMemory;
    QString computerCode;

    //token data
    QList< qreal > tokenEnergies;
    QList< QVector< quint8 > > tokenData;
};

#endif // ALIENCELLREDUCED
