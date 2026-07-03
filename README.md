# ExpressLRS-ESP32-Bootloader

This project builds only `bootloader.bin` for the ExpressLRS ESP32 bootloader under `bootloader_components/main`.

## Supported targets

- ESP32
- ESP32-C3
- ESP32-S3

## Project layout

- `bootloader_components/main/bootloader_start.c` - copied bootloader entrypoint
- `bootloader_components/main/ld/` - target-specific bootloader linker scripts
- `.github/workflows/build.yml` - GitHub Actions matrix build for all supported targets

## Build locally in CLion

### Option 1: use CLion's terminal

This is the shortest path.

1. Install ESP-IDF `v5.4` and its tools.
2. Open `ExpressLRS-ESP32-Bootloader` in CLion.
3. Open **View > Tool Windows > Terminal**.
4. Source the ESP-IDF environment in that terminal:

   ```bash
   . /path/to/esp-idf/export.sh
   ```

5. Pick a target and build the bootloader:

   ```bash
   idf.py set-target esp32
   idf.py bootloader_nodigest
   ```

   Replace `esp32` with `esp32c3` or `esp32s3` as needed.

   This target rebuilds `build/bootloader/bootloader.bin` with `elf2image --dont-append-digest`.

Useful output files:

- `build/bootloader/bootloader.bin`
- `build/partition_table/partition-table.bin`

### Option 2: use CLion's ESP-IDF/CMake integration

1. Open `ExpressLRS-ESP32-Bootloader` in CLion.
2. Go to **Settings > Build, Execution, Deployment > Toolchain**.
3. Add the ESP-IDF environment from your `export.sh` file.
4. Reload the project. If needed, run **Tools > CMake > Reset Cache and Reload Project**.
5. Build the `bootloader_nodigest` target from CLion.

The bootloader artifact is written to `build/bootloader/bootloader.bin` without the appended image digest.

## Command-line build

Outside CLion, the same build works from a shell with ESP-IDF exported:

```bash
idf.py set-target esp32
idf.py bootloader_nodigest
```
