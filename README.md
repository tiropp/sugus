# sugus
This is a sandbox for implementing an OpcUA client on top of the OpcUA library provided by the [OpcUA foundation](https://github.com/OPCFoundation)

## Build
The build system is based on cmake. Use the OPCUA_INCLUDE_DIR and the OPCUA_LIBRARY_DIR cmake variables to point to the [OpcUA foundation UA-AnsiC](https://github.com/OPCFoundation/UA-AnsiC) header include and library directories.

### Example

``` shell
mkdir -p _build/debug
cd _build/debug
cmake ../../ \
      -DCMAKE_BUILD_TYPE=Debug \
      -DOPCUA_INCLUDE_DIR=${opc_dir}/Stack \
      -DOPCUA_LIBRARY_DIR=${opc_dir}/lib/linux/unknown/gcc/debug
```
with opc_dir being UA-AnsiC top level directory.
