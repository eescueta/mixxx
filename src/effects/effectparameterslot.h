#ifndef EFFECTPARAMETERSLOT_H
#define EFFECTPARAMETERSLOT_H

#include <QObject>
#include <QVariant>
#include <QString>

#include "util.h"
#include "controlobject.h"
#include "effects/effect.h"
#include "effects/effectparameterslotbase.h"

class ControlObject;
class ControlPushButton;
class ControlEffectKnob;
class SoftTakeover;

class EffectParameterSlot;
typedef QSharedPointer<EffectParameterSlot> EffectParameterSlotPointer;

class EffectParameterSlot : public EffectParameterSlotBase {
    Q_OBJECT
  public:
    EffectParameterSlot(const unsigned int iRackNumber,
                        const unsigned int iChainNumber,
                        const unsigned int iSlotNumber,
                        const unsigned int iParameterNumber);
    virtual ~EffectParameterSlot();

    static QString formatItemPrefix(const unsigned int iParameterNumber) {
        return QString("parameter%1").arg(iParameterNumber + 1);
    }

    // Load the parameter of the given effect into this EffectParameterSlot
    void loadEffect(EffectPointer pEffect);

    double getValueParameter() const;

    void onChainParameterChanged(double parameter);

    // Syncs the Super button with the parameter, that the following
    // super button change will be passed to the effect parameter
    // used during test
    void syncSofttakeover();

  private slots:
    // Solely for handling control changes
    void slotParameterValueChanged(QVariant value);
    void slotLinkTypeChanged(double v);
    void slotLinkInverseChanged(double v);

  private:
    QString debugString() const {
        return QString("EffectParameterSlot(%1,%2)").arg(m_group).arg(m_iParameterNumber);
    }

    // Clear the currently loaded effect
    void clear();

    SoftTakeover* m_pSoftTakeover;

    // Control exposed to the rest of Mixxx
    ControlEffectKnob* m_pControlValue;
    ControlPushButton* m_pControlLinkType;
    ControlPushButton* m_pControlLinkInverse;

    DISALLOW_COPY_AND_ASSIGN(EffectParameterSlot);
};

#endif /* EFFECTPARAMETERSLOT_H */
