#include <gtest/gtest.h>

#include <QEventLoop>

#include "Base/ServiceLocator.h"
#include "Base/GlobalFactory.h"
#include "Base/NumberGenerator.h"
#include "ModelInterface/ModelBuilderFacade.h"
#include "ModelInterface/Settings.h"
#include "ModelInterface/SimulationController.h"
#include "ModelCpu/SimulationContextImpl.h"
#include "ModelInterface/SimulationParameters.h"
#include "ModelCpu/UnitGrid.h"
#include "ModelCpu/Unit.h"
#include "ModelCpu/UnitContext.h"
#include "ModelCpu/MapCompartment.h"
#include "ModelCpu/UnitThreadControllerImpl.h"
#include "ModelCpu/UnitThread.h"
#include "ModelInterface/SimulationAccess.h"

#include "tests/Predicates.h"

#include "IntegrationTestFramework.h"

class Benchmark
	: public IntegrationTestFramework
{
public:
	Benchmark();

protected:
	void createTestData(SimulationAccess* access);
};

Benchmark::Benchmark()
	: IntegrationTestFramework({ 12 * 33 * 3, 12 * 17 * 3 })
{
}

void Benchmark::createTestData(SimulationAccess * access)
{
	DataChangeDescription desc;
	for (int i = 0; i < 20000 * 9; ++i) {
		desc.addNewParticle(ParticleChangeDescription().setPos(QVector2D(_numberGen->getRandomInt(_universeSize.x), _numberGen->getRandomInt(_universeSize.y)))
			.setVel(QVector2D(_numberGen->getRandomReal()*2.0 - 1.0, _numberGen->getRandomReal()*2.0 - 1.0))
			.setEnergy(50));
	}
	access->updateData(desc);
}

TEST_F(Benchmark, benchmarkOneThreadWithOneUnit)
{
	ModelBuilderFacade* facade = ServiceLocator::getInstance().getService<ModelBuilderFacade>();
	auto controller = facade->buildSimulationController(1, { 1, 1 }, _universeSize, _symbols, _parameters);
	auto access = facade->buildSimulationAccess();
	access->init(controller->getContext());

	createTestData(access);
	runSimulation(20, controller);

	delete access;
	delete controller;

	EXPECT_TRUE(true);
}

TEST_F(Benchmark, benchmarkOneThreadWithManyUnits)
{
	ModelBuilderFacade* facade = ServiceLocator::getInstance().getService<ModelBuilderFacade>();
	auto controller = facade->buildSimulationController(1, { 12, 6 }, _universeSize, _symbols, _parameters);
	auto access = facade->buildSimulationAccess();
	access->init(controller->getContext());

	createTestData(access);
	runSimulation(20, controller);

	delete access;
	delete controller;

	EXPECT_TRUE(true);
}

TEST_F(Benchmark, benchmarkFourThread)
{
	ModelBuilderFacade* facade = ServiceLocator::getInstance().getService<ModelBuilderFacade>();
	auto controller = facade->buildSimulationController(4, { 12, 6 }, _universeSize, _symbols, _parameters);
	auto access = facade->buildSimulationAccess();
	access->init(controller->getContext());

	createTestData(access);
	runSimulation(20, controller);

	delete access;
	delete controller;

	EXPECT_TRUE(true);
}

TEST_F(Benchmark, benchmarkEightThread)
{
	ModelBuilderFacade* facade = ServiceLocator::getInstance().getService<ModelBuilderFacade>();
	auto controller = facade->buildSimulationController(8, { 12, 6 }, _universeSize, _symbols, _parameters);
	auto access = facade->buildSimulationAccess();
	access->init(controller->getContext());

	createTestData(access);
	runSimulation(20, controller);

	delete access;
	delete controller;

	EXPECT_TRUE(true);
}
