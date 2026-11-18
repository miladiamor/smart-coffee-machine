# Smart Coffee Machine – Control Software in C++/Qt

Simulated control software for a coin-operated coffee machine, written in C++ with Qt.
The machine's hardware (motors, valves, heaters, pumps, sensors, coin handling) is modelled as separate
software components, and every process runs as a **state machine** driven by a simulated clock.

Team project (4 students) – *Software Engineering* module, Berliner Hochschule für Technik (BHT), 2025.

## What it does

- Customer selects a drink, inserts coins and optionally adds sugar or milk foam
- The machine checks resources (water, beans, milk, sugar), takes payment and returns change
- The coordinator runs the brewing program: heating, pumping, brewing, frothing, output
- A Qt GUI shows the machine state (selection, brewing, done, "not enough" resources)

## Architecture

```
                 ┌────────────────────┐
   GUI (Qt) ───▶ │    Koordinator     │  central state machine
                 └─────────┬──────────┘
        ┌──────────────────┼────────────────────┐
        ▼                  ▼                    ▼
 Zahlungseinheit     Programmsteuerung      Ressourcen / Fuellstandsmessung
 (payment, coins)    (coffee programs)      (tank levels, resource checks)
        │                  │                    │
        ▼                  ▼                    ▼
 Coin sensor,        Brühgruppe, Pumpe,     Tankwaage, Temperatursensor,
 coin tubes,         Ventil, Heizregler,    inkrementalencoder
 coin ejector        Schäumer, Zuckerdispenser
```

- **30+ classes**, split into actuators, sensors and control logic
- **Tick-based simulation:** a `Clock` (QTimer) advances all state machines step by step; physical
  behaviour such as heating or pumping is modelled per tick (`simulation.h`)
- **Loose coupling:** components talk through interfaces and Qt signals/slots, with dependency
  injection, so each part can be replaced by a mock in tests

## My contribution

- **Koordinator** – the central state machine that coordinates payment, resources and brewing
- **Fuellstandsmessung / resource management** – tank fill-level sensing and resource checks
- **Display** – the interface between machine state and GUI
- Unit and integration tests for these components

## Tests

The project contains **8 unit-test suites and 3 integration-test suites** (QtTest), using mocks and
dependency injection:

| Type | Suites |
|------|--------|
| Unit tests | Koordinator, Fuellstandsmessung, Display, Heizregler, Motorsteuerung, Zahlungseinheit, Brühgruppe, Programmsteuerung |
| Integration tests | Koordinator, Programmsteuerung + Brühgruppe, whole system |

## Build and run

Requirements: Qt 5 or 6 with Qt Creator (qmake).

1. Open `main_project/main_project.pro` in Qt Creator – it builds the app and all test projects
2. Run the `app` target to start the simulation with the GUI
3. Run any `unittest_*` or `integrationstest_*` target to execute the tests

## Project structure

```
app/                     application (include/, src/, GUI, images)
main_project/            Qt "subdirs" project that builds everything
unittest_*/              one unit-test project per component
integrationstest_*/      integration-test projects
```

*Class and file names are in German (e.g. Koordinator = coordinator, Fuellstandsmessung = fill-level
measurement, Zahlungseinheit = payment unit), following the module's specification.*
