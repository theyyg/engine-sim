#ifndef ATG_ENGINE_SIM_COMBUSTION_CHAMBER_H
#define ATG_ENGINE_SIM_COMBUSTION_CHAMBER_H

#include "scs.h"

#include "piston.h"
#include "cylinder_bank.h"
#include "gas_system.h"
#include "cylinder_head.h"
#include "units.h"

class CombustionChamber : public atg_scs::ForceGenerator {
    public:
        struct FlameEvent {
            double lit_n;
            double total_n;
            double percentageLit;

            double lastVolume;
            double travel_x;
            double travel_y;
        };

        struct FrictionModelParams {
            double frictionCoeff = 0.06;
            double breakawayFriction = units::force(50, units::N);
            double breakawayFrictionVelocity = units::distance(0.1, units::m);
            double viscousFrictionCoefficient = units::force(20, units::N);
        };

    public:
        CombustionChamber();
        virtual ~CombustionChamber();

        void initialize(double p0, double t0);
        virtual void apply(atg_scs::SystemState *system);
        double getFrictionForce() const;

        Piston *m_piston;
        CylinderBank *m_bank;
        CylinderHead *m_head;

        double volume() const;

        void ignite();
        void update(double dt);

        double m_blowbyK;
        double m_crankcasePressure;
        double m_manifoldPressure;

        Function *m_totalPropagationToTurbulence;
        Function *m_turbulentFlameSpeed;
        GasSystem m_system;
        FlameEvent m_flameEvent;
        bool m_lit;

        FrictionModelParams m_frictionModel;

        double m_peakTemperature;
        double m_nBurntFuel;
        double m_turbulence;

        double m_exhaustFlow;

    protected:
        double calculateFrictionForce(double v) const;
};

#endif /* ATG_ENGINE_SIM_COMBUSTION_CHAMBER_H */