# nwpc-codes-cpp

A GRIB2 decoder for GRIB2 data produced by NWPC's GRAPES model.

## Building

Use CMake to build from source code.

**OpenJPEG** is required to decode data values. 

`nwpc-codes-cpp` use definition files from **eccodes**. 
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