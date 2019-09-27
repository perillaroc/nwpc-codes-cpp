# nwpc-codes-cpp

A GRIB2 decoder for GRIB2 data produced by NWPC's GRAPES model.

## Building

Use CMake to build from source code.

The following libraries are required:

- [CLI11](https://github.com/CLIUtils/CLI11)
- [fmt](https://github.com/fmtlib/fmt)
- [GSL](https://github.com/microsoft/GSL)
- [OpenJPEG](https://github.com/uclouvain/openjpeg)

**[vcpkg](https://github.com/microsoft/vcpkg)** is recommended to use to install above libraries.

`nwpc-codes-cpp` use definition files from **[eccodes](https://github.com/ecmwf/eccodes)**. 
Please set `ECCODES_DEFINITION_PATH` before running any tools.

## Getting Started

`nwpc-codes-cpp` has several tools to handle GRIB2 data.

### nwpc_codes_ls

`nwpc_codes_ls` shows all messages in a GRIB2 file.

```bash
nwpc_codes_ls some/path/to/grib2/file
```

Results may be like:

```
/g1/COMMONDATA/OPER/NWPC/GRAPES_GFS_GMF/Prod-grib/2019082821/ORIG/gmf.gra.2019082900003.grb2
1 | 0 | 2019-08-29 | 00:00 | fc | regular_ll | Moisture | Convective precipitation | surface | 0 | 0-3 | grid_jpeg
2 | 696727 | 2019-08-29 | 00:00 | fc | regular_ll | Moisture | Large scale precipitation (non-convective) | surface | 0 | 0-3 | grid_jpeg
3 | 1600762 | 2019-08-29 | 00:00 | fc | regular_ll | Moisture | Total precipitation | surface | 0 | 0-3 | grid_jpeg
4 | 2869835 | 2019-08-29 | 00:00 | fc | regular_ll | Moisture | Total snowfall | surface | 0 | 0-3 | grid_jpeg
5 | 3447148 | 2019-08-29 | 00:00 | fc | regular_ll | Temperature | Temperature | surface | 0 | 3 | grid_jpeg
...
833 | 415505220 | 2019-08-29 | 00:00 | fc | regular_ll | Moisture | 238 | surface | 0 | 3 | grid_jpeg
834 | 415745624 | 2019-08-29 | 00:00 | fc | regular_ll | Short-wave Radiation | 228 | surface | 0 | 3 | grid_jpeg
835 | 417112449 | 2019-08-29 | 00:00 | fc | regular_ll | Short-wave Radiation | 227 | surface | 0 | 3 | grid_jpeg
835 grib2 messages in /g1/COMMONDATA/OPER/NWPC/GRAPES_GFS_GMF/Prod-grib/2019082821/ORIG/gmf.gra.2019082900003.grb2
```

### nwpc_codes_dump

`nwpc_codes_dump` dumps all messages in a GRIB2 file.

```bash
nwpc_codes_dump some/path/to/grib2/file
```

Results may be like:

```
/g1/COMMONDATA/OPER/NWPC/GRAPES_GFS_GMF/Prod-grib/2019091321/ORIG/gmf.gra.2019091400003.grb2
===============   MESSAGE 1 ( length=616314 )    ================
1-4       identifier = GRIB
5-6       reserved = 65535
7         discipline = 0 [Meteorological products (0.0) ]
8         editionNumber = 2
9-16      totalLength = 616314
======================   SECTION_1 ( length=21 )    ======================
1-4       section1Length = 21
5         numberOfSection = 1
6-7       centre = 38
8-9       subCentre = 0
10        tablesVersion = 4 [4 (1.0) ]
11        localTablesVersion = 1 [1 (1.1) ]
12        significanceOfReferenceTime = 1 [ Start of forecast (1.2) ]
13-14     year = 2019
15        month = 9
16        day = 14
17        hour = 0
18        minute = 0
19        second = 0
20        productionStatusOfProcessedData = 0 [ Operational products (1.3) ]
21        typeOfProcessedData = 1 [fc (1.4) ]
======================   SECTION_3 ( length=72 )    ======================
1-4       section3Length = 72
5         numberOfSection = 3
6         sourceOfGridDefinition = 0 [Specified in Code table 3.1 (3.0) ]
7-10      numberOfDataPoints = 1036800
11        numberOfOctectsForNumberOfPoints = 0
12        interpretationOfNumberOfPoints = 0 [ There is no appended list (3.11) ]
13-14     gridDefinitionTemplateNumber = 0 [Latitude/longitude (3.1) ]
15        shapeOfEarth = 6 [ Earth assumed spherical with radius of 6,371,229.0 m (3.2) ]
16        scaleFactorOfRadiusOfSphericalEarth = 0
17-20     scaledValueOfRadiusOfSphericalEarth = 0
21        scaleFactorOfEarthMajorAxis = 0
22-25     scaledValueOfEarthMajorAxis = 0
26        scaleFactorOfEarthMinorAxis = 0
27-30     scaledValueOfEarthMinorAxis = 0
31-34     ni = 1440
35-38     nj = 720
39-42     basicAngleOfTheInitialProductionDomain = 0
43-46     subdivisionsOfBasicAngle = 0
47-50     latitudeOfFirstGridPoint = 89875000
51-54     longitudeOfFirstGridPoint = 0
55        resolutionAndComponentFlags = 48
56-59     latitudeOfLastGridPoint = -89875000
60-63     longitudeOfLastGridPoint = 359750000
64-67     iDirectionIncrement = 250000
68-71     jDirectionIncrement = 250000
72        scanningMode = 0
======================   SECTION_4 ( length=58 )    ======================
1-4       section4Length = 58
5         numberOfSection = 4
6-7       nv = 0
8-9       productDefinitionTemplateNumber = 8 [Average, accumulation, extreme values or other statistically processed values at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval (4.0) ]
10        parameterCategory = 1 [Moisture (4.1.0) ]
11        parameterNumber = 10 [Convective precipitation (4.2.0.1) ]
12        typeOfGeneratingProcess = 2 [ Forecast (4.3) ]
13        backgroundProcess = 0
14        generatingProcessIdentifier = 15
15-16     hoursAfterDataCutoff = 0
17        minutesAfterDataCutoff = 0
18        indicatorOfUnitOfTimeRange = 1 [h (4.4) ]
19-22     forecastTime = 0
23        typeOfFirstFixedSurface = 1 [sfc (4.5) ]
24        scaleFactorOfFirstFixedSurface = -1
25-28     scaledValueOfFirstFixedSurface = 4294967295
29        typeOfSecondFixedSurface = 255 [Missing (4.5) ]
30        scaleFactorOfSecondFixedSurface = -1
31-34     scaledValueOfSecondFixedSurface = 4294967295
35-36     yearOfEndOfOverallTimeInterval = 2019
37        monthOfEndOfOverallTimeInterval = 9
38        dayOfEndOfOverallTimeInterval = 14
39        hourOfEndOfOverallTimeInterval = 3
40        minuteOfEndOfOverallTimeInterval = 0
41        secondOfEndOfOverallTimeInterval = 0
42        numberOfTimeRange = 1
43-46     numberOfMissingInStatisticalProcess = 0
47        typeOfStatisticalProcessing = 1 [accum (4.10) ]
48        typeOfTimeIncrement = 2 [ Successive times processed have same start time of forecast, forecast time is incremented (4.11) ]
49        indicatorOfUnitForTimeRange = 1 [h (4.4) ]
50-53     lengthOfTimeRange = 3
54        indicatorOfUnitForTimeIncrement = 255 [ Missing (4.4) ]
55-58     timeIncrement = 0
======================   SECTION_5 ( length=23 )    ======================
1-4       section5Length = 23
5         numberOfSection = 5
6-9       numberOfValues = 1036800
10-11     dataRepresentationTemplateNumber = 40 [JPEG2000 Packing (5.0) ]
12-15     referenceValue = 0
16-17     binaryScaleFactor = 2
18-19     decimalScaleFactor = 6
20        bitsPerValue = 24
21        typeOfOriginalFieldValues = 0 [ Floating point (5.1) ]
22        typeOfCompressionUsed = 0 [Lossless (5.40) ]
23        targetCompressionRatio = 255
======================   SECTION_6 ( length=6 )    ======================
1-4       section6Length = 6
5         numberOfSection = 6
6         bitMapIndicator = 255
======================   SECTION_7 ( length=616114 )    ======================
1-4       section7Length = 616114
5         numberOfSection = 7
6-616114  dataValues = (1036800, 616109)
======================   SECTION_8 ( length=4 )    ======================
1-4       7777 = 7777

```

## Examples

All examples are under `example` directory.

## Tested data

GRIB2 data created by the following operation systems is tested:

- GRAPES_GFS_GMA
- GRAPES_GFS_GDA
- GRAPES_MESO_10KM
- GRAPES_MESO_3KM
- GRAPES_TYM
- GRAPES_MEPS
- GRAPES_REPS

## License

`nwpc-codes-cpp` is licensed under the [MIT License](./LICENSE.md).