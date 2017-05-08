#include <gtest/gtest.h>

#include <QEventLoop>

#include "global/ServiceLocator.h"
#include "global/GlobalFactory.h"
#include "global/NumberGenerator.h"
#include "model/BuilderFacade.h"
#include "model/ModelSettings.h"
#include "model/SimulationController.h"
#include "model/context/SimulationContext.h"
#include "model/context/SimulationParameters.h"
#include "model/context/UnitGrid.h"
#include "model/context/Unit.h"
#include "model/context/UnitContext.h"
#include "model/context/MapCompartment.h"
#include "model/context/_impl/UnitThreadControllerImpl.h"
#include "model/context/_impl/UnitThread.h"
#include "model/AccessPorts/SimulationAccess.h"

#include "tests/Predicates.h"

class MultithreadingTest : public ::testing::Test
{
public:
	MultithreadingTest();
	~MultithreadingTest();

protected:
	SimulationController* _controller = nullptr;
	SimulationContext* _context = nullptr;
	SimulationParameters* _parameters = nullptr;
	UnitThreadControllerImpl* _threadController = nullptr;
	NumberGenerator* _numberGen = nullptr;
	IntVector2D _gridSize{ 6, 6 };
	IntVector2D _universeSize{ 600, 300 };
	IntVector2D _compartmentSize;
};

MultithreadingTest::MultithreadingTest()
{
	BuilderFacade* facade = ServiceLocator::getInstance().getService<BuilderFacade>();
	GlobalFactory* factory = ServiceLocator::getInstance().getService<GlobalFactory>();
	auto metric = facade->buildSpaceMetric(_universeSize);
	auto symbols = facade->buildDefaultSymbolTable();
	_parameters = facade->buildDefaultSimulationParameters();
	_context = static_cast<SimulationContext*>(facade->buildSimulationContext(4, _gridSize, metric, symbols, _parameters));
	_controller = facade->buildSimulationController(_context);
	_threadController = static_cast<UnitThreadControllerImpl*>(_context->getUnitThreadController());
	_numberGen = factory->buildRandomNumberGenerator();
	_numberGen->init(123123, 0);
}

MultithreadingTest::~MultithreadingTest()
{
	delete _controller;
	delete _numberGen;
}

TEST_F(MultithreadingTest, testThreads)
{
	QEventLoop pause;
	_controller->connect(_controller, &SimulationController::timestepCalculated, &pause, &QEventLoop::quit);
	_controller->calculateSingleTimestep();
	pause.exec();

	for (auto const& threadAndCalcSignal : _threadController->_threadsAndCalcSignals) {
		ASSERT_TRUE(threadAndCalcSignal.thr->isFinished()) << "One thread is not finished.";
	}
}


TEST_F(MultithreadingTest, testOneCellMovement)
{
	BuilderFacade* facade = ServiceLocator::getInstance().getService<BuilderFacade>();
	auto access = facade->buildSimulationAccess(_context);

	_parameters->radiationProb = 0.0;

	DataDescription desc;
	desc.addCellCluster(CellClusterDescription().setPos({ 100, 50 }).setVel({ 1.0, 0.5 })
		.addCell(CellDescription().setEnergy(_parameters->cellCreationEnergy)));
	access->updateData(desc);

	QEventLoop pause;
	int timesteps = 0;
	_controller->connect(_controller, &SimulationController::timestepCalculated, [&]() {
		if (++timesteps == 300) {
			_controller->setRun(false);
			pause.quit();
		}
	});
	_controller->setRun(true);
	pause.exec();
	access->requireData({ {0, 0}, _universeSize });
	auto const& data = access->retrieveData();

	ASSERT_EQ(1, data.clusters.size()) << "Wrong number of clusters.";
}


TEST_F(MultithreadingTest, testManyCellsMovement)
{
	BuilderFacade* facade = ServiceLocator::getInstance().getService<BuilderFacade>();
	auto access = facade->buildSimulationAccess(_context);
	DataDescription desc;
	for (int i = 0; i < 10000; ++i) {
		desc.addCellCluster(CellClusterDescription().setPos(QVector2D( _numberGen->getRandomInt(_universeSize.x), _numberGen->getRandomInt(_universeSize.y) ))
			.setVel(QVector2D(_numberGen->getRandomReal() - 0.5, _numberGen->getRandomReal() - 0.5 ))
			.addCell(CellDescription().setEnergy(_parameters->cellCreationEnergy).setMaxConnections(4)));
	}
	access->updateData(desc);

	QEventLoop pause;
	int timesteps = 0;
	_controller->connect(_controller, &SimulationController::timestepCalculated, [&]() {
		if (++timesteps == 200) {
			_controller->setRun(false);
			pause.quit();
		}
	});
	_controller->setRun(true);
	pause.exec();
}

