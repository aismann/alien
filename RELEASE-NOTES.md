# Release notes

## [2.4.7] - 2021-04-14
### Changed
- error messages improved (call stack and bad alloc message)

## [2.4.6] - 2021-04-11
### Changed
- created cell have maximum bonds corresponding to simulation parameters

## [2.4.5] - 2021-04-08
### Fixed
- fixed exception on closing
- negative energies prevented

## [2.4.4] - 2021-04-04
### Fixed
- fixed crash when minimum hardware requirements are not met

## [2.4.3] - 2021-04-02
### Added
- new simulation parameter "offspring token suppress memory copy" (default=false)

### Fixed
- font in metadata tab from visual editor corrected

## [2.4.2] - 2021-03-24
### Changed
- selected cells and particles have lighter colors and smaller sizes in the editor
- border colors of cells and particles darkened
- unused simulation parameter "cluster properties -> max size" removed

## [2.4.1] - 2021-03-17
### Fixed
- fix performance bug when using glow effect

## [2.4.0] - 2021-03-05
### Added
- disc-shaped structures can be created
- selections can be colored

### Changed
- simulation parameters and symbol maps are saved in JSON format
- saved simulations are divided into 4 files: *.sim, *.settings.json, *.parameters.json and *.symbols.json

### Fixed
- second scrollbar in token editor avoided

## [2.3.0] - 2021-02-21
### Added
- infobar, which displays general information, monitor information and logging protocol
- show bug report dialog after crash that allows to send reports to a server

### Changed
- using standard font in dialogs and most widgets
- requirements of the examples lowered

### Fixed
- fix runtime problems for cells with constructor function

## [2.2.2] - 2021-02-10
### Changed
- upgrade to CUDA 11.2, Qt 6.0.1, boost 1.75.0 and VS 2019
- parallel console window is not opened
- examples renamed

### Fixed
- timeout problem during simulation run
- fix crash when monitor is open and simulation or general settings are changed 
- fix crash after inserting collection

## [2.2.1] - 2021-02-05
### Fixed
- fixed crash at display resolutions higher than Full HD

## [2.2.0] - 2021-02-03
### Added
- vector graphic view mode is active from zoom level 4 onwards
- startup screen shows version
- validation of values in "General settings" and "New simulation" dialog
- examples (simulation and collections)

### Changed
- info banner shows rendering mode
- "Computation settings" dialog restructured and renamed to "General settings"
- startup simulation changed

### Removed
- experimental feature "Web access" disabled (will be enabled when finished)

### Fixed
- showing messages in case of CUDA errors instead of immediate termination
- fix typos

## [2.1.0] - 2021-01-17
### Added
- usability: showing first steps window after startup
- allow moving objects with the mouse pointer
- ability to connect to a server and send simulation real-time data (still experimental)
- automatic switching between editor and pixel view depending on zoom level
- new examples

### Changed
- nicer and larger toolbar icons
- new logo
- disable editor for low zoom levels

### Fixed
- fix empty simulation after "step backward" or "restore snapshot"
- fix center scroll position after startup


